#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

extern char *strdup(const char *s1);

GtkWidget* find_child(GtkWidget* parent, const gchar* name) {
	if(g_utf8_collate(gtk_widget_get_name((GtkWidget*)parent), (gchar*)name) == 0) { 
		return parent;
	}
	if(GTK_IS_BIN(parent)) {
		GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
		return find_child(child, name);
	}
	if(GTK_IS_CONTAINER(parent)) {
		GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
		do{
			GtkWidget *widget = find_child((GtkWidget*)children->data, name);
			if(widget != NULL) {
				return widget;
			}
		} while ((children = g_list_next(children)) != NULL);
	}
	return NULL;
}

char ** add_opt(char*** optsptr, char* toadd) {
	char ** opts = *optsptr;
	int optslen=0;
	for(optslen=0;opts[optslen] != NULL;optslen++){}
	opts[optslen] = realloc(opts[optslen], strlen(toadd)+1);
	strcpy(opts[optslen], toadd);
	optslen++;
	opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
	opts[optslen] = NULL;
	return opts;
}

