#pragma once

#include "Direction.h"

struct Coord {
  int x;
  int y;
  bool operator==(const Coord &other) const {
    return x == other.x && y == other.y;
  }
  
};

struct CoordD {
  double x;
  double y;
  bool operator==(const CoordD &other) const {
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

  template <>
  struct hash<CoordD>
  {
    std::size_t operator()(const CoordD& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<double>()(k.x)
        ^ (hash<double>()(k.y) << 1)) >> 1);
    }
  };

}

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
typedef std::shared_ptr<class TrajTile> TrajTilePtr;