//
// Created by tbmc on 23/06/2017.
//

#ifndef CRYPTOCHALLENGE_UTILS_H
#define CRYPTOCHALLENGE_UTILS_H

#include <stdint.h>
#include <strings.h>

/**
 * 
 * @param code
 * @return
 */
uint8_t getChar64FromCode(uint8_t code);

uint8_t getCodeFromHex(char c);
char getHexFromCode(uint8_t c);

char getFromIn(const char *in, size_t len, int i);

void hexCharToArray(const char *in, size_t len, uint8_t *out);

int hammingWeight32(uint32_t i);
int hammingWeight64(uint64_t x);

int hammingDistance(const char *str1, size_t lenStr1, const char *str2, size_t lenStr2);

#endif //CRYPTOCHALLENGE_UTILS_H
