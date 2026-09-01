#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

using namespace std;

void cleanup(SDL_Window *window);

int main(int argc, char *argv[]) 
{
  // SDL_Init(SDL_INIT_VIDEO);
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
    return 1;
  }
  
  // window
  int width = 720;
  int height = 480;
  SDL_Window *window = SDL_CreateWindow("particle garden", width, height, 0);

  if (!window)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing window", nullptr);
    SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());    
    cleanup(window);
    return 1;
  }
  SDL_Log("window created!");
  SDL_Log("Video driver: %s", SDL_GetCurrentVideoDriver());

  if (!SDL_ShowWindow(window))
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error showing window", window);
    SDL_Log("SDL_ShowWindow failed: %s", SDL_GetError());
    cleanup(window);
    return 1;
  }
  
  // gameloop
  bool running = true;
  while (running)
  {
    SDL_Event event{0};
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        running = false;
      }
    }
    // TODO: make this to a case switch
  }



  cleanup(window);
  return 0;
}


void cleanup(SDL_Window *window)
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}