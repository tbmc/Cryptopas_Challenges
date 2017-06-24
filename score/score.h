//
// Created by tbmc on 23/06/2017.
//

#ifndef CRYPTOCHALLENGE_SCORE_H
#define CRYPTOCHALLENGE_SCORE_H

#include <strings.h>
#include <stdbool.h>

bool getCharScore(const char *in, size_t len, float *score);
bool getChi2(const char *in, size_t len, float *outChi2);

#endif //CRYPTOCHALLENGE_SCORE_H
