#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define APP_PATH "app"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Troppi pochi argomenti\n");
		exit(1);
	}

	int n = atoi(argv[1]);
	
	int pipe_m_a[2]; // 0 a read, 1 m write
	int pipe_a_m[2]; // 0 m read, 1 a write
	if(pipe(pipe_m_a) < 0 || pipe(pipe_a_m) < 0) {
		perror("Pipe fallita");
		exit(1);
	}

	int pid = fork();
	if(pid < 0) {
		perror("Fork fallita");
		exit(1);
	}

	if(pid == 0) {
		// figlio, prende app
		printf("Sono il figlio, eseguo l'applicazione\n");
		
		// chiudi estremità inutilizzate
		close(pipe_m_a[1]);
		close(pipe_a_m[0]);
		
		// aggancia pipe STDIN
		dup2(pipe_m_a[0], STDIN_FILENO);
		close(pipe_m_a[0]);

		// aggancia pipe STDOUT
		dup2(pipe_a_m[1], STDOUT_FILENO);
		close(pipe_a_m[1]);

		execl(APP_PATH, APP_PATH, NULL);
		perror("Exec fallita");
		exit(1);	
	} else {
		// padre, prende main
		printf("Sono il padre, mi aggancio all'applicazione\n");

		// chiudi estremità inutilizzate
		close(pipe_m_a[0]);
		close(pipe_a_m[1]);
		
		char init_str[100];
		int len = read(pipe_a_m[0], init_str, sizeof(init_str) - 1);
		if(len < 0) {
			perror("Read fallita");
			exit(1);
		}

		init_str[len] = '\0';
		printf("L'applicazione si è presentata con: %s", init_str);
		
		// pilota
		for(int i = 0; i < 4; i++) {
			char n_str[100];
			
			// invia numero
			sprintf(n_str, "%d\n", n);
			if(write(pipe_m_a[1], n_str, strlen(n_str)) < 0) {
				perror("Write fallita");
				exit(1);
			}
			
			// ottieni numero
			len = read(pipe_a_m[0], n_str, sizeof(n_str) - 1);
			if(len < 0) {
				perror("Read fallita");
				exit(1);
			}
			
			n_str[len] = '\0';
			n = atoi(n_str);

			// stampa numero
			printf("Ottenuto: %d\n", n);
		}

		kill(pid, SIGQUIT);
	}

	return 0;
}
