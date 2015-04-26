#include "erdp.h"

int main(int argc, char *argv[]) {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *erdp;
	GError *error = NULL;

	char *gladefile = find_gladefile();
	if(gladefile == NULL) {
		printf(".glade file not found. Was the program installed correctly?\n");
		return -1;
	}	
	

	/*get all the objects we need*/
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, gladefile, &error);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	erdp = GTK_WIDGET(gtk_builder_get_object(builder, "erdp"));
	
	/*set the window hint and show it*/
	gtk_window_set_type_hint((GtkWindow*)erdp, GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_widget_show(erdp);

	/*we need to figure out the size of a maximized window for the scaling feature*/
	gtk_window_set_decorated((GtkWindow*)window, FALSE);
	gtk_window_maximize((GtkWindow*)window);
	gtk_widget_set_opacity((GtkWidget*)window, 0.0);
	gtk_widget_set_name((GtkWidget*)window, "maxwin");
	g_signal_connect(G_OBJECT(window), "map-event", G_CALLBACK(maxwin), erdp);
	gtk_widget_show(window);

	/*connect all my signal handlers and unmap my builder*/
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	g_free(gladefile);

	gtk_main();
	return 0;
}

