#include "concert.h"
#include "salle.h"
#include <ncurses.h>
#include <ncursesw/ncurses.h>

void print_menu_manager(WINDOW *menu_win, int highlight);

void modemanager(){
  int highlight = 1;
  int choix1;
  int choice = 0;
  WINDOW *menu_win;
    int startx = 0;
    int starty = 0;

   char *choices[] = {
    "Créer une salle",
    "Attribuer un concert",
    "Afficher l'état des salles",
    "Terminer un concert",
    "Modifier une salle",
    "Quitter",
   };

  int n_choices = sizeof(choices) / sizeof(char *);

  clear();
  menu_win = newwin(10, 40, starty, startx);
  keypad(menu_win, TRUE);
  refresh();
  print_menu_manager(menu_win, highlight);

while (1) {
  choix1 = wgetch(menu_win);
  switch (choix1) {
    case KEY_UP:
      if (highlight == 1)
        highlight = n_choices;
      else
        --highlight;
      break;
    case KEY_DOWN:
        if (highlight == n_choices)
          highlight = 1;
        else
          ++highlight;
        break;
    case 10:  // Enter key
        choice = highlight;
      break;
    default:
      break;
  }

print_menu_manager(menu_win, highlight);

    if (choice != 0) {
switch (choice) {

  wclear(menu_win);
    case 1:
      clear();
      creerSalle();
      clear();
      break;
    case 2:
      clear();
      attribuerConcert();
      clear();
      break;
    case 3:
      clear();
      afficherEtatSalles();
      clear();
      break;
    case 4:
      clear();
      terminerConcert();
      clear();
      break;
    case 5:
      clear();
      modifierSalle();
      clear();
      break;
    case 6:
      clear();
      printw("Retour au menu principal.\n");
      refresh();
      getch();
      return;
    }
    choice = 0;
    print_menu_manager(menu_win, highlight);
  }
}
}

void print_menu_manager(WINDOW *menu_win, int highlight){
    int x = 2;
    int y = 2;
    char *choices[] = {
    "Créer une salle",
    "Attribuer un concert",
    "Afficher l'état des salles",
    "Terminer un concert",
    "Modifier une salle",
    "Quitter",
    };
    int n_choices = sizeof(choices) / sizeof(char *);
    
    box(menu_win, 0, 0);
    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}
