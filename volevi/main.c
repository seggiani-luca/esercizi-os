#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void int_handler(int sig) {
	printf("Eh volevi!\n");
}

int main() {
	signal(SIGINT, int_handler);

	while(1) {
		printf("Sono il processo\n");
		sleep(1);
	}
}
