#include "stdafx.h"
#include "TrajTile.h"
#include "Utils.h"
#include "model/Car.h"
#include "model/World.h"
#include "model/Game.h"
#include "model/RectangularUnit.h"


using namespace std;
using namespace model;

const int TrajTile::N_CELLS_IN_TILE = 10;
const double TrajTile::VAL_BORDER = -100.;
const double TrajTile::VAL_OPTIMIZED_TRAJ = 0.5;
const double TrajTile::VAL_FOR_TURNS_ON_FORWARD_LINE = -0.01;
//const double TrajTile::VAL_FOR_TURNS_ON_FORWARD_LINE = 0.;
const double TrajTile::VAL_BONUS = 0.6;

TrajTile::TrajTile(TrajTileType type_tmp, int x_tmp, int y_tmp, model::Direction orientation_tmp) :
type(type_tmp),
x(x_tmp),
y(y_tmp),
orientation(orientation_tmp) {
  for (int i = 0; i < N_CELLS_IN_TILE; i++)
    field_.push_back(std::vector<double>(N_CELLS_IN_TILE));
  
  const int last = N_CELLS_IN_TILE - 1;
  
  for (int x = 0; x < N_CELLS_IN_TILE; x++) {
    for (int y = 0; y < N_CELLS_IN_TILE; y++) {
      field_[x][y] = 0.;
      
      switch (type) {
        case TTT_FORWARD:
          if (x == 0 || x == last)
            field_[x][y] += VAL_BORDER;
          break;
        case TTT_RIGHT_TURN:
          if ((x == 0 || y == 0) ||
              (x == last && y == last)) {
            
            field_[x][y] += VAL_BORDER;
          }
          break;
        case TTT_LEFT_TURN:
          if ((x == last || y == 0) ||
              (x == 0 && y == last)) {
            
            field_[x][y] += VAL_BORDER;
          }
          break;
      }
    }
  }
}

void TrajTile::IterareThroughPath(double start_p, double end_p, FuncT func) {
  
  double s_x = start_p * (N_CELLS_IN_TILE - 1);
  double s_y = 0.;
  double e_x(0.), e_y(0.);
  switch (type) {
    case TTT_RIGHT_TURN:
      e_x = N_CELLS_IN_TILE - 1;
      e_y = end_p * (N_CELLS_IN_TILE - 1);
      break;
    case TTT_LEFT_TURN:
      e_x = 0.;
      e_y = end_p * (N_CELLS_IN_TILE - 1);
      break;
    case TTT_FORWARD:
      e_x = end_p * (N_CELLS_IN_TILE - 1);
      e_y = N_CELLS_IN_TILE - 1;
      break;
    case TTT_U_TURN:
      return;
    default:
      assert(0);
      break;
  }
  double v_x = e_x - s_x;
  double v_y = e_y - s_y;
  
  
  
  const double d_coef = 0.1;
  for (double cur_coef = 0.; cur_coef < 1.; cur_coef += d_coef) {
    int x = s_x + v_x * cur_coef;
    int y = s_y + v_y * cur_coef;
    func(x, y, field_);
  }
}

void TrajTile::SetOptimizedTraj(double start_p, double end_p) {
  IterareThroughPath(start_p, end_p, [] (int x, int y, FieldT& field) {
    field[x][y] += VAL_OPTIMIZED_TRAJ;
    
    if (x > 0)
      field[x - 1][y] += VAL_OPTIMIZED_TRAJ / 4.;
    if (x < N_CELLS_IN_TILE - 1)
      field[x + 1][y] += VAL_OPTIMIZED_TRAJ / 4.;
    if (y > 0)
      field[x][y - 1] += VAL_OPTIMIZED_TRAJ / 4.;
    if (y < N_CELLS_IN_TILE - 1)
      field[x][y + 1] += VAL_OPTIMIZED_TRAJ / 4.;
  });
}

