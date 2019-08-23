#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#include "window.h"

void on_btn_next_clicked() {
    int count = 0;
    char str_count[30] = {0};
    for (count = 0; p1->cards[count] != NULL; count++)
        ;
    if (count == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "you won");
    else {
        sprintf(str_count, "%d", --count);
        gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
        next_run(p1);
        char *output = print();
        gtk_label_set_text(GTK_LABEL(g_lbl_field), output);
    }
}

void on_btn_dodelido_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "dodelido") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_gruen_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GRUEN") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_gelb_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GELB") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_blau_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "BLAU") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_rot_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "ROT") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_ping_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "PINGUIN") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_zebr_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "ZEBRA") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_kamel_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "KAMEL") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_aeh_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "SCHILDKROETE") == 0) //TODO
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_hau_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "GRUEN") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), ""); //TODO
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
        for (int i = 0; i<MAXCARDS; i++)
            add_card(p1, f->cards_all[i]);
        clean_up_field();
    }
}

void on_btn_nichts_clicked() {
    gchar* cmp = evaluate();
    if (strcmp(cmp, "nichts") == 0)
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "true");
    else {
        gtk_label_set_text(GTK_LABEL(g_lbl_field), "false");
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

    g_lbl_field = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_field"));
    g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));

    g_object_unref(builder);
}
