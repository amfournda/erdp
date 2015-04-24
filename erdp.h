#include <gtk/gtk.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>


char* find_gladefile() {
	/*find where my executable is*/
	char path[PATH_MAX];
	char *end;
	size_t len;
	pid_t pid = getpid();
	snprintf(path, sizeof(path), "/proc/%d/exe", pid);
	if (readlink(path, path, PATH_MAX) == -1)
		perror("readlink");
	/*this is bad and hacky and I should feel bad*/
	len = strlen(path) - strlen("/erdp\0");
	printf("Executable Path: %s\n", path);
	for(;strncmp("/erdp\0", &path[len], strlen("/erdp\0")) != 0;len--){
		path[len+ strlen("/erdp\0")] = '\0';
	};
	path[len] = '\0';
	return g_strconcat(path, "/erdp.glade", NULL);
}
