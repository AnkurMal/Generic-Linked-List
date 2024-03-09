#include "linkedList.h"
#include <stdio.h>

int main(void)
{
    Node *list = initList();

    insert(list, 5);
    insert(list, (char)'A');
    insertAt(list, 56.856, 1);
    insert(list, "hello");
    
    printf("The list is: ");
    printList(list);
    
    freeList(list);
    return 0;
}
