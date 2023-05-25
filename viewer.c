#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

/*
 * Check number of arguments passed to the program.
 *
 * @param requiredArgs: value of argc that we want. Must be greater that 0.
 * @return true if number of arguments met, false otherwise. 
 */
bool CheckArgumentNum(int requiredArgs)
{
    bool result = false;

    if(argc == requiredArgs)
    {
        result = true;
    }
    
    return result;
}

int main(int argc, char **argv)
{
    CheckArgumentNum(1)
    return 0;
}
