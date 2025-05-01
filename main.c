#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "testGen.h"
#include "kmp.h"
#include "bruteforce.h"
#include "rabin_karp.h"
#include "boyer_moore.h"


//2 function for read the input.txt and provide the output.txt
char* readTextFile(const char* filename)
{
    FILE* file = fopen(filename, "r");//read only for input file
   // handle error case
   if(!file) {
    printf("Error to open file %s\n", filename);
    exit(1);
   }

   //read from first to the end of the textstring
   fseek(file, 0, SEEK_END);
   long size = ftell(file);
   rewind(file);

   //Alocate memory (rescale the size of the memory)
   char* text = (char*)malloc((size + 1)* sizeof(char));
   //handle resize fail;
   if(!text) {
    printf("fail Memory allocate\n");
    exit(1);
   }

   fread(text, sizeof(char), size, file);

   text[size] = '\0'; //Include Null terminate of the string
    
   fclose(file);
   return text;
}


void writeOutputFile(const char*filename, const char* output) {
    FILE* file = fopen(filename, "w"); //write only for the output file
    if(!file){
        printf("Cannot open output file\n");
        exit(1);
    }
    fprintf(file, "%s", output);
    fclose(file);
}

void runTest(char* result, const char* caseName, const char* filename, int caseID) {
    //char pattern[] = "ABABAB";

    char* patterns[100];
    int patternCount = 0;
    char line[256];
    
    if (caseID == 2) {  // multiple patterns only for case 2
        FILE* pfile = fopen("multi.txt", "r");
        if (!pfile) {
            printf("Failed to open multi.txt!\n");
            exit(1);
        }
        while (fgets(line, sizeof(line), pfile)) {
            line[strcspn(line, "\n")] = 0;
            patterns[patternCount++] = strdup(line);
        }
        fclose(pfile);
    } else {
        patterns[0] = strdup("ABABAB");
        patternCount = 1;
    }
    


    char* text;
    clock_t start, end;
    double kmp_time = 0, brute_time = 0, rk_time = 0, bm_time = 0;
    int kmp_matches = 0, brute_matches = 0, rk_matches = 0, bm_matches = 0;
    char temp[512]; // Made buffer bigger for printing times + matches

    printf("\n[%s]\n", caseName);

    // Decide which case to run
    switch (caseID) {
        case 0:
            genShort(filename);
            break;
        case 1:
            genRepetitive(filename);
            break;
        case 2:
            genMultiple(filename, (const char**)patterns, patternCount, 10000000);
            break;
        
        case 3:
        genOneMatch(filename);
            break;
        default:
            printf("Invalid case ID\n");
            return;
    }

    //for multi-patterned rabinKarp
    text = readTextFile(filename); // must be called before any algorithm uses `text`

    // Rabin-Karp timing — done ONCE for the whole test case
    start = clock();
    if (caseID == 2) {
        rk_matches = rabinKarpMulti((const char**)patterns, patternCount, text);
    } else {
        rk_matches = rabinKarp(patterns[0], text);
    }
    end = clock();
    rk_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    for (int p = 0; p < patternCount; p++) {
        char* pattern = patterns[p];

        // Time Brute Force
        start = clock();
        brute_matches += bruteforce(pattern, text);
        end = clock();
        brute_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        // Time KMP
        start = clock();
        kmp_matches += KMP(pattern, text);
        end = clock();
        kmp_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        /*
        // Time for Rabin-Karp
        start = clock();
        rk_matches += rabinKarp(pattern, text);
        end = clock();
        rk_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        */

        // Time Boyer-Moore
        start = clock();
        bm_matches += boyer_moore(pattern, text);
        end = clock();
        bm_time += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        free(patterns[p]);
    }
    // Print result
    printf("Brute Force time: %.2f ms, Matches: %d\n", brute_time, brute_matches);
    printf("KMP time: %.2f ms, Matches: %d\n", kmp_time, kmp_matches);
    printf("Rabin-Karp time: %.2f ms, Matches: %d\n", rk_time, rk_matches);
    printf("Boyer-Moore time: %.2f ms, Matches: %d\n", bm_time, bm_matches);

    // Write result to result buffer
    sprintf(temp, "[%s]\n", caseName);
    sprintf(temp + strlen(temp), "Brute Force: %.2f ms, Matches: %d\n", brute_time, brute_matches);
    sprintf(temp + strlen(temp), "KMP: %.2f ms, Matches: %d\n", kmp_time, kmp_matches);
    sprintf(temp + strlen(temp), "Rabin-Karp: %.2f ms, Matches: %d\n", rk_time, rk_matches);
    sprintf(temp + strlen(temp), "Boyer-Moore: %.2f ms, Matches: %d\n\n", bm_time, bm_matches);

    strcat(result, temp);

    free(text);
}

int main() {
    /*
    char *text = readTextFile("test.txt"); //read the text only
    char pattern[] = "ABABCABAB";

    printf("Running KMP:\n");
    KMP(pattern, text);

    printf("\nRunning Brute Force:\n");
    bruteforce(pattern, text);

    //writeOutputFile("output.txt", "Pattern matching complete!\n");
    free(text); //free memory space

    return 0;
    */

    const char* testFile = "test.txt";
    char result[4096] = "";  // buffer to store results

    runTest(result, "Short Case", testFile, 0);
    runTest(result, "Repetitive Pattern Case", testFile, 1);
    runTest(result, "Multiple Patterns Case", testFile, 2);
    runTest(result, "Edge/Noise Case", testFile, 3);

    writeOutputFile("output.txt", result);

    printf("\nall tests completed.\n");
    return 0;
}

