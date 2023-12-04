#include "linkedList.h"

/*
TODO: CAN I DIRECTLY PASS THE MALLOCED POINTER TO InsertData_ BY PASSING THE RETURNED void* TO dataPtr USING
FUNCTION POINTER ? DONT KNOW THE ADVANTAGE OF THIS THO
*/
int main(void)
{
    Node *list = NULL;

    InsertData(list, (char)'A');
    InsertData(list, 10);
    InsertData(list, 85.99);
    InsertData(list, 45);
    InsertData(list, 89);
    InsertData(list, 55.4789);
    InsertData(list, "hello");
    //PrintData(list, 7);
    printf("The list is: ");
    PrintList(list);
    FreeList(list);
    
    return 0;
}
