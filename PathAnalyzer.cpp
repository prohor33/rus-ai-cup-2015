#include "stdafx.h"
#include "PathAnalyzer.h"
#include "Utils.h"
#include "Car.h"
#include "World.h"
#include "Game.h"
#include "TrajTile.h"


using namespace std;
using namespace model;

PathAnalyzer* PathAnalyzer::instance_ = nullptr;

PathAnalyzer::PathAnalyzer() :
car_(nullptr),
world_(nullptr),
game_(nullptr) {
  
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
      cout << "tile: TTT_FORWARD" << endl;
    } else {
      model::Direction local_next = Utils::ConvertDirToLocal(next_dir, dir);
      switch (local_next) {
      case RIGHT:
        type = TTT_RIGHT_TURN;
        cout << "tile: TTT_RIGHT_TURN" << endl;
        break;
      case LEFT:
        type = TTT_LEFT_TURN;
        cout << "tile: TTT_LEFT_TURN" << endl;
        break;
      default:
        assert(0);
      }
    }
    const TileNodePtr& n = path_[i];
    traj_tiles_.push_back(TrajTilePtr(new TrajTile(type, n->x, n->y, n->dir)));
  }

  // fill tiles optimized trajectory for turns
  PathPattern* current_pattern = nullptr;
  for (auto& p : patterns_) {
    if (p.CheckIfNow(dir_path_)) {
      current_pattern = &p;
      break;
    }
  }
  if (current_pattern) {
    switch (current_pattern->type) {
    case RIGHT_TURN:
    case LEFT_TURN:
    case LEFT_CUT_TURN:
    case RIGHT_CUT_TURN:
      cout << "applying turn pattern" << endl;
      current_pattern->ApplyField(traj_tiles_);
      break;
    default:
      {}
    }
  }
}

void PathAnalyzer::FindBestTraj() {
  vector<vector<double>> results;
  const double delta = 0.1;
  int index = 0;
  int best_index = -1;
  double max_sum = -10000.;
  for (double start_p = 0.2; start_p <= 0.8; start_p += delta) {
    vector<double> res_tmp;
    double start_p_tmp = start_p;
    double sum = 0.;
    for (auto t : traj_tiles_) {
      res_tmp.push_back(start_p_tmp);
      double end, sum_tmp;
      t->FindOptimizedEnd(start_p_tmp, end, sum_tmp);
      start_p_tmp = end;
      sum += sum_tmp;
    }
    results.push_back(res_tmp);
    if (sum > max_sum) {
      best_index = index;
      max_sum = sum;
    }
    index++;
  }

  assert(best_index >= 0);
  vector<double> start_points = results[best_index];
  
  res_world_points_.clear();
  cout << "start points:\n";
  for (int i = 0; i < start_points.size(); i++) {
    cout << start_points[i] << endl;
    double x, y;
    traj_tiles_[i]->StartPointToWorldCoord(start_points[i], x, y);
    res_world_points_.push_back({x, y});
  }
  
  cout << "\n\n";
}






