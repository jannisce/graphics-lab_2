#include <SDL2/SDL.h>

// Define the size of the framebuffer
const int FRAMEBUFFER_WIDTH = 60;
const int FRAMEBUFFER_HEIGHT = 60;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

// Define a Color struct to hold the RGB values of a pixel
struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// Declare the framebuffer as a global variable
Color framebuffer[FRAMEBUFFER_SIZE];

// Declare a global clearColor of type Color
Color clearColor = {0, 0, 0, 255}; // Initially set to black

// Declare a global currentColor of type Color
Color currentColor = {150, 29, 200, 255}; // Initially set to white

// Function to clear the framebuffer with the clearColor
void clear()
{
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++)
    {
        framebuffer[i] = clearColor;
    }
}

// Function to set a specific pixel in the framebuffer to the currentColor
void point(int x, int y)
{
    // if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT)
    // {
    //     framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
    // }
    //   // Wrap the x and y coordinates to make them loop around the screen
  x = (x + FRAMEBUFFER_WIDTH) % FRAMEBUFFER_WIDTH;
  y = (y + FRAMEBUFFER_HEIGHT) % FRAMEBUFFER_HEIGHT;

  framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
}

void renderBuffer(SDL_Renderer *renderer)
{
    // Create a texture
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        FRAMEBUFFER_WIDTH,
        FRAMEBUFFER_HEIGHT);

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture,
        NULL,
        framebuffer,
        FRAMEBUFFER_WIDTH * sizeof(Color));

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

// -------------------------------------------------------
// patrones

void addGliderPattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char gliderData[][3] = {
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1}};

    int gliderWidth = 3;
    int gliderHeight = 3;

    for (int y = 0; y < gliderHeight; y++)
    {
        for (int x = 0; x < gliderWidth; x++)
        {
            if (gliderData[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

void addLwssPattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char lwssData[][5] = {
        {0, 1, 1, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 1, 1, 0}};

    int lwssWidth = 5;
    int lwssHeight = 4;

    for (int y = 0; y < lwssHeight; y++)
    {
        for (int x = 0; x < lwssWidth; x++)
        {
            if (lwssData[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

// ...

// Function to apply the rules of Conway's Game of Life to update cells
void applyRules(bool cells[][FRAMEBUFFER_HEIGHT], bool nextGeneration[][FRAMEBUFFER_HEIGHT])
{
    for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++)
    {
        for (int x = 0; x < FRAMEBUFFER_WIDTH; x++)
        {
            int neighbors = 0;

            // Check the 8 neighboring cells
            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    if (dx == 0 && dy == 0)
                        continue; // Skip the center cell
                    int nx = x + dx;
                    int ny = y + dy;

                    // Ensure the neighboring cell is within the bounds of the array
                    if (nx >= 0 && nx < FRAMEBUFFER_WIDTH && ny >= 0 && ny < FRAMEBUFFER_HEIGHT)
                    {
                        if (cells[nx][ny])
                        {
                            neighbors++;
                        }
                    }
                }
            }

            // Apply the rules of Conway's Game of Life
            if (cells[x][y])
            {
                nextGeneration[x][y] = (neighbors == 2 || neighbors == 3);
            }
            else
            {
                nextGeneration[x][y] = (neighbors == 3);
            }
        }
    }
}

void addRpentominoPattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char rpentominoData[][3] = {
        {0, 1, 1},
        {1, 1, 0},
        {0, 1, 0}};

    int rpentominoWidth = 3;
    int rpentominoHeight = 3;

    for (int y = 0; y < rpentominoHeight; y++)
    {
        for (int x = 0; x < rpentominoWidth; x++)
        {
            if (rpentominoData[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

void addDiehardPattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char diehardData[][8] = {
        {0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1}};

    int diehardWidth = 8;
    int diehardHeight = 3;

    for (int y = 0; y < diehardHeight; y++)
    {
        for (int x = 0; x < diehardWidth; x++)
        {
            if (diehardData[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

void addAcornPattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char acornData[][7] = {
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 1}};

    int acornWidth = 7;
    int acornHeight = 3;

    for (int y = 0; y < acornHeight; y++)
    {
        for (int x = 0; x < acornWidth; x++)
        {
            if (acornData[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

void addGosperGliderGunPattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char gosperGliderGunData[][36] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int gosperGliderGunWidth = 36;
    int gosperGliderGunHeight = 9;

    for (int y = 0; y < gosperGliderGunHeight; y++)
    {
        for (int x = 0; x < gosperGliderGunWidth; x++)
        {
            if (gosperGliderGunData[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

void addInfinite1Pattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char infinite1Data[][8] = {
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0}};

    int infinite1Width = 8;
    int infinite1Height = 6;

    for (int y = 0; y < infinite1Height; y++)
    {
        for (int x = 0; x < infinite1Width; x++)
        {
            if (infinite1Data[y][x] != 0)
            {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

void addInfinite2Pattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT])
{
    char infinite2Data[5][5] = {
        {1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1}};

    int infinite2Width = 5;
    int infinite2Height = 5;

    for (int y = 0; y < infinite2Height; y++)
    {
        for (int x = 0; x < infinite2Width; x++)
        {
            if (infinite2Data[y][x] != 0)
            {
                cells[startX + x][startY + y] = 1;
            }
        }
    }
}

void addInfinite3Pattern(int startX, int startY, bool cells[][FRAMEBUFFER_HEIGHT]) {
    char infinite3Data[][39] = {
        {1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1}
    };

    int infinite3Width = 39;
    int infinite3Height = 1;

    for (int y = 0; y < infinite3Height; y++) {
        for (int x = 0; x < infinite3Width; x++) {
            if (infinite3Data[y][x] != 0) {
                cells[startX + x][startY + y] = true;
            }
        }
    }
}

// ...

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    bool running = true; // Declare 'running' variable
    SDL_Event event;     // Declare 'event' variable

    bool cells[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {false};
    bool nextGeneration[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {false}; // New matrix for the next generation

    // ... (rest of the code)

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Clear the framebuffer
        clear();

        // Add the glider pattern at position (10, 10)
        addGliderPattern(50, 20, cells);

        // Add the lwss pattern at position (20, 20)
        addLwssPattern(20, 70, cells);

        // Add the rpentomino pattern at position (30, 30)
        addRpentominoPattern(40, 30, cells);

        // Add the diehard pattern at position (40, 40)
        addDiehardPattern(50, 40, cells);

        // Add the acorn pattern at position (50, 50)
        addAcornPattern(30, 50, cells);

        // Add the gosperglidergun pattern at position (60, 60)
        addGosperGliderGunPattern(20, 60, cells);

        // Add the infinite1 pattern at position (70, 70)
        addInfinite1Pattern(10, 40, cells);

        // Add the infinite2 pattern at position (80, 80)
        addInfinite2Pattern(15, 35, cells);

        // Add the infinite3 pattern at position (90, 90)
        addInfinite3Pattern(10, 80, cells);

        // Apply the rules of Conway's Game of Life
        applyRules(cells, nextGeneration);

        // Copy the nextGeneration back to cells
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++)
        {
            for (int x = 0; x < FRAMEBUFFER_WIDTH; x++)
            {
                cells[x][y] = nextGeneration[x][y];
            }
        }

        // Draw the cells in the framebuffer
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++)
        {
            for (int x = 0; x < FRAMEBUFFER_WIDTH; x++)
            {
                if (cells[x][y])
                {
                    point(x, y);
                }
            }
        }

        // Render the framebuffer to the screen
        renderBuffer(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(10);
    }

    // ...

    return 0;
}