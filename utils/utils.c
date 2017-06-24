//
// Created by tbmc on 23/06/2017.
//

#include "utils.h"
#include <stdio.h>
#include <math.h>

#define HEX_55      (0x5555555555555555)
#define HEX_33      (0x3333333333333333)
#define HEX_0F      (0x0F0F0F0F0F0F0F0F)
#define HEX_01      (0x0101010101010101)
#define HEX_00FF    (0x00FF00FF00FF00FF)
#define HEX_FF      (0xFFFFFFFFFFFFFFFF)
#define HEX_64_HALF_RIGHT (0x00000000ffffffff)

#define BIT_1010 (HEX_55)
#define BIT_0011 (HEX_33)

uint8_t getChar64FromCode(uint8_t code) {
    if(!(0 <= code && code <= 63)) {
        printf("%d\n", code);
    }
    if(0 <= code && code <= 25)
        return 'A' + code;
    if(26 <= code && code <= 51)
        return 'a' + code - 26;
    if(52 <= code && code <= 61)
        return '0' + code - 52;
    switch(code) {
        case 62:
            return '+';
        case 63:
            return '/';
    }
}

uint8_t getCodeFromHex(char c) {
    if('0' <= c && c <= '9')
        return c - '0';
    if('A' <= c && c <= 'Z')
        return 10 + c - 'A';
    return 10 + c - 'a';
}

char getHexFromCode(uint8_t c) {
    if(0 <= c && c <= 9)
        return '0' + c;
    return 'a' - 10 + c;
}

char getFromIn(const char *in, size_t len, int i) {
    if(i >= len)
        return 0;
    return in[i];
}

void hexCharToArray(const char *in, size_t len, uint8_t *out) {
    for(int i = 0, j = 0, l = len / 2; i < l; i++, j += 2) {
        uint8_t a = getCodeFromHex(in[j]);
        uint8_t b = getCodeFromHex(in[j + 1]);
        out[i] = (a << 4) | b;
    }
}

int hammerWeight32(uint32_t i) {
    // Number of 1s in each 2-bit slice of i
    i = i - ((i >> 1) & BIT_1010);
    // Number of 1s in each 4-bit slice of i
    i = (i & BIT_0011) + ((i >> 2) & BIT_0011);
    return (((i + (i >> 4)) & HEX_0F) * HEX_01) >> 24;
}
int hammerWeight64(uint64_t x) {
    x -= (x >> 1) & HEX_55;                 // put count of each 2 bits into those 2 bits
    x = (x & HEX_33) + ((x >> 2) & HEX_33); // put count of each 4 bits into those 4 bits
    x = (x + (x >> 4)) & HEX_0F;            // put count of each 8 bits into those 8 bits
    return (x * HEX_01) >> 56;              // returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}

void uint64ToBin(uint64_t c, char *out) {
    uint64_t mask = 1 << 63;
    for(int i = 0; i < 64; i++) {
        out[i] = c & mask;
        mask >>= 1;
    }
    out[64] = '\0';
}

void printHammerDistance(uint64_t a, uint64_t b) {
    char oa[65], ob[65];
    uint64ToBin(a, oa);
    uint64ToBin(b, ob);

    printf("%d %d\n%d\n>>>>>>\n", oa, hammerWeight64(a & b), ob);
}

int hammerDistance(const char *str1, size_t lenStr1, const char *str2, size_t lenStr2) {
    int distance = 0;
    distance += fabsf(lenStr1 - lenStr2) * 8;
    int len = fminf(lenStr1, lenStr2);
    uint64_t n1 = 0, n2 = 0;
    int nn = 0;
    for(int i = 0; i < len; i++) {
        n1 = (n1 << 8) | str1[i];
        n2 = (n2 << 8) | str2[i];
        nn++;
        if(nn >= 8) {
            nn = 0;
            distance += hammerWeight64(n1 & n2);
            n1 = 0; n2 = 0;
        }
        printHammerDistance(n1, n2);
    }
    if(nn > 0) {
        distance += hammerWeight64(n1 & n2);
    }
    return distance;
}





