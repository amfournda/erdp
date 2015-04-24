#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>

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

void add_opt(char* opts[], char* ret[], char* toadd) {
	int len;
	for(len=0;opts[len] != NULL;len++){
		ret[len] = opts[len];
	};
	ret[len] = toadd;
	ret[len+1] = malloc(sizeof(NULL));
	ret[len+1] = NULL;
	return;
}
