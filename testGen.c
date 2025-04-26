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

    fprintf(file, "ABABDABACDABABCABAB");
    fclose(file);
}

// For KMP: repeating pattern
void genRepetitive(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < 1000; i++) {
        fprintf(file, "ABABABAB");
    }
    

    fclose(file);
}

// For Rabin-Karp / hash based: very long & random
void genLongRandom(const char* filename, int length) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    srand(time(NULL)); // tried using time as randomness variable 

    for (int i = 0; i < length; i++) {
        char c = 'A' + rand() % 26; // randomness 2: random capital alphabet
        fputc(c, file);
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
