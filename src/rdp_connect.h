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

char * find_executable(char *name) {
	char *path = getenv("PATH");
	char *dir;
	for(dir = strtok(path, ":"); dir; dir = strtok(NULL, ":")) {
		if(access(g_strconcat(dir, "/", name, NULL), F_OK) != -1) {
			return g_strconcat(dir, "/", name, NULL);
		}
	}
	return NULL;
}

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

char ** add_opt(char*** optsptr, char* toadd) {
	char ** opts = *optsptr;
	int optslen=0;
	for(optslen=0;opts[optslen] != NULL;optslen++){}
	opts[optslen] = realloc(opts[optslen], strlen(toadd)+1);
	strcpy(opts[optslen], toadd);
	optslen++;
	opts = (char **) realloc(opts, sizeof(char *) * (optslen+1));
	opts[optslen] = NULL;
	return opts;
}

bool check_connect(char* fip, char* fuser, char* fpass) {
	pid_t childpid;
	int retval;
	int pipes[2];
	pipe(pipes);

	char **args = malloc(sizeof(char *));
	args[0] = NULL;
	args = add_opt(&args, find_executable("xfreerdp"));
	args = add_opt(&args, "/auth-only");
	args = add_opt(&args, "/cert-ignore");
	args = add_opt(&args, fip);
	args = add_opt(&args, fuser);
	args = add_opt(&args, fpass);

	childpid = fork();

	if(childpid == 0) {
		/*connect STDOUT to our pipe, so our parent can read the output*/
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		/*child execs freerdp with the auth-only argument*/
		execv("/usr/bin/xfreerdp", args);
		return false;

	}
	/*parent waits for the child to return and checks the retval*/
	wait(&retval);
	char buf[4096];
	memset(buf, '\0', 4096);
	fcntl(pipes[0], F_SETFL, O_NONBLOCK);
	read(pipes[0], buf, sizeof(buf));
	printf("%s", buf);
	int i;
	for(i=0;buf[i] != '\0'; i++) {}
	if(buf[i-2] == '0') {
		return true;
	}
	return false;

}
