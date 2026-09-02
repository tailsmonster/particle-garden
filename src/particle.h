// particle.h

#pragma once

struct Particle {
  float x = 0.0f;
  float y = 0.0f;
  float velocityX = 0.0f;
  float velocityY = 0.0f;
  vector<int> colors = { 255, 255, 255, 255 };
  float life = 1.0f;


  void update(float deltaTime);

  void render(SDL_Renderer *renderer) const;

  void setColour(int red, int blue, int green);

  void logCordinates(float &x, float &y);
  
  bool isDead() const;

};