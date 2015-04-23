#include <gtk/gtk.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *erdp;
	GError *error = NULL;

	/*find where my executable is*/
	char path[PATH_MAX];
	size_t len;
	pid_t pid = getpid();
	sprintf(path, "/proc/%d/exe", pid);
	if (readlink(path, path, PATH_MAX) == -1)
		perror("readlink");
	/*this is bad and hacky and I should feel bad*/
	len = strlen(path) - 5;
	printf("Gladefile Path: %s\n", path);
	int i=0;
	for(i=len;path[i] != '/';i--);
	path[i+1] = '\0';
	char *gladefile = malloc(strlen(path)+strlen("erdp.glade"));
	gladefile = g_strconcat(path, "erdp.glade", NULL);
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
	free(gladefile);


	/*set the window hint and show it*/
	gtk_window_set_type_hint((GtkWindow*)erdp, GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_widget_show(erdp);

	gtk_main();
	return 0;
}

