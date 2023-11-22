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
    struct Node *next;
    DataType dataType;
}Node;

static void InsertInt(Node **list, int data);
static void InsertDouble(Node **list, double data);
static void InsertNumber(Node **list, void* dataPtr, DataType dataType);
static void PrintData(Node *list, size_t index);
static void FreeList(Node *list);
static void PrintList(Node *list);

/**
 * Inserts the specified data at the end of the list.
 * @param listPtr pointer to the list (should be initialzed to NULL)
 * @param data data to be inserted to the list
*/
#define InsertData(listPtr, data) _Generic((data), \
        int:    InsertInt, \
        double: InsertDouble \
    )(&listPtr, data)

int main(void)
{
    Node *list = NULL;
    InsertData(list, -5);
    InsertData(list, 10);
    InsertData(list, 85.99);
    InsertData(list, 45);
    InsertData(list, 89);
    InsertData(list, 55.4789);
    PrintData(list, 3);
    printf("The list is: ");
    PrintList(list);
    FreeList(list);

    return 0;
}

void InsertInt(Node **list, int data)
{   
    int* dataPtr = malloc(sizeof(int));
    *dataPtr = data;
    InsertNumber(list, (void*)dataPtr, INT);
}

void InsertDouble(Node **list, double data)
{   
    double* dataPtr = malloc(sizeof(double));
    *dataPtr = data;
    InsertNumber(list, (void*)dataPtr, DOUBLE);
}

void InsertNumber(Node **list, void* dataPtr, DataType dataType)
{   
    Node *newNode = malloc(sizeof(Node));

    newNode->dataType = dataType;
    newNode->data = dataPtr;
    newNode->next = NULL;
    
    if((*list)==NULL)
    {
        *list = newNode;
        (*list)->length = 0;
    }
    else
    {
        Node *tempNode = *list;
        while (tempNode->next!=NULL)
            tempNode = tempNode->next;
        tempNode->next = newNode;
    }
    (*list)->length++;
}

void PrintData(Node *list, size_t index)
{
    for(size_t i=0; i<index; i++)
        list = list->next;

    switch (list->dataType)
    {
        case INT:
            printf("%d\n", *(int*)list->data);
            break;
        case DOUBLE:
            printf("%f\n", *(double*)list->data);
            break;
        default:
            break;
    }
}

void PrintList(Node *list)
{
    int c = 0, length = list->length;
    
    printf("[");
    while (list!=NULL)
    {
        ++c;
        switch (list->dataType)
        {
            case INT:
                if(c<length)
                    printf("%d, ", *(int*)list->data);
                else
                    printf("%d]\n", *(int*)list->data);
                break;
            case DOUBLE:
                if(c<length)
                    printf("%f, ", *(double*)list->data);
                else
                    printf("%f]\n", *(double*)list->data);
                break;
            default:
                break;
        }
        list = list->next;
    }    
}

void FreeList(Node *list)
{
    Node *temp;
    while (list!=NULL)
    {
        temp = list;
        list = list->next;
        free(temp->data);
        free(temp);
    }
}
