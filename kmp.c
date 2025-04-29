#include <stdio.h>
#include <string.h>
#include "kmp.h"

//Function compute longest prefix suffix in the array
void DoLPS(char* pattern, int M, int* lps)
{
    int length=0;
    lps[0] = 0;
    int i = 1;

    while (i<M) {
        if(pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else {

            if (length != 0) {
                length = lps[length - 1];
            }
            //else length =0
            else{
            lps[i] = 0;
            i++;
            }
        }
    }
}

int KMP(char* pattern, char* text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int lps[M]; //lps which hold longest prefix subproblem
    int matchCount = 0;
    DoLPS(pattern, M, lps);
    int i = 0;
    int j= 0;
    while(i < N)
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if(j==M) 
        {
            //printf("Found pattern at index %d\n", i -j);
            matchCount++;
            j = lps[j-1];
        }
        else if(i<N && pattern[j]!= text[i])
        {
            if(j!=0) {
                j=lps[j-1];

            }
            else{
                i++;
            }
        }
    }
    return matchCount;


}

