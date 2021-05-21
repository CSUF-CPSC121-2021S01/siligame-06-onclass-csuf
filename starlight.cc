#include "starlight.h"

void Starlight::Draw(graphics::Image &image) {
  image.DrawRectangle(x_, y_, 2, 2, 200, 200, 200);
}

void Starlight::Move(const graphics::Image &image) {
  y_ = y_ + velocity;
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight()) {
    Starlight::SetIsActive(false);
  }
}
