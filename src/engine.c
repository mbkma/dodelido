#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>

#include "engine.h"

void
initialise() {
    p1 = create_player();
    p2 = create_player();
    p3 = create_player();
    f  = create_field();
    p1->turn = 1;
}

void
quit() {
    free(p1);
    free(p2);
    free(p3);
    free(f);
}

Player*
create_player () {
    int c = 0;
    int a = 0;
    Player *new;
    new = (Player*) malloc(sizeof(Player));
    assert(new != NULL);
    for (int i = 0; i < 8; i++) {
        c = g_random_int_range(0,4);
        a = g_random_int_range(0,3);
        new->cards[i] = create_card(c, a);
        if (g_random_int_range (0,19) < 1)  // prob. of turtle is 1/20
            new->cards[i] = create_card(c, 3);
    }
    new->turn = 0;
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
    new->number_of_turtles = 0;
    return new;
}

void
remove_card (Player *p) {
    for (int i = 1; i<MAXCARDS; i++)
        p->cards[i-1] = p->cards[i];
}

void
add_card (Player *p, Card *card) {
    if (p != NULL && card != NULL) {
        int slot = MAXCARDS - 1;
        while (p->cards[slot]==NULL)
            slot--;
        p->cards[slot+1] = card;
    }
    else
        fprintf(stderr, "err: add_card: null-pointer argument!\n");
}

Player*
get_current_player() {
    if (p1->turn == 1)
        return p1;
    else if (p2->turn == 1)
        return p2;
    else if (p3->turn == 1)
        return p3;
    else {
        fprintf(stderr, "err: get_current_player: It's nobodys turn\n");
        return p1;
    }
}

int 
get_current_player_number() {
    Player *p = get_current_player();
    if (p == p1)
        return 1;
    else if (p == p2)
        return 2;
    else if (p == p3)
        return 3;
    else {
        fprintf(stderr, "err: get_current_player_number: It's nobodys turn\n");
        return 1;
    }
}

int
get_number_of_cards(Player *p) {
    int count;
    for (count = 0; p->cards[count] != NULL; count++)
        ;
    return count;
}

void player_lost_turn_action (Player *p) {
        for (int i = 0; i<MAXCARDS && f->cards_all[i] != NULL; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
}

char *vect_colour[] = {"RED", "BLUE", "YELLOW", "GREEN", "WHITE"};
char *vect_animal[] = {"PENGUIN", "ZEBRA", "CAMEL", "TURTLE", "DINOSAUR"};

char*
evaluate() {
    int max_colour[5] = {0,0,0,0,0};
    int max_animal[4] = {0,0,0,0};
    int max_a = 0, index_a = 0, max_c = 0, index_c = 0, nothing_a = 1, nothing_c = 1;

    for (int i=0; f->cards[i] != NULL && i<3; i++) {
        max_animal[f->cards[i]->animal]++;
        max_colour[f->cards[i]->colour]++;
   // printf("max_a %d\n", max_animal[f->cards[i]->animal]);
    //printf("max_c %d\n", max_colour[f->cards[i]->colour]);
    }
    f->number_of_turtles = max_animal[3];
  //  printf("%d\n", f->number_of_turtles);


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
    if (f->number_of_turtles > 0 && btn_oeh_clicked < f->number_of_turtles)
        return "OEH";
    if (nothing_a && nothing_c)
        return "NOTHING";
    else if (max_a > max_c)
        return vect_animal[index_a];
    else if (max_a < max_c)
        return vect_colour[index_c];
    else if (max_a == max_c)
        return "DODELIDO";
    else
        return "EVALUATE_ERROR";    
}

void
set_turn (Player *p) {
    p->turn = 0;
    if (p == p1 && f->number_of_players > 1)
        p2->turn = 1;
    else if (p == p1)
        p1->turn = 1;
    else if (p == p2 && f->number_of_players > 2)
        p3->turn = 1;
    else if (p == p2)
        p1->turn = 1;
    else if (p == p3)
        p1->turn = 1;
}


void
next_run (Player *p) {
    if (p->cards[0] != NULL) {
        f->cards[f_count % 3] = p->cards[0];
        f->cards_all[f_count] = f->cards[f_count % 3];
        remove_card(p);
        f_count++;
    }
}

char*
get_f_animal(int i) {
    return vect_animal[f->cards[i]->animal];
}

char*
get_f_colour (int i) {
    return vect_colour[f->cards[i]->colour];
}

