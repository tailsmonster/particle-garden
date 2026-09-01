#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

using namespace std;

void cleanup(SDL_Window *window, SDL_Renderer *renderer);

int main(int argc, char *argv[]) 
{
  //init
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
    SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());    
    cleanup(nullptr, nullptr);
    return 1;
  }

  // renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

  if (!renderer)
  {
    SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
    cleanup(window, nullptr);
    return 1;
  }

  SDL_Log("Window created!");
  SDL_Log("Video driver: %s", SDL_GetCurrentVideoDriver());
  SDL_Log("Renderer: %s", SDL_GetRendererName(renderer));


  
  // gameloop
  bool running = true;

  while (running)
  {
    SDL_Event event{};
    while(SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_EVENT_QUIT:
          running = false;
          break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 28, 0, 40, 255);
    SDL_RenderClear(renderer);


    // particle draw stuff will go here eventualy

    SDL_RenderPresent(renderer);
  }



  cleanup(window, renderer);
  return 0;
}


void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
  if (renderer)
  {
    SDL_DestroyRenderer(renderer);
  }
  if (window)
  {
    SDL_DestroyWindow(window);
  } 
  SDL_Quit();
}