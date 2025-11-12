#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

#define NUM_CHILDREN 3

void figlio(int idx) {
	printf("Sono il processo figlio %d\n", idx);
	sleep(1);
	exit(idx);
}

int main() {
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

	for(int i = 0; i < NUM_CHILDREN; i++) {	
		int status;
		wait(&status);
		
		printf("Un figlio è terminato ");
		printf(WIFEXITED(status) ? "volontariamente " : "involontariamente ");
		printf("con exit code %d\n", WEXITSTATUS(status));
	}
}
