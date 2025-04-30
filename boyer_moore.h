#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

int boyer_moore(char *pattern, char *text);

void build_suffix_position(char *pattern, int P, int arr[]);

void build_last_occurrence(char *pattern, int P, int arr[]);

#endif