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

void *indexOfLinkedList(LinkedList *list, int index){
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

#endif