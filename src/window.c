#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gsound.h>

#include "window.h"

char str_lbl_field[30] = {0};
char str_lbl_count[30] = {0};

extern int f_count;
int  count = 0;
int  btn_oeh_clicked = 0;
int  music = 1;
int  time_limit = 0;

void 
on_btn_place_card_clicked() {
    timer = g_timer_new ();
    g_timer_start (timer);
    Player *p = get_current_player();
    btn_oeh_clicked = 0;
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "");
	next_run(p);
    draw_field();
    gtk_widget_set_sensitive (GTK_WIDGET(place_card), FALSE);
}

void 
draw_field() {
    char *filepath;
    filepath = (char *) malloc(200);

    if (get_number_of_cards(p1) == 0 || get_number_of_cards(p2) == 0 || get_number_of_cards(p3) == 0 ) {
        sprintf(str_lbl_field, "Player %d won!", get_current_player_number());
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), str_lbl_field);
    }

    sprintf(str_lbl_count, "Cards %d", get_number_of_cards(get_current_player()));
    sprintf(str_lbl_field, "Player %d", get_current_player_number());

    if (strcmp(get_f_animal(count), "PINGUIN") == 0) {
        if (strcmp(get_f_colour(count), "ROT") == 0)
            strcpy(filepath, "data/c_red_pinguin.png");
        else if (strcmp(get_f_colour(count), "BLAU") == 0)
            strcpy(filepath, "data/c_blue_pinguin.png");
        else if (strcmp(get_f_colour(count), "GRUEN") == 0)
             strcpy(filepath, "data/c_green_pinguin.png");
        else if (strcmp(get_f_colour(count), "GELB") == 0)
             strcpy(filepath, "data/c_yellow_pinguin.png");
    }
    else if (strcmp(get_f_animal(count), "KAMEL") == 0) {
        if (strcmp(get_f_colour(count), "ROT") == 0)
              strcpy(filepath,  "data/c_red_camel.png");
        else if (strcmp(get_f_colour(count), "BLAU") == 0)
            strcpy(filepath, "data/c_blue_camel.png");
        else if (strcmp(get_f_colour(count), "GRUEN") == 0)
             strcpy(filepath, "data/c_green_camel.png");
        else if (strcmp(get_f_colour(count), "GELB") == 0)
           strcpy(filepath, "data/c_yellow_camel.png");
    }
    else if (strcmp(get_f_animal(count), "ZEBRA") == 0) {
        if (strcmp(get_f_colour(count), "ROT") == 0)
            strcpy(filepath, "data/c_red_zebra.png");
        else if (strcmp(get_f_colour(count), "BLAU") == 0)
            strcpy(filepath, "data/c_blue_zebra.png");
        else if (strcmp(get_f_colour(count), "GRUEN") == 0)
             strcpy(filepath, "data/c_green_zebra.png");
        else if (strcmp(get_f_colour(count), "GELB") == 0)
             strcpy(filepath, "data/c_yellow_zebra.png");
    }
    else if (strcmp(get_f_animal(count), "SCHILDKROETE") == 0) {
        if (strcmp(get_f_colour(count), "ROT") == 0)
            strcpy(filepath, "data/c_red_turtle.png");
        else if (strcmp(get_f_colour(count), "BLAU") == 0)
            strcpy(filepath, "data/c_blue_turtle.png");
        else if (strcmp(get_f_colour(count), "GRUEN") == 0)
             strcpy(filepath, "data/c_green_turtle.png");
        else if (strcmp(get_f_colour(count), "GELB") == 0)
             strcpy(filepath, "data/c_yellow_turtle.png");
    }
    if (count == 0)
        gtk_image_set_from_file (image_f1, filepath);
    else if (count == 1)
        gtk_image_set_from_file (image_f2, filepath);
    else if (count == 2)
        gtk_image_set_from_file (image_f3, filepath);

    free(filepath);
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_count), str_lbl_count);
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_player_turn), str_lbl_field);
    count++;
    count %= 3;
}

void
clean_up_field() {
    for (int i = 0; i < MAXCARDS; i++)
        f->cards_all[i] = NULL;
    for (int i = 0; i < 3; i++)
        f->cards[i] = NULL;
    gtk_image_set_from_icon_name (image_f1, "gtk-remove",  GTK_ICON_SIZE_BUTTON);
    gtk_image_set_from_icon_name (image_f2, "gtk-remove",  GTK_ICON_SIZE_BUTTON);
    gtk_image_set_from_icon_name (image_f3, "gtk-remove",  GTK_ICON_SIZE_BUTTON);
    count = 0;
    f_count = 0;
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

void on_menu_about_dialog_response() {
    gtk_widget_hide(GTK_WIDGET(about_dialog)) ;
}

void on_new_dialog_apply_clicked() {
    gtk_widget_hide(new_dialog) ;
    gtk_image_set_from_icon_name (image_f1, "gtk-remove",  GTK_ICON_SIZE_BUTTON);
    gtk_image_set_from_icon_name (image_f2, "gtk-remove",  GTK_ICON_SIZE_BUTTON);
    gtk_image_set_from_icon_name (image_f3, "gtk-remove",  GTK_ICON_SIZE_BUTTON);
    if (music) {
    	GSoundContext *hello = gsound_context_new(NULL, NULL);
	    gsound_context_play_simple(hello, NULL, NULL,
	    	  GSOUND_ATTR_MEDIA_FILENAME, "data/thanks_to_0ad.ogg", NULL);
    }
}

void on_preferences_dialog_apply_clicked() {
    gtk_widget_hide(preferences_dialog) ;
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

void on_preferences_dialog_time_state_set() {
    (time_limit == 0) ? (time_limit = 1) : (time_limit = 0);
}

void on_preferences_dialog_music_state_set() {
    (music == 0) ? (music = 1) : (music = 0);
}

void on_btn_green_clicked() {
    Player *p = get_current_player();
    gchar *cmp = evaluate();
    if (time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "GRUEN") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    gchar *cmp = evaluate();
    if (time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "GELB") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    gchar *cmp = evaluate();
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "BLAU") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "ROT") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "PINGUIN") == 0 && btn_oeh_clicked == f->number_of_turtles)
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

void on_btn_turtle_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "SCHILDKROETE") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "ZEBRA") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "KAMEL") == 0 && btn_oeh_clicked == f->number_of_turtles)
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

void on_btn_dodelido_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "dodelido") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
    btn_oeh_clicked++;
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
        gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    }
    else if (btn_oeh_clicked == f->number_of_turtles)
        ;
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
        set_turn(p);
        gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    }
}

void on_btn_smash_clicked() {
    //TODO
}

void on_btn_nothing_clicked() {
    Player *p = get_current_player();
    gchar* cmp = evaluate();
    if(time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p, f->cards_all[i]);
        clean_up_field();
    }
    else if (strcmp(cmp, "nichts") == 0 && btn_oeh_clicked == f->number_of_turtles)
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
 	image_f1 = GTK_IMAGE(gtk_builder_get_object(builder, "img_f1"));
 	image_f2 = GTK_IMAGE(gtk_builder_get_object(builder, "img_f2"));
 	image_f3 = GTK_IMAGE(gtk_builder_get_object(builder, "img_f3"));

    g_object_unref(builder);
}


