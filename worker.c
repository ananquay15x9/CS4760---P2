// Author: Tu Le
// CS4760 Project 2
// Date: 3/1/2025

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

//Struct for the clock
typedef struct {
	int seconds;
	int nanoseconds;
} SimulatedClock;

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <max_seconds> <max_nanoseconds>\n", argv[0]);
		exit(1);
	}

	//Get command-line arguments
	int max_seconds = atoi(argv[1]);
	int max_nanoseconds = atoi(argv[2]);

	//Shared memory setup
	key_t key = ftok("oss.c", 1); //Use the same key as oss.c
	if (key == -1) {
		perror("ftok");
		exit(1);
	}

	int shmid = shmget(key, sizeof(SimulatedClock), IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("shmget");
		exit(1);
	}

	SimulatedClock *simClock = (SimulatedClock *)shmat(shmid, NULL, 0);
	if (simClock == (SimulatedClock *) -1) {
		perror("shmat");
		exit(1);
	}

	//Calculate the termination time
	int termination_seconds = simClock->seconds + max_seconds;
	int termination_nanoseconds = simClock->nanoseconds + max_nanoseconds;
	if (termination_nanoseconds >= 1000000000) {
		termination_seconds += 1;
		termination_nanoseconds -= 1000000000;
	}

	//Print initial message
	printf("WORKER PID: %d PPID: %d SysClockS: %d SysclockNano: %d TermTimeS: %d TermTimeNano: %d\n", getpid(), getppid(), simClock->seconds, simClock->nanoseconds, termination_seconds, termination_nanoseconds);
	printf("--Just Starting\n");

	int last_output_seconds = simClock->seconds;

	//Main loop
	while (1) {
	//check termination
		if (simClock->seconds > termination_seconds || (simClock->seconds == termination_seconds && simClock->nanoseconds >= termination_nanoseconds)) {
			printf("WORKER PID: %d PPID: %d SysClockS: %d SysclockNano: %d TermTimeS: %d TermTimeNano: %d\n", getpid(), getppid(), simClock->seconds, simClock->nanoseconds, termination_seconds, termination_nanoseconds);
			printf("--Terminating\n");
			break; //exit the loop
		}

		//periodic output
		if (simClock->seconds > last_output_seconds) {
			printf("WORKER PID: %d PPID: %d SysClockS: %d SysclockNano: %d TermTimeS: %d TermTimeNano: %d\n", getpid(), getppid(), simClock->seconds, simClock->nanoseconds, termination_seconds, termination_nanoseconds);
			printf("--%d seconds have passed since starting\n", simClock->seconds - last_output_seconds);
			last_output_seconds = simClock->seconds;
			fflush(stdout); //Flush output
		}
		//Print clock values
		//printf("Worker Clock: %d seconds, %d nanoseconds\n", simClock->seconds, simClock->nanoseconds);
	}

	//Detach shared memoryh
	shmdt(simClock);
	
	return 0;
}
