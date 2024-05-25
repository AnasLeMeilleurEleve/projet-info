#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include "concert.h"
#include "salle.h"

void print_menu_festivalier(WINDOW *menu_win, int highlight);

void modefestivalier() {
    int highlight = 1;
    int choice = 0;
    int c;
    WINDOW *menu_win;
    int startx = 0;
    int starty = 0;

    char *choices[] = {
        "Afficher les concerts en cours",
        "Réserver des sièges",
        "Quitter"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    menu_win = newwin(10, 40, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    print_menu_festivalier(menu_win, highlight);

    while (1) {
        c = wgetch(menu_win);
        switch (c) {
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

    print_menu_festivalier(menu_win, highlight);

    if (choice != 0) {  // User made a choice
        switch (choice) {
            case 1:
                clear();
                afficherConcertsEnCours();
                break;
            case 2:
                clear();
                reserverSieges();
                break;
            case 3:
                clear();
                printw("Retour au menu principal.\n");
                refresh();
                getch();
                return;
        }
        choice = 0;
        print_menu_festivalier(menu_win, highlight);
    }
}
}

void print_menu_festivalier(WINDOW *menu_win, int highlight) {
    int x = 2;
    int y = 2;
    char *choices[] = {
        "Afficher les concerts en cours",
        "Réserver des sièges",
        "Quitter"
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