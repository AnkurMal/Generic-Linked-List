#include "linkedList.h"

#include <stdio.h>
#include <string.h>

#define __assert(expression, listPtr, format, ...) \
    do { \
        if (!(expression)) { \
            fprintf(stderr, "Error in file %s; line %d in function %s:\n", __FILE__, __LINE__, __func__); \
            fprintf(stderr, format "\n", ##__VA_ARGS__); \
            freeList(listPtr); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define __check_and_insert(listPtrToPtr, data, dataPtr, dataType, index) \
    if(dataPtr==NULL) { \
        puts("WARNING: Not enough memory!"); \
        return; } \
    *dataPtr = data; \
    __insert_data(listPtrToPtr, dataPtr, dataType, index);

#define __remove(listPtrToPtr, nodeDataType, data, remvDataType) \
    Node *listPtr = *listPtrToPtr; \
    Node *nextPtr = listPtr->next; \
    \
    if(listPtr->dataType==nodeDataType) \
        if((*(remvDataType*)listPtr->data)==data) {\
            *listPtrToPtr = nextPtr; \
            free(listPtr->data); \
            free(listPtr); \
            nextPtr = NULL; }\
    \
    while (nextPtr!=NULL) { \
        if(nextPtr->dataType==nodeDataType) \
            if((*(remvDataType*)nextPtr->data)==data) { \
                listPtr->next = nextPtr->next; \
                free(nextPtr->data); \
                free(nextPtr); \
                break; } \
        \
        listPtr = listPtr->next; \
        nextPtr = listPtr->next; }

void __insert_char(Node **list, char data, int64_t index)
{
    char* dataPtr = malloc(sizeof(char));
    __check_and_insert(list, data, dataPtr, CHAR, index);
}

void __insert_int(Node **list, int data, int64_t index)
{   
    int* dataPtr = malloc(sizeof(int));
    __check_and_insert(list, data, dataPtr, INT, index);
}

void __insert_double(Node **list, double data, int64_t index)
{   
    double* dataPtr = malloc(sizeof(double));
    __check_and_insert(list, data, dataPtr, DOUBLE, index);
}

void __insert_string(Node **list, const char* data, int64_t index)
{
    char* dataPtr = malloc(strlen(data)+1);
    if(dataPtr==NULL) { 
        puts("WARNING: Not enough memory!"); 
        return; }

    memcpy(dataPtr, data, strlen(data)+1);
    __insert_data(list, dataPtr, STRING, index);
}

void __insert_data(Node **list, void* dataPtr, DataType dataType, int64_t index)
{   
    int64_t length = listLength(*list);
    if(index<0 || index>length)
    {
        free(dataPtr);
        __assert(0, *list, "Inserting data at index %lld of LinkedList of size %lld.", index, length);
    }

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

void __remove_char(Node **list, char data)
{
    __remove(list, CHAR, data, char);
}

void __remove_int(Node **list, int data)
{
    __remove(list, INT, data, int);
}

void __remove_double(Node **list, double data)
{
    __remove(list, DOUBLE, data, double);
}

void __remove_string(Node **list, const char* data)
{
    __remove(list, STRING, data, char*);
}

void __remove_data_at(Node **list, int64_t index)
{
    int64_t length = listLength(*list);
    __assert(index>=0 && index<length, *list, "Removing data from index %lld of LinkedList of size %lld.", index, length);
    
    if(index==0)
    {
        Node *tempPtr = *list;
        *list = (*list)->next;
        free(tempPtr->data);
        free(tempPtr);
    }
    else
    {
        Node *listPtr = *list;
        for(int64_t i=0; i<index-1; i++)
            listPtr = listPtr->next;

        Node *tempPtr = listPtr->next;
        listPtr->next = tempPtr->next;

        free(tempPtr->data);
        free(tempPtr);
    }
}

void __invalid_data_type(Node **list, ...)
{
    __assert(0, *list, "%s", "Invalid data type. Only allowed types are: char, int, double and char* (string).");
}

void __free_list(Node **list)
{
    Node *temp;
    Node *listPtr = *list;
    
    while (listPtr!=NULL)
    {
        temp = listPtr;
        listPtr = listPtr->next;
        free(temp->data);
        free(temp);
    }
    *list = NULL;
}

/**
 * @brief Checks if the list is empty.
 * @param *list the list pointer
 * @return true if the list contains no data, otherwise false
*/
bool isEmpty(Node *list)
{
    if(!listLength(list))
        return true;
    return false;
}

/**
 * @brief Returns the number of elements in the list.
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
 * @brief Prints the data at the specified index in the list.
 * @param *list the list pointer
 * @param index index of the data to be printed
*/
void printData(Node *list, int64_t index)
{
    int64_t length = listLength(list);
    __assert(index>=0 && index<length, list, "Printing data at index %lld of LinkedList of size %lld.", index, length);

    for(int64_t i=0; i<index; i++)
        list = list->next;

    switch (list->dataType)
    {
        case INT:
            printf("%d\n", *(int*)list->data);
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
    }
}

/**
 * @brief Prints the entire list.
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
                if(c<length)  printf("%d, ", *(int*)list->data);
                else          printf("%d", *(int*)list->data);
                break;
            case DOUBLE:
                if(c<length) printf("%lf, ", *(double*)list->data);
                else         printf("%lf", *(double*)list->data);
                break;
            case STRING:
                if(c<length) printf("\"%s\", ", (char*)list->data);
                else         printf("\"%s\"", (char*)list->data);
                break;
            case CHAR:
                if(c<length) printf("\'%c\', ", *(char*)list->data);
                else         printf("\'%c\'", *(char*)list->data);
                break;
        }
        list = list->next;
    }
    printf("]\n");    
}
