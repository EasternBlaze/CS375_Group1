#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boyer_moore.h"

// Build bad character array
void build_last_occurrence(char *pattern, int P, int last[]) {
    for (int i = 0; i < 256; i++) last[i] = -1;
    for (int i = 0; i < P; i++) last[(unsigned char)pattern[i]] = i;
}

// Build good suffix shift array
void build_good_suffix(char *pattern, int P, int *shift) {
    int border[P + 1];
    int i = P, j = P + 1;
    border[i] = j;

    // Border positions
    while (i > 0) {
        while (j <= P && pattern[i - 1] != pattern[j - 1]) {
            if (shift[j] == 0) {
                shift[j] = j - i;
            }
            j = border[j];
        }
        i--; j--;
        border[i] = j;
    }

    // Process prefixes
    j = border[0];
    for (i = 0; i <= P; i++) {
        if (shift[i] == 0) {
            shift[i] = j;
        }
        if (i == j) {
            j = border[j];
        }
    }
}

// Boyer-Moore search function
int boyer_moore(char *pattern, char *text) {
    int T = strlen(text);
    int P = strlen(pattern);
    if (P == 0 || T == 0 || P > T){
        return 0;
    }

    int last[256];
    int *shift = calloc(P + 1, sizeof(int)); // +1 for full match case
    //using pointer because variably sized
    build_last_occurrence(pattern, P, last);
    build_good_suffix(pattern, P, shift);

    int matches = 0;
    int i = 0;

    while (i <= T - P) {
        int j = P - 1;

        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            matches++;
            i += shift[0];  // shift for full match
        } else {
            int bad_shift = j - last[(unsigned char)text[i + j]];
            if (bad_shift < 1){
                bad_shift = 1;
            }

            int good_shift = shift[j + 1];  // shift[j+1] is used for mismatches at j
            int move = bad_shift;
            if (good_shift > bad_shift){
                move = good_shift;
            }

            i += move;
        }
    }

    free(shift);
    return matches;
}
