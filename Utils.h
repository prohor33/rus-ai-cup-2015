#pragma once

#include <string>
#include "Direction.h"
#include "Game.h"

namespace model {
  class World;
  class Game;
  class Car;
}

class Utils {
public:
  static void UpdateWorld(const model::World* world, const model::Game* game) {
    world_ = world;
    game_ = game;
  }
  static int CoordToTile(double v);
  static std::string DirToStr(model::Direction dir) {
    switch (dir) {
      case model::LEFT:
        return "LEFT";
      case model::RIGHT:
        return "RIGHT";
      case model::UP:
        return "UP";
      case model::DOWN:
        return "DOWN";
      default:
        return "WRONG_DIR";
    }
  }
  static double TileToCoord(int v) {
    return (v + 0.5) * game_->getTrackTileSize();
  }
  
private:
  static const model::World* world_;
  static const model::Game* game_;
};