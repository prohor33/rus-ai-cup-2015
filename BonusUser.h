#pragma once

#include "Structs.h"
#include "model/Direction.h"

namespace model {
  class World;
  class Game;
  class Car;
  class Move;
}

class BonusUser {
public:
  static BonusUser* Instance() {
    if (!instance_)
      instance_ = new BonusUser();
    return instance_;
  }
  void UpdateWorld(const model::Car* car, const model::World* world, const model::Game* game, model::Move* move) {
    car_ = car;
    world_ = world;
    game_ = game;
    move_ = move;
  }
  void Use();
  
private:
  void UseProjectile();
  void UseNitro();
  void UseOilStick();

  static BonusUser* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  model::Move* move_;
};