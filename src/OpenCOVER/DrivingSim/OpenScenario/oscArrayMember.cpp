/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#include <oscArrayMember.h>
#include <oscObjectBase.h>

using namespace OpenScenario;

oscArrayMember::oscArrayMember(): oscMember()
{
}

oscArrayMember::~oscArrayMember()
{
    for(std::vector<oscObjectBase *>::iterator it=values.begin();it != values.end(); it++)
    {
        delete *it;
    }
    values.clear();
}