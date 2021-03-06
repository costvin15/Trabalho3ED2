/*
 * Copyright 2019 Vinicius Costa Castro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
    while (node && node->next){
        previous = node;
        node = node->next;
        free(previous);
    }

    free(node);
    free(queue);
    return true;
}

int pushQueue(Queue *queue, void *data){
    QueueNode *aux, *previous;
    
    if (!queue)
        return false;
    if (!data)
        return false;

    aux = queue->root;
    previous = NULL;

    while (aux){
        previous = aux;
        aux = aux->next;
    }

    if (previous)
        previous->next = createQueueNode(data);
    else
        queue->root = createQueueNode(data);
    return true;
}

void *popQueue(Queue *queue){
    void *data;
    QueueNode *current, *previous;

    if (!queue)
        return NULL;
    if (emptyQueue(queue))
        return NULL;
    
    current = queue->root;
    previous = NULL;

    while (current->next){
        previous = current;
        current = current->next;
    }

    if (previous){
        previous->next = NULL;
    } else {
        queue->root = NULL;
    }
    
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
        return false;
    
    return !queue->root;
}

#endif