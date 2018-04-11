#include <stdlib.h>
#include <pthread.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

/*

#define NUM_OF_THREADS 5

struct thread_data {
	int id;
	int start;
	int end;
	int *arr;
};

pthread_mutex_t currentlyIdleMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  currentlyIdleCond  = PTHREAD_COND_INITIALIZER;
int currentlyIdle;

pthread_mutex_t workReadyMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  workReadyCond  = PTHREAD_COND_INITIALIZER;
int workReady;

pthread_cond_t  currentlyWorkingCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t currentlyWorkingMutex= PTHREAD_MUTEX_INITIALIZER;
int currentlyWorking;

pthread_mutex_t canFinishMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  canFinishCond  = PTHREAD_COND_INITIALIZER;
int canFinish;

void *processArray(void *args);

int main(int argc, const char * argv[])
{
	int numOfInts = 10;
	int *ints = malloc(numOfInts * sizeof(int));
	for (int i = 0; i < numOfInts; i++) {
		ints[i] = i;
	}
	//   print(ints, numOfInts);

	pthread_t threads[NUM_OF_THREADS];
	struct thread_data thread_data[NUM_OF_THREADS];
	workReady = 0;
	canFinish = 0;
	currentlyIdle = 0;
	currentlyWorking = 0;

	// these vars are used to calculate the index ranges for each thread
	int remainingWork = numOfInts, amountOfWork;
	int startRange, endRange = -1;
	// Create the threads and give each one its data struct.
	for (int i = 0; i < NUM_OF_THREADS; i++) {

		amountOfWork = remainingWork / (NUM_OF_THREADS - i);
		startRange = endRange + 1;
		endRange   = startRange + amountOfWork - 1;

		thread_data[i].id    = i;
		thread_data[i].arr   = ints;
		thread_data[i].start = startRange;
		thread_data[i].end   = endRange;

		pthread_create(&threads[i], NULL, processArray, (void *)&thread_data[i]);
		remainingWork -= amountOfWork;
	}

	int loops = 1111111;
	int expectedStartingValue = ints[0] + loops; // used to validate the results
	// The elements in ints[] should be incremented by 1 in each loop
	while (loops-- != 0) {

		// Make sure all of them are ready
		pthread_mutex_lock(&currentlyIdleMutex);
		while (currentlyIdle != NUM_OF_THREADS) {
			pthread_cond_wait(&currentlyIdleCond, &currentlyIdleMutex);
		}
		pthread_mutex_unlock(&currentlyIdleMutex);

		// All threads are now blocked; it's safe to not lock the mutex.
		// Prevent them from finishing before authorized.
		canFinish = 0;
		// Reset the number of currentlyWorking threads
		currentlyWorking = NUM_OF_THREADS;

		// Signal to the threads to start
		pthread_mutex_lock(&workReadyMutex);
		workReady = 1;
		pthread_cond_broadcast(&workReadyCond );
		pthread_mutex_unlock(&workReadyMutex);      

		// Wait for them to finish
		pthread_mutex_lock(&currentlyWorkingMutex);
		while (currentlyWorking != 0) {
			pthread_cond_wait(&currentlyWorkingCond, &currentlyWorkingMutex);
		}
		pthread_mutex_unlock(&currentlyWorkingMutex);

		// The threads are now waiting for permission to finish
		// Prevent them from starting again
		workReady = 0;
		currentlyIdle = 0;

		// Allow them to finish
		pthread_mutex_lock(&canFinishMutex);
		canFinish = 1;
		pthread_cond_broadcast(&canFinishCond);
		pthread_mutex_unlock(&canFinishMutex);
	}

	//   print(ints, numOfInts);

	// clean up
	for (int i = 0; i < NUM_OF_THREADS; i++) {
		pthread_cancel(threads[i]);
	}
	free(ints);

	return 0;
}

void *processArray(void *args)
{
	struct thread_data *data = (struct thread_data *)args;
	int *arr  = data->arr;
	int start = data->start;
	int end   = data->end;

	while (1) {

		// Set yourself as idle and signal to the main thread, when all threads are idle main will start
		pthread_mutex_lock(&currentlyIdleMutex);
		currentlyIdle++;
		pthread_cond_signal(&currentlyIdleCond);
		pthread_mutex_unlock(&currentlyIdleMutex);

		// wait for work from main
		pthread_mutex_lock(&workReadyMutex);
		while (!workReady) {
			pthread_cond_wait(&workReadyCond , &workReadyMutex);
		}
		pthread_mutex_unlock(&workReadyMutex);

		// Do the work
	/*
			do the work

*/
		// mark yourself as finished and signal to main
/*		pthread_mutex_lock(&currentlyWorkingMutex);
		currentlyWorking--;
		pthread_cond_signal(&currentlyWorkingCond);
		pthread_mutex_unlock(&currentlyWorkingMutex);

		// Wait for permission to finish
		pthread_mutex_lock(&canFinishMutex);
		while (!canFinish) {
			pthread_cond_wait(&canFinishCond , &canFinishMutex);
		}
		pthread_mutex_unlock(&canFinishMutex);
	}

	pthread_exit(NULL);
}


void print(int *ints, int n)
{
	printf("[");
	for (int i = 0; i < n; i++) {
		printf("%d", ints[i]);
		if (i+1 != n)
			printf(", ");
	}
	printf("]\n");
}

*/
