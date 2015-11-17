#pragma once

#include "Structs.h"
#include "Direction.h"

namespace model {
  class World;
  class Game;
  class Car;
}

enum PathPatternType {
  RIGHT_TURN = 0,
  LEFT_TURN,
  LONG_LINE,
  LINE
};

class PathPattern {
public:
  PathPattern(std::vector<model::Direction> seq, PathPatternType type_tmp) :
  seq_(seq),
  type(type_tmp) {};
  
  bool CheckIfNow(const std::vector<model::Direction>& path) {
    if (seq_.size() > path.size())
      return false;
    std::vector<model::Direction> path_tmp(path.begin(), path.begin() + seq_.size());
    return seq_ == path_tmp;
  }
  
  PathPatternType type;
private:
  std::vector<model::Direction> seq_;
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
  void Analyze(const std::list<TileNodePtr>& path);
  
private:
  static PathAnalyzer* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  std::list<TileNodePtr> path_;
  std::vector<model::Direction> dir_path_;
  std::vector<PathPattern> patterns_;
};