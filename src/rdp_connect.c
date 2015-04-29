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
	char *opts[] = {"/usr/bin/xfreerdp","+cert-ignore", fip, fuser, fpass, NULL};
	if(gtk_toggle_button_get_active((GtkToggleButton*)fullscreen) == TRUE) {
		add_opt(opts, opts, "/f");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)decorations) == TRUE) {
		add_opt(opts, opts, "/disp");
		add_opt(opts, opts, "/aero");
		add_opt(opts, opts, "/menu-anims");
		add_opt(opts, opts, "/fonts");
		add_opt(opts, opts, "/window-drag");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)smartscaling) == TRUE) {
		GdkRectangle *workarea = g_new(GdkRectangle, 1);
		workarea->width = 1024;
		workarea->height = 768;
		GdkScreen *screen = gdk_screen_get_default();
		gdk_screen_get_monitor_workarea(screen, 0, workarea);
		char width[sizeof(int)*8+1] = "\0";
		snprintf(width, sizeof(int)*9, "%d", workarea->width);
		char height[sizeof(int)*8+1] = "\0"; 
		snprintf(height, sizeof(int)*9, "%d", workarea->height);
		char buff2[sizeof(int)*18] = "\0";
		snprintf(buff2, sizeof(int)*18, "/size:%sx%s\0", width, height);
		add_opt(opts, opts, buff2);
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)sound) == TRUE) {
		add_opt(opts, opts, "/sound");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)clipboard) == TRUE) {
		add_opt(opts, opts, "/clipboard");
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)homedir) == TRUE) {
		add_opt(opts, opts, "/home-drive");
	}

	/*add user specified options*/
	char *temp = strdup(gtk_entry_get_text(arguments));
	char *buff = strtok(temp, " ");
	while (buff != NULL) {
		add_opt(opts, opts, buff);
		buff = strtok(NULL, " ");
	}

	/*and call xfreerdp*/
	int i;
	printf("Calling: ");
	for(i=0;opts[i] != NULL;i++) {
		if(opts[i][0] == '/' && opts[i][1] == 'p' && opts[i][2] == ':') {
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
