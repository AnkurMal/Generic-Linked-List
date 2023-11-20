#include <stdio.h>
#include <stdlib.h>

typedef enum DataType
{
    INT, DOUBLE
}DataType;

typedef struct Node
{
    void* data;
    int length;
    void *next;
    DataType dataType;
}Node;

static int InsertNumber(Node **list, void* data, DataType dataType);
static void PrintList(Node *list);

#define InsertData(listPtr, data) _Generic((data), \
        int:    InsertNumber(&listPtr, (void*)((intptr_t)data), INT), \
        double: InsertNumber(&listPtr, (void*)((intptr_t)data), DOUBLE) \
    )

int main(void)
{
    Node *list = NULL;
    InsertData(list, -5);
    InsertData(list, 10);
    InsertData(list, 85.89);
    PrintList(list);
}

int InsertNumber(Node **list, void* data, DataType dataType)
{   
    Node *newNode = malloc(sizeof(Node));
    newNode->dataType = dataType;
    
    Node *tempNode = *list;

    newNode->data = data;
    newNode->next = NULL;

    if(*list==NULL)
    {
        *list = newNode;
        (*list)->length = 0;
    }
    else
    {
        while (tempNode->next!=NULL)
            tempNode = tempNode->next;
        tempNode->next = newNode;
    }
    (*list)->length++;

    return 1;
}

void PrintList(Node *list)
{
    int c = 0;
    int length = list->length;
    
    printf("[");
    while (list!=NULL)
    {
        ++c;
        if(c<length)
            printf("%lld, ", (intptr_t)list->data);
        else
            printf("%f]\n", (double*)list->data);
        list = list->next;
    }    
}