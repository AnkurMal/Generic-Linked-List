#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdlib.h>

// Initializes the list to NULL.
#define initList() NULL

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
 * @brief Inserts the specified data at the end of the list.
 * @param listPtr pointer to the list
 * @param data data to be inserted to the list
 * @note For a character data, it should be explicitely converted to char.
*/
#define insertData(listPtr, data) insertDataAt(listPtr, data, listLength(listPtr))

/**
 * @brief Inserts the specified data at the specified index of the list.
 * @param listPtr pointer to the list
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
