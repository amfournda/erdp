#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char *strdup(const char *s1);

/* find_executable takes a string as its first argument
 * find_executable returns a string that is the full path of the executable in the user's $PATH that matches the name given in the first argument
 */
char * find_executable(char *name) {
	char *path = strdup(getenv("PATH"));
	char *dir;
	for(dir = strtok(path, ":"); dir != NULL; dir = strtok(NULL, ":")) {
		if(access(g_strconcat(dir, "/", name, NULL), F_OK) != -1) {
			return g_strconcat(dir, "/", name, NULL);
		}
	}
	return NULL;
}

/* find_child takes a GtkWidget as its first argument and a string as it's second argument.
 * find_child returns a GtkWidget that is a child of the first argument AND has a name that matches the string in the second argument
 * In essence, this can be used to find a widget by name and you should pretty much always pass the root GtkWidget as it's first argument
 */
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


/* add_opt takes a pointer to a pointer to an array of strings as its first argument and a string as its second argument.
 * add_opt returns a pointer to an array of strings that contains all of the original strings of the first argument, plus the string pointed to by the second argument
 * In essence, this appends the string in toadd to the end of the array optsptr
 */
char ** add_opt(char*** optsptr, char* toadd) {
	char ** opts = *optsptr;
	if(toadd == NULL) {
		return opts;
	}
	int optslen=0;
	for(optslen=0;opts[optslen] != NULL;optslen++){}
	opts[optslen] = realloc(opts[optslen], strlen(toadd)+1);
	strcpy(opts[optslen], toadd);
	optslen++;
	opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
	opts[optslen] = NULL;
	return opts;
}

/* check_connect takes the properly formatted address, username, and password arguments for xfreerdp as arguments
 * check_connect returns true only if the connection to the address given suceeds AND the username and password are valid
 * In essence, this function can be used to check if an rdp connection will succeed
 */
bool check_connect(char* erdp, char* fip, char* fuser, char* fpass) {
	int i;
	pid_t childpid;
	int retval;
	int pipes[2];
	pipe(pipes);

	char **args = malloc(sizeof(char *));
	args[0] = NULL;
	args = add_opt(&args, "");
	args = add_opt(&args, "/auth-only");
	args = add_opt(&args, "/cert-ignore");
	args = add_opt(&args, fip);
	args = add_opt(&args, fuser);
	args = add_opt(&args, fpass);

	printf("Checking connection with: %s ", erdp);
	for(i=0;args[i] != NULL;i++) {
		if(strncmp(args[i], "/p:", 3) == 0) {
			printf("/p:**** ");
			continue;
		}
		printf("%s ", args[i]);
	}
	printf("\n");

	childpid = fork();
	if(childpid == 0) {
		/*child execs freerdp with the auth-only argument*/
		execvp(erdp, args);
		return false;

	}
	/*parent waits for the child to return and checks the return value*/
	wait(&retval);
	printf("\nRetval: %d\n", retval);
	if(retval == 0) {
		return true;
	}
	return false;

}
