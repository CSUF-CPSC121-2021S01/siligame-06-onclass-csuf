#include "game.h"

void Game::CreateOpponents() {
  opponents.push_back(std::make_unique<Opponent>(50, 50));
  opponents.push_back(std::make_unique<Opponent>(110, 50));
  opponents.push_back(std::make_unique<Opponent>(170, 50));
  opponents.push_back(std::make_unique<Opponent>(230, 50));
  opponents.push_back(std::make_unique<Opponent>(290, 50));
  opponents.push_back(std::make_unique<Opponent>(350, 50));
  opponents.push_back(std::make_unique<Opponent>(410, 50));
}

void Game::CreateStars() {
  if (rand() % 2 == 0) {
    stars.push_back(std::make_unique<Starlight>(rand() % 799 + 1));
  }
}

void Game::Init() {
  daplaya.SetX(500);
  daplaya.SetY(300);
  screen.AddMouseEventListener(*this);
  screen.AddAnimationEventListener(*this);
}

void Game::LaunchProjectiles() {
  std::unique_ptr<OpponentProjectile> temp;
  for (int i = 0; i < opponents.size(); i++) {
    temp = opponents[i]->LaunchProjectile();
    if (temp != nullptr) {
      oprojectiles.push_back(std::move(temp));
    }
  }
}

void Game::UpdateScreen() {
  screen.DrawRectangle(0, 0, 800, 600, 0, 0, 0);
  for (int i = 0; i < stars.size(); i++) {
      stars[i]->Draw(screen);
  }
  if (daplaya.GetIsActive()) {
    daplaya.Draw(screen);
  }
  for (int i = 0; i < opponents.size(); i++) {
      opponents[i]->Draw(screen);
  }
  for (int i = 0; i < oprojectiles.size(); i++) {
      oprojectiles[i]->Draw(screen);
  }
  for (int i = 0; i < pprojectiles.size(); i++) {
      pprojectiles[i]->Draw(screen);
  }
  for (int i = 0; i < leftprojectiles.size(); i++) {
      leftprojectiles[i]->Draw(screen);
  }
  for (int i = 0; i < rightprojectiles.size(); i++) {
      rightprojectiles[i]->Draw(screen);
  }

  if (!HasLost()) {
    screen.DrawText(0, 0, std::to_string(score_), 25,
                    graphics::Color(255, 0, 0));
  } else {
    screen.DrawText(screen.GetWidth() / 2 - 100, screen.GetHeight() / 2,
                    "Game Over", 50, graphics::Color(255, 0, 0));
  }
}

void Game::RemoveInactive() {
  for (int i = opponents.size() - 1; i >= 0; i--) {
    if (!opponents[i]->GetIsActive()) {
      opponents.erase(opponents.begin() + i);
    }
  }
  for (int i = oprojectiles.size() - 1; i >= 0; i--) {
    if (!oprojectiles[i]->GetIsActive()) {
      oprojectiles.erase(oprojectiles.begin() + i);
    }
  }
  for (int i = pprojectiles.size() - 1; i >= 0; i--) {
    if (!pprojectiles[i]->GetIsActive()) {
      pprojectiles.erase(pprojectiles.begin() + i);
    }
  }
  for (int i = leftprojectiles.size() - 1; i >= 0; i--) {
    if (!leftprojectiles[i]->GetIsActive()) {
      leftprojectiles.erase(leftprojectiles.begin() + i);
    }
  }
  for (int i = rightprojectiles.size() - 1; i >= 0; i--) {
    if (!rightprojectiles[i]->GetIsActive()) {
      rightprojectiles.erase(rightprojectiles.begin() + i);
    }
  }
  for (int i = stars.size() - 1; i >= 0; i--) {
    if (!stars[i]->GetIsActive()) {
      stars.erase(stars.begin() + i);
    }
  }
}

void Game::Start(graphics::Image &screen) { screen.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponents.size(); i++) {
    opponents[i]->Move(screen);
  }
  for (int i = 0; i < oprojectiles.size(); i++) {
    oprojectiles[i]->Move(screen);
  }
  for (int i = 0; i < pprojectiles.size(); i++) {
    pprojectiles[i]->Move(screen);
  }
  for (int i = 0; i < leftprojectiles.size(); i++) {
    leftprojectiles[i]->Move(screen);
  }
  for (int i = 0; i < rightprojectiles.size(); i++) {
    rightprojectiles[i]->Move(screen);
  }
  for (int i = 0; i < stars.size(); i++) {
    stars[i]->Move(screen);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents.size(); i++) {
    if (daplaya.IntersectsWith(opponents[i].get())) {
      daplaya.SetIsActive(false);
      opponents[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < oprojectiles.size(); i++) {
    if (oprojectiles[i]->IntersectsWith(&daplaya)) {
      daplaya.SetIsActive(false);
      oprojectiles[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < pprojectiles.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (pprojectiles[i]->IntersectsWith(opponents[j].get())) {
        if (opponents[j]->GetHP() == 0) {
          opponents[j]->SetIsActive(false);
        }
        pprojectiles[i]->SetIsActive(false);
        opponents[j]->ReduceHP();
        if (daplaya.GetIsActive()) {
          score_++;
        }
      }
    }
  }
  for (int i = 0; i < leftprojectiles.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (leftprojectiles[i]->IntersectsWith(opponents[j].get())) {
        if (opponents[j]->GetHP() == 0) {
          opponents[j]->SetIsActive(false);
        }
        leftprojectiles[i]->SetIsActive(false);
        opponents[j]->ReduceHP();
        if (daplaya.GetIsActive()) {
          score_++;
        }
      }
    }
  }
  for (int i = 0; i < rightprojectiles.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (rightprojectiles[i]->IntersectsWith(opponents[j].get())) {
        if (opponents[j]->GetHP() == 0) {
          opponents[j]->SetIsActive(false);
        }
        rightprojectiles[i]->SetIsActive(false);
        opponents[j]->ReduceHP();
        if (daplaya.GetIsActive()) {
          score_++;
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (opponents.size() == 0) {
    CreateOpponents();
  }
  CreateStars();
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - daplaya.GetWidth() / 2;
    int new_y = event.GetY() - daplaya.GetHeight() / 2;
    int old_x = daplaya.GetX();
    int old_y = daplaya.GetY();

    daplaya.SetX(new_x);
    daplaya.SetY(new_y);

    if (daplaya.GetIsActive() && tracker % 5 == 0) {
      pprojectiles.push_back(std::make_unique<PlayerProjectile>(
          daplaya.GetX() + 23, daplaya.GetY()));
      pprojectiles.push_back(std::make_unique<PlayerProjectile>(
          daplaya.GetX(), daplaya.GetY() + 20));
      pprojectiles.push_back(std::make_unique<PlayerProjectile>(
          daplaya.GetX() + 48, daplaya.GetY() +20));
    }
    tracker++;

    if (daplaya.IsOutOfBounds(screen)) {
      daplaya.SetX(old_x);
      daplaya.SetY(old_y);
    }
  }

  if (daplaya.GetIsActive() &&
      event.GetMouseAction() == graphics::MouseAction::kPressed) {
    pprojectiles.push_back(std::make_unique<PlayerProjectile>(
        daplaya.GetX() + 23, daplaya.GetY()));
    leftprojectiles.push_back(std::make_unique<SlantProjectileLeft>(
        daplaya.GetX() + 23, daplaya.GetY()));
    rightprojectiles.push_back(std::make_unique<SlantProjectileRight>(
        daplaya.GetX() + 23, daplaya.GetY()));
  }
}
