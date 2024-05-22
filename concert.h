#ifndef CONCERT_H
#define CONCERT_H

#include "salle.h"

#define MAX_CONCERTS 10

typedef struct {
    char nom[50];
    Salle *salle;
    char heureFin[6];
    float prixCategorieA;
    float prixCategorieB;
    float prixCategorieC;
    int enCours; // 1 si le concert est en cours, 0 sinon
} Concert;

extern Concert concerts[MAX_CONCERTS];
extern int nombreConcerts;

void attribuerConcert();
void terminerConcert();
void afficherConcertsEnCours();
void reserverSieges();

#endif // CONCERT_H
