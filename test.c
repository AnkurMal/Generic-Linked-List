#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum DataType
{
    CHAR, INT, DOUBLE, STRING
}DataType;

typedef struct Node
{
    void* data;
    int length;
    struct Node *next;
    DataType dataType;
}Node;

static void InsertData_(Node **list, void* dataPtr, DataType dataType);
static void InsertChar(Node **list, char data);
static void InsertInt(Node **list, int data);
static void InsertDouble(Node **list, double data);
static void InsertString(Node **list, const char* data);
static void PrintData(Node *list, size_t index);
static void PrintList(Node *list);
static void FreeList(Node *list);

/**
 * Inserts the specified data at the end of the list.
 * @param listPtr pointer to the list (should be initialzed to NULL)
 * @param data data to be inserted to the list
 * @note For a character data, it should be explicitely converted to char.
*/
#define InsertData(listPtr, data) _Generic((data), \
        char:   InsertChar, \
        int:    InsertInt, \
        double: InsertDouble, \
        char*:  InsertString \
    )(&listPtr, data)

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
    //PrintData(list, 6);
    printf("The list is: ");
    PrintList(list);
    FreeList(list);

    return 0;
}

void InsertChar(Node **list, char data)
{
    char* dataPtr = malloc(sizeof(char));
    *dataPtr = data;
    InsertData_(list, (void*)dataPtr, CHAR);
}

void InsertInt(Node **list, int data)
{   
    int* dataPtr = malloc(sizeof(int));
    *dataPtr = data;
    InsertData_(list, (void*)dataPtr, INT);
}

void InsertDouble(Node **list, double data)
{   
    double* dataPtr = malloc(sizeof(double));
    *dataPtr = data;
    InsertData_(list, (void*)dataPtr, DOUBLE);
}

void InsertString(Node **list, const char* data)
{
    char* dataPtr = malloc(strlen(data)+1);
    memcpy(dataPtr, data, strlen(data)+1);
    InsertData_(list, (void*)dataPtr, STRING);
}

void InsertData_(Node **list, void* dataPtr, DataType dataType)
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

/**
 * Prints the data at the specified index in the list.
 * @param *list the list pointer
 * @param index index of the data to be printed
*/
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
        case STRING:
            printf("%s\n", (char*)list->data);
            break;
        case CHAR:
            printf("%c\n", *(char*)list->data);
            break;
        default:
            break;
    }
}

/**
 * Prints the entire list.
 * @param *list the list pointer
*/
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
            case STRING:
                if(c<length)
                    printf("\"%s\", ", (char*)list->data);
                else
                    printf("\"%s\"]\n", (char*)list->data);
                break;
            case CHAR:
                if(c<length)
                    printf("\'%c\', ", *(char*)list->data);
                else
                    printf("\'%c\']\n", *(char*)list->data);
                break;
            default:
                break;
        }
        list = list->next;
    }    
}

/**
 * Frees the enitre list.
 * @param *list the list pointer
*/
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
