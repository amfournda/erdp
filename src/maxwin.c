#include <gtk/gtk.h>

extern GtkWidget* find_child(GtkWidget* parent, const gchar* name);

void maxwin(GtkWidget *window, GdkEvent *event, gpointer erdp) {
	int *width, *height;
	gtk_window_get_size((GtkWindow*)window, width, height);
	GtkEntry *ewidth = (GtkEntry *) find_child(erdp, "width");
	GtkEntry *eheight = (GtkEntry *) find_child(erdp, "height");
	char cwidth[sizeof(int)] = {'\0'};
	char cheight[sizeof(int)] = {'\0'};
	snprintf(cwidth, sizeof(int)-1, "%d", *width);
	snprintf(cheight, sizeof(int)-1, "%d", *height);
	gtk_entry_set_text(ewidth, cwidth);
	gtk_entry_set_text(eheight, cheight);
	gtk_widget_destroy(window);
	printf("Debug\n");	
	return;
}
