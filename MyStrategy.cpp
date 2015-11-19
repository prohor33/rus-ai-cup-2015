#include "stdafx.h"
#include "MyStrategy.h"
#include "Utils.h"
#include "PathFinder.h"
#include "PathAnalyzer.h"
#include "Mover.h"

using namespace model;
using namespace std;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
  if (self.isFinishedTrack())
    return;

  Utils::UpdateWorld(&world, &game);
  PathFinder::Instance()->UpdateWorld(&self, &world, &game);
  PathAnalyzer::Instance()->UpdateWorld(&self, &world, &game);
  Mover::Instance()->UpdateWorld(&self, &world, &game, &move);
  
  if (!PathFinder::Instance()->FindPathChain())
    cout << "error: can't find path" << endl;
  
  const std::vector<TileNodePtr> tile_path = PathFinder::Instance()->get_result();
  
  PathAnalyzer::Instance()->Analyze(tile_path);
  const std::vector<std::vector<double>>& path = PathAnalyzer::Instance()->GetPath();
  
  Mover::Instance()->Move(path);  
}

MyStrategy::MyStrategy() { }
