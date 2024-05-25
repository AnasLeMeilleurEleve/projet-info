#include "salle.h"
#include "utils.h"
#include "salle.h"
#include "concert.h"
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

Salle salles[MAX_SALLES];
int nombreSalles = 0; 


void creerSalle() {
  if (nombreSalles >= MAX_SALLES) {
    printw("Nombre maximum de salles atteint.\n");
    refresh();
    getch();
    return;
  }

  Salle *salle = &salles[nombreSalles];
  echo(); // Activer l'écho pour permettre la saisie de texte
  
  do{
    printw("Nom de la salle : ");
    getnstr(salle->nom, sizeof(salle->nom) - 1); // lit l'entrée de l'utilisateur
    if (strlen(salle->nom) == 0) {
      printw("Erreur: Vous devez entrer quelque chose !\n"); // Affiche un message d'erreur si l'entrée est vide
      }
    } while (strlen(salle->nom) == 0);

  
  
  do {
    printw("Nombre de rangées: ");
    refresh();
    scanw("%d", &salle->nombreRangees);
    if (salle->nombreRangees <= 0) {
      printw("Veuillez entrer un nombre valide :\n");
      } 
    } while (salle->nombreRangees <= 0);

  do {
    printw("Nombre de sièges par rangée: ");
    refresh();
    scanw("%d", &salle->nombreSiegesParRangee);
    if (salle->nombreSiegesParRangee <= 0) {
      printw("Veuillez entrer un nombre valide :\n");
      }
    } while (salle->nombreSiegesParRangee <= 0);

  do{
    printw("Nombre de rangées catégorie A: ");
    refresh();
    scanw("%d", &salle->rangeesCategorieA);
    if(salle->rangeesCategorieA<0 || salle->rangeesCategorieA > salle->nombreRangees) {
      printw("Le nombre de rangées catégorie A doit être compris entre 0 et le nombre total de rangées. Veuillez réessayer.\n");
      }
    } while (salle->rangeesCategorieA < 0 || salle->rangeesCategorieA > salle->nombreRangees);

  do{
    printw("Nombre de rangées catégorie B: ");
    refresh();
    scanw("%d", &salle->rangeesCategorieB);
      if (salle->rangeesCategorieB < 0 || (salle->rangeesCategorieA + salle->rangeesCategorieB) > salle->nombreRangees) {
            printw("Le nombre de rangées catégorie B doit être compris entre 0 et le nombre total de rangées moins les rangées catégorie A. Veuillez réessayer.\n");
        }
    } while (salle->rangeesCategorieB < 0 || (salle->rangeesCategorieA + salle->rangeesCategorieB) > salle->nombreRangees);


  noecho(); // Désactiver l'écho

  salle->fosse = 0; // Par défaut, pas de fosse
  memset(salle->sieges, 0, sizeof(salle->sieges));
  nombreSalles++;
  printw("Salle créée avec succès.\n");
  sauvegardeSalle();
  getch(); // Attendre une touche pour continuer
  clear();
  refresh();
}

void afficherEtatSalles() {
  clear();
  if(nombreSalles==0){
    printw("Aucune salle n'a été créee pour l'instant...");
  }
  else{
  for (int i = 0; i < nombreSalles; i++) {
    Salle *salle = &salles[i];
    int siegesOccupes = 0,
        siegesTotal = salle->nombreRangees * salle->nombreSiegesParRangee;

    for (int r = 0; r < salle->nombreRangees; r++) {
      for (int s = 0; s < salle->nombreSiegesParRangee; s++) {
        if (salle->sieges[r][s] == 1) {
          siegesOccupes++;
        }
      }
    }
    afficherPlanSalle(&salles[i]);
    printw("Salle: %s\n", salle->nom);
    printw("Nombre total de sièges: %d\n", siegesTotal);
    printw("Nombre de sièges occupés: %d\n", siegesOccupes);
    printw("Ratio: %.2f%%\n\n", (float)siegesOccupes / siegesTotal * 100);
  }
  }
  getch(); // Attendre une touche pour continuer
  clear();
  refresh();
}

