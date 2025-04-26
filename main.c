#include <stdio.h>
#include "kmp.h"
#include "bruteforce.h"

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    printf("Running KMP:\n");
    KMP(pattern, text);

    printf("\nRunning Brute Force:\n");
    bruteforce(pattern, text);

    return 0;
}