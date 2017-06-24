//
// Created by tbmc on 23/06/2017.
//

#include "score.h"

#define ALPHABET_SIZE (26)

float english_freq[] = {
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
        0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
        0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
        0.00978, 0.02360, 0.00150, 0.01974, 0.00074,                    // V-Z
};

bool getChi2(const char *in, size_t len, float *outChi2) {
    int count[ALPHABET_SIZE];
    for(int i = 0; i < ALPHABET_SIZE; i++)
        count[i] = 0;
    int ignored = 0, weirdChar = 0;

    for(int i = 0; i < len; i++) {
        char c = in[i];
        if(c >= 'A' && c <= 'Z')
            count[c - 'A']++;
        else if(c >= 'a' && c <= 'z')
            count[c - 'a']++;
        else if(32 == c || c == 33 || c == 44 || c == 46)
            ignored++;
        else if(c >= 32 && c <= 126 || c == 9) {
            ignored++;
            weirdChar++;
        }
        else if(c == 10 || c == 13)
            ignored++;
        else
            return false;
    }

    float chi2 = 0;
    int l = len - ignored;
    // chi2 += 50 * weirdChar;
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        float observed = count[i], expected = l * english_freq[i];
        float difference = observed - expected;
        chi2 += difference * difference / expected;
    }
    *outChi2 = chi2;
    return true;
}

bool getCharScore(const char *in, size_t len, float *score) {
    return getChi2(in, len, score);
}
