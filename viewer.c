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

int main(int argc, char **argv)
{
#ifdef DEBUG
    printf("debug mode\n");
#endif

    CheckArgNum(argc, 2);

    char* filename;
    filename = malloc( strlen( argv[1] ) + 1 );
    strcpy( filename, argv[1] );

#ifdef DEBUG
    printf("opening file: %s\n", filename);
#endif
    

    return 0;
}
