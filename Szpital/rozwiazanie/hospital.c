#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "structure.h"

int main(int argc, char **argv)
{
    bool DEBUG = 0;

    extern int descriptions;

    if (argc > 1)
    {
        if(argc == 2 && strcmp(argv[1], "-v") == 0)
        {
            DEBUG = 1;
        }
        else
        {
            printf("ERROR\n");
            return 1;
        }
    }

    struct Request req;

    req.disease = malloc (100000*sizeof(char));
    req.name1 = malloc (100000*sizeof(char));
    req.name2 = malloc (100000*sizeof(char));

    while (canScan())
    {
        req = scanRequest(req);

        bool isOK = realiseRequest(req);

        if (isOK)
        {
            if (req.requestNumber != 3)
            {
                printf("OK\n");
            }
        }
        else
        {
            printf("IGNORED\n");
        }

        if (DEBUG)
        {
            fprintf (stderr, "DESCRIPTIONS: %d\n", descriptions);
        }
    }

    clearRequest(req);
    clearStructure();

    return 0;
}
