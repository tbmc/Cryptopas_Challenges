//
// Created by tbmc on 23/06/2017.
//

#ifndef CRYPTOCHALLENGE_CRYPTO_CHALLENGE_H
#define CRYPTOCHALLENGE_CRYPTO_CHALLENGE_H

#include <strings.h>


typedef struct
{
    size_t keySize;
    float distance;
} KeySizeDistancePair;


void convert_hex_to_base64(const char *in, size_t len, char *out, size_t *outLen);

void fn_xor(const char *in1, const char *in2, size_t len, char *out);

void decrypt_xor(const char *in_string, size_t len_in, char *out, float *out_score, char *out_key);

void find_encrypted_line_in_file(const char *path);

void encrypt_repeated_xor(const char *in, size_t len, const char *key, size_t key_len, char *out, size_t *out_len);

void find_key_size(const char *cipher_text, size_t len_cipher_text, int min_key_size, int max_key_size);


#endif //CRYPTOCHALLENGE_CRYPTO_CHALLENGE_H
