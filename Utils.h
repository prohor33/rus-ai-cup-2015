#pragma once

#include "Direction.h"
#include "Game.h"
#include "PathAnalyzer.h"


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
  static void PrintCoord(int x, int y) {
    std::cout << "(" << x << ", " << y << ")\n";
  }
  static model::Direction ConvertDirToLocal(model::Direction dir, model::Direction local);
  static void PrintPattern(PathPatternType type) {
    switch (type) {
    case RIGHT_TURN:
      std::cout << "RIGHT_TURN" << std::endl;
      break;
    case LEFT_TURN:
      std::cout << "LEFT_TURN" << std::endl;
      break;
    case LONG_LINE:
      std::cout << "LONG_LINE" << std::endl;
      break;
    case LINE:
      std::cout << "LINE" << std::endl;
      break;
    }
  }
  
private:
  static const model::World* world_;
  static const model::Game* game_;
};