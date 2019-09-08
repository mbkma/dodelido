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

void 
initialise_settings() {
    settings.music = TRUE;
    settings.time_limit = FALSE;
}

void 
on_btn_place_card_clicked() {
    if (settings.time_limit) {
        timer = g_timer_new ();
        g_timer_start (timer);
    }
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

    if (strcmp(get_f_animal(count), "PENGUIN") == 0) {
        if (strcmp(get_f_colour(count), "RED") == 0)
            strcpy(filepath, "data/c_red_pinguin.png");
        else if (strcmp(get_f_colour(count), "BLUE") == 0)
            strcpy(filepath, "data/c_blue_pinguin.png");
        else if (strcmp(get_f_colour(count), "GREEN") == 0)
             strcpy(filepath, "data/c_green_pinguin.png");
        else if (strcmp(get_f_colour(count), "YELLOW") == 0)
             strcpy(filepath, "data/c_yellow_pinguin.png");
    }
    else if (strcmp(get_f_animal(count), "CAMEL") == 0) {
        if (strcmp(get_f_colour(count), "RED") == 0)
              strcpy(filepath,  "data/c_red_camel.png");
        else if (strcmp(get_f_colour(count), "BLUE") == 0)
            strcpy(filepath, "data/c_blue_camel.png");
        else if (strcmp(get_f_colour(count), "GREEN") == 0)
             strcpy(filepath, "data/c_green_camel.png");
        else if (strcmp(get_f_colour(count), "YELLOW") == 0)
           strcpy(filepath, "data/c_yellow_camel.png");
    }
    else if (strcmp(get_f_animal(count), "ZEBRA") == 0) {
        if (strcmp(get_f_colour(count), "RED") == 0)
            strcpy(filepath, "data/c_red_zebra.png");
        else if (strcmp(get_f_colour(count), "BLUE") == 0)
            strcpy(filepath, "data/c_blue_zebra.png");
        else if (strcmp(get_f_colour(count), "GREEN") == 0)
             strcpy(filepath, "data/c_green_zebra.png");
        else if (strcmp(get_f_colour(count), "YELLOW") == 0)
             strcpy(filepath, "data/c_yellow_zebra.png");
    }
    else if (strcmp(get_f_animal(count), "TURTLE") == 0) {
        if (strcmp(get_f_colour(count), "RED") == 0)
            strcpy(filepath, "data/c_red_turtle.png");
        else if (strcmp(get_f_colour(count), "BLUE") == 0)
            strcpy(filepath, "data/c_blue_turtle.png");
        else if (strcmp(get_f_colour(count), "GREEN") == 0)
             strcpy(filepath, "data/c_green_turtle.png");
        else if (strcmp(get_f_colour(count), "YELLOW") == 0)
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

void on_menu_new_activate() {
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
    if (settings.music) {
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
    (settings.time_limit == 0) ? (settings.time_limit = 1) : (settings.time_limit = 0);
}

void on_preferences_dialog_music_state_set() {
    (settings.music == 0) ? (settings.music = 1) : (settings.music = 0);
}

void on_btn_clicked(gchar *k) {
    Player *p = get_current_player();
    gchar *cmp = evaluate();
    if (strcmp("OEH", k) == 0)
        btn_oeh_clicked++;
    if (settings.time_limit && g_timer_elapsed (timer, NULL) > 3) {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "time elapsed");
        player_lost_turn_action(p);
    }
    else if (strcmp(cmp, k) == 0) {
        if (strcmp("OEH", k) != 0)
            gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    }
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        player_lost_turn_action(p);
    }
    if (strcmp("OEH", k) != 0)
        gtk_widget_set_sensitive (GTK_WIDGET(place_card), TRUE);
    set_turn(p);
}

void on_btn_green_clicked() {
    on_btn_clicked("GREEN");
}

void on_btn_yellow_clicked() {
    on_btn_clicked("YELLOW");
}

void on_btn_blue_clicked() {
    on_btn_clicked("BLUE");;
}

void on_btn_red_clicked() {
    on_btn_clicked("RED");
}

void on_btn_penguin_clicked() {
    on_btn_clicked("PENGUIN");
}

void on_btn_turtle_clicked() {
    on_btn_clicked("TURTLE");
}

void on_btn_zebra_clicked() {
    on_btn_clicked("ZEBRA");
}

void on_btn_camel_clicked() {
    on_btn_clicked("CAMEL");
}

void on_btn_dodelido_clicked() {
    on_btn_clicked("DODELIDO");
}

void on_btn_oeh_clicked() {
    on_btn_clicked("OEH");
}

void on_btn_smash_clicked() {
    //TODO
}

void on_btn_nothing_clicked() {
    on_btn_clicked("NOTHING");
}

void on_window_main_destroy() {
    gtk_main_quit();
}

void
setup_window() {
    initialise_settings();
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    widgets = g_slice_new(App_Widgets);

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


