#include "stdafx.h"
#include "TrajTile.h"
#include "Utils.h"
#include "Car.h"
#include "World.h"
#include "Game.h"


using namespace std;
using namespace model;

const int TrajTile::N_CELLS_IN_TILE = 10;
const double TrajTile::VAL_BORDER = -10.;
const double TrajTile::VAL_OPTIMIZED_TRAJ = 1.;

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
  double e_x, e_y;
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
    default:
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


