#include "stdafx.h"
#include "PathAnalyzer.h"
#include "Utils.h"
#include "model/Car.h"
#include "model/World.h"
#include "model/Game.h"
#include "TrajTile.h"


using namespace std;
using namespace model;

PathAnalyzer* PathAnalyzer::instance_ = nullptr;

PathAnalyzer::PathAnalyzer() :
car_(nullptr),
world_(nullptr),
game_(nullptr),
is_line_now_(false) {
  
  const double PADDING = 0.2;
  const double PADDING_FROM_CENTER = 0.25;

  patterns_.push_back(PathPattern({ UP, UP, RIGHT }, RIGHT_TURN, { PADDING, 1. - PADDING_FROM_CENTER, 1. - PADDING_FROM_CENTER }));
  patterns_.push_back(PathPattern({ UP, RIGHT }, RIGHT_CUT_TURN, { 1. - PADDING_FROM_CENTER, 1. - PADDING_FROM_CENTER }));
  patterns_.push_back(PathPattern({ UP, UP, LEFT }, LEFT_TURN, { 1. - PADDING, PADDING_FROM_CENTER, PADDING_FROM_CENTER }));
  patterns_.push_back(PathPattern({ UP, LEFT }, LEFT_CUT_TURN, { PADDING_FROM_CENTER, PADDING_FROM_CENTER }));
  patterns_.push_back(PathPattern({ UP, UP, UP, UP }, LONG_LINE, {}));
  patterns_.push_back(PathPattern({ UP, UP, UP }, LINE, {}));
};

void PathAnalyzer::Analyze(const std::vector<TileNodePtr>& path) {
  path_ = path;
  is_line_now_ = false;
  
  //int car_x = Utils::CoordToTile(car_->getX());
  //int car_y = Utils::CoordToTile(car_->getY());
  // add current node
  // path_.push_front(TileNodePtr(new TileNode(car_x, car_y, _UNKNOWN_DIRECTION_, TileNodePtr())));

  dir_path_.clear();
  dir_path_.reserve(path_.size());
  Direction local = (*path_.begin())->dir;
  for (auto n : path_) {
    dir_path_.push_back(Utils::ConvertDirToLocal(n->dir, local));
  }
  
//  PathPattern* current_pattern = nullptr;
//  for (auto& p : patterns_) {
//    if (p.CheckIfNow(dir_path_)) {
//      current_pattern = &p;
//      break;
//    }
//  }
//  if (current_pattern)
//    Utils::PrintPattern(current_pattern->type);
//  else
//    cout << "no pattern :(\n";

  BuildBasicTraj();
  ApplyBonuses();
  FindBestTraj();
}

void PathAnalyzer::BuildBasicTraj() {
  assert(dir_path_.size() == path_.size());
  traj_tiles_.clear();

  // insert tiles
  for (int i = 0; i + 1 < (int)dir_path_.size(); i++) {
    model::Direction dir = dir_path_[i];
    model::Direction next_dir = dir_path_[i + 1]; // normalized to start tile direction
    TrajTileType type(TTT_FORWARD);
    if (dir == next_dir) {
      type = TTT_FORWARD;
//      cout << "tile: TTT_FORWARD" << endl;
    } else {
      model::Direction local_next = Utils::ConvertDirToLocal(next_dir, dir);
      switch (local_next) {
      case RIGHT:
        type = TTT_RIGHT_TURN;
//        cout << "tile: TTT_RIGHT_TURN" << endl;
        break;
      case LEFT:
        type = TTT_LEFT_TURN;
//        cout << "tile: TTT_LEFT_TURN" << endl;
        break;
      default:
        assert(0);
      }
    }
    const TileNodePtr& n = path_[i];
    traj_tiles_.push_back(TrajTilePtr(new TrajTile(type, n->x, n->y, n->dir)));
  }

  // fill tiles optimized trajectory for turns
  for (int start_index = 0; start_index < traj_tiles_.size(); start_index++) {
    for (auto& p : patterns_) {
      if (p.CheckPatternOnIndex(dir_path_, start_index)) {

        if (start_index == 0 && (p.type == LONG_LINE || p.type == LINE))
          is_line_now_ = true;

        if (p.IsTurn()) {
          p.ApplyField(traj_tiles_, start_index);
          start_index += p.length();
        }
        break;
      }
    }
  }
}

void FindBestTrajRec(vector<double> var, int tile_n, vector<vector<double>>& variants) {
  if (var.size() >= tile_n) {
    variants.push_back(var);
    return;
  }
  const double delta = 0.1;
  var.push_back(0.);
  for (double start_p = 0.25; start_p <= 0.75; start_p += delta) {
    var.back() = start_p;
    FindBestTrajRec(var, tile_n, variants);
  }
}

void PathAnalyzer::FindBestTraj() {

  // find current car point
  TrajTilePtr& tile0 = traj_tiles_[0];
  double tile0_x = Utils::TileToCoord(tile0->x);
  double tile0_y = Utils::TileToCoord(tile0->y);
  double current_car_point = 0.;
  double current_car_pos_coef_in_tile = 0.;
  switch (tile0->orientation) {
  case UP:
  case DOWN:
    current_car_point = (car_->getX() - tile0_x) / game_->getTrackTileSize() + 0.5;
    current_car_pos_coef_in_tile = abs(tile0_y - car_->getY()) / game_->getTrackTileSize() - 0.5;
    if (tile0->orientation == DOWN)
      current_car_point = 1. - current_car_point;
    break;
  case RIGHT:
  case LEFT:
    current_car_point = (car_->getY() - tile0_y) / game_->getTrackTileSize() + 0.5;
    current_car_pos_coef_in_tile = abs(tile0_x - car_->getX()) / game_->getTrackTileSize() - 0.5;
    if (tile0->orientation == LEFT)
      current_car_point = 1. - current_car_point;
    break;
  default:
    assert(0);
  }

  const int TRAJ_ANALYZE_LENGTH = 4;
  vector<vector<double>> variants;
  const int traj_analyze_length = std::min<int>((int)traj_tiles_.size(), TRAJ_ANALYZE_LENGTH);
  FindBestTrajRec({}, traj_analyze_length, variants);

  vector<vector<double>> results;
  int index = 0;
  int best_index = -1;
  double max_sum = -numeric_limits<double>::max();
  for (auto& var : variants) {
    double sum = 0.;
    for (int tile_i = 0; tile_i + 1 < var.size(); tile_i++) {
      double sum_tmp = 0.;
      traj_tiles_[tile_i]->GetSum(var[tile_i], var[tile_i + 1], sum_tmp);
      sum += sum_tmp;
      if (tile_i == 0 && traj_tiles_[0]->type == TTT_FORWARD) {
        sum += TrajTile::GetFineFromDelta((current_car_point - var[0]) / current_car_pos_coef_in_tile);
      }
    }
    if (sum > max_sum) {
      best_index = index;
      max_sum = sum;
    }
    index++;
  }

  if (best_index < 0) {
    assert(0);
    best_index = 0;
  }
  vector<double> start_points = variants[best_index];
  
  res_world_points_.clear();
//  cout << "current car point: " << current_car_point << endl;
  
//  cout << "start points:\n";
  for (int i = 0; i < start_points.size(); i++) {
//    cout << start_points[i] << endl;
    double x, y;
    traj_tiles_[i]->StartPointToWorldCoord(start_points[i], x, y);
    res_world_points_.push_back({x, y});
  }
}

void PathAnalyzer::ApplyBonuses() {
  for (auto& tile : traj_tiles_) {
    for (auto& b : world_->getBonuses()) {
      tile->ApplyBonus(b);
    }
  }
}






