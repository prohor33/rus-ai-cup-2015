#include "stdafx.h"
#include "PathPattern.h"


using namespace std;
using namespace model;

void PathPattern::ApplyField(const std::vector<TrajTilePtr>& tiles) {
  for (int i = 0; i + 1 < (int)opt_points_.size(); i++) {
    if (i >= (int)tiles.size())
      break;
    double start_p = opt_points_[i];
    double end_p = opt_points_[i + 1];
  }
}