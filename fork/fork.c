#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EX_CODE 44 / 6 + 2 

int main() {
	pid_t pid = fork();
	if(pid < 0) {
		perror("fork");
		exit(1);
	}

	if(pid == 0) {
		printf("Sono %d, figlio del processo %d\n", getpid(), getppid());
		exit(EX_CODE);
	} else {
		printf("Sono il padre, il PID di mio figlio e': %d\n", pid);	
		
		int status;
		wait(&status);
		printf("Mio figlio e' morto... exit code: %d\n", WEXITSTATUS(status));
	}

	return 0;
}
