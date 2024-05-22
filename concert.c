#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concert.h"
#include "salle.h"
#include "utils.h"

Concert concerts[MAX_CONCERTS];
int nombreConcerts = 0;

void attribuerConcert() {
    if (nombreConcerts >= MAX_CONCERTS) {
        printf("Nombre maximum de concerts atteint.\n");
        return;
    }

    Concert *concert = &concerts[nombreConcerts];
    printf("Nom du concert: ");
    scanf("%s", concert->nom);

    printf("Choisir une salle par nom: ");
    char nomSalle[50];
    scanf("%s", nomSalle);

    Salle *salle = findSalleByName(nomSalle);

    if (salle == NULL) {
        printf("Salle non trouvée.\n");
        return;
    }

    concert->salle = salle;

    printf("Le concert aura-t-il une fosse (1 pour oui, 0 pour non)?: ");
    scanf("%d", &salle->fosse);

    printf("Prix pour la catégorie A: ");
    scanf("%f", &concert->prixCategorieA);
    printf("Prix pour la catégorie B: ");
    scanf("%f", &concert->prixCategorieB);
    printf("Prix pour la catégorie C: ");
    scanf("%f", &concert->prixCategorieC);

    printf("Heure de fin du concert (HH:MM): ");
    scanf("%s", concert->heureFin);

    concert->enCours = 1; // Le concert est en cours
    nombreConcerts++;
    printf("Concert attribué avec succès.\n");
}

void terminerConcert() {
    printf("Nom du concert à terminer: ");
    char nomConcert[50];
    scanf("%s", nomConcert);

    for (int i = 0; i < nombreConcerts; i++) {
        if (strcmp(concerts[i].nom, nomConcert) == 0) {
            concerts[i].enCours = 0; // Le concert n'est plus en cours
            memset(concerts[i].salle->sieges, 0, sizeof(concerts[i].salle->sieges)); // Libérer tous les sièges
            printf("Concert terminé et sièges libérés.\n");
            return;
        }
    }

    printf("Concert non trouvé.\n");
}

void afficherConcertsEnCours() {
    printf("Concerts en cours:\n");
    for (int i = 0; i < nombreConcerts; i++) {
        if (concerts[i].enCours) {
            printf("Concert: %s, Salle: %s, Heure de fin: %s\n", concerts[i].nom, concerts[i].salle->nom, concerts[i].heureFin);
        }
    }
}

void reserverSieges() {
    printf("Nom du concert pour la réservation: ");
    char nomConcert[50];
    scanf("%s", nomConcert);

    Concert *concert = NULL;
    for (int i = 0; i < nombreConcerts; i++) {
        if (strcmp(concerts[i].nom, nomConcert) == 0 && concerts[i].enCours) {
            concert = &concerts[i];
            break;
        }
    }

    if (concert == NULL) {
        printf("Concert non trouvé ou déjà terminé.\n");
        return;
    }

    Salle *salle = concert->salle;

    printf("Plan de la salle %s:\n", salle->nom);
    afficherPlanSalle(salle);

    int nombreReservations, rangee, siege;
    float prixTotal = 0.0;
    printf("Nombre de sièges à réserver: ");
    scanf("%d", &nombreReservations);

    for (int i = 0; i < nombreReservations; i++) {
        printf("Réservation %d: Entrez la rangée et le siège (format: rangee siege): ", i + 1);
        scanf("%d %d", &rangee, &siege);

        if (rangee < 0 || rangee >= salle->nombreRangees || siege < 0 || siege >= salle->nombreSiegesParRangee || salle->sieges[rangee][siege] == 1) {
            printf("Siège invalide ou déjà occupé.\n");
            i--;
            continue;
        }

        salle->sieges[rangee][siege] = 1; // Marquer le siège comme occupé

        if (rangee < salle->rangeesCategorieA) {
            prixTotal += concert->prixCategorieA;
        } else if (rangee < salle->rangeesCategorieA + salle->rangeesCategorieB) {
            prixTotal += concert->prixCategorieB;
        } else {
            prixTotal += concert->prixCategorieC;
        }
    }

    printf("Réservation réussie. Prix total: %.2f\n", prixTotal);
}
