#include "stdafx.h"
#include "PathFinder.h"
#include "Car.h"
#include "World.h"
#include "Game.h"
#include "Utils.h"

using namespace std;
using namespace model;

PathFinder* PathFinder::instance_ = nullptr;
int PathFinder::MAX_TILE_PATTERN_SIZE = 6;


bool PathFinder::FindPathTo(const model::Car* car, int targ_x, int targ_y, Direction& dir) {
  assert(world_ && game_);
  
  {
    tile_map_ = world_->getTilesXY();
    QueueType empty_q;
    std::swap(queue_, empty_q);
    visited_tiles_.clear();
    result_.clear();
  }
  int tile_x = Utils::CoordToTile(car->getX());
  int tile_y = Utils::CoordToTile(car->getY());
//  cout << "current position: (" << tile_x << ", " << tile_y << ")" << endl;
  Direction res = FindPathRec(TileNodePtr(new TileNode(tile_x, tile_y, _UNKNOWN_DIRECTION_, TileNodePtr())), targ_x, targ_y);
  
  if (res == _UNKNOWN_DIRECTION_)
    return false;
  dir = res;
  
  if (result_.size() >= MAX_TILE_PATTERN_SIZE)
    return true;  // no need for second pass
  
  // find path to the second next target point
  int next_waypoint_i = -1;
  int i = 0;
  for (auto p : world_->getWaypoints()) {
    if (p[0] == car->getNextWaypointX() &&
        p[1] == car->getNextWaypointY()) {
      next_waypoint_i = i + 1;
    }
    i++;
  }
  if (next_waypoint_i < 0 || next_waypoint_i >= world_->getWaypoints().size())
    return false;
  
  auto second_next_p = world_->getWaypoints()[next_waypoint_i];
  double target2_x = Utils::TileToCoord(second_next_p[0]);
  double target2_y = Utils::TileToCoord(second_next_p[1]);
  
  std::list<model::Direction> result0 = result_;
  
  return true;
}


Direction PathFinder::FindPathRec(TileNodePtr node, int targ_x, int targ_y) {
  assert(!tile_map_.empty());
  int x = node->x;
  int y = node->y;
  
//  cout << "going deeper (" << node->x << ", " << node->y << ")" << endl;
  
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
    while (cur_node->parent) {
//      cout << "to coord (" << cur_node->x << ", " << cur_node->y <<
//      ") decided to go " << Utils::DirToStr(cur_node->dir) << endl;
      result_.push_front(cur_node->dir);
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