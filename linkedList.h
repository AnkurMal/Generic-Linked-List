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
            freeList(listPtr); \
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
    struct Node *next;
    DataType dataType;
}Node;

void __insert_data(Node **list, void* dataPtr, DataType dataType, int64_t index);
void __insert_char(Node **list, char data, int64_t index);
void __insert_int(Node **list, long data, int64_t index);
void __insert_double(Node **list, double data, int64_t index);
void __insert_string(Node **list, const char* data, int64_t index);
void __invalid_data_type(Node **list, ...);

int64_t listLength(Node *list);
void printData(Node *list, int64_t index);
void printList(Node *list);
void freeList(Node *list);

/**
 * Inserts the specified data at the end of the list.
 * @param listPtr pointer to the list (should be initialzed to NULL)
 * @param data data to be inserted to the list
 * @note For a character data, it should be explicitely converted to char.
*/
#define insertData(listPtr, data) insertDataAt(listPtr, data, listLength(listPtr))

/**
 * Inserts the specified data at the specified index of the list.
 * @param listPtr pointer to the list (should be initialzed to NULL)
 * @param data data to be inserted to the list
 * @param index index at which the specified data is to be inserted
 * @note For a character data, it should be explicitely converted to char.
*/
#define insertDataAt(listPtr, data, index) _Generic((data), \
        char:        __insert_char, \
        short:       __insert_int, \
        int:         __insert_int, \
        long:        __insert_int, \
        float:       __insert_double, \
        double:      __insert_double, \
        char*:       __insert_string, \
        const char*: __insert_string, \
        default:     __invalid_data_type \
    )(&listPtr, data, index)
    
#endif
