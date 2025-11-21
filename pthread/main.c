#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NTHREADS 4

pthread_t father;

void* thread_routine(void* arg) {
	int num_arg = *(int*) arg;
	free(arg);

	for(int i = 0; i < 4; i++) {
		printf("Sono il thread %d\n", num_arg);
		sleep(num_arg);
	}

	return NULL;
}

int main() {
	pthread_t threads[NTHREADS];
	father = pthread_self();

	for(int i = 0; i < NTHREADS; i++) {
		int* arg = (int*) malloc(sizeof(int));
		*arg = i + 1; 
		pthread_create(&threads[i], NULL, thread_routine, arg);
	}

	pthread_exit(NULL);

	return 0;
}
