#include <pthread.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NTHREADS 12
#define ITERS 100000

int cont = 0;
pthread_mutex_t mutex;

void* thread_routine(void* arg) {
	int num = *(int*) arg;
	free(arg);

	for(int i = 0; i < ITERS; i++) {
		pthread_mutex_lock(&mutex);
		cont++;
		printf("Thread: %d, count: %d\n", num, cont);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main() {
	pthread_mutex_init(&mutex, NULL);

	pthread_t threads[NTHREADS];

	for(int i = 0; i < NTHREADS; i++) {
		int* arg = (int*) malloc(sizeof(int));
		*arg = i + 1;
		pthread_create(&threads[i], NULL, thread_routine, arg);
	}

	pthread_exit(NULL);

	return 0;
}
