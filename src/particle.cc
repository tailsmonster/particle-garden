// particle.cc

#include "./particle.h"

void Particle::update(float deltaTime)
{
  x += velocityX * deltaTime;
  y += velocityY * deltaTime;

  life -= deltaTime;

  velocityY += 80.0f * deltaTime;
  velocityx += 80.0f * deltaTime;
}

void Particle::render(SDL_Renderer *renderer) const
{
  SDL_FRect rect{
    x,
    y,
    4.0f,
    4.0f
  };

  SDL_RenderFillRect(renderer, &rect);
}

void Particle::setColour(int red, int blue, int green)
{
  Particle::colors = { red, blue, green, 255 };
}


void Particle::logCordinates(float &x, float &y)
{
  SDL_Log("x: %f, y: %f", x, y);
}

bool Particle::isDead() const
{
  return life <= 0.0f;
}

