//
// Created by tbmc on 23/06/2017.
//

#ifndef CRYPTOCHALLENGE_SCORE_H
#define CRYPTOCHALLENGE_SCORE_H

#include <strings.h>
#include <stdbool.h>

/**
 * Same as @see getCharScore
 * It is just a rename for simplicity and default name
 *
 * @param in
 * @param len
 * @param score
 * @return
 */
bool get_char_score(const char *in, size_t len, float *score);

/**
 * Calculate a score for a string.
 * help to know if the string is english plain text or
 * if text is just random characters
 * @param in String to evaluate
 * @param len Length of in
 * @param outChi2 Pointer to get result in case of success
 * @return true if evaluation is successful or false if not
 */
bool get_chi2(const char *in, size_t len, float *outChi2);

#endif //CRYPTOCHALLENGE_SCORE_H
