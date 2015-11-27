#pragma once

#include "Structs.h"
#include "model/Direction.h"
#include "PathPattern.h"

namespace model {
  class World;
  class Game;
  class Car;
  class Move;
}

class Mover {
public:
  Mover() :
  car_(nullptr),
  world_(nullptr),
  game_(nullptr),
  rolling_back_(false),
  start_rolling_back_p_x_(0.),
  start_rolling_back_p_y_(0.),
  last_roll_back_tick(-100) {};
  
  static Mover* Instance() {
    if (!instance_)
      instance_ = new Mover();
    return instance_;
  }
  void UpdateWorld(const model::Car* car, const model::World* world, const model::Game* game, model::Move* move) {
    car_ = car;
    world_ = world;
    game_ = game;
    move_ = move;
  }
  void Move(const std::vector<std::vector<double>>& path);
  
private:
  void GetNextPoint(double& x, double& y);
  void TurnToPoint(double x, double y);
  void SetAngle(double rad);
  void AnalyzeHistory();
  bool CheckIfNotMoving();
  void StartRollingBack();
  void StopRollingBack();
  void RollingBack();
  void UseApproachToTurn();
  void ControlMaxSpeed();

  static Mover* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  model::Move* move_;
  std::vector<std::vector<double>> path_;
  std::list<std::vector<double>> history_;
  bool rolling_back_;
  double start_rolling_back_p_x_;
  double start_rolling_back_p_y_;
  int last_roll_back_tick;
};