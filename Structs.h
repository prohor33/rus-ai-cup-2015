#pragma once

#include "Direction.h"

struct Coord {
  int x;
  int y;
  bool operator==(const Coord &other) const {
    return x == other.x && y == other.y;
  }
  
};

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