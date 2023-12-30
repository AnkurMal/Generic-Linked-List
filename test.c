#include "linkedList.h"
#include <stdio.h>

/*
TODO: CAN I DIRECTLY PASS THE MALLOCED POINTER TO insertData_ BY PASSING THE RETURNED void* TO dataPtr USING
FUNCTION POINTER ? DONT KNOW THE ADVANTAGE OF THIS THO
*/

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
