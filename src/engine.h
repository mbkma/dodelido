#ifndef _ENGINE_H_
#define _ENGINE_H_

#define MAXCARDS 50

static int f_count = 0;

static char *vect_colour[] = {"ROSA", "BLAU", "GELB", "GRUEN", "WEISS"};
static char *vect_animal[] = {"PINGUIN", "ZEBRA", "KAMEL", "SCHILDKROETE", "DINO"};

typedef struct _card {
    int colour;
    int animal;
} Card;

typedef struct _field {
    Card    *cards[3];
    Card    *cards_all[MAXCARDS];
} Field;

typedef struct _player {
    Card    *cards[MAXCARDS];
	int		turn;
} Player;

Player  *p1, *p2;
Field   *f;

Player* create_player ();
Card*   create_card (int c, int a);
Field*  create_field ();

void    initialise();
char*   evaluate ();
void    quit();
void    add_card (Player *p, Card *card);
void	remove_card (Player *p);
void    clean_up_field();
void    next_run (Player *p);
char*	print();

#endif /*_ENGINE_H_*/
