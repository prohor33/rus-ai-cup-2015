#pragma once

#include "Structs.h"
#include "model/Direction.h"

enum PathPatternType {
  U_TURN = 0,
  U_TURN_CUT,
  LEFT_U_TURN,
  LEFT_U_TURN_CUT,
  RIGHT_U_TURN,
  RIGHT_U_TURN_CUT,
  RIGHT_TURN,
  RIGHT_CUT_TURN,
  LEFT_TURN,
  LEFT_CUT_TURN,
  LONG_LINE,
  LINE
};

class PathPattern {
public:
  PathPattern(std::vector<model::Direction> seq, PathPatternType type_tmp, std::vector<double> opt_points, double max_speed_tmp) :
    seq_(seq),
    type(type_tmp),
    opt_points_(opt_points),
    max_speed(max_speed_tmp) {};

  bool CheckPatternOnIndex(const std::vector<model::Direction>& path, int start_index) {
    if (seq_.size() + start_index > path.size())
      return false;
    std::vector<model::Direction> path_tmp(path.begin() + start_index, path.begin() + start_index + seq_.size());
    return seq_ == path_tmp;
  }
  void ApplyField(const std::vector<TrajTilePtr>& tiles, int start_index);
  int length() const {
    return seq_.size();
  }
  bool IsTurn() {
    switch (type) {
    case RIGHT_TURN:
    case LEFT_TURN:
    case LEFT_CUT_TURN:
    case RIGHT_CUT_TURN:
    case RIGHT_U_TURN:
    case RIGHT_U_TURN_CUT:
    case LEFT_U_TURN:
    case LEFT_U_TURN_CUT:
    case U_TURN:
    case U_TURN_CUT:
      return true;
    default:
      return false;
    }
  }
  bool IsRightTurn() {
    switch (type) {
      case RIGHT_TURN:
      case RIGHT_CUT_TURN:
      case RIGHT_U_TURN:
      case RIGHT_U_TURN_CUT:
        return true;
      case LEFT_TURN:
      case LEFT_CUT_TURN:
      case LEFT_U_TURN:
      case LEFT_U_TURN_CUT:
        return false;
      default:
        assert(0);
        return false;
    }
  }
  bool IsCutTurn() const {
    switch (type) {
      case LEFT_CUT_TURN:
      case RIGHT_CUT_TURN:
      case RIGHT_U_TURN_CUT:
      case LEFT_U_TURN_CUT:
      case U_TURN_CUT:
        return true;
      default:
        return false;
    }
  }

  const PathPatternType type;
  const double max_speed;
private:
  std::vector<model::Direction> seq_;
  std::vector<double> opt_points_;  // optimized default trajectory points
};