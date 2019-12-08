#include <stdio.h>
#include "headers/menu.h"

#include "headers/linkedlist.h"
#include <stdlib.h>

int compare(void *a, void *b){
    int *ptrA, *ptrB;

    ptrA = (int *) a;
    ptrB = (int *) b;

    if ((*ptrA) == (*ptrB))
        return 0;
    if ((*ptrA) > (*ptrB))
        return 1;
    return -1;
}

int main(void){
    /* menu(); */
    int i, *ptr;
    LinkedList *list;
    list = createLinkedList();

    for (i = 0; i < 10; i++){
        ptr = (int *) malloc(sizeof(int));
        *ptr = 100 - (i * 10);
        insertSortedLinkedList(list, (void *) ptr, compare);
    }

    for (i = 0; i < 10; i++){
        ptr = (int *) indexOfLinkedList(list, i);
        if (ptr){
            printf("%d\n", *ptr);
        } else {
            printf("%d nao existe\n", i);
        }
    }

    return 0;
}