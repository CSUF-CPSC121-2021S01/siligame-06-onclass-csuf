#include "player.h"

#include "cpputils/graphics/image.h"
#include "opponent.h"

void Player::Draw(graphics::Image &image) {
  graphics::Image playa;
  playa.Load("ship.bmp");
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      image.SetColor(x_ + j, y_ + i, playa.GetColor(j, i));
    }
  }
}

void Player::Move(const graphics::Image &image) {
  // currently left empty
}

void PlayerProjectile::Draw(graphics::Image &image) {
  graphics::Image gbullet;
  gbullet.Load("pprojectile.bmp");
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      image.SetColor(x_ + j, y_ + i, gbullet.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &image) {
  y_ = y_ - 10;
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
      x_ < 0 || y_ < 0) {
    PlayerProjectile::SetIsActive(false);
  }
}

 // additional classes and functions
void SlantProjectileLeft::Draw(graphics::Image &image) {
  graphics::Image gbullet;
  gbullet.Load("pprojectile.bmp");
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      image.SetColor(x_ + j, y_ + i, gbullet.GetColor(j, i));
    }
  }
}

void SlantProjectileRight::Draw(graphics::Image &image) {
  graphics::Image gbullet;
  gbullet.Load("pprojectile.bmp");
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      image.SetColor(x_ + j, y_ + i, gbullet.GetColor(j, i));
    }
  }
}

void SlantProjectileLeft::Move(const graphics::Image &image) {
  y_ = y_ - 10;
  x_ = x_ - 5;
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
      x_ < 0 || y_ < 0) {
    SlantProjectileLeft::SetIsActive(false);
  }
}

void SlantProjectileRight::Move(const graphics::Image &image) {
  y_ = y_ - 10;
  x_ = x_ + 5;
  if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
      x_ < 0 || y_ < 0) {
    SlantProjectileRight::SetIsActive(false);
  }
}
