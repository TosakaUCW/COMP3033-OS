#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

#include <semaphore.h>

#define TRUE 1

void *AAfunc(void *param);
void *namefunc(void *param);
void *studentIDfunc(void *param);

/* semaphores to enforce ordering:
 *   semID_done   signals that all student‑ID lines are printed
 *   semName_done signals that the name line is printed
 */
sem_t semID_done;
sem_t semName_done;

int main(int argc, char *argv[]) {
	int i, scope;
	pthread_t threadID_id, threadName_id, threadAA_id; 	/* the thread identifier */
	pthread_attr_t attr; 	/* set of attributes for the thread */
	
	
	/* get the default attributes */
	pthread_attr_init(&attr);
	
	/* initialize semaphores to 0 (locked) */
    sem_init(&semID_done, 0, 0);
    sem_init(&semName_done, 0, 0);

	/* create 3 threads */
	pthread_create(&threadID_id, &attr, studentIDfunc, &threadID_id);
	pthread_create(&threadName_id, &attr, namefunc, &threadName_id);
	pthread_create(&threadAA_id, &attr, AAfunc, &threadAA_id);
	
	/* Now join on each thread */
	pthread_join(threadID_id, NULL);
	pthread_join(threadName_id, NULL);
	pthread_join(threadAA_id, NULL);
	
    printf("Program is done\n");
	
	/* clean up */
    sem_destroy(&semID_done);
    sem_destroy(&semName_done);
	
	return 0;
}
void *studentIDfunc(void *param) {
	for (int i = 0; i < 10; i++)
	   printf("%d: My student ID is 2330016056\n", i);
	   
	/* signal that all ID lines are done */
    sem_post(&semID_done);
	
	pthread_exit(0);
}
void *namefunc(void *param) {
	/* wait until student‑ID lines are done */
    sem_wait(&semID_done);
	
	printf("My name is Bohan YANG\n");
	
	/* signal that the name line is done */
    sem_post(&semName_done);
	
	pthread_exit(0);
}
void *AAfunc(void *param) {
	/* wait until the name line is done */
	// sem_wait(&semID_done);
    sem_wait(&semName_done);
	
	printf("My AA is CiCi Chong CHEN\n");	
	pthread_exit(0);
}


/***
 * Task1 output of first time:
0: My student ID is 222222222222
1: My student ID is 222222222222
2: My student ID is 222222222222
My name is Judy
My AA is HOLY ONE
Program is done
3: My student ID is 222222222222
4: My student ID is 222222222222
5: My student ID is 222222222222
6: My student ID is 222222222222
7: My student ID is 222222222222
8: My student ID is 222222222222
9: My student ID is 222222222222
*/

/***
 * Task1 output of second time:
Program is done
My name is Judy
My AA is HOLY ONE
0: My student ID is 222222222222
1: My student ID is 222222222222
2: My student ID is 222222222222
3: My student ID is 222222222222
4: My student ID is 222222222222
5: My student ID is 222222222222
6: My student ID is 222222222222
7: My student ID is 222222222222
8: My student ID is 222222222222
9: My student ID is 222222222222
*/

/***
 * Task1 output of third time:
Program is done
0: My student ID is 222222222222
My AA is HOLY ONE
1: My student ID is 222222222222
2: My student ID is 222222222222
3: My student ID is 222222222222
4: My student ID is 222222222222
5: My student ID is 222222222222
6: My student ID is 222222222222
7: My student ID is 222222222222
8: My student ID is 222222222222
9: My student ID is 222222222222
My name is Judy
*/

/***
 * Task1 Explain why:
	The reason for the different output orders in each run of the program is due to the non-deterministic nature of thread scheduling in multi-threaded programs. 
	The threads studentIDfunc, namefunc, and AAfunc are executed concurrently, and the operating system's thread scheduler determines when each thread runs. 
	Since the scheduler can assign CPU time to each thread at different moments during each execution, the order in which the threads are executed—and therefore the output—can vary. 
	Even though the threads are created in a specific order, the operating system may start and run them in a different sequence each time. 
	This leads to different output orders across multiple runs. 
	Additionally, if the value of i in studentIDfunc is increased, the interleaving of thread outputs becomes even more complex, leading to even less predictable behavior.
*/

/***
 * Output of Task2:
0: My student ID is 2330016056
1: My student ID is 2330016056
2: My student ID is 2330016056
3: My student ID is 2330016056
4: My student ID is 2330016056
5: My student ID is 2330016056
6: My student ID is 2330016056
7: My student ID is 2330016056
8: My student ID is 2330016056
9: My student ID is 2330016056
My name is Bohan YANG
My AA is CiCi Chong CHEN
Program is done
*/