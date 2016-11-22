/** ****************************************************************
 * @file    aufgabe4/list.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    22.11.2016
 * @brief   Implementation for dynamic List module
 ******************************************************************
 */

#include "list.h"
#include "errors.h"

/*
 * Initializes a new list
 */
int list_init(List *list) {
    if (list == NULL) {
        return E_LIST_NULL;
    }

    list->first = NULL;
    list->size = 0;
    return 0;
}

/*
 * Removes (deletes) all elements
 *
 * This method MUST be called before list goes out of scope, otherwise there
 * might be unfreed memory left on the heap
 */
int list_clear(List *list) {
    if (list == NULL) {
        return E_LIST_NULL;
    }
    Node *node = list->first;
    // go through list
    while (node != NULL) {
        Node *next = node->next;
        free(node);
        node = next;
    }
    list->first = NULL;
    list->size = 0;
    return 0;
}

/*
 * Adds a VALUE_TYPE to the List
 */
int list_append(List *list, VALUE_TYPE val) {
    if (list == NULL) {
        return E_LIST_NULL;
    }
    if (list->first == NULL) {
        Node *node = (Node*) malloc(sizeof(Node));
        if (node == NULL) {
            return E_NO_MEMORY;
        }
        node->next = NULL;
        node->value = val;
        list->first = node;
    } else {
        Node *node = list->first;
        // go through list
        while (node->next != NULL) {
            node = node->next;
        }
        Node *new = (Node*) malloc(sizeof(Node));
        if (new == NULL) {
            return E_NO_MEMORY;
        }
        new->next = NULL;
        new->value = val;
        node->next = new;
    }
    list->size++;
    return 0;

}

/*
 * Removes an element from the list
 *
 * This method silently ignores errors
 */
void list_remove(List *list, int index) {
    if (list == NULL) {
        return;
    }
    if (index < 0 || index >= list->size) {
        return;
    }
    if (index == 0) {
        Node *node = list->first;
        list->first = node->next;
        free(node);
    } else {
        Node *node = list->first;
        // go to the one before the index
        for (int i = 0; i < index - 1; i++) {
            node = node->next;
        }
        Node *del = node->next;
        node->next = del->next;
        free(del);
    }
    list->size--;
}

/*
 * Sets the rectangle at a specific index
 */
int list_set(List *list, int index, VALUE_TYPE val) {
    if (list == NULL) {
        return E_LIST_NULL;
    }
    if (index < 0 || index >= list->size) {
        return E_INDEX_OUT_OF_BOUNDS;
    }

    Node *node = list->first;
    // go to the one at the index
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    node->value = val;
    return 0;
}

/*
 * Returns an Iterator for the List
 */
Iterator list_get_iterator(List *list) {
    Iterator it;
    if (list == NULL) {
        it.list = NULL;
        it.next = NULL;
        it.current_index = 0;
    } else {
        it.list = list;
        it.next = list->first;
        it.current_index = 0;
    }
    return it;
}

/*
 * Checks whether there are more elements to process
 */
bool iterator_has_next(Iterator *it) {
    if (it == NULL) {
        return false;
    }
    return it->next != NULL;
}

/*
 * Gets next element to process
 */
int iterator_next(Iterator *it, VALUE_TYPE *val) {
    if (it == NULL) {
        return E_INVALID_STATE;
    } else if (!iterator_has_next(it)) {
        return E_INVALID_STATE;
    }
    *val = it->next->value;
    it->next = it->next->next;
    it->current_index++;
    return 0;
}

/*
 * Remove the current element from the List
 *
 * This method silently ignores errors
 */
void iterator_remove(Iterator *it) {
    if (it == NULL) {
        return;
    }
    it->current_index--;
    list_remove(it->list, it->current_index);
}
/*
 * Update the rectangle stored at the current index in the list
 */
void iterator_update(Iterator *it, VALUE_TYPE val){
    list_set(it->list, it->current_index - 1, val);
}
