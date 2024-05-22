#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "salle.h"
#include "utils.h"

Salle salles[MAX_SALLES];
int nombreSalles = 0;

void creerSalle() {
    if (nombreSalles >= MAX_SALLES) {
        printf("Nombre maximum de salles atteint.\n");
        return;
    }

    Salle *salle = &salles[nombreSalles];
    printf("Nom de la salle: ");
    scanf("%s", salle->nom);
    printf("Nombre de rangées: ");
    scanf("%d", &salle->nombreRangees);
    printf("Nombre de sièges par rangée: ");
    scanf("%d", &salle->nombreSiegesParRangee);
    printf("Nombre de rangées catégorie A: ");
    scanf("%d", &salle->rangeesCategorieA);
    printf("Nombre de rangées catégorie B: ");
    scanf("%d", &salle->rangeesCategorieB);

    salle->fosse = 0; // Par défaut, pas de fosse
    memset(salle->sieges, 0, sizeof(salle->sieges)); 
    nombreSalles++;
    printf("Salle créée avec succès.\n");
}

void afficherEtatSalles() {
    for (int i = 0; i < nombreSalles; i++) {
        Salle *salle = &salles[i];
        int siegesOccupes = 0, siegesTotal = salle->nombreRangees * salle->nombreSiegesParRangee;

        for (int r = 0; r < salle->nombreRangees; r++) {
            for (int s = 0; s < salle->nombreSiegesParRangee; s++) {
                if (salle->sieges[r][s] == 1) {
                    siegesOccupes++;
                }
            }
        }

        printf("Salle: %s\n", salle->nom);
        printf("Nombre total de sièges: %d\n", siegesTotal);
        printf("Nombre de sièges occupés: %d\n", siegesOccupes);
        printf("Ratio: %.2f%%\n\n", (float)siegesOccupes / siegesTotal * 100);
    }
}

void modifierSalle() {
    printf("Nom de la salle à modifier: ");
    char nomSalle[50];
    scanf("%s", nomSalle);

    Salle *salle = findSalleByName(nomSalle);

    if (salle == NULL) {
        printf("Salle non trouvée.\n");
        return;
    }

    printf("Nombre de rangées catégorie A: ");
    scanf("%d", &salle->rangeesCategorieA);
    printf("Nombre de rangées catégorie B: ");
    scanf("%d", &salle->rangeesCategorieB);
    printf("Le concert aura-t-il une fosse (1 pour oui, 0 pour non)?: ");
    scanf("%d", &salle->fosse);

    printf("Modification réussie.\n");
}

void afficherPlanSalle(Salle *salle) {
    for (int r = 0; r < salle->nombreRangees; r++) {
        for (int s = 0; s < salle->nombreSiegesParRangee; s++) {
            if (salle->sieges[r][s] == 0) {
                if (r < salle->rangeesCategorieA) {
                    printf(RED"0 " WHITE);
                } else if (r < salle->rangeesCategorieA + salle->rangeesCategorieB) {
                    printf(BLUE"0 " WHITE);
                } else {
                    printf("0 ");
                }
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
}

Salle* findSalleByName(char *nom) {
    for (int i = 0; i < nombreSalles; i++) {
        if (strcmp(salles[i].nom, nom) == 0) {
            return &salles[i];
        }
    }
    return NULL;
}
