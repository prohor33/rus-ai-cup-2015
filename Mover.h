#pragma once

#include "Structs.h"
#include "Direction.h"
#include "PathPattern.h"

namespace model {
  class World;
  class Game;
  class Car;
  class Move;
}

class Mover {
public:
  static Mover* Instance() {
    if (!instance_)
      instance_ = new Mover();
    return instance_;
  }
  void UpdateWorld(const model::Car* car, const model::World* world, const model::Game* game, model::Move* move) {
    car_ = car;
    world_ = world;
    game_ = game;
    move_ = move;
  }
  void Move(const std::vector<std::vector<double>>& path);
  void TurnToPoint(double x, double y);
  
private:
  static Mover* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  model::Move* move_;
  std::vector<std::vector<double>> path_;
};