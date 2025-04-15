/************************************************************************************
 *                                                                                  *
 * Author		:  	Bohan YANG                                                      *
 *                                                                                  *
 * Studdent ID	:   2330016506                                                      *
 *                                                                                  *
 * Date			:   2025 / 04/ 15                               			        *
 *                                                         					        *
 * Purpose		:   This program simulates a multilevel queue scheduling algorithm.	*
 *                                                         					        *
 ***********************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

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

void runTask1(){
	// Task 1: Multilevel Queue Scheduling Simulation
	
	// Prompt user for the number of processes
	int n;
	printf("Enter the number of processes to schedule: ");
	scanf("%d", &n);
	
	// Array to store burst times
	int burst[n];
	
	// Prompt user for burst times of each process
	for (int i = 0; i < n; i++) {
		printf("Enter the burst time of P%d: ", i + 1);
		scanf("%d", &burst[i]);
	}
	
	// Initialize queues for each level of scheduling
	int Q1[n], head1 = 0, tail1 = 0;
	int Q2[n], head2 = 0, tail2 = 0;
	int Q3[n], head3 = 0, tail3 = 0;
	
	// Array to store the scheduling sequence
	int ans[3 * n], cnt = 0;
	
	// Fill Q1 with process IDs
	for (int i = 0; i < n; i++) {
		Q1[tail1++] = i;
	}
	
	// Q1: FCFS + RR (q = 4)
	while (head1 < tail1) {
		int id = Q1[head1++];
		ans[cnt++] = id;
		
		// If the process has more than 4 time units left, it goes to Q2
		if (burst[id] > 4) {
			burst[id] -= 4;
			Q2[tail2++] = id;
		} else {
			burst[id] = 0;
		}
	}
	
	// Q2: FCFS + RR (q = 8)
	while (head2 < tail2) {
		int id = Q2[head2++];
		ans[cnt++] = id;
		
		// If the process has more than 8 time units left, it goes to Q3
		if (burst[id] > 8) {
			burst[id] -= 8;
			Q3[tail3++] = id;
		} else {
			burst[id] = 0;
		}
	}
	
	// Q3: FCFS
	while (head3 < tail3) {
		int id = Q3[head3++];
		ans[cnt++] = id;
		burst[id] = 0;
	}
	
	// Print the scheduling sequence
	printf("The scheduling sequence is: ");
	for (int i = 0; i < cnt; i++) {
		if (i == cnt - 1) {
			printf("P%d\n", ans[i] + 1);
		} else {
			printf("P%d, ", ans[i] + 1);
		}
	}
}
void runTask2(){
	int quant[4];
	printf("Enter the quantum for Q1, Q2, Q3, and Q4: ");
	for (int i = 0; i < 4; i++) {
		scanf("%d", &quant[i]);
	}
	
	// Prompt user for the number of processes
	int n;
	printf("Enter the number of processes to schedule: ");
	scanf("%d", &n);
	
	// Array to store burst times and priorities
	int burst[n], priority[n];
	// Initialize queues for each level of scheduling
	int Q[5][n], head[5] = {0}, tail[5] = {0};
	// Array to store the scheduling sequence
	int ans[5 * n], cnt = 0;
	
	// Prompt user for burst times of each process
	for (int i = 0; i < n; i++) {
		printf("Enter the burst time and priority of P%d: ", i + 1);
		scanf("%d, %d", &burst[i], &priority[i]);
		priority[i]--;
		Q[priority[i]][tail[priority[i]]++] = i;
	}
	
	for (int i = 0; i < 5; i++) {
		while (head[i] < tail[i]) {
			int id = Q[i][head[i]++];
			ans[cnt++] = id;
			
			// Q5 is FCFS
			if (i == 4) {
				burst[id] = 0;
				continue;
			}
			
			// If the process has more than the quantum time left, it goes to the next queue
			if (burst[id] > quant[i]) {
				burst[id] -= quant[i];
				Q[i + 1][tail[i + 1]++] = id;
			} else {
				burst[id] = 0;
			}
		}
	}
	
	// Print the scheduling sequence
	printf("The scheduling sequence is: ");
	for (int i = 0; i < cnt; i++) {
		if (i == cnt - 1) {
			printf("P%d\n", ans[i] + 1);
		} else {
			printf("P%d, ", ans[i] + 1);
		}
	}
}
