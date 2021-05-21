#include <cstdlib>
#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef STARLIGHT
#define STARLIGHT

class Starlight : public GameElement {
 public:
  Starlight() {}
  Starlight(int x) : GameElement(x, 0, 2, 2), velocity(rand() % 11 + 5) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;

 private:
  int velocity;
};

#endif
