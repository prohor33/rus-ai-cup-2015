#pragma once

#include "model/Direction.h"
#include "model/Game.h"
#include "PathAnalyzer.h"


namespace model {
  class World;
  class Game;
  class Car;
}

class Utils {
public:
  static void UpdateWorld(const model::World* world_tmp, const model::Game* game_tmp) {
    world = world_tmp;
    game = game_tmp;
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
    return (v + 0.5) * game->getTrackTileSize();
  }
  template<class T>
  static void PrintCoord(const T& x, const T& y) {
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
  static void GlobalPointToLocalInsideTile(double x_in, double y_in, model::Direction orientation, double& x_out, double& y_out);
  
  static const model::World* world;
  static const model::Game* game;
};