#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "concert.h"
#include "salle.h"
#include "utils.h"

Concert concerts[MAX_CONCERTS];
int nombreConcerts = 0;

void sauvegardeConcert(){
    FILE *fConcerts = fopen("concerts.txt", "w");
    if (fConcerts == NULL) {
        mvprintw(1, 0, "Erreur d'ouverture du fichier concerts.txt");
        refresh();
        getch();
        return;
    }

    for (int i = 0; i < nombreConcerts; i++) {
        Concert *concert = &concerts[i];
        fprintf(fConcerts, "%s %s %s %.2f %.2f %.2f %d\n",
                concert->nom, concert->salle->nom, concert->heureFin,
                concert->prixCategorieA, concert->prixCategorieB, concert->prixCategorieC,
                concert->enCours);
    }
    fclose(fConcerts);
    refresh();
}

int heureValide(char *heure) {
    // Vérifie la longueur
    if (strlen(heure) != 5) {
        return 0;
    }

    // Vérifie le format HH:MM qui sera demandé dans la fonction attribuerConcert
    if (!isdigit(heure[0]) || !isdigit(heure[1]) || heure[2] != ':' || 
        !isdigit(heure[3]) || !isdigit(heure[4])) {
        return 0;
    }

    // Convertit les heures et minutes en entiers
    int h = (heure[0] - '0') * 10 + (heure[1] - '0');
    int m = (heure[3] - '0') * 10 + (heure[4] - '0');

    // Vérifie que les heures sont entre 00 et 23 et les minutes entre 00 et 59
    if (h < 0 || h > 23 || m < 0 || m > 59) {
        return 0;
    }

    return 1;
}

void attribuerConcert() {
    if (nombreConcerts >= MAX_CONCERTS) {
        printw("Nombre maximum de concerts atteint.\n");
        refresh();
        getch();
        return;
    }
    else if(nombreSalles==0){
        printw("Impossible d'attribuer un concert s'il n'y a pas de salle c'est logique");
        getch();
        clear();
        refresh();
        return;
    }
    Concert *concert = &concerts[nombreConcerts];
    echo(); // Activer l'écho pour permettre à getstr() d'afficher les caractères
    do{
        printw("Nom du concert: ");
        getnstr(concert->nom, sizeof(concert->nom) - 1); // lit l'entrée de l'utilisateur
        if (strlen(concert->nom) == 0) {
        printw("Erreur: Vous devez entrer quelque chose !\n"); // Affiche un message d'erreur si l'entrée est vide
      }
    } while (strlen(concert->nom) == 0);

    printw("Choisir une salle par nom: ");
    refresh();
    char nomSalle[50];
    getstr(nomSalle);
    noecho(); // Désactiver l'écho après avoir pris l'entrée

    Salle *salle = findSalleByName(nomSalle);

    if (salle == NULL) {
        printw("Salle non trouvée.\n");
        sauvegardeConcert();
        getch(); // Attendre une touche pour continuer
        clear();
        refresh();
        return;
    }

    concert->salle = salle;
    do{
    printw("Le concert aura-t-il une fosse (1 pour oui, 0 pour non)?: ");
    refresh();
    scanw("%d", &salle->fosse);
    if (salle->fosse != 0 && salle->fosse != 1){
            printw("Choix invalide. Veuillez réessayer.\n");
        }
    }while (salle->fosse != 0 && salle->fosse != 1);

    echo();

    do{
        printw("Prix pour la catégorie A: ");
        refresh();
        scanw("%f", &concert->prixCategorieA);
        if(concert->prixCategorieA<=0){
            printw("Choix invalide. Veuillez réessayer.\n");
        }
    }while (concert->prixCategorieA<=0);

    do{
        printw("Prix pour la catégorie B: ");
        refresh();
        scanw("%f", &concert->prixCategorieB);
        if(concert->prixCategorieB<=0||concert->prixCategorieA<=concert->prixCategorieB){
            printw("Ce que vous avez entré est invalide, ou alors le nombre que vous avez entré est supérieur ou égal au prix de la catégorié A.\n");
        }
    }while (concert->prixCategorieB<=0||concert->prixCategorieA<=concert->prixCategorieB);

    do{
        printw("Prix pour la catégorie C: ");
        refresh();
        scanw("%f", &concert->prixCategorieC);
        if(concert->prixCategorieC<=0||concert->prixCategorieB<=concert->prixCategorieC){
            printw("Ce que vous avez entré est invalide, ou alors le nombre que vous avez entré est supérieur ou égal au prix de la catégorié B.\n");
        }
    }while (concert->prixCategorieC<=0||concert->prixCategorieB<=concert->prixCategorieC);

int valid = 0;
    do{
        // Demande de l'entrée utilisateur
        printw("Heure de fin du concert, veuillez impérativement l'écrire sous la forme suivante (HH:MM): ");
        refresh();
        getnstr(concert->heureFin, sizeof(concert->heureFin));
        // Vérifie si l'heure est valide
        if (heureValide(concert->heureFin)) {
            valid = 1;  // Marque l'entrée comme valide
        } else {
            printw("Erreur: Veuillez bien suivre les indications pour entrer correctement l'heure de fin du concert\n");
            }
    }while(!valid);

    concert->enCours = 1; // Le concert est en cours
    nombreConcerts++;
    printw("Concert attribué avec succès.\n");
    sauvegardeConcert();
    noecho(); // Désactiver l'écho après avoir pris l'entrée
    getch(); // Attendre une touche pour continuer
    clear();
    refresh();
}  


