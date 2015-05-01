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
	char *fip = malloc(strlen("/v:")+strlen(gtk_entry_get_text(rip))+1);
	fip = g_strconcat("/v:", gtk_entry_get_text(rip), NULL);
	char *fuser = malloc(strlen("/u:")+strlen(gtk_entry_get_text(ruser))+1);
	fuser = g_strconcat("/u:", gtk_entry_get_text(ruser), NULL);
	char *fpass = malloc(strlen("/p:")+strlen(gtk_entry_get_text(rpass))+1);
	fpass = g_strconcat("/p:", gtk_entry_get_text(rpass), NULL);
	
	/*check what options to add to rdp from the options tickboxes*/
	char *opts[] = {"/usr/bin/xfreerdp","+cert-ignore", fip, fuser, fpass};
	opts[5] = malloc(sizeof(char*));
	opts[5] = NULL;
	char *buff = malloc(sizeof(char)*FILENAME_MAX);
	if(gtk_toggle_button_get_active((GtkToggleButton*)fullscreen) == TRUE) {
		buff = "/f";
		add_opt(opts, opts, strlen(buff), buff);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)decorations) == TRUE) {
		buff = "/disp";
		add_opt(opts, opts, strlen(buff), buff);
		buff = "/aero";
		add_opt(opts, opts, strlen(buff), buff);
		buff = "/menu-anims";
		add_opt(opts, opts, strlen(buff), buff);
		buff = "/fonts";
		add_opt(opts, opts, strlen(buff), buff);
		buff = "/window-drag";
		add_opt(opts, opts, strlen(buff), buff);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)smartscaling) == TRUE) {
		GdkRectangle *workarea = g_new(GdkRectangle, 1);
		workarea->width = 1024;
		workarea->height = 768;
		GdkScreen *screen = gdk_screen_get_default();
		gdk_screen_get_monitor_workarea(screen, gdk_screen_get_primary_monitor(screen), workarea);
		char width[10] = "\0";
		snprintf(width, 9, "%d", workarea->width);
		char height[10] = "\0"; 
		snprintf(height, 9, "%d", workarea->height);
		snprintf(buff, 31, "/size:%sx%s", width, height);
		add_opt(opts, opts, strlen(buff), buff);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)sound) == TRUE) {
		buff = "/sound";
		add_opt(opts, opts, strlen(buff), buff);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)clipboard) == TRUE) {
		buff = "/clipboard";
		add_opt(opts, opts, strlen(buff), buff);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)homedir) == TRUE) {
		buff = "/home-drive";
		add_opt(opts, opts, strlen(buff), buff);
	}

	/*add user specified options*/
	char *temp = strdup(gtk_entry_get_text(arguments));
	buff = strtok(temp, " ");
	while (buff != NULL) {
		add_opt(opts, opts, strlen(buff), buff);
		buff = strtok(NULL, " ");
	}
	g_free(temp);

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
