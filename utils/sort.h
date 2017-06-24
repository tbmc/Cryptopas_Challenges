//
// Created by tbmc on 24/06/2017.
//

#ifndef CRYPTOCHALLENGE_TSORT_H
#define CRYPTOCHALLENGE_TSORT_H

#include <stdint.h>
#include <strings.h>
#include <stdbool.h>

/**
 * Function used to compare 2 int.
 * Its parameters are voids because it can be passed
 * as parameter to bubbleSort
 * @param a int 1
 * @param b int 2
 * @return 1 if a > b, 0 if a == b and -1 if a < b
 */
int compInt(void *a, void *b);

/**
 * Swap 2 elements of unknown type
 * @param a element 1
 * @param b element 2
 * @param len sizeof(type)
 */
void swapUniversal(void *a, void *b, size_t len);

/**
 * Sort an array
 *
 * @param array Array to sort. It will be modified.
 * @param arrayLen Length of array
 * @param typeSize sizeof(type)
 * @param comp Function used to do comparison. It parameters has to be voids and return an int
 * @param increasingOrder Sort with increasing order if true, or with decreasing order if false
 */
void bubbleSort(void *array, size_t arrayLen, size_t typeSize, int (*comp)(void *a, void *b), bool increasingOrder);


#endif //CRYPTOCHALLENGE_TSORT_H
