/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef _STEP_FILE_H_
#define _STEP_FILE_H_

#define MAX_DELTA 500

class coStepFile
{

private:
    int skip, delta;
    int len_nb; //length of the start path
    int finished;
    int base_number;
    int file_index;
    char preffix[128], suffix[128];
    char base[128];
    bool singleFile;

public:
    // Member functions
    coStepFile(const char *);

    void get_nextpath(char **);
    void set_delta(int);
    void getDelta(int *);
    void set_skip_value(int);
    void get_skip_value(int *);
};
#endif
