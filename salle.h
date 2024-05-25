#ifndef SALLE_H
#define SALLE_H

#define MAX_RANGEE 100
#define MAX_SIEGES_PAR_RANGEE 100
#define MAX_SALLES 10

typedef struct {
    char nom[50];
    int nombreRangees;
    int nombreSiegesParRangee;
    int rangeesCategorieA;
    int rangeesCategorieB;
    float prixCategorieA;
    float prixCategorieB;
    float prixCategorieC;
    int fosse; // 1 si oui, 0 sinon
    int sieges[MAX_RANGEE][MAX_SIEGES_PAR_RANGEE]; 
} Salle;

extern Salle salles[MAX_SALLES];
extern int nombreSalles;


void creerSalle();
void afficherEtatSalles();
void modifierSalle();
void afficherPlanSalle(Salle *salle);
void sauvegardeSalle();
Salle* findSalleByName(char *nom);

#endif // SALLE_H
