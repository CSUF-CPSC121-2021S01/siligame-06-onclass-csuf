#include <memory>
#include <cstdlib>

#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef OPPONENT
#define OPPONENT

class Opponent : public GameElement {
 public:
  Opponent() {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50), hp(15) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
  void ReduceHP();
  int GetHP() { return hp; }
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();
  int counter = 0;
  int hp;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5), speed_(rand() % 8 + 5) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
  void SetSpeed(int speed) { speed_ = speed; }
  double speed_;
};
#endif
