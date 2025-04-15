/****************************************************************************
 *                                                                          *
 * Author		:  	                                                        *
 *                                                                          *
 * Studdent ID	: Console mode (command line) program.                      *
 *                                                                          *
 * Date			:                                             			    *
 *                                                         					*
 * Purpose		:                                                           *
 *                                                         					*
 ****************************************************************************/
 
#include <stdio.h>

void runTask1();
void runTask2();

int main(){
	while(1){
		printf("\nEnter a task number (1 or 2) or 0 to exit: ");
		int taskNo = 0;
		scanf("%d", &taskNo);
		switch(taskNo){
				case 0: exit(0);
				case 1: runTask1(); break;
				case 2: runTask2(); break;
				default: printf("Please enter 0, 1 or 2.\n");
		}
	}
}

void runTask1(){}
void runTask2(){}
