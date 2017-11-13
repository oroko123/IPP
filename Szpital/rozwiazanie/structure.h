#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdbool.h>

struct Dis
{
   struct Dis *next;

   char* diseaseDescription;
   int* diseaseOccurancesCounter;
};

typedef struct Dis* Disease;

struct Pat
{
    struct Pat *next;

    int diseases;
    char* name;
    Disease lastDisease;
};

typedef struct Pat* Patient;

bool newDiseaseEnterDescription(char* name, char* disease);

bool newDiseaseCopyDescription(char* name1, char* name2);

bool changeDescription(char* name1, int diseaseNumber, char* disease);

bool printDescription(char* name, int diseaseNumber);

bool deletePatientData(char* name);

bool realiseRequest(struct Request com);

void clearStructure();

#endif
