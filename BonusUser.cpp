#include "stdafx.h"
#include "BonusUser.h"
#include "Utils.h"
#include "Car.h"
#include "World.h"
#include "Game.h"
#include "Move.h"
#include "PathAnalyzer.h"


using namespace std;
using namespace model;

BonusUser* BonusUser::instance_ = nullptr;

void BonusUser::Use() {
  UseProjectile();
  UseNitro();
  UseOilStick();
}

void BonusUser::UseProjectile() {
  if (car_->getProjectileCount() == 0 || car_->getRemainingProjectileCooldownTicks() > 0)
    return;
  // TODO: add strategy for tire too

  for (auto& targ_car : world_->getCars()) {
    if (targ_car.isTeammate())
      continue;
    double angle = car_->getAngleTo(targ_car);
    if (abs(angle) > game_->getSideWasherAngle())
      continue;
    double dist = car_->getDistanceTo(targ_car);
    const double zero_angle = 0.2 / 180.0 * PI;
    if (dist > game_->getTrackTileSize() * 4 && abs(angle) > zero_angle)
      continue; // too far with not 0 angle
    move_->setThrowProjectile(true);
    return;
  }
}

void BonusUser::UseNitro() {
  if (world_->getTick() < game_->getInitialFreezeDurationTicks())
    return;
  if (car_->getNitroChargeCount() == 0 || car_->getRemainingNitroCooldownTicks() > 0 || move_->isUseNitro())
    return;
  if (PathAnalyzer::Instance()->is_line_now())
    move_->setUseNitro(true);
}

void BonusUser::UseOilStick() {
  if (car_->getOilCanisterCount() == 0 || car_->getRemainingOilCooldownTicks() > 0)
    return;
  // keep only one oil canister
  if (car_->getOilCanisterCount() > 1)
    move_->setSpillOil(true);

  const double MIN_ANGLE = 165.0 / 180.0 * PI;
  const double MAX_DIST = game_->getTrackTileSize() * 4.;
  for (auto& targ_car : world_->getCars()) {
    if (targ_car.isTeammate())
      continue;
    double angle = car_->getAngleTo(targ_car);
    if (abs(angle) < MIN_ANGLE)
      continue;
    double dist = car_->getDistanceTo(targ_car);
    if (dist > MAX_DIST)
      continue; // too far with not 0 angle
    move_->setSpillOil(true);
    return;
  }

  //getOilSlickRadius
  //getOilSlickInitialRange
  //getOilSlickLifetime
  //isSpillOil
}


