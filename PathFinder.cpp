#include "stdafx.h"
#include "PathFinder.h"
#include "model/Car.h"
#include "model/World.h"
#include "model/Game.h"
#include "Utils.h"

using namespace std;
using namespace model;

PathFinder* PathFinder::instance_ = nullptr;
int PathFinder::PATH_CHAIN_SIZE = 6;

bool PathFinder::FindPathChain() {
  assert(world_ && game_);
  
  int prev_waypoint = -1;
  int next_waypoint = car_->getNextWaypointIndex();
  result_.clear();
  while ((int)result_.size() < PATH_CHAIN_SIZE) {
    if (!FindPathFromTo(prev_waypoint, next_waypoint))
      return false;
    prev_waypoint = next_waypoint;
    next_waypoint++;
    if (next_waypoint >= (int)world_->getWaypoints().size())
      next_waypoint = 0;
  }
  
//  cout << "result:\n";
//  for (auto n : result_) {
//    cout << Utils::DirToStr(n->dir) << " => (" << n->x << ", " << n->y << ")" << endl;
//  }
//  cout << "\n\n";
  
  return true;
}

bool PathFinder::FindPathFromTo(int waypoint_from, int waypoint_to) {
  int from_x, from_y;
  
  if (waypoint_from < 0) {
    // start from car
    from_x = Utils::CoordToTile(car_->getX());
    from_y = Utils::CoordToTile(car_->getY());
//    cout << "current position: (" << from_x << ", " << from_y << ")" << endl;
  } else {
    from_x = world_->getWaypoints()[waypoint_from][0];
    from_y = world_->getWaypoints()[waypoint_from][1];
  }
  
  int to_x = world_->getWaypoints()[waypoint_to][0];
  int to_y = world_->getWaypoints()[waypoint_to][1];
  
  PrepareToFindRec();
  Direction res = FindPathRec(TileNodePtr(new TileNode(from_x, from_y, _UNKNOWN_DIRECTION_, TileNodePtr())), to_x, to_y);
  
  for (auto n : local_result_)
    result_.push_back(n);
  
  if (res == _UNKNOWN_DIRECTION_)
    return false;

  return true;
}


Direction PathFinder::FindPathRec(TileNodePtr node, int targ_x, int targ_y) {
  assert(!tile_map_.empty());
  int x = node->x;
  int y = node->y;
  
  auto insert_to_queue = [&] (int x, int y, Direction dir) {
    if (visited_tiles_.find({x, y}) == visited_tiles_.end())
      queue_.push(TileNodePtr(new TileNode(x, y, dir, node)));
  };
  
  visited_tiles_.insert({x, y});
  if (x == targ_x && y == targ_y) {
    // found it!
//    cout << "found target! (" << targ_x << ", " << targ_y << ")" << endl;
    // go back to see who is the first parent
    TileNodePtr cur_node = node;
    TileNodePtr prev_node;
    local_result_.clear();
    while (cur_node->parent) {
      local_result_.push_front(cur_node);
      prev_node = cur_node;
      cur_node = cur_node->parent;
    }
    if (!prev_node)
      return _DIRECTION_COUNT_; // already in place
    return prev_node->dir;
  }
  
  TileType type = tile_map_[x][y];
  if (type == VERTICAL ||
      type == LEFT_BOTTOM_CORNER ||
      type == RIGHT_BOTTOM_CORNER ||
      type == CROSSROADS ||
      type == LEFT_HEADED_T ||
      type == RIGHT_HEADED_T ||
      type == TOP_HEADED_T) {
    // go up
    insert_to_queue(x, y - 1, UP);
  }
  if (type == VERTICAL ||
      type == LEFT_TOP_CORNER ||
      type == RIGHT_TOP_CORNER ||
      type == CROSSROADS ||
      type == LEFT_HEADED_T ||
      type == RIGHT_HEADED_T ||
      type == BOTTOM_HEADED_T) {
    // go down
    insert_to_queue(x, y + 1, DOWN);
  }
  if (type == HORIZONTAL ||
      type == RIGHT_TOP_CORNER ||
      type == RIGHT_BOTTOM_CORNER ||
      type == CROSSROADS ||
      type == LEFT_HEADED_T ||
      type == TOP_HEADED_T ||
      type == BOTTOM_HEADED_T) {
    // go left
    insert_to_queue(x - 1, y, LEFT);
  }
  if (type == HORIZONTAL ||
      type == LEFT_TOP_CORNER ||
      type == LEFT_BOTTOM_CORNER ||
      type == CROSSROADS ||
      type == RIGHT_HEADED_T ||
      type == TOP_HEADED_T ||
      type == BOTTOM_HEADED_T) {
    // go right
    insert_to_queue(x + 1, y, RIGHT);
  }
  
  if (queue_.empty())
      return _UNKNOWN_DIRECTION_;  // can't find
  
  TileNodePtr next = queue_.front();
  queue_.pop();
  Direction res = FindPathRec(next, targ_x, targ_y);
  if (res != _UNKNOWN_DIRECTION_) {
    return res;  // found it
  }
  
  return _UNKNOWN_DIRECTION_;  // can't find
}

void PathFinder::PrepareToFindRec() {
  tile_map_ = world_->getTilesXY();
  QueueType empty_q;
  std::swap(queue_, empty_q);
  visited_tiles_.clear();
}