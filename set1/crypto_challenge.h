//
// Created by tbmc on 23/06/2017.
//

#ifndef CRYPTOCHALLENGE_CRYPTO_CHALLENGE_H
#define CRYPTOCHALLENGE_CRYPTO_CHALLENGE_H

#include <strings.h>

void convertHexToBase64(const char *in, size_t len, char *out, size_t *outLen);

void fnXor(const char *in1, const char *in2, size_t len, char *out);

void decryptXor(const char *inString, size_t lenIn, char *out, float *outScore, char *outKey);

void findEncryptedLineInFile(const char *path);

void encryptRepeatedXor(const char *in, size_t len, const char *key, size_t keyLen, char *out, size_t *outLen);


#endif //CRYPTOCHALLENGE_CRYPTO_CHALLENGE_H
