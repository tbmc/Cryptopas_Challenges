//
// Created by tbmc on 23/06/2017.
//

#include <stdio.h>
#include <stdint.h>
#include <float.h>

#include "crypto_challenge.h"

#include "../utils/utils.h"
#include "../score/score.h"
#include "../utils/sort.h"

#define BIN_2_BITS_RIGHT (0b00000011)
#define BIN_2_BITS_LEFT  (0b11000000)
#define BIN_4_BITS_RIGHT (0b00001111)

void convert_hex_to_base64(const char *in, size_t len, char *out, size_t *outLen)
{
    size_t ol = 0;
    uint8_t a1, a2, a3, o1, o2;
    for (int i = 0; i < len; i += 3)
    {
        a1 = get_code_from_hex(get_from_in(in, len, i));
        a2 = get_code_from_hex(get_from_in(in, len, i + 1));
        a3 = get_code_from_hex(get_from_in(in, len, i + 2));

        o1 = (a1 << 2) | (a2 >> 2);
        o2 = ((a2 & BIN_2_BITS_RIGHT) << 4) | a3;

        out[ol++] = get_char64_from_code(o1);
        out[ol++] = get_char64_from_code(o2);

    }
    *outLen = ol;
}

void fn_xor(const char *in1, const char *in2, size_t len, char *out)
{
    for (int i = 0; i < len; i++)
    {
        uint8_t c = get_code_from_hex(in1[i]) ^get_code_from_hex(in2[i]);
        out[i] = get_hex_from_code(c);
    }
}

void decryptXor1Char(const char *in, size_t len, char key, char *out)
{
    for (int i = 0; i < len; i++)
    {
        out[i] = in[i] ^ key;
    }
}

void decrypt_xor(const char *in_string, size_t len_in, char *out, float *out_score, char *out_key)
{
    size_t len = len_in / 2;
    uint8_t in_array[len];
    hex_char_to_array(in_string, len_in, in_array);

    char test[len + 1], best[len], key;
    float max_score = FLT_MAX, score;
    for (uint16_t i = 0; i < 256; i++)
    {
        decryptXor1Char(in_array, len, i, test);
        test[len] = '\0';
        bool b = get_char_score(test, len, &score);
        if (b && score < max_score)
        {
            max_score = score;
            key = i;
            strcpy(best, test);
            // printf("\n%f %s\n", score, test);
        }
    }

    strcpy(out, best);
    *out_score = score;
    *out_key = key;
}

void find_encrypted_line_in_file(const char *path)
{
    FILE *f;
    size_t max_size = 250;
    char line[max_size];

    f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Error\n");
        return;
    }

    size_t len;
    char best[max_size], decoded[max_size], key;
    float score = FLT_MAX, temp_score;
    while (fgets(line, max_size, f) != NULL)
    {
        len = strlen(line) - 1;
        line[len] = '\0';
        decrypt_xor(line, len, decoded, &temp_score, &key);

        if (strlen(decoded) != len / 2)
            continue;
        if (temp_score < score)
        {
            score = temp_score;
            strcpy(best, decoded);
            // printf("%f | temp : %s\n", temp_score, decoded);
            printf(":::::::");
        }
        printf("%d %d %s %c\n", (int) temp_score, (int) score, decoded, key);
    }
    fclose(f);
    printf("%f %s\n", score, best);
}


void encrypt_repeated_xor(const char *in, size_t len, const char *key, size_t key_len, char *out, size_t *out_len)
{
    size_t ol = 0;
    size_t key_pointer = 0;
    for (int i = 0; i < len; i++)
    {
        char a = in[i];
        char k = key[key_pointer];
        key_pointer = (key_pointer + 1) % key_len;
        char e = a ^ k;
        out[ol++] = get_hex_from_code(e >> 4);
        out[ol++] = get_hex_from_code(e & BIN_4_BITS_RIGHT);
    }
    // out[ol] = '\0';
    *out_len = ol;
}


int comp_key_size_distance_pair(void *a, void *b)
{
    KeySizeDistancePair *p = a, *q = b;
    float r = p->distance - q->distance;
    if (r > 0)
        return 1;
    return r == 0 ? 0 : -1;
}

void find_key_size(const char *cipher_text, size_t len_cipher_text, int min_key_size, int max_key_size)
{
    char firstKeySize[100], secondKeySize[100];
    KeySizeDistancePair results[max_key_size - min_key_size + 1];
    size_t idxResults = 0;

    for (size_t keySize = min_key_size; keySize < max_key_size; keySize++)
    {

        strncpy(firstKeySize, cipher_text, keySize);
        firstKeySize[keySize] = '\0';

        strncpy(secondKeySize, cipher_text + keySize, keySize);
        secondKeySize[keySize] = '\0';

        int distance = hamming_distance(firstKeySize, keySize, secondKeySize, keySize);
        float normalizedDistance = (float) distance / (float) keySize;
        results[idxResults++] = (KeySizeDistancePair) {
                .keySize = keySize,
                .distance = normalizedDistance
        };

    }
    bubble_sort(results, idxResults, sizeof(KeySizeDistancePair), &comp_key_size_distance_pair, true);

    for (int i = 0; i < idxResults; i++)
    {
        KeySizeDistancePair p = results[i];
        printf("%d %f\n", p.keySize, p.distance);
    }
}

void decrypt_file6(const char *path)
{
    FILE *f;
    size_t max_size = 250;
    char line[max_size];

    f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Error\n");
        return;
    }

    size_t len;

    while (fgets(line, max_size, f) != NULL)
    {
        len = strlen(line) - 1;
        line[len] = '\0';

    }
    fclose(f);

}









