#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
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

bool LoadMedia(char* path);

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
        if( windowCreated == false)
        {
            MyError("Failed to create window.");
            success = false;
        }

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
    //The final optimized image
	SDL_Surface* optimizedSurface = NULL;

    // load file from path
    SDL_Surface* loadedSurface = IMG_Load(path);

    // check loaded surface
    if( loadedSurface == NULL)
    {
        SDLError("Unable to load image.");
    }

    // convert to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if( optimizedSurface == NULL)
    {
        SDLError("Unable to optimize image.");
    }

    // free old loaded surface
    SDL_FreeSurface(loadedSurface);

    return optimizedSurface;
}


/**
 * Load image
 * @param path: the path of the file, ie the full file name
 * @return success: true if action succeeded, false otherwise
 */
bool LoadMedia(char* path)
{
    bool success = true;

    // TODO: make this deal with other file types
    gImageSurface = LoadSurface(path);

    if(gImageSurface == NULL)
    {
        SDLError("Image could not be loaded.");
        success = false;
    }

    return success;SDL_Surface *surface;
}

/**
 * Close window
 *
 */
void CloseWindow()
{
    SDL_FreeSurface(gImageSurface);
    gImageSurface = NULL;

    // quit SDL systems
    SDL_Quit();
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

    SetFileType(extension);

    bool initStatus = Init(extension);
    bool loadMediaStatus;

    if( initStatus == false)
    {
        MyError("Failed to initialize.\n");
    }
    else // initialized successfully
    {
        // load media
        loadMediaStatus = LoadMedia(filename);
        if( loadMediaStatus == false)
        {
            MyError("Failed to load media.\n");
        }
        else // successful
        {
            // main loop
            
            // flag
            bool quit = false;

            // event handler
            SDL_Event e;

            //while running
            while( quit == false)
            {
                // check event queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    // user tries to quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                //SDL_BlitSurface(gImageSurface, NULL, gScreenSurface, NULL);

                //Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled( gImageSurface, NULL, gScreenSurface, &stretchRect );

                // update window
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    // free memory
    free(filename);
    free(name);
    free(extension);
    free(filenameCopy);
    free(tokenList);

    return 0;
}
