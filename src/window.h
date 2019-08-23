#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "engine.h"

GtkBuilder	*builder; 
GtkWidget	*window;
GtkWidget	*g_lbl_field;
GtkWidget	*g_lbl_count;

void setup_window(void);
void on_window_main_destroy(void);
void on_btn_next_clicked(void);

#endif /*_WINDOW_H_*/
