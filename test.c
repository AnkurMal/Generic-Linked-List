#include "linkedList.h"
#include <stdio.h>

int main(void)
{
    Node *list = initList();

    insertData(list, 5);
    insertData(list, (char)'A');
    insertDataAt(list, 56.856, 1);
    insertData(list, "hello");
    
    printf("The list is: ");
    printList(list);
    
    freeList(list);
    return 0;
}
