#include "stdafx.h"
#include "PathPattern.h"
#include "TrajTile.h"
#include "Utils.h"
#include "Car.h"
#include "World.h"
#include "Game.h"


using namespace std;
using namespace model;

int PathPattern::ApplyField(const std::vector<TrajTilePtr>& tiles, int start_index, int start_inside_pattern) {
  int fields_applyed = 0;
  for (int i = 0; start_inside_pattern + i + 1 < (int)opt_points_.size(); i++) {
    if (start_index + i >= (int)tiles.size())
      break;
    double start_p = opt_points_[start_inside_pattern + i];
//    cout << "apply start_p = " << start_p << endl;
    double end_p = opt_points_[start_inside_pattern + i + 1];
    tiles[start_index + i]->SetOptimizedTraj(start_p, end_p);
    fields_applyed++;
  }
  return fields_applyed;
}

int PathPattern::GetIndexInsidePattern(Direction orientation, int start_x, int start_y, int x, int y) {

  int curr_x = start_x;
  int curr_y = start_y;
  int index = 0;
  if (curr_x == x && curr_y == y)
    return index;
  index++;
  
  for (int i = 1; i < seq_.size(); i++) {
    Direction dir = Utils::ConvertDirToGlobal(seq_[i], orientation);
//    cout << "orientation: " << Utils::DirToStr(orientation) << endl;
//    cout << "local: " << Utils::DirToStr(seq_[i]) << endl;
//    cout << "global dir: " << Utils::DirToStr(dir) << endl;
    
    switch (dir) {
      case UP:
        curr_y--;
        break;
      case DOWN:
        curr_y++;
        break;
      case RIGHT:
        curr_x++;
        break;
      case LEFT:
        curr_x--;
        break;
      default:
        assert(0);
        break;
    }
    
    if (curr_x == x && curr_y == y)
      return index;
    
//    cout << "iterate on: ";
//    Utils::PrintCoord(curr_x, curr_y);
//    cout << "while car coord is: ";
//    Utils::PrintCoord(Utils::CoordToTile(Utils::car->getX()), Utils::CoordToTile(Utils::car->getY()));
//    cout << "and looking for (x, y): ";
//    Utils::PrintCoord(x, y);
    index++;
  }
  
  return -1;
}