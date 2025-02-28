// Author: Tu Le
// CS4760 Project 2
// Date: 2/27/2025

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>

// Struct for the clock
typedef struct {
	int seconds;
	int nanoseconds;
} SimulatedClock;

int main(int argc, char **argv( {
	//

	// Shared memory here
	key_t key = 1234;
	int shmid;
	SimulatedClock *clock;

	// Created shared memory segment
	shmid = shmget(key, sizeof(SimulatedClock), IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("shmget");
		exit(1);
	}

	// Attach shared memory segment
	clock = (SimulatedClock *)shmat(shmid, NULL, 0);
	if (clock == (SimulatedClock *) -1) {
		perror("shmat");
		exit(1);
	}

	// Create clock
	clock->seconds = 0;
	clock->nanoseconds = 0;

	//Detach shared memory when done
	shmdt(clock);

	// Clean up the shared memory segment
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
