#include <stdio.h>
#include "concert.h"
#include "salle.h"

void modefestivalier() {
    int choix2;
    do {
        printf("Menu Festivalier:\n");
        printf("1. Afficher les concerts en cours\n");
        printf("2. Réserver des sièges\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix2);

        switch (choix2) {
            case 1:
                afficherConcertsEnCours();
                break;
            case 2:
                reserverSieges();
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix2 != 0);
}
