#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define __assert(expression, listPtr, format, ...) \
    do { \
        if (!(expression)) { \
            fprintf(stderr, "Error in file %s; line %d in function %s:\n", __FILE__, __LINE__, __func__); \
            fprintf(stderr, format "\n", ##__VA_ARGS__); \
            FreeList(listPtr); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

typedef enum DataType
{
    CHAR, INT, DOUBLE, STRING
}DataType;

typedef struct Node
{
    void* data;
    int64_t length;
    struct Node *next;
    DataType dataType;
}Node;

void __insert_data(Node **list, void* dataPtr, DataType dataType);
void __insert_char(Node **list, char data);
void __insert_int(Node **list, long data);
void __insert_double(Node **list, double data);
void __insert_string(Node **list, const char* data);
void __invalid_data_type(Node **list, ...);

void PrintData(Node *list, int64_t index);
void PrintList(Node *list);
void FreeList(Node *list);

/**
 * Inserts the specified data at the end of the list.
 * @param listPtr pointer to the list (should be initialzed to NULL)
 * @param data data to be inserted to the list
 * @note For a character data, it should be explicitely converted to char.
*/
#define InsertData(listPtr, data) _Generic((data), \
        char:     __insert_char, \
        short:    __insert_int, \
        int:      __insert_int, \
        long:     __insert_int, \
        float:    __insert_double, \
        double:   __insert_double, \
        char*:    __insert_string, \
        default:  __invalid_data_type \
    )(&listPtr, data)
    
#endif
