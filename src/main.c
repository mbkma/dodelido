#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#include "window.h"

int main (int argc, char **argv) {
    initialise();

    gtk_init(&argc, &argv);

	setup_window();
    gtk_widget_show(window);
    gtk_main();

    quit();

    return 0;
}
