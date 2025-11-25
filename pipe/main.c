#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* mess = "Ciao figlio!";

int main() {
	int pipefd[2]; // figlio: 0, padre: 1

	if(pipe(pipefd) < 0) {
		perror("Pipe fallita");
		exit(1);
	}

	int pid = fork();
	if(fork < 0) {
		perror("Fork fallita");
		exit(1);
	}

	if(pid == 0) {
		// figlio
		close(pipefd[1]);
		
		char buf[20];
		int len = read(pipefd[0], buf, sizeof(buf) - 1);
		if(len < 0) {
			perror("Read fallita");
			exit(1);
		}
		buf[len] = '\0';

		printf("%s\n", buf);

		close(pipefd[0]);
	} else {
		// padre
		close(pipefd[0]);
		
		sleep(1);
		if(write(pipefd[1], mess, strlen(mess)) < 0) {
			perror("Write fallita");
			exit(1);
		}

		close(pipefd[1]);
	}

	return 0;
}
