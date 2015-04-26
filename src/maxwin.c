#include "maxwin.h"

void maxwin(GtkWidget *passedwindow, GdkEvent *event, gpointer erdp) {
	int *width, *height;
	GtkWidget *window = (GtkWidget*) g_object_clone((GObject*)passedwindow);
	//gtk_window_get_size((GtkWindow*) window, width, height);
	printf("Debug\n");
	GtkEntry *ewidth = (GtkEntry *) find_child(erdp, "width");
	GtkEntry *eheight = (GtkEntry *) find_child(erdp, "height");
	char cwidth[sizeof(int)] = {'\0'};
	char cheight[sizeof(int)] = {'\0'};
	//snprintf(cwidth, sizeof(int)-1, "%d", *width);
	//snprintf(cheight, sizeof(int)-1, "%d", *height);
	//gtk_entry_set_text(ewidth, cwidth);
	//gtk_entry_set_text(eheight, cheight);
	gtk_window_close((GtkWindow*)window);
	return;
}
