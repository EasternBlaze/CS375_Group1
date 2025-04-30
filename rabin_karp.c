#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int rabinKarpMulti(const char* patterns[], int numPatterns, char* text) {
    int n = strlen(text);
    if (numPatterns == 1) {
        return rabinKarp((char*)patterns[0], text);
    }

    typedef struct PatternNode {
        const char* pattern;
        struct PatternNode* next;
    } PatternNode;

    typedef struct {
        const char* pattern;
        int len;
        int hash;
    } PatternInfo;

    PatternInfo* infos = malloc(numPatterns * sizeof(PatternInfo));
    if (!infos) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Track unique pattern lengths
    int lengths[100];
    int lengthCount = 0;

    // Precompute pattern hashes and lengths
    for (int i = 0; i < numPatterns; i++) {
        infos[i].pattern = patterns[i];
        infos[i].len = strlen(patterns[i]);

        int m = infos[i].len;
        int p = 0;
        for (int j = 0; j < m; j++) {
            p = (d * p + patterns[i][j]) % q;
        }
        infos[i].hash = p;

        // Register length if not seen
        int found = 0;
        for (int j = 0; j < lengthCount; j++) {
            if (lengths[j] == m) {
                found = 1;
                break;
            }
        }
        if (!found) {
            lengths[lengthCount++] = m;
        }
    }

    // Build hash buckets per (length, hash)
    PatternNode* buckets[100][q];
    memset(buckets, 0, sizeof(buckets));

    for (int i = 0; i < numPatterns; i++) {
        int len = infos[i].len;
        int hash = infos[i].hash;

        int li = -1;
        for (int j = 0; j < lengthCount; j++) {
            if (lengths[j] == len) {
                li = j;
                break;
            }
        }

        PatternNode* node = malloc(sizeof(PatternNode));
        node->pattern = infos[i].pattern;
        node->next = buckets[li][hash];
        buckets[li][hash] = node;
    }

    int totalMatches = 0;

    // --- For each length ---
    for (int li = 0; li < lengthCount; li++) {
        int m = lengths[li];
        if (m > n) continue;

        // Step 3: h = d^(m-1) % q
        int h = 1;
        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }

        // Step 5-8: initial text hash t0
        int t = 0;
        for (int i = 0; i < m; i++) {
            t = (d * t + text[i]) % q;
        }

        // Step 9-14: slide the window
        for (int s = 0; s <= n - m; s++) {
            // Step 10: If pattern hash matches
            PatternNode* node = buckets[li][t];
            while (node) {
                if (strncmp(node->pattern, text + s, m) == 0) {
                    totalMatches++;
                }
                node = node->next;
            }

            // Step 13-14: update rolling hash
            if (s < n - m) {
                t = (d * (t - text[s] * h) + text[s + m]) % q;
                if (t < 0) t += q;
            }
        }
    }

    // Cleanup
    for (int li = 0; li < lengthCount; li++) {
        for (int hval = 0; hval < q; hval++) {
            PatternNode* node = buckets[li][hval];
            while (node) {
                PatternNode* next = node->next;
                free(node);
                node = next;
            }
        }
    }

    free(infos);
    return totalMatches;
}