#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "structure.h"

Patient patientsList = NULL;
int descriptions;

void deleteDisease(Disease disease)
{
    (*disease->diseaseOccurancesCounter)--;
    if ((*disease->diseaseOccurancesCounter) <= 0)
    {
        free(disease->diseaseDescription);
        free(disease->diseaseOccurancesCounter);

        descriptions--;
    }
}

void clearDiseaseHistory(Disease disease)
{
    if (disease->next != NULL)
    {
        clearDiseaseHistory(disease->next);
    }
    if (disease != NULL)
    {
        deleteDisease(disease);
        free(disease);
    }
}

Patient createPatient(char* name)
{
    Patient pat;

    pat = malloc(sizeof(struct Pat));
    pat->name = malloc(strlen(name)+1);

    strcpy(pat->name, name);
    pat->next = patientsList;
    pat->lastDisease = NULL;
    pat->diseases = 0;

    patientsList = pat;

    return pat;
}

Patient findPatient(char* name)
{

    Patient pointer = patientsList;

    while (pointer != NULL && strcmp(pointer->name, name) != 0)
    {
        pointer = pointer->next;
    }

    return pointer;
}

Disease findDisease(Patient pat, int DiseaseNumber)
{
    Disease pointer = pat->lastDisease;

    DiseaseNumber = pat->diseases - DiseaseNumber + 1;

    if (pointer != NULL)
    {
        while (pointer != NULL && DiseaseNumber > 1)
        {
            pointer = pointer->next;
            DiseaseNumber--;
        }
    }
    return pointer;
}

bool newDiseaseEnterDescription(char* name, char* disease)
{
    Patient pat = findPatient(name);
    if (pat == NULL)
    {
        pat = createPatient(name);
    }

    Disease newDisease = malloc(sizeof(struct Dis));
    newDisease->diseaseDescription = malloc(strlen(disease)+1);
    newDisease->diseaseOccurancesCounter = malloc(sizeof(int));

    strcpy(newDisease->diseaseDescription, disease);
    *newDisease->diseaseOccurancesCounter = 1;

    newDisease->next = pat->lastDisease;

    pat->lastDisease = newDisease;
    pat->diseases++;

    descriptions++;

    return true;
}

bool newDiseaseCopyDescription(char* name1, char* name2)
{
    Patient pat2 = findPatient(name2);
    if (pat2 == NULL || pat2->diseases == 0)
    {
        return false;
    }

    Patient pat1 = findPatient(name1);
    if (pat1 == NULL)
    {
        pat1 = createPatient(name1);
    }

    Disease newDisease = malloc(sizeof(struct Dis));

    newDisease->next = pat1->lastDisease;
    newDisease->diseaseDescription = pat2->lastDisease->diseaseDescription;
    newDisease->diseaseOccurancesCounter = pat2->lastDisease->diseaseOccurancesCounter;

    (*newDisease->diseaseOccurancesCounter)++;

    pat1->diseases++;
    pat1->lastDisease = newDisease;

    return true;
}

bool changeDescription(char* name, int diseaseNumber, char* disease)
{
    Patient pat = findPatient(name);
    if (pat == NULL || diseaseNumber > pat->diseases)
    {
        return false;
    }

    Disease oldDisease = findDisease(pat, diseaseNumber);
    deleteDisease(oldDisease);

    oldDisease->diseaseDescription = malloc(strlen(disease)+1);
    oldDisease->diseaseOccurancesCounter = malloc(sizeof(int));

    strcpy(oldDisease->diseaseDescription, disease);
    *oldDisease->diseaseOccurancesCounter = 1;

    descriptions++;

    return true;
}

bool printDescription(char* name, int diseaseNumber)
{
    Patient pat = findPatient(name);
    if (pat == NULL || diseaseNumber > pat->diseases)
    {
        return false;
    }

    Disease disease = findDisease(pat, diseaseNumber);

    printf("%s\n", (disease->diseaseDescription));

    return true;
}

bool deletePatientData(char* name)
{
    Patient pat = findPatient(name);
    if (pat == NULL)
    {
        return false;
    }

    if (pat->diseases > 0)
    {
        clearDiseaseHistory(pat->lastDisease);
        pat->lastDisease = NULL;
        pat->diseases = 0;
    }
    return true;
}

bool realiseRequest(struct Request req)
{
    switch (req.requestNumber)
    {
        case 0:
            return newDiseaseEnterDescription(req.name1, req.disease);
        case 1:
            return newDiseaseCopyDescription(req.name1, req.name2);
        case 2:
            return changeDescription(req.name1, req.diseaseNumber, req.disease);
        case 3:
            return printDescription(req.name1, req.diseaseNumber);
        case 4:
            return deletePatientData(req.name1);
        default:
            return true;
    }
}

void clearStructure()
{
    Patient pointer = patientsList;
    while (pointer != NULL)
    {
        if(pointer->lastDisease != NULL)
        {
            clearDiseaseHistory(pointer->lastDisease);
        }

        patientsList = pointer->next;

        free(pointer->name);
        free(pointer);

        pointer = patientsList;
    }
}
