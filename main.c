#include <stdio.h>
#include <stdlib.h>
#include "kmp.h"
#include "bruteforce.h"

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


int main() {
    char *text = readTextFile("test.txt"); //read the text only
    char pattern[] = "ABABCABAB";

    printf("Running KMP:\n");
    KMP(pattern, text);

    printf("\nRunning Brute Force:\n");
    bruteforce(pattern, text);

    //writeOutputFile("output.txt", "Pattern matching complete!\n");
    free(text); //free memory space

    return 0;
}


