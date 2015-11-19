#include "stdafx.h"
#include "Mover.h"
#include "Utils.h"
#include "Car.h"
#include "World.h"
#include "Game.h"
#include "Move.h"


using namespace std;
using namespace model;

Mover* Mover::instance_ = nullptr;

void Mover::Move(const std::vector<std::vector<double>>& path) {
  path_ = path;
  
  cout << "next point coord: ";
  Utils::PrintCoord(path[0][0], path[0][1]);
  
  const double rad = game_->getTrackTileSize() / 2.0;
  double x = 0.;
  double y = 0.;
  for (int i = 0; i + 1 < path.size(); i++) {
    auto& p0 = path[i];
    auto& p1 = path[i + 1];
    for (double coef = 0.; coef < 1.; coef += 0.2) {
      x = (p1[0] - p0[0]) * coef + p0[0];
      y = (p1[1] - p0[1]) * coef + p0[1];
      double cur_dist = hypot(x - car_->getX(), y - car_->getY());
      if (cur_dist > rad)
        goto found_point;
    }
  }
found_point:
  TurnToPoint(x, y);
}

void Mover::TurnToPoint(double x, double y) {
 
  cout << "car coord: ";
  Utils::PrintCoord(car_->getX(), car_->getY());
  cout << "next point to turn to: ";
  Utils::PrintCoord(x, y);
  
  double angleToWaypoint = car_->getAngleTo(x, y) * 180.0 / PI;
  cout << "angle to waypoint: " << angleToWaypoint << endl;
  double speedModule = hypot(car_->getSpeedX(), car_->getSpeedY());
  
  cout << "wheel turn: " << angleToWaypoint / 35.0 << endl;
  move_->setWheelTurn(angleToWaypoint / 35.0);
  move_->setEnginePower(1.0);
  
  cout << "\n\n";
  /*  if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI) {
   move.setBrake(true);
   }	*/
}