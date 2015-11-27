#include "stdafx.h"
#include "Utils.h"
#include "model/World.h"
#include "model/Game.h"

using namespace model;

const Car* Utils::car = nullptr;
const World* Utils::world = nullptr;
const Game* Utils::game = nullptr;

int Utils::CoordToTile(double v) {
  return (int)(v / game->getTrackTileSize());
}

Direction Utils::ConvertDirToGlobal(Direction dir, Direction local) {
  Direction res = UP;
  if (ConvertDirToLocal(res, local) == dir)
    return res;
  res = DOWN;
  if (ConvertDirToLocal(res, local) == dir)
    return res;
  res = RIGHT;
  if (ConvertDirToLocal(res, local) == dir)
    return res;
  res = LEFT;
  if (ConvertDirToLocal(res, local) == dir)
    return res;
  assert(0);
  return UP;
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

void Utils::GlobalPointToLocalInsideTile(double x_in, double y_in, Direction orientation, double& x_out, double& y_out) {
  switch (orientation) {
  case UP:
    x_out = x_in;
    y_out = y_in;
    return;
  case DOWN:
    x_out = 1. - x_in;
    y_out = 1. - y_in;
    return;
  case RIGHT:
    x_out = y_in;
    y_out = 1. - x_in;
    return;
  case LEFT:
    x_out = 1. - y_in;
    y_out = x_in;
    return;
  default:
    assert(0);
  }
}

double Utils::AngleToNormal(double angle) {
  if (angle < -PI)
    angle += 2 * PI;
  if (angle > PI)
    angle -= 2 * PI;
  return angle;
}

bool Utils::IsRightTurn(double from, double to) {
  assert(from >= - PI && from <= PI);
  assert(to >= - PI && to <= PI);
  double delta = to - from;
  if (delta > PI)
    delta -= 2 * PI;
  if (delta < -PI)
    delta += 2 * PI;
  return delta > 0;
}

void Utils::RotateVector(double v_in_x, double v_in_y, double angle, double& v_out_x, double& v_out_y) {
  v_out_x = v_in_x * cos(angle) + v_in_y * sin(angle);
  v_out_y = -v_in_x * sin(angle) + v_in_y * cos(angle);
}

void Utils::RotateToOrientation(double x_in, double y_in, model::Direction orientation, double& x_out, double& y_out) {
  switch (orientation) {
    case UP:
      x_out = x_in;
      y_out = y_in;
      return;
    case DOWN:
      RotateVector(x_in, y_in, PI, x_out, y_out);
      return;
    case RIGHT:
      RotateVector(x_in, y_in, PI / 2., x_out, y_out);
      return;
    case LEFT:
      RotateVector(x_in, y_in, -PI / 2., x_out, y_out);
      return;
    default:
      assert(0);
      break;
  }
}

void Utils::PrintPattern(PathPatternType type) {
  switch (type) {
    case RIGHT_TURN:
      std::cout << "RIGHT_TURN" << std::endl;
      break;
    case RIGHT_CUT_TURN:
      std::cout << "RIGHT_CUT_TURN" << std::endl;
      break;
    case LEFT_TURN:
      std::cout << "LEFT_TURN" << std::endl;
      break;
    case LEFT_CUT_TURN:
      std::cout << "LEFT_CUT_TURN" << std::endl;
      break;
    case LONG_LINE:
      std::cout << "LONG_LINE" << std::endl;
      break;
    case LINE:
      std::cout << "LINE" << std::endl;
      break;
    case U_TURN:
      std::cout << "U_TURN" << std::endl;
      break;
    case U_TURN_CUT:
      std::cout << "U_TURN_CUT" << std::endl;
      break;
    case LEFT_U_TURN:
      std::cout << "LEFT_U_TURN" << std::endl;
      break;
    case LEFT_U_TURN_CUT:
      std::cout << "LEFT_U_TURN_CUT" << std::endl;
      break;
    case RIGHT_U_TURN:
      std::cout << "RIGHT_U_TURN" << std::endl;
      break;
    case RIGHT_U_TURN_CUT:
      std::cout << "RIGHT_U_TURN_CUT" << std::endl;
      break;
    case SHARP_RIGHT_U_TURN:
      std::cout << "SHARP_RIGHT_U_TURN" << std::endl;
      break;
    case SHARP_LEFT_U_TURN:
      std::cout << "SHARP_LEFT_U_TURN" << std::endl;
      break;
    default:
      assert(0);
      break;
  }
}





