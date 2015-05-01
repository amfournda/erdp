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

void add_opt(char* opts[], char* ret[], int len, char* toadd) {
	ret = realloc(ret, sizeof(char*)*len);
	int i;
	for(i=0;i < len;len++){
		ret[len] = opts[len];
	};
	return;
}