void TrajTile::FindOptimizedEnd(double start_p, double& best_end_p, double& best_sum) {
  const double delta = 0.1;
  int best_index = -1;
  int index = 0;
  double max_sum = -10000.;
  for (double end_p = 0.2; end_p <= 0.8; end_p += delta) {
    double sum = 0.;
    IterareThroughPath(start_p, end_p, [&] (int x, int y, FieldT& field) {
      sum += field[x][y];
    });
    if (sum > max_sum) {
      best_index = index;
      max_sum = sum;
    }
    index++;
  }
  assert(best_index >= 0);
  best_end_p = 0.2 + best_index * delta;
  best_sum = max_sum;
}

void TrajTile::GetSum(double start_p, double end_p, double& sum) {
  SumCacheT::const_iterator it = cached_sums_.find({ start_p, end_p });
  if (it != cached_sums_.end()) {
    sum = it->second;
    return;
  }
  sum = 0.;
  IterareThroughPath(start_p, end_p, [&](int x, int y, FieldT& field) {
    sum += field[x][y];
  });
  if (type == TTT_FORWARD) {
    sum += GetFineBetweenTwoPoints(start_p, end_p);
  }
  cached_sums_[{start_p, end_p}] = sum;
}

double TrajTile::GetFineBetweenTwoPoints(double start_p, double end_p) {
  return GetFineFromDelta(end_p - start_p);
}

double TrajTile::GetFineFromDelta(double delta) {
  return pow(abs(delta), 2.0) * VAL_FOR_TURNS_ON_FORWARD_LINE;
}

void TrajTile::StartPointToWorldCoord(double start_p, double& world_x, double& world_y) {
  double center_x = Utils::TileToCoord(x);
  double center_y = Utils::TileToCoord(y);
  
  double size = Utils::game->getTrackTileSize();
  
  switch (orientation) {
    case UP:
      world_x = center_x - size / 2. + start_p * size;
      world_y = center_y + size / 2.;
      return;
    case DOWN:
      world_x = center_x + size / 2. - start_p * size;
      world_y = center_y - size / 2.;
      return;
    case RIGHT:
      world_x = center_x - size / 2.;
      world_y = center_y - size / 2. + start_p * size;
      return;
    case LEFT:
      world_x = center_x + size / 2.;
      world_y = center_y + size / 2. - start_p * size;
      return;
    default:
      assert(0);
      break;
  }
}

void TrajTile::ApplyObject(const RectangularUnit& obj, double v) {
  double tile_x = Utils::TileToCoord(x);
  double tile_y = Utils::TileToCoord(y);
  double tile_size = Utils::game->getTrackTileSize();
  
  double obj_x = (obj.getX() - (tile_x - tile_size / 2.)) / tile_size;
  double obj_y = (obj.getY() - (tile_y - tile_size / 2.)) / tile_size;
  if (obj_x < 0. || obj_x > 1. || obj_y < 0. || obj_y > 1.)
    return;

  {
    // apply tile orientation
    double obj_local_x, obj_local_y;
    Utils::GlobalPointToLocalInsideTile(obj_x, obj_y, orientation, obj_local_x, obj_local_y);

    int x = obj_local_x * (N_CELLS_IN_TILE - 1);
    int y = obj_local_y * (N_CELLS_IN_TILE - 1);

    field_[x][y] += v;
    if (x > 0)
      field_[x - 1][y] += v / 4.;
    if (x < N_CELLS_IN_TILE - 1)
      field_[x + 1][y] += v / 4.;
    if (y > 0)
      field_[x][y - 1] += v / 4.;
    if (y < N_CELLS_IN_TILE - 1)
      field_[x][y + 1] += v / 4.;
  }
}

const double VAL_BONUS_NITRO_BOOST = 0.3;
const double VAL_BONUS_REPAIR_KIT_MAX = 1.8;
const double VAL_BONUS_AMMO_CRATE = 1.0;
const double VAL_BONUS_OIL_KANISTER = 0.2;
const double VAL_BONUS_PURE_SCORE = 2.0;

