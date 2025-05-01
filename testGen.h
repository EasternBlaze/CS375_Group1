#ifndef TESTGEN_H
#define TESTGEN_H

void genShort(const char* filename);
void genRepetitive(const char* filename);
void genMultiple(const char* filename, const char* patterns[], int numPatterns, int length);
void genOneMatch(const char* filename);

#endif