//
// Created by tbmc on 24/06/2017.
//

#include "sort.h"

#include <math.h>


int comp_int(void *a, void *b) {
    int *p = a, *q = b;
    int r = (*p) - (*q);
    return r / ((int) fabsf(r));
}

void swap_universal(void *a, void *b, size_t len) {
    uint8_t *p = a, *q = b, temp;
    for(size_t i = 0; i < len; i++) {
        temp = p[i];
        p[i] = q[i];
        q[i] = temp;
    }
}


void bubble_sort_optimised(void *array, size_t array_len, size_t type_size, int (*comp)(void *a, void *b), bool increasing_order) {
    bool sorted = false;
    int comp_bool;
    size_t i, j;
    void *p, *q, *idx;
    for(i = array_len - 1; i > 0 && !sorted; i--) {
        sorted = true;
        for(j = 0; j < i; j++) {

            idx = array + (j * type_size);
            p = idx + type_size;
            q = idx;
            comp_bool = comp(p, q);

            if(!increasing_order)
                comp_bool = -comp_bool;

            if(comp_bool < 0) {
                swap_universal(p, q, type_size);
                sorted = false;
            }
        }
    }
}

void bubble_sort(void *array, size_t array_len, size_t type_size, int (*comp)(void *a, void *b), bool increasing_order) {
    bubble_sort_optimised(array, array_len, type_size, comp, increasing_order);
}


