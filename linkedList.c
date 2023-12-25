#include "linkedList.h"

#define CHECK_DATA_AND_INSERT(listPtr2, data, dataPtr, dataType, index) \
    if(dataPtr==NULL) { \
        puts("WARNING: Not enough memory!"); \
        return; } \
    *dataPtr = data; \
    __insert_data(listPtr2, (void*)dataPtr, dataType, index);

void __insert_char(Node **list, char data, int64_t index)
{
    char* dataPtr = malloc(sizeof(char));
    CHECK_DATA_AND_INSERT(list, data, dataPtr, CHAR, index);
}

void __insert_int(Node **list, long data, int64_t index)
{   
    long* dataPtr = malloc(sizeof(long));
    CHECK_DATA_AND_INSERT(list, data, dataPtr, INT, index);
}

void __insert_double(Node **list, double data, int64_t index)
{   
    double* dataPtr = malloc(sizeof(double));
    CHECK_DATA_AND_INSERT(list, data, dataPtr, DOUBLE, index);
}

void __insert_string(Node **list, const char* data, int64_t index)
{
    char* dataPtr = malloc(strlen(data)+1);
    if(dataPtr==NULL) { 
        puts("WARNING: Not enough memory!"); 
        return; }

    memcpy(dataPtr, data, strlen(data)+1);
    __insert_data(list, (void*)dataPtr, STRING, index);
}

void __insert_data(Node **list, void* dataPtr, DataType dataType, int64_t index)
{   
    Node *newNode = malloc(sizeof(Node));
    if(newNode==NULL) { 
        free(dataPtr);
        puts("WARNING: Not enough memory!"); 
        return; }

    newNode->dataType = dataType;
    newNode->data = dataPtr;
    newNode->next = NULL;
    
    if((*list)==NULL)
        *list = newNode;
    else
    {
        Node *tempNode = *list;
        for(int64_t i=0; i<index-1; i++)
            tempNode = tempNode->next;
            
        newNode->next = tempNode->next;
        tempNode->next = newNode;
    }
}

void __invalid_data_type(Node **list, ...)
{
    __assert(0, *list, "%s", "Invalid data type");
}

/**
 * Returns the number of elements in the list.
 * @param *list the list pointer
 * @return the number of elements in the list
*/
int64_t listLength(Node *list)
{
    int64_t length = 0;
    while (list!=NULL)
    {
        length++;
        list = list->next;
    }
    return length;
}

/**
 * Prints the data at the specified index in the list.
 * @param *list the list pointer
 * @param index index of the data to be printed
*/
void printData(Node *list, int64_t index)
{
    int64_t length = listLength(list);
    __assert(index>0 && index<length, list, "Printing data at index %lld of LinkedList of size %lld", index, length);

    for(int64_t i=0; i<index; i++)
        list = list->next;

    switch (list->dataType)
    {
        case INT:
            printf("%ld\n", *(long*)list->data);
            break;
        case DOUBLE:
            printf("%lf\n", *(double*)list->data);
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
void printList(Node *list)
{
    int c = 0;
    int64_t length = listLength(list);
    
    printf("[");
    while (list!=NULL)
    {
        ++c;
        switch (list->dataType)
        {
            case INT:
                if(c<length)
                    printf("%ld, ", *(long*)list->data);
                else
                    printf("%ld]\n", *(long*)list->data);
                break;
            case DOUBLE:
                if(c<length)
                    printf("%lf, ", *(double*)list->data);
                else
                    printf("%lf]\n", *(double*)list->data);
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
void freeList(Node *list)
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
