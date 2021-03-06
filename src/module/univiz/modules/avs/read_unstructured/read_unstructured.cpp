/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

/* mod_gen Version 1                                                     */
/* Module Name: "read unstructured" (Output) (Subroutine)              */
/* Author: Ronald Peikert                                                */
/* Date Created: Thu Jun  7 11:53:58 2001                                */
/*                                                                       */
/* This file is automatically generated by the Module Generator (mod_gen)*/
/* Please do not modify or move the contents of this comment block as    */
/* mod_gen needs it in order to read module sources back in.             */
/*                                                                       */
/* input 0 "ucd" ucd REQUIRED                                            */
/* param 0 "status" textblock " " "" ":"                          */
/* End of Module Description Comments                                    */

#include <stdio.h>
#include <avs/avs.h>
#include <avs/port.h>
#include <avs/ucd_defs.h>

/* ----> START OF USER-SUPPLIED CODE SECTION #1 (INCLUDE FILES, GLOBAL VARIABLES)*/

using namespace std;

#include <math.h>
#include "vector"
#include "algorithm"
#include "values.h"

#include "avs_ext.h"
#include "unstructured.h"
#include "unisys.h"

/* <---- END OF USER-SUPPLIED CODE SECTION #1                            */

/* *****************************************/
/*  Module Description                     */
/* *****************************************/
int read_unstructured_desc()
{

    int in_port, out_port, param, iresult;
    extern int read_unstructured_compute(UCD_structure * *ucd,
                                         char *file_name);

    AVSset_module_name("read unstructured", MODULE_RENDER);

    /* Input Port Specifications               */

    /* Output Port Specifications              */
    out_port = AVScreate_output_port("ucd", "ucd");

    /* Parameter Specifications                */
    param = AVSadd_parameter("file name", "string", "", "", "");
    AVSconnect_widget(param, "browser");

    AVSset_compute_proc((int (*)())read_unstructured_compute);

    /* ----> START OF USER-SUPPLIED CODE SECTION #2 (ADDITIONAL SPECIFICATION INFO)*/
    /* <---- END OF USER-SUPPLIED CODE SECTION #2                            */
    return (1);
}

/* *****************************************/
/* Module Compute Routine                  */
/* *****************************************/
int read_unstructured_compute(UCD_structure **ucd,
                              char *file_name)
{

    /* ----> START OF USER-SUPPLIED CODE SECTION #3 (COMPUTE ROUTINE BODY)   */

    Unstructured *unst = new Unstructured(file_name);
    if (!unst)
    {
        AVSerror("could not read Unstructured file: %s\n", file_name);
        return 0;
    }

    if (*ucd)
        UCDstructure_free(*ucd);
    // ### check
    *ucd = (UCD_structure *)UCDstructure_alloc(unst->name,
                                               0, // ### data_veclen
                                               0, // ### name flag
                                               unst->nCells,
                                               unst->getNodeListSize(), // cell tsize
                                               0, // ### cell veclen
                                               unst->nNodes,
                                               0, //### node_csize,
                                               unst->getNodeVecLenTot(),
                                               0 // ### util flag
                                               );

    // node components
    {
        // ### 256 char max
        int *nodeComponents = new int[unst->getNodeCompNb()];
        char *node_component_labels = new char[unst->getNodeCompNb() * 257];
        for (int c = 0; c < unst->getNodeCompNb(); c++)
        {
            nodeComponents[c] = unst->getNodeCompVecLen(c);

            if (c > 0)
                strcat(node_component_labels, ".");
            strcat(node_component_labels, unst->getNodeCompLabel(c));
        }
        UCDstructure_set_node_components(*ucd, nodeComponents, unst->getNodeCompNb());
        UCDstructure_set_node_labels(*ucd, node_component_labels, ".");

        delete[] nodeComponents;
        delete[] node_component_labels;
    }

    // coordinates
    for (int n = 0; n < unst->nNodes; n++)
    {
        vec3 p;
        unst->getCoords(n, p);
        (*ucd)->x[n] = p[0];
        (*ucd)->y[n] = p[1];
        (*ucd)->z[n] = p[2];
    }

    // data
    {
        float *nodeDataPtr = (*ucd)->node_data;
        for (int c = 0; c < unst->getNodeCompNb(); c++)
        {
            int veclen = unst->getNodeCompVecLen(c);
            if (veclen == 1)
            {
                for (int n = 0; n < unst->nNodes; n++)
                {
                    nodeDataPtr[n] = unst->getScalar(n, c);
                }
            }
            else
            {
                // #### assuming vec3! TODO
                for (int n = 0; n < unst->nNodes; n++)
                {
                    vec3 v;
                    unst->getVector3(n, c, v);
                    nodeDataPtr[n * 3 + 0] = v[0];
                    nodeDataPtr[n * 3 + 1] = v[1];
                    nodeDataPtr[n * 3 + 2] = v[2];
                }
            }
            nodeDataPtr += veclen * unst->nNodes;
        }
    }

    // set cell info
    {
        int idx = 0;
        for (int c = 0; c < unst->nCells; c++)
        {
            int *nodeList = unst->getCellNodesAVS(c);
            UCDcell_set_information(*ucd, c, "", "", 0, unst->getCellType(c), 0, nodeList);
            idx += nVertices[unst->getCellType(c)];
        }
    }

    // Set extent
    {
        float minExt[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
        float maxExt[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
        for (int n = 0; n < unst->nNodes; n++)
        {
            float x, y, z;
            x = (*ucd)->x[n];
            y = (*ucd)->y[n];
            z = (*ucd)->z[n];

            if (x < minExt[0])
                minExt[0] = x;
            if (y < minExt[1])
                minExt[1] = y;
            if (z < minExt[2])
                minExt[2] = z;

            if (x > maxExt[0])
                maxExt[0] = x;
            if (y > maxExt[1])
                maxExt[1] = y;
            if (z > maxExt[2])
                maxExt[2] = z;
        }
        UCDstructure_set_extent(*ucd, minExt, maxExt);
    }

    delete unst;

    /* <---- END OF USER-SUPPLIED CODE SECTION #3              */
    return (1);
}

/* ***********************************************************************/
/* Initialization for modules contained in this file.                    */
/* ***********************************************************************/
static int((*mod_list[])()) = {
    read_unstructured_desc
};
#define NMODS (sizeof(mod_list) / sizeof(char *))

#ifdef __cplusplus
extern "C" // Add for C++
    {
#endif

void AVSinit_modules()
{ // Modify for C++
    AVSinit_from_module_list(mod_list, NMODS);
}

#ifdef __cplusplus
} // Add for C++
#endif

/* ----> START OF USER-SUPPLIED CODE SECTION #4 (SUBROUTINES, FUNCTIONS, UTILITY ROUTINES)*/

/* <---- END OF USER-SUPPLIED CODE SECTION #4                            */
