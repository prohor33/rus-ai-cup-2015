#pragma once

#include "TileType.h"
#include "Direction.h"
#include "Structs.h"

namespace model {
  class World;
  class Game;
  class Car;
}

class PathFinder {
public:
  PathFinder() :
  car_(nullptr),
  world_(nullptr),
  game_(nullptr) {};
  
  static int PATH_CHAIN_SIZE;
  
  static PathFinder* Instance() {
    if (!instance_)
      instance_ = new PathFinder();
    return instance_;
  }
  void UpdateWorld(const model::Car* car, const model::World* world, const model::Game* game) {
    car_ = car;
    world_ = world;
    game_ = game;
  }
  bool FindPathChain();
  std::vector<TileNodePtr> get_result() const {
    std::vector<TileNodePtr> res;
    res.reserve(result_.size());
    for (auto& n : result_)
      res.push_back(n);
    return res;
  }
  
private:
  static PathFinder* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  std::vector<std::vector<model::TileType>> tile_map_;
  std::unordered_set<Coord> visited_tiles_;
  QueueType queue_;
  std::list<TileNodePtr> result_;
  std::list<TileNodePtr> local_result_;
  
  bool FindPathFromTo(int waypoint_from, int waypoint_to);
  model::Direction FindPathRec(TileNodePtr node, int targ_x, int targ_y);
  void PrepareToFindRec();
};