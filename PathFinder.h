#pragma once

#include <vector>
#include <list>
#include <queue>
#include <tuple>
#include <unordered_set>
#include "TileType.h"
#include "Direction.h"

namespace model {
  class World;
  class Game;
  class Car;
}

struct Coord {
  int x;
  int y;
  bool operator==(const Coord &other) const {
    return x == other.x && y == other.y;
  }
  
};

namespace std {
  
  template <>
  struct hash<Coord>
  {
    std::size_t operator()(const Coord& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;
      
      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      
      return ((hash<int>()(k.x)
               ^ (hash<int>()(k.y) << 1)) >> 1);
    }
  };
  
}

class PathFinder {
public:
  PathFinder() :
  world_(nullptr),
  game_(nullptr) {};
  
  static int MAX_TILE_PATTERN_SIZE;
  
  static PathFinder* Instance() {
    if (!instance_)
      instance_ = new PathFinder();
    return instance_;
  }
  void UpdateWorld(const model::World* world, const model::Game* game) {
    world_ = world;
    game_ = game;
  }
  bool FindPathTo(const model::Car* car, int x, int y, model::Direction& dir);
  
private:
  static PathFinder* instance_;
  const model::World* world_;
  const model::Game* game_;
  std::vector<std::vector<model::TileType>> tile_map_;
  std::unordered_set<Coord> visited_tiles_;
  
  struct TileNode {
    TileNode(int tmp_x, int tmp_y, model::Direction tmp_dir, std::shared_ptr<TileNode> tmp_p) :
    x(tmp_x), y(tmp_y), dir(tmp_dir), parent(tmp_p) {};
    int x;
    int y;
    model::Direction dir; // direction to this cell
    std::shared_ptr<TileNode> parent;
  };
    typedef std::shared_ptr<TileNode> TileNodePtr;
  typedef std::queue<TileNodePtr> QueueType;
  QueueType queue_;
  std::list<model::Direction> result_;
  
  model::Direction FindPathRec(TileNodePtr node, int targ_x, int targ_y);
};