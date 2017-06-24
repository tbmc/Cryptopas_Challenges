//
// Created by tbmc on 24/06/2017.
//

#ifndef CRYPTOCHALLENGE_TSORT_H
#define CRYPTOCHALLENGE_TSORT_H

#include <stdint.h>
#include <strings.h>
#include <stdbool.h>


int compInt(void *a, void *b);

void swapUniversal(void *a, void *b, size_t len);

void bubbleSort(void *array, size_t arrayLen, size_t typeSize, int (*comp)(void *a, void *b), bool increasingOrder);


#endif //CRYPTOCHALLENGE_TSORT_H
