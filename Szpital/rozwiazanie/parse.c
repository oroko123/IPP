#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"

const char *tab[5]=
{
    "NEW_DISEASE_ENTER_DESCRIPTION",
    "NEW_DISEASE_COPY_DESCRIPTION",
    "CHANGE_DESCRIPTION",
    "PRINT_DESCRIPTION",
    "DELETE_PATIENT_DATA"
};

char scanedRequest[30];

bool canScan()
{
    char x;
    if (scanf(" %c", &x) != EOF)
    {
        ungetc(x, stdin);
        return true;
    }
    else
    {
        return false;
    }
}

struct Request scanRequest(struct Request req)
{
    scanf("%s", scanedRequest);
    scanf(" %s", req.name1);
    int i;
    for (i = 0; i < 5; i++)
    {
        if (strcmp(tab[i], scanedRequest) == 0)
        {
            req.requestNumber = i;
            switch (i)
            {
                case 0:
                    scanf(" %[^\n]s", req.disease);
                    break;
                case 1:
                    scanf(" %[^\n]s", req.name2);
                    break;
                case 2:
                    scanf(" %d", &req.diseaseNumber);
                    scanf(" %[^\n]s", req.disease);
                    break;
                case 3:
                    scanf(" %d", &req.diseaseNumber);
                    break;
                case 4:
                    break;
            }
        }
    }
    return req;
}

void clearRequest(struct Request req)
{
    free(req.disease);
    free(req.name1);
    free(req.name2);
}
