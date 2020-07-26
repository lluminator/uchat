#include "../inc/uchat.h"

void switch_menu(GtkWidget *wid, t_main *m) {
    char *way = NULL;
    int y;

    (void)wid;
    if (m->menu->flag == 0 && m->set->flag == 0 ) { 
        way = "./source/resource/cancel.png";
        y = 42;
        show_menu(m);
    }
    else {
        way = "./source/resource/burger2.png";
        y = 37;
        if (m->set->flag == 1)
            hide_set(m);
        else
            hide_menu(m);
    }
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file(way);
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, y);
    gtk_widget_show(m->cap->burger_but_img);
}
