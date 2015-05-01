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
	
	/*check what options to add to rdp from the options tickboxes*/
	int optslen = 4;
	char **opts = malloc(optslen * sizeof(char*));
	opts[0] = "/usr/bin/xfreerdp";
	opts[1] = "+cert-ignore";
	opts[2] = fip;
	opts[3] = fuser;
	opts[4] = fpass;

	if(gtk_toggle_button_get_active((GtkToggleButton*)fullscreen) == TRUE) {
		optslen++;
		opts[optslen] = "/f";
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)decorations) == TRUE) {
		optslen++;
		opts[optslen] = "/disp";
		optslen++;
		opts[optslen] = "/fonts";
		optslen++;
		opts[optslen] = "/aero";
		optslen++;
		opts[optslen] = "/window-drag";
		optslen++;
		opts[optslen] = "/menu-anims";
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)smartscaling) == TRUE) {
		GdkRectangle *workarea = g_new(GdkRectangle, 1);
		GdkScreen *screen = gdk_screen_get_default();
		gint monitor = gdk_screen_get_primary_monitor(screen);
		gdk_screen_get_monitor_workarea(screen, monitor, workarea);
		int width = workarea->width*1.0;
		int height = workarea->height*0.95;
		char sizebuff[32];
		snprintf(sizebuff, 31, "/size:%dx%d", width, height);
		optslen++;
		opts[optslen] = sizebuff;
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)sound) == TRUE) {
		optslen++;
		opts[optslen] = "/sound";
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)clipboard) == TRUE) {
		optslen++;
		opts[optslen] = "/clipboard";
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)homedir) == TRUE) {
		optslen++;
		opts[optslen] = "/home-drive";
	}
	

	/* Add the trailing NULL */
	optslen++;
	opts[optslen] = NULL;


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
