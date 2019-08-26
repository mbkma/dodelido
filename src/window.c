#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>

#include "window.h"

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define WAIT 3

char str_count[30] = {0};

void on_btn_place_card_clicked() {
	next_run(p1);
}

char*
get_number_of_cards() {
    int count;
    for (count = 0; p1->cards[count] != NULL; count++)
        ;
    sprintf(str_count, "%d", count);
    return str_count;
}

gboolean timer_handler(app_widgets *widgets)
{
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), print());    // update label
    gtk_label_set_text(GTK_LABEL(widgets->g_lbl_count), get_number_of_cards());
    
    return TRUE;
}


void on_menu_new_activate() {
    g_timeout_add_seconds(1, (GSourceFunc)timer_handler, widgets);
}

void on_btn_dodelido_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "dodelido") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_green_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GRUEN") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_yellow_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GELB") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_blue_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "BLAU") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_red_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "ROT") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_penguin_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "PINGUIN") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_zebra_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "ZEBRA") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_camel_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "KAMEL") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_oeh_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "SCHILDKROETE") == 0) //TODO
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_smash_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "DINO") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), ""); //TODO
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_nothing_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "nichts") == 0)
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(widgets->g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
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

    g_object_unref(builder);
}
