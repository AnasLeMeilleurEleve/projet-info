#include <stdio.h>
#include "salle.h"
#include "concert.h"

void modemanager() {
    int choix1;
    do {
        printf("Menu Manager:\n");
        printf("1. Créer une salle\n");
        printf("2. Attribuer un concert\n");
        printf("3. Afficher l'état des salles\n");
        printf("4. Terminer un concert\n");
        printf("5. Modifier une salle\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix1);

        switch (choix1) {
            case 1:
                creerSalle();
                break;
            case 2:
                attribuerConcert();
                break;
            case 3:
                afficherEtatSalles();
                break;
            case 4:
                terminerConcert();
                break;
            case 5:
                modifierSalle();
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix1 != 0);
}
