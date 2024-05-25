#include "festivalier.h"
#include "manager.h"
#include <ncurses.h>

void choixmode();

int main() {
  // Initialisation de curses
  initscr(); 
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  // Affichage du menu principal
  printw("MENU PRINCIPAL\n");
  refresh();
  choixmode();

  // Terminer la session curses
  endwin();
  return 0;
}

void choixmode() {
  int choix;
  do {
    clear();
printw("*  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. *\n");
printw("* | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | *\n");
printw("* | |     ______   | || |  ____  ____  | || |  _________   | || |  _________   | || |    _______   | || |  _________   | | *\n");
printw("* | |   .' ___  |  | || | |_  _||_  _| | || | |_   ___  |  | || | |_   ___  |  | || |   /  ___  |  | || | |  _   _  |  | | *\n");
printw("* | |  / .'   \\_|  | || |   \\ \\  / /   | || |   | |_  \\_|  | || |   | |_  \\_|  | || |  |  (__ \\_|  | || | |_/ | | \\_|  | | *\n");
printw("* | |  | |         | || |    \\ \\/ /    | || |   |  _|      | || |   |  _|  _   | || |   '.___`-.   | || |     | |      | | *\n");
printw("* | |  \\ `.___.'\\  | || |    _|  |_    | || |  _| |_       | || |  _| |___/ |  | || |  |`\\____) |  | || |    _| |_     | | *\n");
printw("* | |   `._____.'  | || |   |______|   | || | |_____|      | || | |_________|  | || |  |_______.'  | || |   |_____|    | | *\n");
printw("* | |              | || |              | || |              | || |              | || |              | || |              | | *\n");
printw("* | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | *\n");
printw("*  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' *\n\n");

    printw("Choisissez le mode d'utilisation:\n\n");
    printw("1. Manager\n");
    printw("2. Festivalier\n");
    printw("0. Quitter\n");
    printw("Votre choix: ");
    refresh();
    scanw("%d", &choix);

    switch (choix) {
    case 1:
      clear();
      modemanager();
      break;
    case 2:
      clear();
      modefestivalier();
      break;
    case 0:
      clear();
      printw("*                                              _ *\n");
      printw("*     /\\                                      (_) *\n");
      printw("*    /  \\    _   _   _ __   ___ __   __  ___   _  _ __ *\n");
      printw("*   / /\\ \\  | | | | | '__| / _ \\ \\ / / / _ \\ | || '__| *\n");
      printw("*  / ____ \\ | |_| | | |   |  __/ \\ V / | (_) || || | *\n");
      printw("* /_/    \\_\\ \\__,_| |_|    \\___|  \\_/   \\___/ |_||_| *\n");
      refresh();
      getch();
      break;
    default:
      clear();
      printw("Choix invalide. Veuillez réessayer.\n");
      refresh();
      getch();
    }
  } while (choix != 0);
}
