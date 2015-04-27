#include "maxwin.h"

void maxwin(GtkWidget *window, GdkEvent *event, gpointer erdp) {
	/* Get the size of the workarea in the user's desktop */
	int *width, *height;
	gtk_window_get_size((GtkWindow*) window, width, height);
	GtkEntry *ewidth = (GtkEntry *) find_child(erdp, "width");
	GtkEntry *eheight = (GtkEntry *) find_child(erdp, "height");
	GtkCheckButton *smartscaling = (GtkCheckButton*) find_child(erdp, "smartscaling");
	gtk_toggle_button_set_active((GtkToggleButton*)smartscaling, TRUE);
	char cwidth[numPlaces(*width)+2];
	char cheight[numPlaces(*height)+2];
	snprintf(cwidth, numPlaces(*width)+2, "%d", *width);
	snprintf(cheight, numPlaces(*height)+2, "%d", *height);

	/* and set the appropriate option boxes to their values */
	gtk_entry_set_text(ewidth, cwidth);
	gtk_entry_set_text(eheight, cheight);
	gtk_window_close((GtkWindow*)window);
	return;
}
