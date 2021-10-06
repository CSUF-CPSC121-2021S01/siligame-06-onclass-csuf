#include <string>
#include <vector>
#include <iostream>

#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"
#include "starlight.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() { screen.Initialize(800, 600); }
  Game(int width, int height) { screen.Initialize(width, height); }

  graphics::Image &GetGameScreen() { return screen; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponents; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return oprojectiles;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return pprojectiles;
  }
  Player &GetPlayer() { return daplaya; }
  int GetScore() { return score_; }
  bool HasLost() { return lost_; }

  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void CreateStars();
  void LaunchProjectiles();
  void RemoveInactive();
  void Init();
  void UpdateScreen();
  void Start(graphics::Image &screen);
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent &event) override;

 private:
  graphics::Image screen;
  std::vector<std::unique_ptr<Opponent>> opponents;
  std::vector<std::unique_ptr<OpponentProjectile>> oprojectiles;
  std::vector<std::unique_ptr<PlayerProjectile>> pprojectiles;
  std::vector<std::unique_ptr<SlantProjectileLeft>> leftprojectiles;
  std::vector<std::unique_ptr<SlantProjectileRight>> rightprojectiles;
  std::vector<std::unique_ptr<Starlight>> stars;
  Player daplaya;
  int score_ = 0;
  bool lost_ = false;
  int tracker = 0;
};