void TrajTile::ApplyBonus(const Bonus& b) {
  switch (b.getType()) {
    case NITRO_BOOST:
      ApplyObject(b, VAL_BONUS_NITRO_BOOST);
      break;
    case REPAIR_KIT:
      ApplyObject(b, 0.2 + VAL_BONUS_REPAIR_KIT_MAX * (1.0 - Utils::car->getDurability()));
      break;
    case AMMO_CRATE:
      ApplyObject(b, VAL_BONUS_AMMO_CRATE);
      break;
    case OIL_CANISTER:
      ApplyObject(b, VAL_BONUS_OIL_KANISTER);
      break;
    case PURE_SCORE:
      ApplyObject(b, VAL_BONUS_PURE_SCORE);
      break;
    default:
      ApplyObject(b, VAL_BONUS);
      break;
  }
}

bool TrajTile::IsPointInside(double p_x_world, double p_y_world, bool only_for_direction) {
  double tile_x = Utils::TileToCoord(x);
  double tile_y = Utils::TileToCoord(y);
  double tile_half_size = Utils::game->getTrackTileSize() / 2.0;
  
  p_x_world -= tile_x;
  p_y_world -= tile_y;
  
  double p_x, p_y;
  Utils::RotateToOrientation(p_x_world, p_y_world, orientation, p_x, p_y);
  
  bool check_max_x = true;
  bool check_min_x = true;
  bool check_max_y = true;
  bool check_min_y = true;
  
  if (only_for_direction) {
    assert(type == TTT_FORWARD); // develope only for this case
    check_min_y = false;
    check_max_y = false;
  }
  
  double padding_max_x = type == TTT_RIGHT_TURN ? 0. : Utils::game->getTrackTileMargin();
  double padding_min_x = type == TTT_LEFT_TURN ? 0. : Utils::game->getTrackTileMargin();
  double padding_max_y = 0.;
  double padding_min_y = type == TTT_FORWARD ? 0. : Utils::game->getTrackTileMargin();
//  double padding_max_x = 0.;
//  double padding_min_x = 0.;
//  double padding_max_y = 0.;
//  double padding_min_y = 0.;
  
  if (check_max_x) {
    if (p_x > tile_half_size - padding_max_x)
      return false;
  }
  
  if (check_min_x) {
    if (p_x < -tile_half_size + padding_min_x)
      return false;
  }
  
  if (check_max_y) {
    if (p_y > tile_half_size - padding_max_y)
      return false;
  }
  
  if (check_min_y) {
    if (p_y < -tile_half_size + padding_min_y)
      return false;
  }

  return true;
}

bool TrajTile::IsCarInside(const StateInTurn& s) {
  if (!IsPointInside(s.x, s.y))
    return false;
  
  if (type != TTT_FORWARD)  // more complex solution only for forward
    return true;
  
  // x - longwise
  double half_size_x = Utils::car->getWidth() / 2.;
  double half_size_y = Utils::car->getHeight() / 2.;
  
  double car_point_x = 0.;
  double car_point_y = 0.;
  // to world coord system
  Utils::RotateVector(half_size_x, half_size_y, -s.car_angle, car_point_x, car_point_y);
  car_point_x += s.x;
  car_point_y += s.y;
  if (!IsPointInside(car_point_x, car_point_y, true))
    return false;
  
  Utils::RotateVector(-half_size_x, half_size_y, -s.car_angle, car_point_x, car_point_y);
  car_point_x += s.x;
  car_point_y += s.y;
  if (!IsPointInside(car_point_x, car_point_y, true))
    return false;
  
  Utils::RotateVector(-half_size_x, -half_size_y, -s.car_angle, car_point_x, car_point_y);
  car_point_x += s.x;
  car_point_y += s.y;
  if (!IsPointInside(car_point_x, car_point_y, true))
    return false;
  
  Utils::RotateVector(half_size_x, -half_size_y, -s.car_angle, car_point_x, car_point_y);
  car_point_x += s.x;
  car_point_y += s.y;
  if (!IsPointInside(car_point_x, car_point_y, true))
    return false;
  
  return true;
}