void modifierSalle() {
    char nomSalle[50];
    echo(); // Activer l'écho pour permettre à getstr() d'afficher les caractères
    printw("Nom de la salle à modifier: ");
    getstr(nomSalle);
    Salle *salle = findSalleByName(nomSalle);
    if (salle == NULL) {
        printw("Salle non trouvée.\n");
    }
    
  else{
  do {
    printw("Nombre de rangées: ");
    refresh();
    scanw("%d", &salle->nombreRangees);
    if (salle->nombreRangees <= 0) {
      printw("Veuillez entrer un nombre valide :\n");
      } 
    } while (salle->nombreRangees <= 0);

  do {
    printw("Nombre de sièges par rangée: ");
    refresh();
    scanw("%d", &salle->nombreSiegesParRangee);
    if (salle->nombreSiegesParRangee <= 0) {
      printw("Veuillez entrer un nombre valide :\n");
      }
    } while (salle->nombreSiegesParRangee <= 0);

  do{
    printw("Nombre de rangées catégorie A: ");
    refresh();
    scanw("%d", &salle->rangeesCategorieA);
    if(salle->rangeesCategorieA<0 || salle->rangeesCategorieA > salle->nombreRangees) {
      printw("Le nombre de rangées catégorie A doit être compris entre 0 et le nombre total de rangées. Veuillez réessayer.\n");
      }
    } while (salle->rangeesCategorieA < 0 || salle->rangeesCategorieA > salle->nombreRangees);

  do{
    printw("Nombre de rangées catégorie B: ");
    refresh();
    scanw("%d", &salle->rangeesCategorieB);
      if (salle->rangeesCategorieB < 0 || (salle->rangeesCategorieA + salle->rangeesCategorieB) > salle->nombreRangees) {
            printw("Le nombre de rangées catégorie B doit être compris entre 0 et le nombre total de rangées moins les rangées catégorie A. Veuillez réessayer.\n");
        }
    } while (salle->rangeesCategorieB < 0 || (salle->rangeesCategorieA + salle->rangeesCategorieB) > salle->nombreRangees);
  
  noecho(); // Désactiver l'écho
  printw("Modification réussie.\n");
  }
  getch(); // Attendre une touche pour continuer
  clear();
  refresh();
}


void afficherPlanSalle(Salle *salle) {
  for (int r = 0; r < salle->nombreRangees; r++) {
    for (int s = 0; s < salle->nombreSiegesParRangee; s++) {
      if (salle->sieges[r][s] == 0) {
        if (r < salle->rangeesCategorieA) {
          attron(COLOR_PAIR(1)); // Assurez-vous de définir une paire de couleurs pour RED
          printw("0 ");
          attroff(COLOR_PAIR(1));
        } else if (r < salle->rangeesCategorieA + salle->rangeesCategorieB) {
          attron(COLOR_PAIR(2)); // Assurez-vous de définir une paire de couleurs pour BLUE
          printw("0 ");
          attroff(COLOR_PAIR(2));
        } else {
          printw("0 ");
        }
      } else {
        printw("X ");
      }
    }
    printw("\n");
  }
  refresh();
}

Salle *findSalleByName(char *nom) {
  for (int i = 0; i < nombreSalles; i++) {
    if (strcmp(salles[i].nom, nom) == 0) {
      return &salles[i];
    }
  }
  return NULL;
}

void sauvegardeSalle(){
    FILE *fSalles = fopen("salles.txt", "a+");
    if (fSalles == NULL) {
        mvprintw(0, 0, "Erreur d'ouverture du fichier salles.txt");
        refresh();
        getch();
        endwin();
        return;
    }

    for (int i = 0; i < nombreSalles; i++) {
        Salle *salle = &salles[i];
        fprintf(fSalles, "%s %d %d %d %d %.2f %.2f %.2f %d\n",
                salle->nom, salle->nombreRangees, salle->nombreSiegesParRangee,salle->rangeesCategorieA,
                salle->rangeesCategorieB,salle->prixCategorieA, salle->prixCategorieB, salle->prixCategorieC,salle->fosse);
    }
    fclose(fSalles);
}