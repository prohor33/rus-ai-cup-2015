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
  static void UpdateWorld(const model::Car* car_tmp, const model::World* world_tmp, const model::Game* game_tmp) {
    car = car_tmp;
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
  static model::Direction ConvertDirToGlobal(model::Direction dir, model::Direction local);
  static void PrintPattern(PathPatternType type);
  static void GlobalPointToLocalInsideTile(double x_in, double y_in, model::Direction orientation, double& x_out, double& y_out);
  static double AngleToNormal(double angle);
  static bool IsRightTurn(double from, double to);
  static void RotateVector(double v_in_x, double v_in_y, double angle, double& v_out_x, double& v_out_y);
  static void RotateToOrientation(double x_in, double y_in, model::Direction orientation, double& x_out, double& y_out);
  
  static const model::Car* car;
  static const model::World* world;
  static const model::Game* game;
};