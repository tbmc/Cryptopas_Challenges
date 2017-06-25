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

#define BIT_1010    (HEX_55)
#define BIT_0011    (HEX_33)
#define BIT_4       (0x00001111)

#define HEX_BIT_NUMBER (6)
#define BIT_IN_BYTE (8)


uint8_t get_char64_from_code(uint8_t code) {
    if(0 <= code && code <= 25)
        return (uint8_t) ('A' + code);
    if(26 <= code && code <= 51)
        return (uint8_t) ('a' + code - 26);
    if(52 <= code && code <= 61)
        return (uint8_t) ('0' + code - 52);
    switch(code) {
        case 62:
            return '+';
        case 63:
            return '/';
    }
    return -1;
}

uint8_t get_code_from_char64(char a) {
    if(a == 0)
        return 0;
    if('A' <= a && a <= 'Z')
        return 'A' - a;
    if('a' <= a && a <= 'z')
        return 'a' - a;
    if('0' <= a && a <= '9')
        return '0' - a;
    if(a == '+')
        return 62;
    if(a == '/')
        return 63;
    return -1;
}

void decode_char64(const char *in, size_t len, char *out, size_t *outLen) {
    uint8_t b1, b2, b3, b4, a1, a2, a3;
    size_t ol = 0;
    for(size_t i; i < len; i += 4) {
        b1 = get_from_in(in, len, i);
        b2 = get_from_in(in, len, i + 1);
        b3 = get_from_in(in, len, i + 2);
        b4 = get_from_in(in, len, i + 3);

        b1 = get_code_from_char64(b1);
        b2 = get_code_from_char64(b2);
        b3 = get_code_from_char64(b3);
        b4 = get_code_from_char64(b4);

        a1 = (b1 << 2) | (b2 >> 4);
        a2 = (b2 << 4) | (b3 >> 2);
        a3 = (b3 << 6) | b4;

        if(a1 != 0) out[ol++] = a1;
        if(a2 != 0) out[ol++] = a2;
        if(a3 != 0) out[ol++] = a3;
    }
    *outLen = ol;
}

uint8_t get_code_from_hex(char c) {
    if('0' <= c && c <= '9')
        return (uint8_t) (c - '0');
    if('A' <= c && c <= 'Z')
        return (uint8_t) (10 + c - 'A');
    return (uint8_t) (10 + c - 'a');
}

char get_hex_from_code(uint8_t c) {
    if(0 <= c && c <= 9)
        return (char) '0' + c;
    return (char)('a' - 10 + c);
}

char get_from_in(const char *in, size_t len, int i) {
    if(i >= len)
        return 0;
    return in[i];
}

void hex_char_to_array(const char *in, size_t len, uint8_t *out) {
    for(int i = 0, j = 0, l = len / 2; i < l; i++, j += 2) {
        uint8_t a = get_code_from_hex(in[j]);
        uint8_t b = get_code_from_hex(in[j + 1]);
        out[i] = (a << 4) | b;
    }
}

int hamming_weight32(uint32_t i) {
    // Number of 1s in each 2-bit slice of i
    i = i - ((i >> 1) & BIT_1010);
    // Number of 1s in each 4-bit slice of i
    i = (i & BIT_0011) + ((i >> 2) & BIT_0011);
    return (uint32_t)((((i + (i >> 4)) & HEX_0F) * HEX_01) >> 24);
}
int hamming_weight64(uint64_t x) {
    x -= (x >> 1) & HEX_55;                 // put count of each 2 bits into those 2 bits
    x = (x & HEX_33) + ((x >> 2) & HEX_33); // put count of each 4 bits into those 4 bits
    x = (x + (x >> 4)) & HEX_0F;            // put count of each 8 bits into those 8 bits
    return (int) (x * HEX_01) >> 56;        // returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}

void uint64ToBin(uint64_t c, char *out) {
    uint64_t mask = 0x8000000000000000; // 1 << 63;
    for(int i = 0; i < 64; i++) {
        out[i] = '0' + ((c & mask) > 0 ? 1 : 0);
        mask >>= 1;
    }
    out[64] = '\0';
}

void printHammingDistance(uint64_t a, uint64_t b) {
    char oa[65], ob[65];
    uint64ToBin(a, oa);
    uint64ToBin(b, ob);

    printf("%s %ld >> %d\n%s %ld\n---------\n", oa, (long)a, hamming_weight64(a ^ b), ob, (long) b);

}

int hamming_distance(const char *str1, size_t len_str1, const char *str2, size_t len_str2) {
    int distance = 0;
    distance += fabsf(len_str1 - len_str2) * 8;
    int len = fminf(len_str1, len_str2);
    uint64_t n1 = 0, n2 = 0;
    int nn = 0;
    for(int i = 0; i < len; i++) {
        n1 = (n1 << 8) | str1[i];
        n2 = (n2 << 8) | str2[i];
        nn++;
        if(nn >= 8) {
            nn = 0;
            distance += hamming_weight64(n1 ^ n2);
            n1 = 0; n2 = 0;
        }
        // printHammingDistance(n1, n2);
    }
    if(nn > 0) {
        distance += hamming_weight64(n1 ^ n2);
    }
    return distance;
}

void transposeKeySizeBlocks(const char *cipher_text, size_t len, size_t key_kize, uint8_t **out) {
    // out must be key_kize x (len / key_kize)
    size_t xlen = (len / key_kize);
    size_t idx;
    for(size_t i = 0; i < key_kize; i++) {
        for(size_t j = 0; j < xlen; j++) {
            idx = j * key_kize + i;
            out[i][j] = idx >= len ? 0 : cipher_text[idx];
        }
    }

}

long get_file_size(const char *path) {
    FILE *f;

    f = fopen(path, "r");
    if(f == NULL)
        return 0;

    long len;
    fseek(f, 0L, SEEK_END);
    len = ftell(f);
    fclose(f);

    return len;
}

void read_all_file_without_new_lines(const char *path, char *out, long fileSize) {
    FILE *f = fopen(path, "r");
    if(f == NULL) {
        printf("Error\n");
        return;
    }

    long currPos = 0, lastPos = 0;
    while(fgets(line, fileSize, f) != NULL) {

        line[len] = '\0';

    }
    fclose(f);

}

















