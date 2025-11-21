#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NTHREADS 12
#define ITERS 100000

int cont = 0;

void* thread_routine(void* arg) {
	int num = *(int*) arg;
	free(arg);

	for(int i = 0; i < ITERS; i++) {
		cont++;
		printf("Thread: %d, count: %d\n", num, cont);
	}

	return NULL;
}

int main() {
	pthread_t threads[NTHREADS];

	for(int i = 0; i < NTHREADS; i++) {
		int* arg = (int*) malloc(sizeof(int));
		*arg = i + 1;
		pthread_create(&threads[i], NULL, thread_routine, arg);
	}

	pthread_exit(NULL);

	return 0;
}
