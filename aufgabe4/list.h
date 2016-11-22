/** ****************************************************************
 * @file    aufgabe4/list.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    22.11.2016
 * @brief   Header for a dynamic List
 ******************************************************************
 */


#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define VALUE_TYPE uint64_t

typedef struct Node_s Node;

struct Node_s{
    Node *next;
    VALUE_TYPE value;
};

typedef struct{
    Node *first;
    int size;
}List;

typedef struct{
    List *list;
    Node *next;
    int current_index;
} Iterator;

/**
 * @brief Initializes a new list
 *
 * @param[in, out] list the list to initialize
 * @return error code
 * @retval 0           no error
 * @retval E_LIST_NULL the list is null, so it can't be accessed
 */
int list_init(List *list);

/**
 * @brief Removes (deletes) all elements
 *
 * This method MUST be called before list goes out of scope, otherwise there
 * might be unfreed memory left on the heap
 *
 * @param[in, out] list the list to clear
 * @return error code
 * @retval 0           no error
 * @retval E_LIST_NULL the list is null, so it can't be accessed
 */
int list_clear(List *list);

/**
 * @brief Adds a VALUE_TYPE to the List
 *
 * This will allocate memory on the Heap, so make sure you list_clear() your
 * list before it goes out of scope
 *
 * @param[in, out] list the list to add to
 * @param[in] val      the VALUE_TYPE to add
 * @return error code
 * @retval 0           no error
 * @retval E_LIST_NULL the list is null, so it can't be accessed
 * @retval E_NO_MEMORY not enough memory
 */
int list_append(List *list, VALUE_TYPE val);

/**
 * @brief Sets the VALUE_TYPE at a specific index
 *
 * @param[in, out] list the list to add to
 * @param[in] index     the index at which to set
 * @param[in] val       the VALUE_TYPE to set
 * @return error code
 * @retval 0                     no error
 * @retval E_LIST_NULL           the list is null, so it can't be accessed
 * @retval E_INDEX_OUT_OF_BOUNDS the index is invalid
 */
int list_set(List *list, int index, VALUE_TYPE val);


/**
 * @brief Removes an element from the list
 *
 * This method silently ignores errors
 *
 * @param[in, out] list the list to delete from
 * @param[in] index     the index at which to delete
 */
void list_remove(List *list, int index);

/**
 * @brief Returns an Iterator for the List
 *
 * @param[in] list the List to iterate over
 * @return an Iterator
 */
Iterator list_get_iterator(List *list);

/**
 * @brief Checks whether there are more elements to process
 *
 * @param[in, out] it the Iterator to check
 * @return whether or not there are more elements
 */
bool iterator_has_next(Iterator *it);

/**
 * @brief Gets next element to process
 *
 * @param[in, out] it the Iterator to check
 * @param[out] val    will contain the next VALUE_TYPE if method returned 0
 * @return error code
 * @retval 0               no error
 * @retval E_ILLEGAL_STATE the Iterator has no next
 */
int iterator_next(Iterator *it, VALUE_TYPE *val);

/**
 * @brief Remove the current element from the List
 *
 * This method silently ignores errors
 *
 * @param[in, out] it the Iterator to remove on
 */
void iterator_remove(Iterator *it);

/**
 * @brief Update the rectangle stored at the current index in the list
 *
 * @param[in, out] it the Iterator to remove on
 * @param[in] val    the new VALUE_TYPE
 */
void iterator_update(Iterator *it, VALUE_TYPE val);

#endif /* LIST_H_ */
