#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "testGen.h"

// a base, short case.
void genShort(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < 20; i++) {
        fprintf(file, "ABABDABACDABABCABAB"); // repeat 20 times
    }
    fclose(file);
}

// For KMP: repeating pattern
void genRepetitive(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < 12500; i++) {  // 12500 × 8 = 100,000 letters
        fprintf(file, "ABABABAB");
    }
    

    fclose(file);
}
/*
// For Rabin-Karp / hash based: very long & random
// increased frequency of pattern insertion and used full ASCII instead of just alphabets
void genLongRandom(const char* filename, int length) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    // longer lattern for this case
    const char* pattern = "ABACBCACBACBACBABCABCACBCBACABCABCACBCACABCBAAB";
    int patternLen = strlen(pattern);

    int alphabet_size = 95;  // 126 - 32 + 1

    for (int i = 0; i < length;) {
        // Insert the real pattern every ~100 characters
        if ((i % 100 == 0) && (i + patternLen < length)) {
            fputs(pattern, file);
            i += patternLen;
        } else {
            // rng for ASCII character
            char c = 32 + rand() % alphabet_size;
            fputc(c, file);
            i++;
        }
    }

    fclose(file);
}
*/

void genLongRandom(const char* filename, int length) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    const char* pattern = "ABACADABACADABACADABACADABACADABACADABACADABACAD"; // longer pattern
    int patternLen = strlen(pattern);

    for (int i = 0; i < length;) {
        // Insert the pattern very sparsely
        if ((i % 100000 == 0) && (i + patternLen < length)) {
            fputs(pattern, file);
            i += patternLen;
        } else {
            // Choose from a small set of characters (A, B, C, D)
            char c = 'A' + (rand() % 4);
            fputc(c, file);
            i++;
        }
    }

    fclose(file);
}


// For Boyer-Moore: almost no pattern match
void genNoMatch(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // tried using 'noise' to prevent pattern match
    for (int i = 0; i < 500; i++) {
        fprintf(file, "XYZXYZXYZXYZXYZ");
    }
    fprintf(file, "ABABCABAB"); // this one's the real pattern
    for (int i = 0; i < 500; i++) {
        fprintf(file, "XYZXYZXYZXYZXYZ");
    }

    fclose(file);
}
