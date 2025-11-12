#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>

#define NUM_CHILDREN 3

void parent_handler(int sig) {
	// ignora
}

void child_handler(int sig) {
	printf("Sono il figlio %d ho ricevuto il segnale %d e termino\n", getpid(), sig);
	exit(1);
}

void figlio(int idx) {
	printf("Sono il processo figlio %d ", idx);
	if(idx == 0) {
		printf(" e mi blocco subito\n");
		exit(0);
	}
	
	printf(" e mi metto in attesa della SIGUSR\n");
	signal(SIGUSR1, child_handler);

	while(1) sleep(1);
}

int main() {
	signal(SIGUSR1, parent_handler);
	
	for(int i = 0; i < NUM_CHILDREN; i++) {	
		int ret = fork();
		if(ret == 0) {
			// sei il figlio
			figlio(i);
		}
		if(ret > 0) {
			// sei il padre
		}
		if(ret < 0) {
			perror("Fork fallita");
			exit(1);
		}
	}

	sleep(3);
	kill(0, SIGUSR1);

	for(int i = 0; i < NUM_CHILDREN; i++) {	
		int status;
		wait(&status);
		
		printf("Un figlio è terminato ");
		printf(WIFEXITED(status) ? "volontariamente " : "involontariamente ");
		printf("con exit code %d\n", WEXITSTATUS(status));
	}
}
