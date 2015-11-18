#include "stdafx.h"
#include "MyStrategy.h"
#include "Utils.h"
#include "PathFinder.h"
#include "PathAnalyzer.h"


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
  
//  for (auto p : world.getWaypoints()) {
//    Utils::PrintCoord(p[0], p[1]);
//  }
//  cout << "\n\n\n";
//  return;
  
  Utils::UpdateWorld(&world, &game);
  PathFinder::Instance()->UpdateWorld(&self, &world, &game);
  PathAnalyzer::Instance()->UpdateWorld(&self, &world, &game);
  
  if (!PathFinder::Instance()->FindPathChain())
    cout << "error: can't find path" << endl;
  
  const std::vector<TileNodePtr> tile_path = PathFinder::Instance()->get_result();
  
  PathAnalyzer::Instance()->Analyze(tile_path);
  const std::vector<std::vector<double>>& path = PathAnalyzer::Instance()->GetPath();
  
  
//    cout << "already in place" << endl;
//  cout << Utils::DirToStr(dir) << endl;
  
  
//  double nextWaypointX = Utils::TileToCoord(self.getNextWaypointX());
//  double nextWaypointY = Utils::TileToCoord(self.getNextWaypointY());
  
  double nextWaypointX = path[0][0];
  double nextWaypointY = path[0][1];
  
  double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
  double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
  
  move.setWheelTurn(angleToWaypoint * 180.0 / PI / 35.0);
  move.setEnginePower(1.0);
  
/*  if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI) {
    move.setBrake(true);
  }	*/	
}

MyStrategy::MyStrategy() { }
