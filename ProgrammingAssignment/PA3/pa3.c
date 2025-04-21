#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

#define TRUE 1

void *AAfunc(void *param);
void *namefunc(void *param);
void *studentIDfunc(void *param);

int main(int argc, char *argv[]) {
	int i, scope;
	pthread_t threadID_id, threadName_id, threadAA_id; 	/* the thread identifier */
	pthread_attr_t attr; 	/* set of attributes for the thread */
	
	
	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create 3 threads */
	pthread_create(&threadID_id, &attr, studentIDfunc, &threadID_id);
	pthread_create(&threadName_id, &attr, namefunc, &threadName_id);
	pthread_create(&threadAA_id, &attr, AAfunc, &threadAA_id);
	
    printf("Program is done\n");
	/* Now join on each thread */
	pthread_join(threadID_id, NULL);
	pthread_join(threadName_id, NULL);
	pthread_join(threadAA_id, NULL);
	return 0;
}
void *studentIDfunc(void *param) {
	for (int i = 0; i < 10; i++)
	   printf("%d: My student ID is 222222222222\n", i);
	pthread_exit(0);
}
void *namefunc(void *param) {
	printf("My name is Judy\n");
	pthread_exit(0);
}
void *AAfunc(void *param) {
	printf("My AA is HOLY ONE\n");	
	pthread_exit(0);
}


/***
 * Task1 output of first time:

*/

/***
 * Task1 output of second time:

*/

/***
 * Task1 output of third time:

*/

/***
 * Task1 Explain why:
 
*/

/***
 * Output of Task2:

*/