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

  bool CheckPatternOnIndex(const std::vector<model::Direction>& path, int start_index) {
    if (seq_.size() > path.size() + start_index)
      return false;
    std::vector<model::Direction> path_tmp(path.begin() + start_index, path.begin() + start_index + seq_.size());
    return seq_ == path_tmp;
  }
  void ApplyField(const std::vector<TrajTilePtr>& tiles, int start_index);
  int length() const {
    return seq_.size();
  }

  PathPatternType type;
private:
  std::vector<model::Direction> seq_;
  std::vector<double> opt_points_;  // optimized default trajectory points
};