#ifndef _ENGINE_H_
#define _ENGINE_H_

#define MAXCARDS 50

#include "window.h"

int f_count;

typedef struct _card {
    int colour;
    int animal;
} Card;

typedef struct _field {
    Card    *cards[3];
    Card    *cards_all[MAXCARDS];
    int     number_of_players;
    int     number_of_turtles;
} Field;

typedef struct _player {
    Card    *cards[MAXCARDS];
	int		turn;
} Player;

Player  *p1, *p2, *p3;
Field   *f;

Player*     create_player ();
Card*       create_card (int c, int a);
Field*      create_field ();

void        initialise (void);
char*       evaluate (void);
void        quit (void);
void        add_card (Player *p, Card *card);
void	    remove_card (Player *p);
void        set_turn (Player *p);
void        next_run (Player *p);
void        player_lost_turn_action (Player *p);
char*       get_f_animal(int i);
char*       get_f_colour(int i);
int         get_number_of_cards(Player *p);
int         get_current_player_number(void);
Player*     get_current_player(void);


#endif /*_ENGINE_H_*/


