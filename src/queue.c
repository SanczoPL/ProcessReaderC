#include "queue.h"

//#define DEBUG

static const char * log_error =  "\x1b[31m";
static const char * log_end = "\x1b[0m";
static const char * log_warn =  "\x1b[33m";
static const char * log_debug =  "\x1b[32m";


struct QNode* newNode(int k, char* name)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->pid = k;
    strcpy(temp->name , name);
    temp->next = NULL;
    return temp;
}
  
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->count = 0;
    return q;
}
  
void push_back(struct Queue* q, int k, char* name)
{
	#ifdef DEBUG
    printf("%sDEBUG: pushQueue(%d,%s)\n%s",log_debug, k, name, log_end);
    #endif
    struct QNode* temp = newNode(k, name);
  
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->count++;
        return;
    }
  
    q->rear->next = temp;
    q->rear = temp;
    q->count++;
}

bool isEmpty(struct Queue* q)
{
    return (q->rear == NULL);
}

void pop_front(struct Queue* q)
{
    if (q->front == NULL)
    {
        return;
    }
  
    struct QNode* temp = q->front;
    

    if(q->front->next == NULL)
    {
        q->front = NULL;
        q->count--;
        q->rear = NULL;
        free(temp);
        return;
    }

    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    q->count--;

    free(temp);
}

bool deleteQueue(struct Queue* q)
{
    #ifdef DEBUG
    printf("%sDEBUG: deleteQueue()\n%s",log_debug, log_end);
    #endif
    
	while(q->front != NULL)
	{
		pop_front(q);
	}

    if(q->rear == NULL && q->front == NULL)
    {
        free(q);
        return true;
    }
    return false;

}
