#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int sig) {
	// do nothing
}

int my_sleep(int secs) {
	// installa segnale
	__sighandler_t prev = signal(SIGALRM, alarm_handler);
	
	alarm(secs);
	int ret = pause();
	
	// rimuovi segnale
	signal(SIGALRM, prev);

	return ret;
}

int main() {
	int ret = my_sleep(1);
	
	printf("Buongiorno! pause() ha ritornato %d\n", ret);
}
