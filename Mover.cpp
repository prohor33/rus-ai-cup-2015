#include "stdafx.h"
#include "Mover.h"
#include "Utils.h"
#include "model/Car.h"
#include "model/World.h"
#include "model/Game.h"
#include "model/Move.h"


using namespace std;
using namespace model;

Mover* Mover::instance_ = nullptr;

void Mover::Move(const std::vector<std::vector<double>>& path) {
  path_ = path;
  AnalyzeHistory();
  
  if (rolling_back_) {
    RollingBack();
    return;
  }
  
  if (PathAnalyzer::Instance()->is_found_approach_to_turn()) {
    UseApproachToTurn();
    return;
  }
  
//  cout << "next point coord: ";
//  Utils::PrintCoord(path[0][0], path[0][1]);
  double x, y;
  GetNextPoint(x, y);
  TurnToPoint(x, y);
  ControlMaxSpeed();
}

void Mover::GetNextPoint(double& x, double& y) {
  const double rad = game_->getTrackTileSize() / 2.0;
  x = 0.;
  y = 0.;
  if (path_.empty())
    return;
  x = path_[0][0];
  y = path_[0][1];
  for (int i = 0; i + 1 < path_.size(); i++) {
    auto& p0 = path_[i];
    auto& p1 = path_[i + 1];
    for (double coef = 0.; coef < 1.; coef += 0.2) {
      x = (p1[0] - p0[0]) * coef + p0[0];
      y = (p1[1] - p0[1]) * coef + p0[1];
      double cur_dist = hypot(x - car_->getX(), y - car_->getY());
      if (cur_dist > rad)
        return;
    }
  }
}

void Mover::TurnToPoint(double x, double y) {
 
//  cout << "car coord: ";
//  Utils::PrintCoord(car_->getX(), car_->getY());
//  cout << "next point to turn to: ";
//  Utils::PrintCoord(x, y);
  
  double angleToWaypoint = car_->getAngleTo(x, y) * 180.0 / PI;
  bool go_backward = false;

  {
    // TODO: this code disabled because it's not right + if stuck backward, rollback will not help!
    //  if (angleToWaypoint > 90.) {
    //    angleToWaypoint -= 180.;
    //    go_backward = true;
    //  }
    //  if (angleToWaypoint < -90.) {
    //    angleToWaypoint += 180.;
    //    go_backward = true;
    //  }
    //  cout << "angle to waypoint: " << angleToWaypoint << endl;
    //  double speedModule = hypot(car_->getSpeedX(), car_->getSpeedY());
  }

  SetAngle(angleToWaypoint * PI / 180.0);
  move_->setEnginePower(go_backward ? -1.0 : 1.0);
}

void Mover::SetAngle(double rad) {
  //  cout << "wheel turn: " << angleToWaypoint / 35.0 << endl;
  move_->setWheelTurn(rad * 180.0 / PI / 35.0);
}

void Mover::AnalyzeHistory() {
  if (world_->getTick() < game_->getInitialFreezeDurationTicks())
    return;
  if (car_->getDurability() == 0.)  // whaiting for respawn
    return;

  history_.push_front({ car_->getX(), car_->getY() });

  const int MAX_HISTORY_SIZE = 100;
  if (history_.size() > MAX_HISTORY_SIZE)
    history_.pop_back();

  if (CheckIfNotMoving())
    StartRollingBack();
}

bool Mover::CheckIfNotMoving() {
  const int NOT_MOVING_HIST_SIZE = 20;
  if (history_.size() < NOT_MOVING_HIST_SIZE)
    return false;
  double min_x = numeric_limits<double>::max();
  double max_x = -numeric_limits<double>::max();
  double min_y = numeric_limits<double>::max();
  double max_y = -numeric_limits<double>::max();
  int index = 0;
  for (auto& p : history_) {
    if (index >= NOT_MOVING_HIST_SIZE)
      break;
    min_x = min<double>(p[0], min_x);
    max_x = max<double>(p[0], max_x);
    min_y = min<double>(p[1], min_y);
    max_y = max<double>(p[1], max_y);
    index++;
  }
  double move_v = hypot(max_x - min_x, max_y - min_y);
  const double MIN_MOVE = game_->getTrackTileSize() / 100.;
  
//  cout << "move: " << move_v << " min_move: " << MIN_MOVE << endl;
  if (move_v < MIN_MOVE) {
    return true;
  }
  return false;
}

void Mover::StartRollingBack() {
  if (rolling_back_) {
//    cout << "already rolling back => not starting to roll" << endl;
    return;
  }
  const int ROLLBACK_COOLDOWN_TICKS = 200;
  if (world_->getTick() - last_roll_back_tick < ROLLBACK_COOLDOWN_TICKS) {
    
//    cout << "world_->getTick(): " << world_->getTick() << endl;
//    cout << "last_roll_back_tick: " << last_roll_back_tick << endl;
//    cout << "cooldown, tick left: " << ROLLBACK_COOLDOWN_TICKS - (world_->getTick() - last_roll_back_tick) << endl;
    return;
  }
//  cout << ">>>>>>>>>>>>>>>>>>>>>>>>> START ROLLING BACK <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
  rolling_back_ = true;
  start_rolling_back_p_x_ = car_->getX();
  start_rolling_back_p_y_ = car_->getY();
  last_roll_back_tick = world_->getTick();
}

void Mover::StopRollingBack() {
//  cout << "stop rolling back" << endl;
  rolling_back_ = false;
  move_->setEnginePower(0.);
  move_->setWheelTurn(0.);
  last_roll_back_tick = world_->getTick();
}

void Mover::RollingBack() {
//  cout << "rolling back" << endl;
  move_->setEnginePower(-1.);
  
  double x, y;
  GetNextPoint(x, y);
  double angleToWaypoint = car_->getAngleTo(x, y);
  SetAngle(-angleToWaypoint); // going backward
  
  double dist = car_->getDistanceTo(start_rolling_back_p_x_, start_rolling_back_p_y_);
  const double MAX_ROLL_BACK_DIST = game_->getTrackTileSize() / 4.;
  if (dist > MAX_ROLL_BACK_DIST)
    StopRollingBack();
  const int MAX_ROLLBACK_TICKS = 200;
  if (world_->getTick() - last_roll_back_tick > MAX_ROLLBACK_TICKS)
    StopRollingBack();
}

void Mover::UseApproachToTurn() {
  move_->setWheelTurn(PathAnalyzer::Instance()->founded_approach_wheel_turn());
  move_->setEnginePower(1.);
}

void Mover::ControlMaxSpeed() {
  const double& max_speed = PathAnalyzer::Instance()->max_speed();
  double speed = hypot(car_->getSpeedX(), car_->getSpeedY());
  move_->setBrake(speed > max_speed);
//  if (speed > max_speed) {
//    cout << "speed > max_speed: " << speed << " > " << max_speed << endl;
//  }
}


