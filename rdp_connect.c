#include "rdp_connect.h"

void rdp_connect(GtkButton *connect, gpointer erdp) {
	/*get the string info*/
	GtkEntry *rip = (GtkEntry *) find_child(erdp, "address");
	GtkEntry *ruser = (GtkEntry *) find_child(erdp, "user");
	GtkEntry *rpass = (GtkEntry *) find_child(erdp, "pass");
	GtkCheckButton *fullscreen = (GtkCheckButton *) find_child(erdp, "fullscreen");

	/*format my strings correctly*/
	char *fip = malloc(strlen("/v:")+strlen(gtk_entry_get_text(rip))+1);
	fip = g_strconcat("/v:", gtk_entry_get_text(rip), NULL);
	char *fuser = malloc(strlen("/u:")+strlen(gtk_entry_get_text(ruser))+1);
	fuser = g_strconcat("/u:", gtk_entry_get_text(ruser), NULL);
	char *fpass = malloc(strlen("/p:")+strlen(gtk_entry_get_text(rpass))+1);
	fpass = g_strconcat("/p:", gtk_entry_get_text(rpass), NULL);
	
	/*check what options to add to rdp*/
	char *opts[] = {"/usr/bin/xfreerdp","/cert-ignore", fip, fuser, fpass, NULL};
	int len=5;
	if(gtk_toggle_button_get_active((GtkToggleButton*)fullscreen) == TRUE) {
		opts[len] = realloc(opts[len], sizeof("/f"));
		opts[len] = "/f";
		len++;
		opts[len] = malloc(sizeof(NULL));
		opts[len] = NULL;
	}

	/*and call xfreerdp*/
	int i;
	printf("Calling: ");
	for(i=0;opts[i] != NULL;i++) {
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
