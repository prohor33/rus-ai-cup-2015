#pragma once

#include "Structs.h"

namespace model {
  class World;
  class Game;
  class Car;
}

class PathAnalyzer {
public:
  PathAnalyzer() :
  car_(nullptr),
  world_(nullptr),
  game_(nullptr) {};
  static PathAnalyzer* Instance() {
    if (!instance_)
      instance_ = new PathAnalyzer();
    return instance_;
  }
  void UpdateWorld(const model::Car* car, const model::World* world, const model::Game* game) {
    car_ = car;
    world_ = world;
    game_ = game;
  }
  void Analyze(const std::list<TileNodePtr>& path);
  
private:
  static PathAnalyzer* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  std::list<TileNodePtr> path_;
};