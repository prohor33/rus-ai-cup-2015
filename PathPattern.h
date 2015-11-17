#pragma once

#include "Structs.h"
#include "Direction.h"

enum PathPatternType {
  RIGHT_TURN = 0,
  RIGHT_CUT_TURN,
  LEFT_TURN,
  LEFT_CUT_TURN,
  LONG_LINE,
  LINE
};

class PathPattern {
public:
  PathPattern(std::vector<model::Direction> seq, PathPatternType type_tmp, std::vector<double> opt_points) :
    seq_(seq),
    type(type_tmp),
    opt_points_(opt_points) {};

  bool CheckIfNow(const std::vector<model::Direction>& path) {
    if (seq_.size() > path.size())
      return false;
    std::vector<model::Direction> path_tmp(path.begin(), path.begin() + seq_.size());
    return seq_ == path_tmp;
  }
  void ApplyField(const std::vector<TrajTilePtr>& tiles);

  PathPatternType type;
private:
  std::vector<model::Direction> seq_;
  std::vector<double> opt_points_;  // optimized default trajectory points
};