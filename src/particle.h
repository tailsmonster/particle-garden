// particle.h

#pragma once

#include <SDL3/SDL.h>
#include <vector>

using namespace std;

struct Particle {
  float x = 0.0f;
  float y = 0.0f;
  float velocityX = 0.0f;
  float velocityY = 0.0f;
  vector<int> colours = { 255, 255, 255, 255 };
  float life = 1.0f;
  float size = 4.0f;


  void update(float deltaTime);

  void render(SDL_Renderer *renderer) const;

  void setColour(int red, int green, int blue, int alpha = 255);

  void logCordinates(float &x, float &y);

  bool isDead() const;

};