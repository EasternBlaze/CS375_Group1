#include <stdio.h>
#include <string.h>

#define d 256             // Number of characters in input alphabet (ASCII)
#define q 10007             // A prime number to reduce collisions (Division method)
 
int rabinKarp(char* pattern, char* text){
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for portion of text
    int h = 1;
    int matchCount = 0;

    // Edge case: pattern longer than text
    if (m > n){
        //printf("Pattern longer than text. No match.\n");
        return 0;
    }

    for (i = 0; i < m - 1; i++){
        h = (h * d) % q;
    }

    // initial hash values for pattern and first window
    for (i = 0; i < m; i++){
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (i = 0; i <= n - m; i++){
        if (p == t){
            // If hash matches, start comparison
            for (j = 0; j < m; j++){
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m){
                matchCount++; 
                //printf("Pattern found at index %d\n", i);
            }
        }

        // Calculate hash value for next chunk
        if (i < n - m){
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // Make sure t is positive
            if (t < 0){
                t = (t + q);
            }
        }
    }
    return matchCount;
}
