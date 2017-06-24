//
// Created by tbmc on 24/06/2017.
//

#include "sort.h"

#include <math.h>


int compInt(void *a, void *b) {
    int *p = a, *q = b;
    int r = (*p) - (*q);
    return r / ((int) fabsf(r));
}

void swapUniversal(void *a, void *b, size_t len) {
    uint8_t *p = a, *q = b, temp;
    for(size_t i = 0; i < len; i++) {
        temp = p[i];
        p[i] = q[i];
        q[i] = temp;
    }
}


void bubbleSortOptimised(void *array, size_t arrayLen, size_t typeSize, int (*comp)(void *a, void *b), bool increasingOrder) {
    bool sorted = false;
    int compBool;
    size_t i, j;
    void *p, *q, *idx;
    for(i = arrayLen - 1; i > 0 && !sorted; i--) {
        sorted = true;
        for(j = 0; j < i; j++) {

            idx = array + (j * typeSize);
            p = idx + typeSize;
            q = idx;
            compBool = comp(p, q);

            if(!increasingOrder)
                compBool = -compBool;

            if(compBool < 0) {
                swapUniversal(p, q, typeSize);
                sorted = false;
            }
        }
    }
}

void bubbleSort(void *array, size_t arrayLen, size_t typeSize, int (*comp)(void *a, void *b), bool increasingOrder) {
    bubbleSortOptimised(array, arrayLen, typeSize, comp, increasingOrder);
}


