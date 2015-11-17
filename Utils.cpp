#include "stdafx.h"
#include "Utils.h"
#include "World.h"
#include "Game.h"

using namespace model;

const World* Utils::world = nullptr;
const Game* Utils::game = nullptr;

int Utils::CoordToTile(double v) {
  return (int)(v / game->getTrackTileSize());
}

Direction Utils::ConvertDirToLocal(Direction dir, Direction local) {
  switch (local) {
  case UP:
    return dir;
  case DOWN:
  {
             switch (dir) {
             case UP: return DOWN;
             case DOWN: return UP;
             case LEFT: return RIGHT;
             case RIGHT: return LEFT;
             }
             return dir;
  }
    break;
  case RIGHT:
  {
              switch (dir) {
              case UP: return LEFT;
              case DOWN: return RIGHT;
              case LEFT: return DOWN;
              case RIGHT: return UP;
              }
              return dir;
  }
    break;
  case LEFT:
  {
              switch (dir) {
              case UP: return RIGHT;
              case DOWN: return LEFT;
              case LEFT: return UP;
              case RIGHT: return DOWN;
              }
              return dir;
  }
    break;
  default:
    assert(0);
    return dir;
  }
}