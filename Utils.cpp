#include "stdafx.h"
#include "Utils.h"
#include "World.h"
#include "Game.h"

const model::World* Utils::world_ = nullptr;
const model::Game* Utils::game_ = nullptr;

int Utils::CoordToTile(double v) {
  return v / game_->getTrackTileSize();
}