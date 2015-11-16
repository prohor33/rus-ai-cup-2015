#include "stdafx.h"
#include "PathAnalyzer.h"

using namespace std;
using namespace model;

PathAnalyzer* PathAnalyzer::instance_ = nullptr;

void PathAnalyzer::Analyze(const std::list<TileNodePtr>& path) {
  path_ = path;
}