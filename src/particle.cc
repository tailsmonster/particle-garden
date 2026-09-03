// particle.cc

#include "./particle.h"

void Particle::update(float deltaTime)
{
  x += velocityX * deltaTime;
  y += velocityY * deltaTime;

  life -= deltaTime;

  velocityY += 80.0f * deltaTime;
  velocityX += 80.0f * deltaTime;
}

void Particle::render(SDL_Renderer *renderer) const
{
  SDL_SetRenderDrawColor(renderer, colours[0], colours[1], colours[2], colours[3]);
  SDL_FRect rect{
    x,
    y,
    4.0f,
    4.0f
  };

  SDL_RenderFillRect(renderer, &rect);
}

void Particle::setColour(int red, int green, int blue, int alpha)
{
  colours = { red, green, blue, alpha };
}


void Particle::logCordinates(float &x, float &y)
{
  SDL_Log("x: %f, y: %f", x, y);
}

bool Particle::isDead() const
{
  return life <= 0.0f;
}

