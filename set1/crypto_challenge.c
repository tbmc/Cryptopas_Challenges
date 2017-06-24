//
// Created by tbmc on 23/06/2017.
//

#include <stdio.h>
#include <stdint.h>
#include <float.h>

#include "crypto_challenge.h"

#include "../utils/utils.h"
#include "../score/score.h"

#define BIN_2_BITS_RIGHT (0b00000011)
#define BIN_2_BITS_LEFT  (0b11000000)
#define BIN_4_BITS_RIGHT (0b00001111)

void convertHexToBase64(const char *in, size_t len, char *out, size_t *outLen) {
    size_t ol = 0;
    uint8_t a1, a2, a3, o1, o2;
    for(int i = 0; i < len; i += 3) {
        a1 = getCodeFromHex(getFromIn(in, len, i));
        a2 = getCodeFromHex(getFromIn(in, len, i + 1));
        a3 = getCodeFromHex(getFromIn(in, len, i + 2));

        o1 = (a1 << 2) | (a2 >> 2);
        o2 = ((a2 & BIN_2_BITS_RIGHT) << 4) | a3;

        out[ol++] = getChar64FromCode(o1);
        out[ol++] = getChar64FromCode(o2);

    }
    *outLen = ol;
}

void fnXor(const char *in1, const char *in2, size_t len, char *out) {
    for(int i = 0; i < len; i++) {
        uint8_t c = getCodeFromHex(in1[i]) ^ getCodeFromHex(in2[i]);
        out[i] =  getHexFromCode(c);
    }
}

void decryptXor1Char(const char *in, size_t len, char key, char *out) {
    for(int i = 0; i < len; i++) {
        out[i] = in[i] ^ key;
    }
}

void decryptXor(const char *inString, size_t lenIn, char *out, float *outScore, char *outKey) {
    size_t len = lenIn / 2;
    uint8_t inArray[len];
    hexCharToArray(inString, lenIn, inArray);

    char test[len + 1], best[len], key;
    float maxScore = FLT_MAX, score;
    for(uint16_t i = 0; i < 256; i++) {
        decryptXor1Char(inArray, len, i, test);
        test[len] = '\0';
        bool b = getCharScore(test, len, &score);
        if(b && score < maxScore) {
            maxScore = score;
            key = i;
            strcpy(best, test);
            // printf("\n%f %s\n", score, test);
        }
    }

    strcpy(out, best);
    *outScore = score;
    *outKey = key;
}

void findEncryptedLineInFile(const char *path) {
    FILE *f;
    size_t maxSize = 250;
    char line[maxSize];

    f = fopen(path, "r");
    if(f == NULL) {
        printf("Error\n");
        return;
    }

    size_t len;
    char best[maxSize], decoded[maxSize], key;
    float score = FLT_MAX, tempScore;
    while(fgets(line, maxSize, f) != NULL) {
        len = strlen(line) - 1;
        line[len] = '\0';
        decryptXor(line, len, decoded, &tempScore, &key);

        if(strlen(decoded) != len / 2)
            continue;
        if(tempScore < score) {
            score = tempScore;
            strcpy(best, decoded);
            // printf("%f | temp : %s\n", tempScore, decoded);
            printf(":::::::");
        }
        printf("%d %d %s %c\n", (int) tempScore, (int) score, decoded, key);
    }
    fclose(f);
    printf("%f %s\n", score, best);
}


void encryptRepeatedXor(const char *in, size_t len, const char *key, size_t keyLen, char *out, size_t *outLen) {
    size_t ol = 0;
    size_t keyPointer = 0;
    for(int i = 0; i < len; i++) {
        char a = in[i];
        char k = key[keyPointer];
        keyPointer = (keyPointer + 1) % keyLen;
        char e = a ^ k;
        out[ol++] = getHexFromCode(e >> 4);
        out[ol++] = getHexFromCode(e & BIN_4_BITS_RIGHT);
    }
    // out[ol] = '\0';
    *outLen = ol;
}









