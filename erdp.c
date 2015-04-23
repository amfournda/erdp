#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *erdp;
	GError *error = NULL;

	/*get all the objects we need*/
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "erdp.glade", &error);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	erdp = GTK_WIDGET(gtk_builder_get_object(builder, "erdp"));
	
	/*connect all my signal handlers and unmap my builder*/
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));


	/*set the window hint and show it*/
	gtk_window_set_type_hint((GtkWindow*)erdp, GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_widget_show(erdp);

	gtk_main();
	return 0;
}

