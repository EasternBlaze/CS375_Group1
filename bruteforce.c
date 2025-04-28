#include <stdio.h>
#include <string.h>
#include "bruteforce.h"

//Using bruteforce func
int bruteforce(char* pattern, char *text)
{
    int M = strlen(pattern);
    int N = strlen(text);
    int matchCount = 0;

    for(int i =0 ; i<=N-M; i++)
    {
        int j;
        //check pattern match starting from pos i
        for(j=0; j<M; j++)
        {
            if(text[i+j] != pattern[j])
            {
                break;
            }
        }
        //If pattern is match
        if(j==M) {
           // printf("Pattern found at index %d\n", i);
           matchCount++;
        }
    }
    return matchCount;
}

