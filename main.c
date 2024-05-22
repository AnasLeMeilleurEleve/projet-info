#include <stdio.h>
#include "manager.h"
#include "festivalier.h"

void choixmode();

int main() {
    printf("MENU PRINCIPAL\n");
    choixmode();
    return 0;
}

void choixmode() {
    int choix;
    do {
        printf("Choisissez le mode d'utilisation:\n");
        printf("1. Manager\n");
        printf("2. Festivalier\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                modemanager();
                break;
            case 2:
                modefestivalier();
                break;
            case 0:
                printf("Au revoir.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}
