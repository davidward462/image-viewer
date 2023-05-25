#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

bool CheckArgumentNum(int minArgs, int maxArgs)
{
    if((argc > minArgs) && (argc < maxArgs))
    {
        return true;
    }
    else
    {
        return false;
    }

}

int main(int argc, char **argv)
{
    return 0;
}
