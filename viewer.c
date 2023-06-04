#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#define DEBUG

// Screen dimensions
// Might be changable later
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum fileType
{
    bmp,
    png,
    jpg,
    none,
    error,
};


// Function prototypes
void SDLError(char* msg);

void MyError(char* msg);

void SetFileType(char* type);

bool CreateWindow();

bool Init(char* filetype);

bool LoadMedia();

void CloseWindow();

SDL_Surface* LoadSurface(char* path);

void CheckArgNum(int argc, int requiredArgs);

char** Tokenize(char* string, int stringLen);
    

// Global variables

// type of file read
enum fileType gCurrentType = none;

// The window that we render to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

// The current displayed image (if not PNG)
SDL_Surface* gImageSurface = NULL;

/**
 * Print message to standard error and show SDL error
 *
 * @param msg: message to print. Newline not required
 * @return void
 */
void SDLError(char* msg)
{
    fprintf(stderr, "%s. Error: %s\n", msg, SDL_GetError() );
}

/**
 * Print message to standard error with newline
 *
 * @param msg: message to print.
 * @return void
 */
void MyError(char* msg)
{
    fprintf(stderr, "%s\n");
}

/**
* Get filetype string and set global enum variable
*
* @param filetype: type of file input to the program
* @return void
*/
void SetFileType(char* filetype)
{
    if( strcmp(filetype, "bmp") == 0) // bitmap
    {
        #ifdef DEBUG
        printf("type is bmp\n");
        #endif

        gCurrentType = bmp;
    }
    else if( strcmp(filetype, "png") == 0) // png
    {
        #ifdef DEBUG
        printf("type is png\n");
        #endif

        gCurrentType = png;
    }
    else if( strcmp(filetype, "jpg") == 0) //jpg
    {
        #ifdef DEBUG
        printf("type is jpg\n");
        #endif

        gCurrentType = jpg;
    }
    else // error
    {
        if( strcmp( filetype, "") == 0 ) // empty string
        {
            SDLError("No filetype detected.\n");
            gCurrentType = none;
        }
        else
        {
            SDLError("Filetype not supported.\n");
            gCurrentType = error;
        }

    }
}

/**
 * Create window
 *
 */
bool CreateWindow()
{
    #ifdef DEBUG
    printf("run CreateWindow()\n");
    #endif

    bool success = true;
        // create window
        gWindow = SDL_CreateWindow("Image viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(gWindow == NULL)
        {
            // error
            SDLError("Window could not be created");
            success = false;
        }
    return success;
}

/** 
 * Initialize SDL
 *
 */
bool Init(char* filetype)
{
    #ifdef DEBUG
    printf("run Init(%s)\n", filetype);
    #endif

    bool success = true;

    // initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        // error
        SDLError("SDL failed to initialize");
        success = false;
    }
    else // success
    {

        bool windowCreated = CreateWindow();

        // TODO: init filetype

        // temp
        gScreenSurface = SDL_GetWindowSurface( gWindow );


    }

    return success;
}

/**
*
*
*/
SDL_Surface* LoadSurface(char* path)
{
    return NULL;
}


/**
 * Load image
 *
 */
bool LoadMedia(char* path)
{
    bool success = true;

    // TODO: make this deal with other file types
    gImageSurface = LoadSurface(path);

    if(gImageSurface == NULL)
    {
        SDLError("image could not be loaded.");
        success = false;
    }

    return success;
}

/**
 * Close window
 *
 */
void CloseWindow()
{
    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = NULL;

    SDL_FreeSurface(gImageSurface);
    gImageSurface = NULL;

    return;
}

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
    // TODO: make this more efficient and flexible.
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

    char* filename;
    char* extension;
    char* name;

    // Store command line argument
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
    
    // tokenize and store
    char** tokenList = malloc(stringLen * 2);
    tokenList = Tokenize(filenameCopy, stringLen);

    // copy
    name = malloc( strlen(tokenList[0]) + 1);
    extension = malloc( strlen(tokenList[1]) + 1 );
    strcpy(name, tokenList[0]);
    strcpy(extension, tokenList[1]);


    #ifdef DEBUG
    printf("filename: %s\n", name);
    printf("extension: %s\n", extension);
    #endif


    Init(extension);

    // free memory
    free(filename);
    free(filenameCopy);
    free(tokenList);

    return 0;
}
