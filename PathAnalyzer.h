#pragma once

#include "Structs.h"
#include "model/Direction.h"
#include "PathPattern.h"

namespace model {
  class World;
  class Game;
  class Car;
}

class PathAnalyzer {
public:
  PathAnalyzer();
  static PathAnalyzer* Instance() {
    if (!instance_)
      instance_ = new PathAnalyzer();
    return instance_;
  }
  void UpdateWorld(const model::Car* car, const model::World* world, const model::Game* game) {
    car_ = car;
    world_ = world;
    game_ = game;
  }
  void Analyze(const std::vector<TileNodePtr>& path);
  const std::vector<std::vector<double>>& GetPath() const {
    return res_world_points_;
  }
  bool is_line_now() const {
    return is_line_now_;
  }
  bool is_found_approach_to_turn() const {
    return is_found_approach_to_turn_;
  }
  double founded_approach_wheel_turn() const {
    return founded_approach_wheel_turn_;
  }
  
  
private:
  void BuildBasicTraj();
  void FindBestTraj();
  void ApplyBonuses();
  bool FindApproachToTurn(PathPattern p);
  typedef std::function<bool (const StateInTurn&, double first_wheel_turn)> CheckTurnEndF;
  void FindApproachToTurnRec(const StateInTurn& state, const CheckTurnEndF& f_check_end, double first_wheel_turn, int depth = 0);

  static PathAnalyzer* instance_;
  const model::Car* car_;
  const model::World* world_;
  const model::Game* game_;
  std::vector<TileNodePtr> path_;
  std::vector<model::Direction> dir_path_;
  std::vector<PathPattern> patterns_;
  std::vector<TrajTilePtr> traj_tiles_;
  std::vector<std::vector<double>> res_world_points_;
  bool is_line_now_;
  bool is_found_approach_to_turn_;
  double founded_approach_wheel_turn_;
};