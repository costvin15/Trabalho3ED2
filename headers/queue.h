#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct _queue_node_ QueueNode;
typedef struct _queue_ Queue;

Queue *createQueue();
QueueNode *createQueueNode(void *);
int destroyQueue(Queue *);
int pushQueue(Queue *, void *);
void *popQueue(Queue *);
void *frontQueue(Queue *);
int emptyQueue(Queue *);

#else

extern Queue *createQueue();
extern QueueNode *createQueueNode(void *);
extern int destroyQueue(Queue *);
extern int pushQueue(Queue *, void *);
extern void *popQueue(Queue *);
extern void *frontQueue(Queue *);
extern int emptyQueue(Queue *);

#endif