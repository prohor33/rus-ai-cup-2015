#include "stdafx.h"
#include "PathAnalyzer.h"
#include "Utils.h"
#include "Car.h"
#include "World.h"
#include "Game.h"


using namespace std;
using namespace model;

PathAnalyzer* PathAnalyzer::instance_ = nullptr;

PathAnalyzer::PathAnalyzer() :
car_(nullptr),
world_(nullptr),
game_(nullptr) {
  
  patterns_.push_back(PathPattern({ UP, RIGHT }, RIGHT_TURN));
  patterns_.push_back(PathPattern({ UP, LEFT }, LEFT_TURN));
  patterns_.push_back(PathPattern({ UP, UP, UP, UP }, LONG_LINE));
  patterns_.push_back(PathPattern({ UP, UP }, LINE));
};

void PathAnalyzer::Analyze(const std::list<TileNodePtr>& path) {
  path_ = path;
  
  //int car_x = Utils::CoordToTile(car_->getX());
  //int car_y = Utils::CoordToTile(car_->getY());
  // add current node
//  path_.push_front(TileNodePtr(new TileNode(car_x, car_y, _UNKNOWN_DIRECTION_, TileNodePtr())));

  dir_path_.clear();
  dir_path_.reserve(path_.size());
  Direction local = (*path_.begin())->dir;
  for (auto n : path_) {
    dir_path_.push_back(Utils::ConvertDirToLocal(n->dir, local));
  }
  
  PathPattern* current_pattern = nullptr;
  for (auto& p : patterns_) {
    if (p.CheckIfNow(dir_path_)) {
      current_pattern = &p;
      break;
    }
  }
  if (current_pattern)
    Utils::PrintPattern(current_pattern->type);
  else
    cout << "no pattern :(\n";
}