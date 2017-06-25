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
uint8_t get_char64_from_code(uint8_t code);

/**
 * Return corresponding code from char in base 64
 * @param a Char in base 64
 * @return Code corresponding
 */
uint8_t get_code_from_char64(char a);

/**
 * Decode a string in base 64 to a normal string
 * @param in String of base-64 symbols
 * @param len Length
 * @param out
 * @param outLen
 */
void decode_char64(const char *in, size_t len, char *out, size_t *outLen);

/**
 * Get code from hex char
 * it is the inverse of @see getHexFromCode
 * @param c hex digit
 * @return
 */
uint8_t get_code_from_hex(char c);

/**
 * Get hex digit from code
 * it is the inverse of @see getCodeFromHex
 * @param c
 * @return
 */
char get_hex_from_code(uint8_t c);

/**
 * Get a char from a string or 0 if i >= len
 * @param in Source string
 * @param len Length of in
 * @param i Index of the element to get
 * @return element at the given index or 0
 */
char get_from_in(const char *in, size_t len, int i);

/**
 * Convert a hex string to a char string
 * Output string should have a size = (len / 2) + 1
 * @param in Source hex string
 * @param len Length of in
 * @param out Output char string
 */
void hex_char_to_array(const char *in, size_t len, uint8_t *out);

/**
 * /!\ Not tested !
 *
 * Return Hamming Weight for a 32 bit number
 *
 * @param i 32 bit number
 * @return
 */
int hamming_weight32(uint32_t i);

/**
 * Return Hamming Weight for a 64 bit number
 * @see https://en.wikipedia.org/wiki/Hamming_weight
 * @param x 64 bit number
 * @return Number of 1s in x
 */
int hamming_weight64(uint64_t x);

/**
 * Calculate the number of bit which are different in the 2 strings
 * It does a @see hammingWeight64 on every byte and when length
 * are different, it multiply difference by 8
 * (because 8 bit in each byte)
 * @param str1 String 1
 * @param len_str1 Length of str1
 * @param str2 String 2
 * @param len_str2 Length of str2
 * @return Number of bit different
 */
int hamming_distance(const char *str1, size_t len_str1, const char *str2, size_t len_str2);

/**
 * Return size of file
 * @param path Relative path of the file
 * @return Size of the file in bytes
 */
long get_file_size(const char *path);

/**
 * Read a file and remove new lines
 * @param path Path of the file to read
 * @param out Out string, where will be stocked the entire file
 * @param file_size Size of the file, you need to pass it @see get_file_size
 */
void read_all_file_without_new_lines(const char *path, char *out, long file_size);









#endif //CRYPTOCHALLENGE_UTILS_H
