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

void genMultiple(const char* filename, const char* patterns[], int numPatterns, int length) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int patternInsertInterval = length / (numPatterns * 10);
    int nextInsert = patternInsertInterval;
    int i = 0;

    srand(time(NULL)); // seed random

    while (i < length) {
        if (i >= nextInsert && (i + 50 < length)) {
            const char* pat = patterns[rand() % numPatterns];
            fputs(pat, file);
            i += strlen(pat);
            nextInsert += patternInsertInterval;
        } 
        else {
            char c = 'A' + (rand() % 26);
            fputc(c, file);
            i++;
        }
    }

    fclose(file);
}


// For Boyer-Moore: almost no pattern match
void genOneMatch(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // tried using 'noise' to prevent pattern match
    for (int i = 0; i < 500; i++) {
        fprintf(file, "XYZXYZXYZXYZXYZ");
    }
    fprintf(file, "ABABAB"); // this one's the real pattern
    for (int i = 0; i < 500; i++) {
        fprintf(file, "XYZXYZXYZXYZXYZ");
    }

    fclose(file);
}