void terminerConcert() {
    if(nombreConcerts==0){
        printw("Impossible de terminer un concert s'il n'y en a pas de base c'est logique");
        getch();
        clear();
        refresh();
        return;
    }
    printw("Nom du concert à terminer: ");
    refresh();
    echo(); // Activer l'écho pour getstr
    char nomConcert[50];
    getstr(nomConcert);
    noecho(); // Désactiver l'écho après avoir pris l'entrée
    int concertTrouve = 0; // Flag pour vérifier si le concert a été trouvé
    for (int i = 0; i < nombreConcerts; i++) {
        if (strcmp(concerts[i].nom, nomConcert) == 0) {
            concerts[i].enCours = 0; // Le concert n'est plus en cours
            memset(concerts[i].salle->sieges, 0, sizeof(concerts[i].salle->sieges)); // Libérer tous les sièges
            printw("Concert terminé et sièges libérés.\n");
            concertTrouve=1;
            getch(); // Attendre une touche pour continuer
            clear();
            refresh();
            nombreConcerts--;
        }
    }

    if(!concertTrouve){
        printw("Concert non trouvé.\n");
        getch(); // Attendre une touche pour continuer
        clear();
        refresh();
    }
}

void afficherConcertsEnCours() {
    printw("Concerts en cours:\n");
    refresh();
    for (int i = 0; i < nombreConcerts; i++) {
        if (concerts[i].enCours) {
            printw("Concert: %s, Salle: %s, Heure de fin: %s\n", concerts[i].nom, concerts[i].salle->nom, concerts[i].heureFin);
            refresh();
        }
    }
    getch();
    clear();
    refresh();

}

void reserverSieges() {
    printw("Nom du concert pour la réservation: ");
    refresh();
    echo(); // Activer l'écho pour getstr
    char nomConcert[50];
    getstr(nomConcert);
    noecho(); // Désactiver l'écho après avoir pris l'entrée

    Concert *concert = NULL;
    for (int i = 0; i < nombreConcerts; i++) {
        if (strcmp(concerts[i].nom, nomConcert) == 0 && concerts[i].enCours) {
            concert = &concerts[i];
            break;
        }
    }

    if (concert == NULL) {
        printw("Concert non trouvé ou déjà terminé.\n");
        refresh();
        getch();
        return;
    }

    Salle *salle = concert->salle;

    printw("Plan de la salle %s:\n", salle->nom);
    refresh();
    afficherPlanSalle(salle);

    int nombreReservations, rangee, siege;
    float prixTotal = 0.0;
    echo(); //Pour que l'utilisateur puisse voir ce qu'il entre

    do{
        printw("Nombre de sièges à réserver: ");
        refresh();
        scanw("%d", &nombreReservations);
        if(nombreReservations<0 || nombreReservations>(salle->nombreRangees*salle->nombreSiegesParRangee)){
            printw("Nombre invalide, veuillez réessayer svp.\n");
        }
    } while(nombreReservations<0 || nombreReservations>(salle->nombreRangees*salle->nombreSiegesParRangee));

    for (int i = 0; i < nombreReservations; i++) {
        
        printw("Réservation %d: Entrez la rangée et le siège (format: rangee siege): ",i+1);
        refresh();
        scanw("%d %d", &rangee, &siege);     

        if (rangee < 0 || rangee >= salle->nombreRangees || siege < 0 || siege >= salle->nombreSiegesParRangee || salle->sieges[rangee][siege] == 1) {
            printw("Siège invalide ou déjà occupé.\n");
            refresh();
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

    printw("Réservation réussie. Prix total: %.2f\n", prixTotal);
    getch();
    clear();
    refresh();
}
