#include "stdafx.h"
#include "PathPattern.h"
#include "TrajTile.h"


using namespace std;
using namespace model;

void PathPattern::ApplyField(const std::vector<TrajTilePtr>& tiles, int start_index) {
  switch (type) {
  case RIGHT_TURN:
  case LEFT_TURN:
  case LEFT_CUT_TURN:
  case RIGHT_CUT_TURN:
    break;
  default:
    return;
  }

  for (int i = 0; i + 1 < (int)opt_points_.size(); i++) {
    if (start_index + i >= (int)tiles.size())
      break;
    double start_p = opt_points_[i];
    cout << "apply start_p = " << start_p << endl;
    double end_p = opt_points_[i + 1];
    tiles[start_index + i]->SetOptimizedTraj(start_p, end_p);
  }
}