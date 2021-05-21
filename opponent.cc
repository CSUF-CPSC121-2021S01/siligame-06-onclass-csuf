#include "opponent.h"

#include <string>

#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image &image) {
  graphics::Image oppo;
  oppo.Load("goofy.bmp");
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      image.SetColor(x_ + j, y_ + i, oppo.GetColor(j, i));
    }
  }
}

void OpponentProjectile::Draw(graphics::Image &image) {
  graphics::Image obullet;
  obullet.Load("oprojectile.bmp");
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      image.SetColor(x_ + j, y_ + i, obullet.GetColor(j, i));
    }
  }
}

void Opponent::Move(const graphics::Image &image) {
  x_ = x_ + 1;
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
      x_ < 0 || y_ < 0) {
    Opponent::SetIsActive(false);
  }
}

void OpponentProjectile::Move(const graphics::Image &image) {
  y_ = y_ + speed_;
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
      x_ < 0 || y_ < 0) {
    OpponentProjectile::SetIsActive(false);
  }
}

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile() {
  if (counter % 45 == 0) {
    counter++;
    return std::make_unique<OpponentProjectile>(GetX() + 25, GetY() + 50);
  }
  counter++;
  return nullptr;
}

void Opponent::ReduceHP() {
  hp--;
}
