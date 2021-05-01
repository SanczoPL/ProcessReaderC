#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define BUF_LEN	40

struct QNode {
	int pid;
	char name[BUF_LEN];
	struct QNode* next;
};

struct Queue {
	int count;
	struct QNode *front, *rear;
};

bool printQueue(struct Queue* q);

bool printNameFromQueue(struct Queue* q);

bool printPidFromQueue(struct Queue* q);

struct Queue* findPidInQueue(struct Queue* q, int k);

struct Queue* findNameInQueue(struct Queue* q, char * name);

struct QNode* newNode(int k, char* name);
  
struct Queue* createQueue();

void push_back(struct Queue* q, int k, char* name);
  
bool isEmpty(struct Queue* q);

void pop_front(struct Queue* q);

bool deleteQueue(struct Queue* q);

#endif // QUEUE_H
