#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Troppi pochi argomenti\n");
		exit(1);
	}

	printf("Faccio la fork() per creare un figlio...\n");

	int ret = fork();
	if(ret == 0) {
		// sei il figlio
		execl("/bin/ls", "ls", argv[1], NULL);
	}
	if(ret > 0) {
		// sei il padre
	}
	if(ret < 0) {
		perror("Fork fallita");
		exit(1);
	}

	int status;
	wait(&status);
	
	printf("Mio figlio è terminato ");
	printf(WIFEXITED(status) ? "volontariamente " : "involontariamente ");
	printf("con codice %d\n", WEXITSTATUS(status));

	return 0;
}
