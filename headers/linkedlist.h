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

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct _linked_list_node_ LinkedListNode;
typedef struct _linked_list_ LinkedList;

LinkedList *createLinkedList();
LinkedListNode *createLinkedListNode(void *);
int destroyLinkedList(LinkedList *);
LinkedListNode *destroyLinkedListNode(LinkedListNode *);

int insertSortedLinkedList(LinkedList *, void *, int (*)(void *, void *));
void *indexOfLinkedList(LinkedList *, int);

#else

extern LinkedList *createLinkedList();
extern LinkedListNode *createLinkedListNode(void *);

extern int insertSortedLinkedList(LinkedList *, void *, int (*)(void *, void *));
extern void *indexOfLinkedList(LinkedList *, int);

#endif