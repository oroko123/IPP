#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>

struct Request
{
    int requestNumber;
    /*Identifies request: 0 - NEW_DISEASE_ENTER_DESCRIPTION,
                          1 - NEW_DISEASE_COPY_DESCRIPTION,
                          2 - CHANGE_DESCRIPTION,
                          3 - PRINT_DESCRIPTION,
                          4 - DELETE_PATIENT_DATA.         */
    char* name1;
    char* name2;
    char* disease;
    int diseaseNumber;
};

bool canScan();

struct Request scanRequest (struct Request req);

void clearRequest(struct Request req);

#endif
