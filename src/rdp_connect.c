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
	int optslen = 5;
	char **opts = malloc(optslen * sizeof(char*));
	opts[0] = malloc(sizeof(char) * (strlen("/usr/bin/xfreerdp")+1));
	strcpy(opts[0], "/usr/bin/xfreerdp");
	opts[1] = malloc(sizeof(char) * (strlen("/cert-ignore")+1));
	strcpy(opts[1], "/cert-ignore");
	opts[2] = malloc(sizeof(char) * (strlen(fip)+1));
	strcpy(opts[2], fip);
	opts[3] = malloc(sizeof(char) * (strlen(fuser)+1));
	strcpy(opts[3], fuser);
	opts[4] = malloc(sizeof(char) * (strlen(fpass)+1));
	strcpy(opts[4], fpass);
	
	if(gtk_toggle_button_get_active((GtkToggleButton*)fullscreen) == TRUE) {
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/f")+1));
		strcpy(opts[optslen], "/f");
		optslen++;
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)decorations) == TRUE) {
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/disp")+1));
		strcpy(opts[optslen], "/disp");
		optslen++;
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/fonts")+1));
		strcpy(opts[optslen], "/fonts");
		optslen++;
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/aero")+1));
		strcpy(opts[optslen], "/aero");
		optslen++;
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/window-drag")+1));
		strcpy(opts[optslen], "/window-drag");
		optslen++;
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/menu-anims")+1));
		strcpy(opts[optslen], "/menu-anims");
		optslen++;
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
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen(sizebuff)+1));
		strcpy(opts[optslen], sizebuff);
		optslen++;
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)sound) == TRUE) {
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/sound")+1));
		strcpy(opts[optslen], "/sound");
		optslen++;
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)clipboard) == TRUE) {
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/clipboard")+1));
		strcpy(opts[optslen], "/clipboard");
		optslen++;
	}
	if(gtk_toggle_button_get_active((GtkToggleButton*)homedir) == TRUE) {
		opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
		opts[optslen] = malloc(sizeof(char) * (strlen("/home-drive")+1));
		strcpy(opts[optslen], "/home-drive");
		optslen++;
	}
	

	/* Add the trailing NULL */
	opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
	opts[optslen] = malloc(sizeof(NULL));
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
