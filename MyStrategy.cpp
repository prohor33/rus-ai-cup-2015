#include "stdafx.h"
#include "MyStrategy.h"
#include "Utils.h"
#include "PathFinder.h"
#include "PathAnalyzer.h"
#include "Mover.h"
#include "BonusUser.h"

using namespace model;
using namespace std;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
//  std::list<std::vector<double>> a;
//  a.push_front({0., 1.});
//  return;
  
  if (self.isFinishedTrack())
    return;

  Utils::UpdateWorld(&self, &world, &game);
  PathFinder::Instance()->UpdateWorld(&self, &world, &game);
  PathAnalyzer::Instance()->UpdateWorld(&self, &world, &game);
  Mover::Instance()->UpdateWorld(&self, &world, &game, &move);
  BonusUser::Instance()->UpdateWorld(&self, &world, &game, &move);
  
  if (!PathFinder::Instance()->FindPathChain()) {
    cout << "error: can't find path" << endl;
    std::vector<std::vector<double>> path;
    path.push_back({ Utils::TileToCoord(self.getNextWaypointX()), Utils::TileToCoord(self.getNextWaypointY())});
    Mover::Instance()->Move(path);
    return;
  }
  
  const std::vector<TileNodePtr> tile_path = PathFinder::Instance()->get_result();
  
  PathAnalyzer::Instance()->Analyze(tile_path);
  const std::vector<std::vector<double>>& path = PathAnalyzer::Instance()->GetPath();
  
  Mover::Instance()->Move(path);
  BonusUser::Instance()->Use();
}

MyStrategy::MyStrategy() { }
