#include "linkedList.h"

void __insert_char(Node **list, char data)
{
    char* dataPtr = malloc(sizeof(char));
    *dataPtr = data;
    __insert_data(list, (void*)dataPtr, CHAR);
}

void __insert_int(Node **list, long int data)
{   
    long int* dataPtr = malloc(sizeof(long int));
    *dataPtr = data;
    __insert_data(list, (void*)dataPtr, INT);
}

void __insert_double(Node **list, double data)
{   
    double* dataPtr = malloc(sizeof(double));
    *dataPtr = data;
    __insert_data(list, (void*)dataPtr, DOUBLE);
}

void __insert_string(Node **list, const char* data)
{
    char* dataPtr = malloc(strlen(data)+1);
    memcpy(dataPtr, data, strlen(data)+1);
    __insert_data(list, (void*)dataPtr, STRING);
}

void __insert_data(Node **list, void* dataPtr, DataType dataType)
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

void __invalid_data_type(Node **list, ...)
{
    __assert(0, *list, "%s", "Invalid data type");
}

/**
 * Prints the data at the specified index in the list.
 * @param *list the list pointer
 * @param index index of the data to be printed
*/
void PrintData(Node *list, int64_t index)
{
    __assert(index>0 && index<list->length, list, "Printing data at index %lld of LinkedList of size %zu", index, list->length);

    for(int64_t i=0; i<index; i++)
        list = list->next;

    switch (list->dataType)
    {
        case INT:
            printf("%ld\n", *(long int*)list->data);
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
                    printf("%ld, ", *(long int*)list->data);
                else
                    printf("%ld]\n", *(long int*)list->data);
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