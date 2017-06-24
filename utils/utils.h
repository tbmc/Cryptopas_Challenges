//
// Created by tbmc on 23/06/2017.
//

#ifndef CRYPTOCHALLENGE_UTILS_H
#define CRYPTOCHALLENGE_UTILS_H

#include <stdint.h>
#include <strings.h>

/**
 * Return corresponding char in base 64 from number
 * @param code number in [0, 63]
 * @return
 */
uint8_t getChar64FromCode(uint8_t code);

/**
 * Get code from hex char
 * it is the inverse of @see getHexFromCode
 * @param c hex digit
 * @return
 */
uint8_t getCodeFromHex(char c);

/**
 * Get hex digit from code
 * it is the inverse of @see getCodeFromHex
 * @param c
 * @return
 */
char getHexFromCode(uint8_t c);

/**
 * Get a char from a string or 0 if i >= len
 * @param in Source string
 * @param len Length of in
 * @param i Index of the element to get
 * @return element at the given index or 0
 */
char getFromIn(const char *in, size_t len, int i);

/**
 * Convert a hex string to a char string
 * Output string should have a size = (len / 2) + 1
 * @param in Source hex string
 * @param len Length of in
 * @param out Output char string
 */
void hexCharToArray(const char *in, size_t len, uint8_t *out);

/**
 * /!\ Not tested !
 *
 * Return Hamming Weight for a 32 bit number
 *
 * @param i 32 bit number
 * @return
 */
int hammingWeight32(uint32_t i);

/**
 * Return Hamming Weight for a 64 bit number
 * @see https://en.wikipedia.org/wiki/Hamming_weight
 * @param x 64 bit number
 * @return Number of 1s in x
 */
int hammingWeight64(uint64_t x);

/**
 * Calculate the number of bit which are different in the 2 strings
 * It does a @see hammingWeight64 on every byte and when length
 * are different, it multiply difference by 8
 * (because 8 bit in each byte)
 * @param str1 String 1
 * @param lenStr1 Length of str1
 * @param str2 String 2
 * @param lenStr2 Length of str2
 * @return Number of bit different
 */
int hammingDistance(const char *str1, size_t lenStr1, const char *str2, size_t lenStr2);

#endif //CRYPTOCHALLENGE_UTILS_H
