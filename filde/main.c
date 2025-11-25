#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define PATH "./file.txt"
#define BUF_SIZE 100

int main() {
	int fd = open(PATH, 0);
	if(fd < 0) {
		perror("Open fallita");
		exit(1);
	}

	int pid = fork();
	if(pid < 0) {
		perror("Fork fallita");
		exit(1);
	}

	if(pid == 0) {
		close(fd);
		int fd = open(PATH, 0);
		if(fd < 0) {
			perror("Open fallita");
			exit(1);
		}
		
		char buf[2];
		if(read(fd, buf, 2) >= 0) {
			printf("Figlio ha letto: %s\n", buf);
		} else {
			perror("Read figlio fallita");
		}
	} else {
		sleep(1);
	
		char buf[BUF_SIZE];
		if(read(fd, buf, BUF_SIZE) >= 0) {
			printf("Padre ha letto: %s\n", buf);
		} else {
			perror("Read padre fallita");
		}
	
		close(fd);
	}

	return 0;
}
