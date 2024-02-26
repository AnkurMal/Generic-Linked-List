#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Initializes the list to NULL.
#define initList() NULL

/**
 * @brief Frees the enitre list.
 * @param listPtr the list pointer
*/
#define freeList(listPtr) __free_list(&listPtr)

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
void __insert_int(Node **list, int data, int64_t index);
void __insert_double(Node **list, double data, int64_t index);
void __insert_string(Node **list, const char* data, int64_t index);

void __replace_char(Node **list, char data, int64_t index);
void __replace_int(Node **list, int data, int64_t index);
void __replace_double(Node **list, double data, int64_t index);
void __replace_string(Node **list, const char* data, int64_t index);

void __remove_char(Node **list, char data);
void __remove_int(Node **list, int data);
void __remove_double(Node **list, double data);
void __remove_string(Node **list, const char* data);
void __remove_data_at(Node **list, int64_t index);

int64_t __index_of_char(Node **list, char data);
int64_t __index_of_int(Node **list, int data);
int64_t __index_of_double(Node **list, double data);
int64_t __index_of_string(Node **list, const char* data);

void __invalid_data_type(Node **list, ...);
void __free_list(Node **list);

bool isEmpty(Node *list);
int64_t listLength(Node *list);
void printData(Node *list, int64_t index);
void printList(Node *list);

/**
 * @brief Inserts the specified data at the end of the list.
 * @param listPtr pointer to the list
 * @param data data to be inserted to the list
 * @note For a character data, it should be explicitely converted to char.
*/
#define insert(listPtr, data) insertAt(listPtr, data, listLength(listPtr))

/**
 * @brief Inserts the specified data at the specified index of the list.
 * @param listPtr pointer to the list
 * @param data data to be inserted to the list
 * @param index index at which the specified data is to be inserted
 * @note For a character data, it should be explicitely converted to char.
*/
#define insertAt(listPtr, data, index) _Generic((data), \
        char:        __insert_char, \
        int:         __insert_int, \
        double:      __insert_double, \
        char*:       __insert_string, \
        const char*: __insert_string, \
        default:     __invalid_data_type \
    )(&listPtr, data, index)

/**
 * @brief Replaces the specified data from the specified index of the list.
 * @param listPtr pointer to the list
 * @param data data to be replaced in the list
 * @param index index from which the specified data is to be replaced
 * @note For a character data, it should be explicitely converted to char.
*/
#define replace(listPtr, data, index) _Generic((data), \
        char:        __replace_char, \
        int:         __replace_int, \
        double:      __replace_double, \
        char*:       __replace_string, \
        const char*: __replace_string, \
        default:     __invalid_data_type \
    )(&listPtr, data, index)

/**
 * @brief Removes the specified data from the list.
 * @param listPtr pointer to the list
 * @param data data to be removed from the list
 * @note For a character data, it should be explicitely converted to char.
*/
#define removeData(listPtr, data) _Generic((data), \
        char:        __remove_char, \
        int:         __remove_int, \
        double:      __remove_double, \
        char*:       __remove_string, \
        const char*: __remove_string, \
        default:     __invalid_data_type \
    )(&listPtr, data)

/**
 * @brief Removes the specified data from the specified index of the list.
 * @param listPtr pointer to the list
 * @param index index from which the specified data is to be removed
*/
#define removeDataAt(listPtr, index) __remove_data_at(&listPtr, index)

/**
 * @brief Returns the index of the first occurrence of the specified data in the list, or -1 if the list does not contain the data.
 * @param listPtr pointer to the list
 * @param data data to search for in the list
 * @returns the index of the first occurrence of the specified data in the list, or -1 if the list does not contain the data
 * @note For a character data, it should be explicitely converted to char.
*/
#define indexOf(listPtr, data) _Generic((data), \
        char:        __index_of_char, \
        int:         __index_of_int, \
        double:      __index_of_double, \
        char*:       __index_of_string, \
        const char*: __index_of_string, \
        default:     __invalid_data_type \
    )(&listPtr, data)
    
#endif
