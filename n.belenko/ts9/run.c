#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>


int main() {
	const char *filename = "text.txt";
	pid_t p = fork();

	if (p < 0) {
		perror("> fork error");
		return 1;
	} 
	else if (!p) {
		execlp ("cat", "cat", filename, (char *)NULL);
		perror ("> execlp error");
		exit(1);
	} 
	else {
		printf ("child procces | %d | created\n", p);
		waitpid (p, NULL, 0);
		printf ("child procces | %d | killed \n", p);
	}

	return 0;
}
