#include "rdp_connect.h"

void rdp_connect(GtkButton *connect, gpointer erdp) {
	/*get the string info*/
	GtkEntry *rip = (GtkEntry *) find_child(erdp, "address");
	GtkEntry *ruser = (GtkEntry *) find_child(erdp, "user");
	GtkEntry *rpass = (GtkEntry *) find_child(erdp, "pass");
	GtkEntry *arguments = (GtkEntry *) find_child(erdp, "arguments");
	GtkCheckButton *fullscreen = (GtkCheckButton *) find_child(erdp, "fullscreen");
	GtkCheckButton *decorations = (GtkCheckButton *) find_child(erdp, "decorations");
	GtkCheckButton *smartscaling = (GtkCheckButton *) find_child(erdp, "smartscaling");
	GtkCheckButton *sound = (GtkCheckButton *) find_child(erdp, "sound");
	GtkCheckButton *clipboard = (GtkCheckButton *) find_child(erdp, "clipboard");
	GtkCheckButton *homedir = (GtkCheckButton *) find_child(erdp, "homedir");

	/*format my strings correctly*/
	char *fip = g_strconcat("/v:", gtk_entry_get_text(rip), NULL);
	char *fuser = g_strconcat("/u:", gtk_entry_get_text(ruser), NULL);
	char *fpass = g_strconcat("/p:", gtk_entry_get_text(rpass), NULL);

	/*check to see if the connection is valid*/
	if(check_connect(fip, fuser, fpass) != TRUE) {
		return;
	}
	
	/*check what options to add to rdp from the options tickboxes*/
	char **opts = malloc(sizeof(char *));
	opts[0] = NULL;
	opts = add_opt(&opts, "/usr/bin/xfreerdp");
	opts = add_opt(&opts, "/cert-ignore");
	opts = add_opt(&opts, fip);
	opts = add_opt(&opts, fuser);
	opts = add_opt(&opts, fpass);
	
	if(gtk_toggle_button_get_active((GtkToggleButton*)fullscreen) == TRUE) {
		opts = add_opt(&opts, "/f");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)decorations) == TRUE) {
		opts = add_opt(&opts, "/disp");
		opts = add_opt(&opts, "/fonts");
		opts = add_opt(&opts, "/aero");
		opts = add_opt(&opts, "/window-drag");
		opts = add_opt(&opts, "/menu-anims");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)smartscaling) == TRUE) {
		GdkRectangle *workarea = g_new(GdkRectangle, 1);
		GdkScreen *screen = gdk_screen_get_default();
		gint monitor = gdk_screen_get_primary_monitor(screen);
		gdk_screen_get_monitor_workarea(screen, monitor, workarea);
		int width = workarea->width;
		int height = workarea->height;
		char sizebuff[32];
		snprintf(sizebuff, 31, "/size:%dx%d", width, height);
		opts = add_opt(&opts, sizebuff);
		snprintf(sizebuff, 31, "/smart-sizing:%dx%d", width, height);
		opts = add_opt(&opts, sizebuff);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)sound) == TRUE) {
		opts = add_opt(&opts, "/sound");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)clipboard) == TRUE) {
		opts = add_opt(&opts, "/clipboard");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)homedir) == TRUE) {
		opts = add_opt(&opts, "/home-drive");
	}

	/* add the user specified options. We do no error checking */
	char *argtext = strdup(gtk_entry_get_text(arguments));
	char *argbuff = strtok(argtext, " ");
	while(argbuff != NULL) {
		opts = add_opt(&opts, argbuff);
		strtok(NULL, " ");
	}

	/*and call xfreerdp*/
	int i;
	printf("Calling: ");
	for(i=0;opts[i] != NULL;i++) {
		if(strncmp(opts[i], "/p:", 3) == 0) {
			printf("/p:**** ");
			continue;
		}
		printf("%s ", opts[i]);
	}
	printf("\n");
	execv("/usr/bin/xfreerdp", opts);
	/*code never gets here*/
	return;
}

void cancel() {
	gtk_main_quit();
	return;
}
