#include "../inc/uchat.h"

void log_enter_notify_event(GtkWidget *widget, GdkEventButton *event, t_wid *wid)
{	
	if(gtk_widget_is_visible (wid->sig->sig_gif))
		gtk_widget_hide(wid->sig->sig_gif);
	if (wid->sig->flagimg == 1)
		gtk_widget_hide(wid->sig->sig_display);
	gtk_widget_show(wid->log->log_gif);
}
