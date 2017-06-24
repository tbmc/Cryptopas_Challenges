cmake_minimum_required(VERSION 3.7)
project(CryptoChallenge)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c set1/crypto_challenge.c set1/crypto_challenge.h utils/utils.c utils/utils.h score/score.c score/score.h utils/sort.c utils/sort.h)
add_executable(CryptoChallenge ${SOURCE_FILES})