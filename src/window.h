#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "engine.h"

GtkBuilder	*builder; 
GtkWidget	*window;
GtkWidget	*new_dialog;
GtkWidget   *about_dialog;
GtkWidget   *place_card;
GtkWidget   *preferences_dialog;

typedef struct {
    GtkWidget	*g_lbl_field;
    GtkWidget	*g_lbl_count;
    GtkWidget	*g_lbl_player_turn;
} app_widgets;

void            setup_window(void);
void            on_window_main_destroy(void);
void            on_btn_place_card_clicked(void);
app_widgets     *widgets;
gboolean        timer_handler(app_widgets *widgets);
void            draw_field();

#endif /*_WINDOW_H_*/
