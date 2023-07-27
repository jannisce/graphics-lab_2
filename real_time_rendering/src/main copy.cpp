#include <iostream>
#include <SDL2/SDL.h>

const int FRAMEBUFFER_WIDTH = 80;
const int FRAMEBUFFER_HEIGHT = 80;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

struct Color
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

Color framebuffer[FRAMEBUFFER_SIZE];

Color clearColor = {0, 0, 0, 255};       // Initially set to black
Color aliveColor = {255, 255, 255, 255}; // Initially set to white

int x = 10;
int y = 10;

// Function to check the number of alive neighbors around a given cell
int countAliveNeighbors(int x, int y)
{
  int count = 0;
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if (i == 0 && j == 0)
        continue; // Skip the current cell
      int nx = x + i;
      int ny = y + j;
      if (nx >= 0 && nx < FRAMEBUFFER_WIDTH && ny >= 0 && ny < FRAMEBUFFER_HEIGHT)
      {
        if (framebuffer[ny * FRAMEBUFFER_WIDTH + nx].r == aliveColor.r &&
            framebuffer[ny * FRAMEBUFFER_WIDTH + nx].g == aliveColor.g &&
            framebuffer[ny * FRAMEBUFFER_WIDTH + nx].b == aliveColor.b)
        {
          count++;
        }
      }
    }
  }
  return count;
}

void update()
{
  // Create a copy of the framebuffer to store the next state
  Color nextFramebuffer[FRAMEBUFFER_SIZE];

  // Update the state of each cell based on the rules of the Game of Life
  for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++)
  {
    for (int x = 0; x < FRAMEBUFFER_WIDTH; x++)
    {
      int aliveNeighbors = countAliveNeighbors(x, y);
      if (framebuffer[y * FRAMEBUFFER_WIDTH + x].r == aliveColor.r &&
          framebuffer[y * FRAMEBUFFER_WIDTH + x].g == aliveColor.g &&
          framebuffer[y * FRAMEBUFFER_WIDTH + x].b == aliveColor.b)
      {
        // Cell is currently alive
        if (aliveNeighbors < 2 || aliveNeighbors > 3)
        {
          // Cell dies due to underpopulation or overpopulation
          nextFramebuffer[y * FRAMEBUFFER_WIDTH + x] = clearColor;
        }
        else
        {
          // Cell survives
          nextFramebuffer[y * FRAMEBUFFER_WIDTH + x] = aliveColor;
        }
      }
      else
      {
        // Cell is currently dead
        if (aliveNeighbors == 3)
        {
          // Cell becomes alive due to reproduction
          nextFramebuffer[y * FRAMEBUFFER_WIDTH + x] = aliveColor;
        }
        else
        {
          // Cell remains dead
          nextFramebuffer[y * FRAMEBUFFER_WIDTH + x] = clearColor;
        }
      }
    }
  }

  // Copy the next state back to the original framebuffer
  for (int i = 0; i < FRAMEBUFFER_SIZE; i++)
  {
    framebuffer[i] = nextFramebuffer[i];
  }
}

void clear()
{
  for (int i = 0; i < FRAMEBUFFER_SIZE; i++)
  {
    framebuffer[i] = clearColor;
  }
}

void point(int x, int y)
{
  // Wrap the x and y coordinates to make them loop around the screen
  x = (x + FRAMEBUFFER_WIDTH) % FRAMEBUFFER_WIDTH;
  y = (y + FRAMEBUFFER_HEIGHT) % FRAMEBUFFER_HEIGHT;

  framebuffer[y * FRAMEBUFFER_WIDTH + x] = aliveColor;
}

// Function to set 10 pixels alive at the start
void setInitialAlivePixels()
{
  point(10, 30);
  point(11, 31);
  point(12, 30);
  point(13, 30);
  point(13, 29);
  point(20, 30);
  point(21, 31);
  point(22, 30);
  point(23, 30);
  point(23, 29);
  point(35, 35);
  point(36, 35);
  point(35, 36);
  point(36, 36);
  point(37, 36);
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

void render(SDL_Renderer *renderer)
{
  // Update the framebuffer based on the rules of the Game of Life
  update();

  // Render the framebuffer to the screen
  renderBuffer(renderer);
}

int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = SDL_CreateWindow("life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED);

  // Set 10 pixels alive at the start
  setInitialAlivePixels();

  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }

    // Call our render function
    render(renderer);

    // Present the frame buffer to the screen
    SDL_RenderPresent(renderer);

    // Delay to limit the frame rate
    SDL_Delay(1200); // Adjust the delay value as needed
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
