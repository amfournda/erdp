#include <gtk/gtk.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>


char* find_gladefile() {
	/*find where my executable is*/
	char path[PATH_MAX];
	char *gladename = "/erdp.glade";
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

	/*if the gladefile exists in the same directory as my executable, use it*/
	if(access(g_strconcat(path, gladename, NULL), R_OK) != -1) {
		return g_strconcat(path, gladename, NULL);
	}

	/*if it doesn't exist there, check in my path plus share/ */
	if(access(g_strconcat(path, "/share", gladename, NULL), R_OK) != -1) {
		return g_strconcat(path, "/share", gladename, NULL);
	}
	
	/*if it doesn't exist there, check in /usr/share/erdp/ */
	if(access(g_strconcat("/usr/share/erdp", gladename, NULL), R_OK) != -1) {
		return g_strconcat("/usr/share/erdp", gladename, NULL);
	}

	/*maybe /usr/local/ */
	if(access(g_strconcat("/usr/local/share/erdp", gladename, NULL), R_OK) != -1) {
		return g_strconcat("/usr/local/share/erdp", gladename, NULL);
	}

	/* I give up. Return NULL */
	return NULL;
}

