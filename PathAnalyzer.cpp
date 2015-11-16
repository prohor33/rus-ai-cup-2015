#include "stdafx.h"
#include "PathAnalyzer.h"

using namespace std;
using namespace model;

PathAnalyzer* PathAnalyzer::instance_ = nullptr;

PathAnalyzer::PathAnalyzer() :
car_(nullptr),
world_(nullptr),
game_(nullptr) {
  
  patterns_.push_back(PathPattern({UP, RIGHT}));  // turn to the right
};

void PathAnalyzer::Analyze(const std::list<TileNodePtr>& path) {
  path_ = path;
}