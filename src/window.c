#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gsound.h>

#include "window.h"

char str_count[30] = {0};
char str_player[30] = {0};
int  btn_oeh_clicked = 0;
int  music = 0;

void 
on_btn_place_card_clicked() {
    Player *p = get_current_player();
	next_run(p);
    draw_field();
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), FALSE);
    btn_oeh_clicked = 0;
}

Player*
get_current_player() {
    if (p1->turn == 1)
        return p1;
    else if (p2->turn == 1)
        return p2;
    else if (p3->turn == 1)
        return p3;
    else
        return p1;
}

void 
draw_field() {
    Player *p = get_current_player();
    if (p == p1)
        sprintf(str_player, "Player %d", 1);
    else if (p == p2)
        sprintf(str_player, "Player %d", 2);
    else if (p == p3)
        sprintf(str_player, "Player %d", 3);
    else
        sprintf(str_player, "Player %d", 1);
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), print());
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_count), get_number_of_cards(get_current_player()));
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_player_turn), str_player);
}

char*
get_number_of_cards(Player *p) {
    int count;
    for (count = 0; p->cards[count] != NULL; count++)
        ;
    sprintf(str_count, "%d Cards", count);
    return str_count;
}

/*
gboolean timer_handler(app_widgets *widgets)
{
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), print());    // update label
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_count), get_number_of_cards());
    
    return TRUE;
}
*/  //TODO: implement computer player

void on_menu_new_activate() {
   // g_timeout_add_seconds(1, (GSourceFunc)timer_handler, widgets); //TODO: implement computer player
    gtk_dialog_run(GTK_DIALOG(new_dialog));
}

void on_menu_about_activate() {
    gtk_dialog_run(GTK_DIALOG(about_dialog));
}

void on_new_dialog_apply_clicked() {
    gtk_widget_destroy(new_dialog) ;
    draw_field();
    if (music) {
    	GSoundContext *hello = gsound_context_new(NULL, NULL);
	    gsound_context_play_simple(hello, NULL, NULL,
	    	  GSOUND_ATTR_MEDIA_FILENAME, "data/thanks_to_0ad.ogg", NULL);
        }
}

void on_dialog_rb1_toggled() {
    f->number_of_players = 1;
}

void on_dialog_rb2_toggled() {
    f->number_of_players = 2;
}

void on_dialog_rb3_toggled() {
    f->number_of_players = 3;
}

void on_menu_preferences_activate() {
    gtk_dialog_run(GTK_DIALOG(preferences_dialog));
}

void on_preferences_dialog_music_state_set() {
    (music == 0) ? (music = 1) : (music = 0);
}

void on_preferences_dialog_apply_clicked() {
    gtk_widget_destroy(preferences_dialog) ;
}

void on_btn_dodelido_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "dodelido") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_green_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GRUEN") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_yellow_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GELB") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_blue_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "BLAU") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_red_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "ROT") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_penguin_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "PINGUIN") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_zebra_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "ZEBRA") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_camel_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "KAMEL") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_oeh_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (f->number_of_turtles == 0) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    if (f->number_of_turtles == btn_oeh_clicked)
        gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    btn_oeh_clicked++;
}

void on_btn_smash_clicked() {
    //TODO
}

void on_btn_nothing_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if (strcmp(cmp, "nichts") == 0 && btn_oeh_clicked == f->number_of_turtles)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_window_main_destroy() {
    gtk_main_quit();
}

void
setup_window() {
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    widgets = g_slice_new(app_widgets);

    widgets->g_lbl_field = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_field"));
    widgets->g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
    widgets->g_lbl_player_turn = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_player_turn"));
    place_card = GTK_WIDGET(gtk_builder_get_object(builder, "btn_place_card"));
    new_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "menu_new_dialog"));
 	about_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "menu_about_dialog"));
 	preferences_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "menu_preferences_dialog"));

    g_object_unref(builder);
}


