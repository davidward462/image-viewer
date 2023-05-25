#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

#define DEBUG

/*
 * Check number of arguments passed to the program.
 *
 * @param requiredArgs: value of argc that we want. Must be greater that 0.
 * @return nothing. Exit with error if wrong number of args.
 *
 */
void CheckArgNum(int argc, int requiredArgs)
{
    if(argc != requiredArgs)
    {
        // an error occured
        fprintf(stderr, "Incorrect number of arguments. Expected: %d\n", requiredArgs);
        exit(1);
    }
}

/*
 * Split filename into name and extension.
 *
 * @param string: string to be tokenized.
 * @param stringLen: length of string param.
 * @return tokenList: array of chars containing the filename and extension.
 *
 */
char** Tokenize(char* string, int stringLen)
{
    const char* delim = ".";
    char** tokenList = malloc(stringLen * 2);
    tokenList[0] = strtok(string, delim);
    tokenList[1] = strtok(NULL, delim);
    return tokenList;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    printf("debug mode\n");
#endif

    CheckArgNum(argc, 2);

    // Store command line argument
    char* filename;
    int stringLen = strlen( argv[1] ) + 1;
    filename = malloc( stringLen );
    strcpy( filename, argv[1] );

    // make copy
    char* filenameCopy;
    filenameCopy = malloc(stringLen);
    strcpy( filenameCopy, filename);

#ifdef DEBUG
    printf("opening file: %s\n", filename);
#endif
    
    char** tokenList = malloc(stringLen * 2);
    tokenList = Tokenize(filenameCopy, stringLen);

#ifdef DEBUG
    printf("filename: %s\n", tokenList[0]);
    printf("extension: %s\n", tokenList[1]);
#endif

    // free memory
    free(filename);
    free(filenameCopy);
    

    return 0;
}
