// main.cc

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "./particle.h"

using namespace std;

float randomFloat(float min, float max);
void spawnParticles(vector<Particle> &particles, float x, float y, int count);
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


  //time 
  Uint64 previousTime = SDL_GetTicks();

  // mouse state
  float previousMouseX = 0.0f;
  float previousMouseY = 0.0f;

  bool firstMouseFrame = true;
  
  // . ݁₊ ⊹ . ݁ ⟡ ݁ . ⊹ ₊ ݁.
  vector<Particle> particles;
  bool invertedColours = false;
  vector<int> colour1 = { 28, 0, 40, 255 };
  vector<int> colour2 = { 220, 255, 237, 255 };
  // . ݁₊ ⊹ . ݁ ⟡

  
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
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
          invertedColours = !invertedColours;
          SDL_Log("inverted colours!");
          break;
      }
    }

    // calculate delta time
    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;

    // get mouse position
    float mouseX;
    float mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    if (firstMouseFrame)
    {
      previousMouseX = mouseX;
      previousMouseY = mouseY;
      firstMouseFrame = false;
    }

    // get mouse movement
    float mouseDeltaX = mouseX - previousMouseX;
    float mouseDeltaY = mouseY - previousMouseY;
    float mouseDistance = sqrt(mouseDeltaX * mouseDeltaX + mouseDeltaY * mouseDeltaY);

    // particles on window
    if (mouseDistance > 0.3f)
      spawnParticles(particles, mouseX, mouseY, 6);

    previousMouseX = mouseX;
    previousMouseY = mouseY;

    for (Particle &particle : particles)
    {
      particle.update(deltaTime);
      if (invertedColours)
        particle.setColour(colour1[0], colour1[1], colour1[2], colour1[3]);
      else
        particle.setColour(colour2[0], colour2[1], colour2[2], colour2[3]);
    }

    particles.erase(remove_if(particles.begin(), particles.end(), [](const Particle &particle)
    {
      return particle.isDead();
    }), particles.end());



    // bg colour
    if (invertedColours)
    {
      SDL_SetRenderDrawColor(renderer, colour2[0], colour2[1], colour2[2], colour2[3]);    
    } 
    else
    {
      SDL_SetRenderDrawColor(renderer, colour1[0], colour1[1], colour1[2], colour1[3]);
    }
    
    SDL_RenderClear(renderer);

    // draw particles
    for (const Particle &particle : particles)
    {
      particle.render(renderer);
    }
    

    SDL_RenderPresent(renderer);
  }



  cleanup(window, renderer);
  return 0;
}

float randomFloat(float min, float max)
{
  float normalized = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return min + normalized * (max - min);
}

void spawnParticles(vector<Particle> &particles, float x, float y, int count)
{
  for (int i = 0; i < count; i++)
  {
    Particle particle;

    particle.x = x;
    particle.y = y;

    particle.velocityX = randomFloat(-180.0f, 180.0f);
    particle.velocityY = randomFloat(-180.0f, 180.0f);

    particle.life = randomFloat(0.3f, 0.8f);

    particles.push_back(particle);
    particle.logCordinates(x, y);
  }
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
