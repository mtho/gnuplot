#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

main() {
	int in[2], out[2];
	pid_t pid;
	char plot[64];
	
	// Create the pipe
	if(pipe (in)) {
		fprintf (stderr, "Pipe failed.\n");
		return EXIT_FAILURE;
	}
	if(pipe (out)) {
		fprintf (stderr, "Pipe failes.\n");
		return EXIT_FAILURE;
	}

	pid = fork();
	if(pid == 0) {
		dup2(in[0],0);
		close(in[0]);
		close(in[1]);

		dup2(out[1],1);
		close(out[0]);
		close(out[1]);

		printf("\nChild created..\n");
		execlp("gnuplot", "-persist", NULL);
		return EXIT_SUCCESS;
	} else if (pid < 0) {
		exit(1);
	} else {
		printf("Parent process executing..\n");	
		fgets(plot, 64, stdin);
		write(in[1], plot,128);
		return;
	}
}
