#include <stdio.h>
#include <string.h>
#include "boyer_moore.h"

// Preprocess last occurrences
void build_last_occurrence(char *pattern, int P, int last_occurrence[]) {
    for (int i = 0; i < 256; i++)
        last_occurrence[i] = -1;
    for (int i = 0; i < P; i++)
        last_occurrence[(unsigned char)pattern[i]] = i;
}

void build_suffix_position(char *pattern, int P, int arr[]){
    for (int i=P-1; i>=0; i--){
        //for every position in the pattern
        int shifted = 0;
        for (int j=i-1; j>=0; j--){
            int found = 0;
            for (int m=0; m<(P-1-i); m++){
                if(pattern[i+1+m] != pattern[j+m]){
                    found = 1;
                    break;
                }
            }
            //We record where we find the right-most occurance of the suffix, and the resulting offset is i-j
            if(found == 0){
                arr[i] = i - j;
                shifted = 1;
                break;
            }
        }
        if(shifted == 0){//if we did not find a suffix match
            for (int j = P-1- i; j>0; j--) {
                int found = 0;
                for (int k = 0; k < j; k++) {
                    if (pattern[k] != pattern[P - j + k]) {
                        found = 1;
                        break;
                    }
                }
                //record largest prefix match
                if (found == 0) {
                    arr[i] = P-j-i;
                    shifted = 1;
                    break;
                }
            }
            if (shifted == 0){
                arr[i] = P;
                //if we don't find any instance of this suffix again, it means that this does not occur anywhere else, so the pattern will begin after, and no instance of this suffix as a prefix, then we can entirely skip
            }
        }
    }
    arr[P-1] = 1;
}

int boyer_moore(char *pattern, char *text){
    int T = strlen(text);
    int P = strlen(pattern);
    int shift[P];
    int last_occurrence[256]; // ASCII size
    build_last_occurrence(pattern, P, last_occurrence);
    build_suffix_position(pattern, P, shift);
    int matches = 0;
    int i = 0;
    while (i <= T - P) {
        int j = P - 1;
        while (j >= 0 && pattern[j] == text[i + j]){
            j--;
        }
        if (j < 0) {
            matches++;
            i += 1; 
        } else {
            char mismatched_char = text[i + j];
            int l = last_occurrence[(unsigned char)mismatched_char];

            int bad_char_shift;

            if (l < 0) {
                bad_char_shift = j + 1;
            } else {
                bad_char_shift = j - l;
            }

            int suffix_shift = shift[j];

            int max_shift = 0;

            if (bad_char_shift > suffix_shift) {
                max_shift = bad_char_shift;
            } else {
                max_shift = suffix_shift;
            }

            if (max_shift < 1) {
                max_shift = 1;
            }

            i += max_shift;
        }
    }
    return matches;
}
