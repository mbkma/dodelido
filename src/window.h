#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "engine.h"

GtkBuilder	*builder; 
GtkWidget	*window;
GtkWidget   *place_card;
GtkWidget	*new_dialog;
GtkWidget   *about_dialog;
GtkWidget   *preferences_dialog;
GtkImage    *image_f1;
GtkImage    *image_f2;
GtkImage    *image_f3;
GTimer      *timer;

int  btn_oeh_clicked;

typedef struct {
    GtkWidget	*g_lbl_field;
    GtkWidget	*g_lbl_count;
    GtkWidget	*g_lbl_player_turn;
} App_Widgets;

struct {
    gboolean  music;
    gboolean  time_limit;
} settings;

void            setup_window(void);
void            on_window_main_destroy(void);
void            on_btn_place_card_clicked(void);
App_Widgets     *widgets;
void            draw_field();
void            clean_up_field();

#endif /*_WINDOW_H_*/
