#pragma once

#include "Structs.h"
#include "Direction.h"
#include "PathPattern.h"

namespace model {
  class World;
  class Game;
  class Car;
}

enum TrajTileType {
  TTT_FORWARD = 0,
  TTT_RIGHT_TURN,
  TTT_LEFT_TURN
};

class TrajTile {
public:
  TrajTile(TrajTileType type_tmp, int x_tmp, int y_tmp, model::Direction orientation_tmp) :
  type(type_tmp),
  x(x_tmp),
  y(y_tmp),
  orientation(orientation_tmp) {
    const int N_CELLS_IN_TILE = 10;
    for (int i = 0; i < N_CELLS_IN_TILE; i++)
      field_.push_back(std::vector<double>(N_CELLS_IN_TILE));

    const double val_border = -1.;
    const int last = N_CELLS_IN_TILE - 1;

    for (int x = 0; x < N_CELLS_IN_TILE; x++) {
      for (int y = 0; y < N_CELLS_IN_TILE; y++) {
        field_[x][y] = 0.;

        switch (type) {
        case TTT_FORWARD:
          if (x == 0 || x == last)
            field_[x][y] += val_border;
          break;
        case TTT_RIGHT_TURN:
          if ((x == 0 || y == 0) ||
            (x == last && y == last)) {
            
            field_[x][y] += val_border;
          }
          break;
        case TTT_LEFT_TURN:
          if ((x == last || y == 0) ||
            (x == 0 && y == last)) {

            field_[x][y] += val_border;
          }
          break;
        }
      }
    }
  }

  TrajTileType type;
  int x, y;
  model::Direction orientation;

private:
  std::vector<std::vector<double>> field_;
};

class PathAnalyzer {
public:
  PathAnalyzer();
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
  void Analyze(const std::vector<TileNodePtr>& path);
  
private:
  void BuildBasicTraj();

  static PathAnalyzer* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  std::vector<TileNodePtr> path_;
  std::vector<model::Direction> dir_path_;
  std::vector<PathPattern> patterns_;
};