#include "erdp.h"

int main(int argc, char *argv[]) {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *erdp;
	GError *error = NULL;

	/*find where my executable is*/
	char path[PATH_MAX];
	char *end;
	size_t len;
	pid_t pid = getpid();
	snprintf(path, sizeof(path), "/proc/%d/exe", pid);
	if (readlink(path, path, PATH_MAX) == -1)
		perror("readlink");
	/*this is bad and hacky and I should feel bad*/
	len = strlen(path) - strlen("/erdp\0");
	printf("Executable Path: %s\n", path);
	for(;strncmp("/erdp\0", &path[len], strlen("/erdp\0")) != 0;len--){
		path[len+ strlen("/erdp\0")] = '\0';
	};
	path[len] = '\0';
	char *gladefile = g_strconcat(path, "/erdp.glade", NULL);
	printf("Gladefile Path: %s\n", gladefile);

	/*get all the objects we need*/
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, gladefile, &error);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	erdp = GTK_WIDGET(gtk_builder_get_object(builder, "erdp"));
	
	/*connect all my signal handlers and unmap my builder*/
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	g_free(gladefile);


	/*set the window hint and show it*/
	gtk_window_set_type_hint((GtkWindow*)erdp, GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_widget_show(erdp);

	gtk_main();
	return 0;
}

