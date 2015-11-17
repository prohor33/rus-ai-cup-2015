#pragma once

#include "Structs.h"
#include "Direction.h"
#include "PathPattern.h"

namespace model {
  class World;
  class Game;
  class Car;
}

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
  const std::vector<std::vector<double>>& GetPath() const {
    return res_world_points_;
  }
  
private:
  void BuildBasicTraj();
  void FindBestTraj();

  static PathAnalyzer* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  std::vector<TileNodePtr> path_;
  std::vector<model::Direction> dir_path_;
  std::vector<PathPattern> patterns_;
  std::vector<TrajTilePtr> traj_tiles_;
  std::vector<std::vector<double>> res_world_points_;
};