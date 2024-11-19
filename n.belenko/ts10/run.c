#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
		return 1;
	}

	pid_t p = fork();

	if (p < 0) {
		perror("> fork error");
		return 1;
	} else if (p == 0) {
		execvp(argv[1], &argv[1]);
		perror("> execlp error");
		exit(1);
	} else {
		int status;
		if (waitpid(p, &status, 0) == -1) {
			perror("> waitp error");
			return 1;
		}

		if (WIFEXITED(status)) {
			printf("child process exit code: %d\n", WEXITSTATUS(status));
		} else {
			printf("---- killed ok ----\n");
		}
	}

	return 0;
}
