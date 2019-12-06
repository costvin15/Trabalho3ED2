#ifndef _QUEUE_C_
#define _QUEUE_C_

#include "../headers/queue.h"
#include <stdlib.h>
#include <stdbool.h>

struct _queue_node_ {
    void *value;
    QueueNode *next;
};

struct _queue_ {
    QueueNode *root;
};

Queue *createQueue(){
    Queue *queue;

    queue = (Queue *) malloc(sizeof(Queue));
    if (!queue)
        return NULL;

    queue->root = NULL;
    return queue;
}

QueueNode *createQueueNode(void *data){
    QueueNode *node;

    if (!data)
        return NULL;
    
    node = (QueueNode *) malloc(sizeof(QueueNode));
    if (!node)
        return NULL;
    node->value = data;
    node->next = NULL;
    return node;
}

int destroyQueue(Queue *queue){
    QueueNode *node, *previous;

    if (!queue)
        return false;
    
    previous = NULL;
    node = queue->root;
    while (node->next){
        previous = node;
        node = node->next;
        free(previous);
    }

    free(node);
    free(queue);
    return true;
}

int pushQueue(Queue *queue, void *data){
    QueueNode *aux;
    
    if (!queue)
        return false;
    if (!data)
        return false;
    
    if (!queue->root){
        queue->root = createQueueNode(data);
        return true;
    }

    aux = queue->root;
    while (aux->next)
        aux = aux->next;
    aux->next = createQueueNode(data);
    return true;
}

void *popQueue(Queue *queue){
    void *data;
    QueueNode *current, *previous;

    if (!queue)
        return NULL;
    
    current = queue->root;
    while (current->next){
        previous = current;
        current = current->next;
    }

    previous->next = NULL;
    data = current->value;
    free(current);
    return data;
}

void *frontQueue(Queue *queue){
    QueueNode *current;
    
    if (!queue)
        return NULL;

    while (current->next)
        current = current->next;
    
    return current->value;
}

int emptyQueue(Queue *queue){
    if (!queue)
        return NULL;
    
    return !queue->root;
}

#endif