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

#ifndef _LINKED_LIST_C_
#define _LINKED_LIST_C_

#include "../headers/linkedlist.h"
#include <stdlib.h>
#include <stdbool.h>

struct _linked_list_node_ {
    void *data;
    LinkedListNode *next;
};

struct _linked_list_ {
    LinkedListNode *head;
};

LinkedList *createLinkedList(){
    LinkedList *list;

    list = (LinkedList *) malloc(sizeof(LinkedList));
    if (!list)
        return NULL;
    list->head = NULL;
    return list;
}

LinkedListNode *createLinkedListNode(void *data){
    LinkedListNode *node;
    
    if (!data)
        return NULL;

    node = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;
    return node;
}


int destroyLinkedList(LinkedList *list){
    LinkedListNode *current;

    if (!list)
        return false;
    
    current = list->head;
    while (current)
        current = destroyLinkedListNode(current);
    
    return true;
}

LinkedListNode *destroyLinkedListNode(LinkedListNode *node){
    LinkedListNode *aux;

    if (!node)
        return NULL;
    
    aux = node->next;
    free(node->data);
    free(node);

    return aux;
}

int insertSortedLinkedList(LinkedList *list, void *data, int (*compare)(void *, void *)){
    LinkedListNode *node, *current, *previous;

    if (!list)
        return false;
    if (!data)
        return false;
    if (!compare)
        return false;

    previous = NULL;
    current = list->head;

    while (current){
        if (compare(current->data, data) == 1)
            break;

        previous = current;
        current = current->next;
    }

    node = createLinkedListNode(data);
    node->next = current;
    if (previous){
        previous->next = node;
    } else {
        list->head = node;
    }

    return true;
}

int insertLinkedList(LinkedList *list, void *data){
    LinkedListNode *node, *current, *previous;

    if (!list)
        return false;
    if (!data)
        return false;
    
    node = createLinkedListNode(data);

    previous = NULL;
    current = list->head;

    while (current){
        previous = current;
        current = current->next;
    }

    if (previous)
        previous->next = node;
    else
        list->head = node;
    return true;
}

void *removeFront(LinkedList *list){
    LinkedListNode *node;
    void *data;

    if (!list)
        return NULL;

    node = list->head;
    if (!node)
        return NULL;
    list->head = node->next;
    data = node->data;
    free(node);
    return data;
}

void *getDataByIndexLinkedList(LinkedList *list, int index){
    LinkedListNode *current;

    if (!list)
        return NULL;
    if (index < 0)
        return NULL;
        
    current = list->head;
    while (index > 0 && current){
        current = current->next;
        index--;
    }
    
    if (current)
        return current->data;
    return NULL;
}

LinkedListNode *getDataLinkedList(LinkedList *list, void *data, int (*compare)(void *, void *)){
    LinkedListNode *node;

    if (!list)
        return NULL;
    if (!data)
        return NULL;
    if (!compare)
        return NULL;
    
    node = list->head;
    
    while (node){
        if (compare(node->data, data) == 0)
            return node;
        node = node->next;
    }

    return NULL;
}

LinkedListNode *getHeadLinkedList(LinkedList *list){
    if (!list)
        return NULL;
    return list->head;
}

LinkedListNode *getNextLinkedListNode(LinkedListNode *node){
    if (!node)
        return NULL;
    return node->next;
}

void *getDataLinkedListNode(LinkedListNode *node){
    if (!node)
        return NULL;
    return node->data;
}

int getLenghtLinkedList(LinkedList *list){
    int c;
    LinkedListNode *node;

    if (!list)
        return 0;
    
    c = 0;
    node = list->head;
    while (node){
        node = node->next;
        c++;
    }

    return c;
}

#endif