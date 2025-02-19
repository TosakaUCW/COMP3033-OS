/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Console mode (command line) program.                           *
 *                                                                          *
 * History : Date      Reason                                               *
 *           25/02/19  Created                                              *
 *           25/02/19  Complished  					    *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct record{
	char name[20];
	int score;
	struct record *next;

} Node;
Node* createList(char fileName[]);
Node* insertARecord(Node *pHead);
Node* deleteARecord(Node *pHead);
Node* saveLinkedList(Node* pHead, const char *fileName);
void printLinkedList(Node* pHead);

int main(int argc, char *argv[])
{
	Node *pHead;
	//create a linked list using the info from record.txt, return the head pointer
    //It is assumed that the info is sorted descently in scores.
	pHead = createList("record.txt");
	printLinkedList(pHead);

	printf("choose operation(i: insert, d: delete, q: exit): ");
	char ch = getchar();
	while (ch != 'q'){

		if (ch == 'i')
			pHead = insertARecord(pHead); //insert a record of a student info if this student does not exist. Return the new head pointer if the new record is inserted as the first.
		if (ch == 'd')
			pHead = deleteARecord(pHead); //delete a record of a student info if this student exist. Return the new head pointer if the original head was deleted.
	    printLinkedList(pHead);

		printf("choose operation(i: insert, d: delete, q: exit): ");
		getchar();
		ch = getchar();
    }
	//save the records in the list pointed by pHead into a file again
    saveLinkedList(pHead, "new_record.txt");

	return 0;
}


Node* createList(char fileName[])
{
	FILE *fp;
	Node stuRecord;
	Node *pNewRecord, *pNode, *pHead = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) return NULL;
	while (fscanf(fp, "%s%d", stuRecord.name, &stuRecord.score) != EOF){
		pNewRecord =(Node*)malloc(sizeof(Node));
		strcpy(pNewRecord->name, stuRecord.name);   //copy name to new node
		pNewRecord -> score = stuRecord.score; //assign score to new node
		pNewRecord -> next = NULL; //After all the nodes are added, the next of the end node should be NULL to indicate that this is the last one, no node after it.

		// if the list is empty, pNewRecord will be the first node in the list
		if (pHead == NULL)
			pHead = pNewRecord;
		else //otherwise, if list is not empty, add pNewRecord to the end of the list
			pNode -> next = pNewRecord;
        pNode = pNewRecord;    //Each time after a new node is added to the list, pNode should be changed to pointed to the end node.
    }
 	fclose(fp);
    return pHead;

}
void printLinkedList(Node* pHead)
{
	Node *pNode = pHead;
	while (pNode != NULL){
		printf("%s%d\n", pNode -> name, pNode -> score);
		pNode = pNode->next;
	}
	return;
}
Node* insertARecord(Node *pHead)
{
	//enter name and score
	Node *pNewRecord;
	Node *pNode1 = pHead, *pNode2;

	pNewRecord = (Node*)malloc(sizeof(Node));
	printf("Please enter a record of a student(name, score):");
	scanf("%s%d", pNewRecord -> name, &pNewRecord -> score);
	pNewRecord -> next = NULL;

	if (pNode1 == NULL)
		return pNewRecord;

	//search the list to find the proper place to put the record
	while(pNode1 != NULL && pNode1 -> score > pNewRecord -> score){
		if (strcmp(pNode1 -> name, pNewRecord -> name) == 0){
			printf("Name Exist\n");
			free(pNewRecord);
			return pHead;
		}
		pNode2 = pNode1; //record the current node before pNode1 moves to point to the next
		pNode1 = pNode1->next;
	}

	if (pNode1 == pHead){ //for the case pHead -> score < pNewRecord -> score
		pNewRecord -> next = pHead;
		pHead = pNewRecord;
	}
	else {//for the cases pNode1 == NULL or pNode1 -> score < pNewRecord -> score < pNode2 -> score
		pNode2 -> next = pNewRecord;
	    pNewRecord -> next = pNode1;
	}

	return pHead;

}
Node* deleteARecord(Node *pHead)
{
	char name[20];
	Node *pNode1 = pHead, *pNode2;
	printf("Please enter a name of a student to delete:");
	scanf("%s", name);
    while(pNode1 != NULL && strcmp(pNode1->name, name) != 0){
		pNode2 = pNode1;
		pNode1 = pNode1 -> next;
	}
	if (pNode1 == NULL)
		return pHead;

	if (pNode1 == pHead) //for the case that head's name is name
	    pHead = pNode1->next; //the second node will be the head
	else //pNode1 -> name is name
		pNode2 -> next = pNode1->next;

	free(pNode1); //free the memory for original head
	return pHead;
}
Node* saveLinkedList(Node* pHead, const char *fileName)
{
    Node *pNode = pHead;
    FILE *fp;

	fp = fopen(fileName, "w");

	while (pNode != NULL) {
        fprintf(fp, "%s%d\n", pNode->name, pNode->score);
        pNode = pNode->next;
    }

	fclose(fp);
	return 0;
}
