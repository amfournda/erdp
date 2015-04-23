#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

GtkWidget* find_child(GtkWidget* parent, const gchar* name) {
	if (g_strcasecmp(gtk_widget_get_name((GtkWidget*)parent), (gchar*)name) == 0) { 
		return parent;
	}
	if (GTK_IS_BIN(parent)) {
		GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
		return find_child(child, name);
	}
	if (GTK_IS_CONTAINER(parent)) {
		GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
		while ((children = g_list_next(children)) != NULL) {
			GtkWidget* widget = find_child(children->data, name);
			if (widget != NULL) {
				return widget;
			}
		}
	}
	return NULL;
}

void rdp_connect(GtkButton *connect, gpointer erdp) {
	/*get the string info*/
	GtkEntry *rip = (GtkEntry *) find_child(erdp, "address");
	GtkEntry *ruser = (GtkEntry *) find_child(erdp, "user");
	GtkEntry *rpass = (GtkEntry *) find_child(erdp, "pass");

	/*and call xfreerdp*/
	//execl("/usr/bin/xfreerdp", "/cert-ignore", fip, fuser, fpass, NULL);
	/*code never gets here*/
	return;
}

void cancel() {
	gtk_main_quit();
	return;
}
