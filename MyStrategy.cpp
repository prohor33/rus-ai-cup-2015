#include "stdafx.h"
#include "MyStrategy.h"
#include "Utils.h"
#include "PathFinder.h"
#include "stdafx.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>

using namespace model;
using namespace std;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
//  move.setEnginePower(1.0);
//  move.setThrowProjectile(true);
//  move.setSpillOil(true);
//
//  if (world.getTick() > game.getInitialFreezeDurationTicks()) {
//      move.setUseNitro(true);
//  }
  
  Utils::UpdateWorld(&world, &game);
  PathFinder::Instance()->UpdateWorld(&world, &game);
  
  Direction dir;
  if (!PathFinder::Instance()->FindPathTo(&self, self.getNextWaypointX(), self.getNextWaypointY(), dir))
    cout << "error: can't find path" << endl;
  if (dir == _DIRECTION_COUNT_)
    cout << "already in place" << endl;
  cout << Utils::DirToStr(dir) << endl;
  
  
  double nextWaypointX = Utils::TileToCoord(self.getNextWaypointX());
  double nextWaypointY = Utils::TileToCoord(self.getNextWaypointY());
  
  double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
  double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
  
  move.setWheelTurn(angleToWaypoint * 32.0 / PI);
  move.setEnginePower(0.75);
  
  if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI) {
    move.setBrake(true);
  }		
}

MyStrategy::MyStrategy() { }
