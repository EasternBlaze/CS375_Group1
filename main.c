#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "testGen.h"
#include "kmp.h"
#include "bruteforce.h"
#include "rabin_karp.h"


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
    char pattern[] = "ABABCABAB";
    char* text;
    clock_t start, end;
    double kmp_time; double brute_time; double rk_time;
    char temp[256]; // buffer to hold time

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
            genLongRandom(filename, 100000);
            break;
        case 3:
            genNoMatch(filename);
            break;
        default:
            printf("Invalid case ID\n");
            return;
    }

    text = readTextFile(filename);

    start = clock();
    KMP(pattern, text);
    end = clock();
    kmp_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    start = clock();
    bruteforce(pattern, text);
    end = clock();
    brute_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    start = clock();
    rabinKarp(pattern, text);
    end = clock();
    rk_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;


    printf("Brute Force time: %.2f ms\n", brute_time);
    printf("KMP time: %.2f ms\n", kmp_time);
    printf("Rabin_Karp time: %.2f ms\n", rk_time);

    //part to write out results
    sprintf(temp, "[%s]\n", caseName);
    sprintf(temp + strlen(temp), "Brute Force: %.2f ms\n", brute_time);
    sprintf(temp + strlen(temp), "KMP: %.2f ms\n", kmp_time);
    sprintf(temp + strlen(temp), "Rabin-Karp: %.2f ms\n\n", rk_time);

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
    runTest(result, "Long Random Case", testFile, 2);
    runTest(result, "Edge/Noise Case", testFile, 3);

    writeOutputFile("output.txt", result);

    printf("\nall tests completed.\n");
    return 0;
}

