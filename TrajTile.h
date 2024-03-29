#pragma once

#include "Structs.h"
#include "model/Direction.h"
#include "model/Bonus.h"
#include "PathPattern.h"


enum TrajTileType {
  TTT_FORWARD = 0,
  TTT_RIGHT_TURN,
  TTT_LEFT_TURN,
  TTT_U_TURN
};

class TrajTile {
public:
  TrajTile(TrajTileType type_tmp, int x_tmp, int y_tmp, model::Direction orientation_tmp);
  
  typedef std::vector<std::vector<double>> FieldT;
  typedef std::function<void (int x, int y, FieldT& field)>  FuncT;
  
  void SetOptimizedTraj(double start_p, double end_p);
  void IterareThroughPath(double start_p, double end_p, FuncT);
  void FindOptimizedEnd(double start_p, double& best_end_p, double& best_sum);
  void StartPointToWorldCoord(double start_p, double& x, double& y);
  void GetSum(double start_p, double end_p, double& sum);
  static double GetFineBetweenTwoPoints(double start_p, double end_p);
  static double GetFineFromDelta(double delta);
  void ApplyObject(const model::RectangularUnit& obj, double v);
  void ApplyBonus(const model::Bonus& b);
  bool IsPointInside(double p_x, double p_y, bool only_for_direction = false);
  bool IsCarInside(const StateInTurn& car_state);
  
  static const int N_CELLS_IN_TILE;
  static const double VAL_BORDER;
  static const double VAL_OPTIMIZED_TRAJ;
  static const double VAL_FOR_TURNS_ON_FORWARD_LINE;
  static const double VAL_BONUS;
  
  TrajTileType type;
  int x, y;
  model::Direction orientation;
  
private:
  FieldT field_;
  typedef std::unordered_map<CoordD, double> SumCacheT;
  SumCacheT cached_sums_;
};