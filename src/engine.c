#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#include "engine.h"

void
initialise() {
    p1 = create_player();
    p2 = create_player();
    f = create_field();
}

void
quit() {
    free(p1);
    free(p2);
    free(f);
}

Player*
create_player () {
    Player *new;
    new = (Player*) malloc(sizeof(Player));
    assert(new != NULL);
    for (int i = 0; i < 8; i++) {
        int c = rand() % 5;
        int a = rand() % 4;
        new->cards[i] = create_card(c, a);
    }
    return new;
}

Card*
create_card (int c, int a) {
    Card *new;
    new = (Card*) malloc(sizeof(Card));
    assert(new != NULL);
    new->colour = c;
    new->animal = a;
    return new;
}

Field*
create_field () {
    Field *new;
    new = (Field*) malloc(sizeof(Field));
    return new;
}

void
remove_card (Player *p) {
    for (int i = 1; i<MAXCARDS; i++)
        p->cards[i-1] = p->cards[i];
}

void
add_card (Player *p, Card *card) {
    if(p != NULL && card != NULL) {
        int slot = MAXCARDS - 1;
        while (p->cards[slot]==NULL)
            slot--;
        p->cards[slot+1] = card;
    }
}

void
clean_up_field() {
    for (int i = 0; i < MAXCARDS; i++)
        f->cards_all[i] = NULL;
    for (int i = 0; i < 3; i++)
        f->cards[i] = NULL;
}

char*
p_print() {
    char *str;
    str = (char *) malloc(500);
    str = strcpy(str, "");
    for (int i=0; i < MAXCARDS; i++) {
        strcat(str, "[ ");
        if (p1->cards[i] != NULL) {
            strcat(str, vect_animal[p1->cards[i]->animal]);
            strcat(str, ", ");
            strcat(str, vect_colour[p1->cards[i]->colour]);
        }
        strcat(str, " ]");
    }
    return str;
}

void
next_run (Player *p) {
    if (p->cards[0] != NULL) {
        f->cards[f_count % 3] = p->cards[0];
        f->cards_all[f_count] = f->cards[f_count % 3];
        remove_card(p);
        f_count++;
    }
    printf("%s\n\n", p_print());
}

gchar*
evaluate() {
    int max_colour[5] = {0,0,0,0,0};
    int max_animal[4] = {0,0,0,0};
    int max_a = 0, index_a = 0, max_c = 0, index_c = 0, nothing_a = 1, nothing_c = 1;

    for (int i=0; f->cards[i] != NULL && i<3; i++) {
        max_animal[f->cards[i]->animal]++;
        max_colour[f->cards[i]->colour]++;
    }

    for (int i = 0; i<4; i++) {
        if (max_animal[i] > max_a) {
            max_a = max_animal[i];
            index_a = i;
        }
        if (max_animal[i] > 1)
            nothing_a = 0;
    }
    for (int i = 0; i<5; i++) {
        if (max_colour[i] > max_c) {
            max_c = max_colour[i];
            index_c = i;
        }
        if (max_colour[i] > 1)
            nothing_c = 0;
    }
    if (nothing_a && nothing_c)
        return "nichts";
    else if (max_a > max_c)
        return vect_animal[index_a];
    else if (max_a < max_c)
        return vect_colour[index_c];
    else if (max_a == max_c)
        return "dodelido";
    else
        return "error";    
}

gchar*
print() {
    gchar *str;
    str = (gchar *) malloc(200);
    str = strcpy(str, "");
    for (int i=0; i < 3; i++) {
        if (f->cards[i] != NULL) {
            strcat(str, "[ ");
            strcat(str, vect_animal[f->cards[i]->animal]);
            strcat(str, ", ");
            strcat(str, vect_colour[f->cards[i]->colour]);
            strcat(str, " ]");
        }
    }
    return str;
}
