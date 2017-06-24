
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

#include "utils/utils.h"
#include "set1/crypto_challenge.h"

int strCmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    printf("%s\n%s\n", s1, s2);
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

bool testHexToBase64() {
    const char in[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    // const char in[] = "573";
    const char wanted[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    char out[150];
    for(int i = 0; i < 150; i++) {
        out[i] = 0;
    }
    size_t len = strlen(in);
    size_t outLen;

    convertHexToBase64(in, len, out, &outLen);
    out[outLen] = '\0';

    if(strCmp(out, wanted) != 0) {
        printf("Erreur : %s\n%s\n%s\n%d %d\n%d\n", in, out, wanted, strlen(out), strlen(wanted), strCmp(out, wanted));
        return false;
    }else {
        printf("Test HexToBase64 ok\n");
    }
    return true;
}

bool testXor() {
    const char a[] = "1c0111001f010100061a024b53535009181c";
    const char b[] = "686974207468652062756c6c277320657965";
    const char wanted[] = "746865206b696420646f6e277420706c6179";
    size_t len = strlen(a);
    char out[len + 1];

    fnXor(a, b, len, out);
    out[len] = '\0';

    if(strCmp(out, wanted) != 0) {
        printf("Erreur !\n");
        printf("%s\n%s\n", wanted, out);
        return false;
    }else {
        printf("Test XOR ok\n");
        return true;
    }
}

bool testDecryptXor() {
    const char a[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t len = strlen(a);
    char b[150];
    float osef1; char osef2;
    decryptXor(a, len, b, &osef1, &osef2);
    b[len] = '\0';
    printf("%s\n", b);
}

bool testDecryptXorFile() {
    findEncryptedLineInFile("others/4.txt");
}

bool testEncryptRepeatedXor() {
    const char *in = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char *wanted = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    const char *key = "ICE";
    char out[500];
    size_t len;
    encryptRepeatedXor(in, strlen(in), key, strlen(key), out, &len);
    out[len] = '\0';
    printf("%s %d\n", out, strcmp(out, wanted));
}

bool testHammerWeight() {
    printf(">>>%d\n", ((uint64_t) (1 << 40)));
    char *a = "this is a test", *b = "wokka wokka!!!";
    printf("Distance : %d\n", hammerDistance(a, strlen(a), b, strlen(b)));
}

int main(int argc, char *argv[]) {
    printf("Crypto Challenge!\n");

    // testHexToBase64();
    // testXor();
    // testDecryptXor();
    // testDecryptXorFile();
    // testEncryptRepeatedXor();
    testHammerWeight();

    char scan[50];
    scanf("%s", scan);

    return 0;
}