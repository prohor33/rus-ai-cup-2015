#include "stdafx.h"
#include "PathAnalyzer.h"
#include "Utils.h"
#include "model/Car.h"
#include "model/World.h"
#include "model/Game.h"
#include "TrajTile.h"


using namespace std;
using namespace model;

PathAnalyzer* PathAnalyzer::instance_ = nullptr;
const double NO_SPEED_LIMIT = 800.;

PathAnalyzer::PathAnalyzer() :
car_(nullptr),
world_(nullptr),
game_(nullptr),
is_line_now_(false),
is_found_approach_to_turn_(false),
founded_approach_wheel_turn_(0.),
max_speed_(NO_SPEED_LIMIT) {
  
  const double PADDING = 0.2;
  const double PADDING_FROM_CENTER = 0.25;
  const double MIDDLE = 0.5;
  const double SPEED_LIMIT = 30.;

  patterns_.push_back(PathPattern({ UP, UP, RIGHT, LEFT, DOWN }, RIGHT_U_TURN, { MIDDLE, MIDDLE, MIDDLE, MIDDLE, MIDDLE }, 0.5 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, RIGHT, RIGHT, DOWN }, RIGHT_U_TURN_CUT, { MIDDLE, MIDDLE, MIDDLE, MIDDLE }, 0.4 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, UP, LEFT, LEFT, DOWN }, LEFT_U_TURN, { MIDDLE, MIDDLE, MIDDLE, MIDDLE, MIDDLE }, 0.5 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, LEFT, LEFT, DOWN }, LEFT_U_TURN_CUT, { MIDDLE, MIDDLE, MIDDLE, MIDDLE }, 0.4 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, UP, DOWN }, U_TURN, { 0., 0., 0. }, 0.3 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, DOWN }, U_TURN_CUT, { 0., 0. }, 0.25 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, UP, RIGHT }, RIGHT_TURN, { PADDING, 1. - PADDING_FROM_CENTER, 1. - PADDING_FROM_CENTER }, SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, RIGHT }, RIGHT_CUT_TURN, { 1. - PADDING_FROM_CENTER, 1. - PADDING_FROM_CENTER }, 0.6 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, UP, LEFT }, LEFT_TURN, { 1. - PADDING, PADDING_FROM_CENTER, PADDING_FROM_CENTER }, SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, LEFT }, LEFT_CUT_TURN, { PADDING_FROM_CENTER, PADDING_FROM_CENTER }, 0.6 * SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, UP, UP, UP }, LONG_LINE, {}, NO_SPEED_LIMIT));
  patterns_.push_back(PathPattern({ UP, UP, UP }, LINE, {}, NO_SPEED_LIMIT));
};

void PathAnalyzer::Analyze(const std::vector<TileNodePtr>& path) {
  path_ = path;
  is_line_now_ = false;
  is_found_approach_to_turn_ = false;
  max_speed_ = NO_SPEED_LIMIT;
  
  //int car_x = Utils::CoordToTile(car_->getX());
  //int car_y = Utils::CoordToTile(car_->getY());
  // add current node
  // path_.push_front(TileNodePtr(new TileNode(car_x, car_y, _UNKNOWN_DIRECTION_, TileNodePtr())));

  dir_path_.clear();
  dir_path_.reserve(path_.size());
  Direction local = (*path_.begin())->dir;
  for (auto n : path_) {
    dir_path_.push_back(Utils::ConvertDirToLocal(n->dir, local));
  }
  
//  PathPattern* current_pattern = nullptr;
//  for (auto& p : patterns_) {
//    if (p.CheckIfNow(dir_path_)) {
//      current_pattern = &p;
//      break;
//    }
//  }
//  if (current_pattern)
//    Utils::PrintPattern(current_pattern->type);
//  else
//    cout << "no pattern :(\n";

  BuildBasicTraj();
  
  if (is_found_approach_to_turn_)
    return;
  
  ApplyBonuses();
  FindBestTraj();
}

void PathAnalyzer::BuildBasicTraj() {
  assert(dir_path_.size() == path_.size());
  traj_tiles_.clear();

  // insert tiles
  for (int i = 0; i + 1 < (int)dir_path_.size(); i++) {
    model::Direction dir = dir_path_[i];
    model::Direction next_dir = dir_path_[i + 1]; // normalized to start tile direction
    TrajTileType type(TTT_FORWARD);
    if (dir == next_dir) {
      type = TTT_FORWARD;
//      cout << "tile: TTT_FORWARD" << endl;
    } else {
      model::Direction local_next = Utils::ConvertDirToLocal(next_dir, dir);
      switch (local_next) {
      case RIGHT:
        type = TTT_RIGHT_TURN;
//        cout << "tile: TTT_RIGHT_TURN" << endl;
        break;
      case LEFT:
        type = TTT_LEFT_TURN;
//        cout << "tile: TTT_LEFT_TURN" << endl;
        break;
      case DOWN:
        type = TTT_U_TURN;
        break;
      default:
        assert(0);
      }
    }
    const TileNodePtr& n = path_[i];
    traj_tiles_.push_back(TrajTilePtr(new TrajTile(type, n->x, n->y, n->dir)));
  }

  // fill tiles optimized trajectory for turns
  for (int start_index = 0; start_index < traj_tiles_.size(); start_index++) {
    for (auto& p : patterns_) {
      if (p.CheckPatternOnIndex(dir_path_, start_index)) {

        if (start_index == 0 && (p.type == LONG_LINE))
          is_line_now_ = true;
        
        if (start_index == 0)
          max_speed_ = p.max_speed;

        if (p.IsTurn()) {

            // not using this code for now
//          if (p.IsCutTurn() && start_index == 0) {
//            if (FindApproachToTurn(p))
//              return;
//            // ok, go standart strategy
//          }
          
          // for debug
          p.ApplyField(traj_tiles_, start_index);
          start_index += p.length();
        }
        break;
      }
    }
  }
  return;
}

void FindBestTrajRec(vector<double> var, int tile_n, vector<vector<double>>& variants) {
  if (var.size() >= tile_n) {
    variants.push_back(var);
    return;
  }
  const double delta = 0.1;
  var.push_back(0.);
  for (double start_p = 0.25; start_p <= 0.75; start_p += delta) {
    var.back() = start_p;
    FindBestTrajRec(var, tile_n, variants);
  }
}

void PathAnalyzer::FindBestTraj() {

  // find current car point
  TrajTilePtr& tile0 = traj_tiles_[0];
  double tile0_x = Utils::TileToCoord(tile0->x);
  double tile0_y = Utils::TileToCoord(tile0->y);
  double current_car_point = 0.;
  double current_car_pos_coef_in_tile = 0.;
  switch (tile0->orientation) {
  case UP:
  case DOWN:
    current_car_point = (car_->getX() - tile0_x) / game_->getTrackTileSize() + 0.5;
    current_car_pos_coef_in_tile = abs(tile0_y - car_->getY()) / game_->getTrackTileSize() - 0.5;
    if (tile0->orientation == DOWN)
      current_car_point = 1. - current_car_point;
    break;
  case RIGHT:
  case LEFT:
    current_car_point = (car_->getY() - tile0_y) / game_->getTrackTileSize() + 0.5;
    current_car_pos_coef_in_tile = abs(tile0_x - car_->getX()) / game_->getTrackTileSize() - 0.5;
    if (tile0->orientation == LEFT)
      current_car_point = 1. - current_car_point;
    break;
  default:
    assert(0);
  }

  const int TRAJ_ANALYZE_LENGTH = 4;
  vector<vector<double>> variants;
  const int traj_analyze_length = std::min<int>((int)traj_tiles_.size(), TRAJ_ANALYZE_LENGTH);
  FindBestTrajRec({}, traj_analyze_length, variants);

  vector<vector<double>> results;
  int index = 0;
  int best_index = -1;
  double max_sum = -numeric_limits<double>::max();
  for (auto& var : variants) {
    double sum = 0.;
    for (int tile_i = 0; tile_i + 1 < var.size(); tile_i++) {
      double sum_tmp = 0.;
      traj_tiles_[tile_i]->GetSum(var[tile_i], var[tile_i + 1], sum_tmp);
      sum += sum_tmp;
      if (tile_i == 0 && traj_tiles_[0]->type == TTT_FORWARD) {
        sum += TrajTile::GetFineFromDelta((current_car_point - var[0]) / current_car_pos_coef_in_tile);
      }
    }
    if (sum > max_sum) {
      best_index = index;
      max_sum = sum;
    }
    index++;
  }

  if (best_index < 0) {
    assert(0);
    best_index = 0;
  }
  vector<double> start_points = variants[best_index];
  
  res_world_points_.clear();
//  cout << "current car point: " << current_car_point << endl;
  
//  cout << "start points:\n";
  for (int i = 0; i < start_points.size(); i++) {
//    cout << start_points[i] << endl;
    double x, y;
    traj_tiles_[i]->StartPointToWorldCoord(start_points[i], x, y);
    res_world_points_.push_back({x, y});
  }
}

void PathAnalyzer::ApplyBonuses() {
  for (auto& tile : traj_tiles_) {
    for (auto& b : world_->getBonuses()) {
      tile->ApplyBonus(b);
    }
  }
}

const int TICK_STEP = 1;
const int MAX_SEARCH_DEPTH = 100 / TICK_STEP;

void PathAnalyzer::FindApproachToTurnRec(const StateInTurn& state, const CheckTurnEndF& f_check_end, double first_wheel_turn, bool right_turn, int depth) {
//  if (depth > MAX_SEARCH_DEPTH)
//    return;
  
  if (f_check_end(state, first_wheel_turn)) {
    return; // continue iterating
  }
  
//  cout << "\n\nnext step:\n";
//  cout << "wheel turn: " << state.wheel_turn << endl;
//  Utils::PrintCoord(state.x, state.y);
//  cout << "speed: (" << state.v_x << ", " << state.v_y << ")" << endl;
//  cout << "car angle: " << state.car_angle * 180.0 / PI << endl;
  
  StateInTurn next;
  next.wheel_turn = state.wheel_turn;
  {
    next.x = state.x + state.v_x;
    next.y = state.y + state.v_y;
  }
  
  double v_x_in_car = 0.;
  double v_y_in_car = 0.;
  {
    // find v in car coordinate system
    Utils::RotateVector(state.v_x, state.v_y, state.car_angle, v_x_in_car, v_y_in_car);
    
    // v_x_in_car - lengthwise
    if (v_x_in_car < 0) {
      // moving backward
      assert(0);
      return;
    }
    
    {
      // v_x
      v_x_in_car += -sgn(v_x_in_car) * game_->getCarMovementAirFrictionFactor() * v_x_in_car * TICK_STEP;
      
      double d_v_x = -sgn(v_x_in_car) * game_->getCarLengthwiseMovementFrictionFactor() * TICK_STEP;
      if (abs(v_x_in_car) > abs(d_v_x))
        v_x_in_car -= d_v_x;
      v_x_in_car += d_v_x;
      
      // assume engine power = 1.0
      v_x_in_car += 0.25 * TICK_STEP;
    }
    {
      // v_y
      v_y_in_car += -sgn(v_y_in_car) * game_->getCarCrosswiseMovementFrictionFactor() * TICK_STEP;
    }
    
    // back to world coordinate system
    Utils::RotateVector(v_x_in_car, v_y_in_car, -state.car_angle, next.v_x, next.v_y);
  }
  
  // TODO: use angle speed too
  
  {
    next.car_angle = state.car_angle + state.wheel_turn * game_->getCarAngularSpeedFactor() * v_x_in_car * TICK_STEP;
    next.car_angle = Utils::AngleToNormal(next.car_angle);
  }
  
//  cout << "\n\nstep out:\n";
//  cout << "wheel turn: " << next.wheel_turn << endl;
//  Utils::PrintCoord(next.x, next.y);
//  cout << "speed: (" << next.v_x << ", " << next.v_y << ")" << endl;
//  cout << "car angle: " << next.car_angle * 180.0 / PI << endl;
//  cout << "delta wheel: " << game_->getCarWheelTurnChangePerTick() * TICK_STEP << endl;
  
  if (!right_turn) {
      next.wheel_turn = state.wheel_turn + game_->getCarWheelTurnChangePerTick() * TICK_STEP;
      if (next.wheel_turn > -1.0 && next.wheel_turn < 1.0) {
//        cout << "go +\n";
        FindApproachToTurnRec(next, f_check_end, first_wheel_turn, right_turn, depth + 1);
      }
  } else {
    next.wheel_turn = state.wheel_turn - game_->getCarWheelTurnChangePerTick() * TICK_STEP;
    if (next.wheel_turn > -1.0 && next.wheel_turn < 1.0) {
      //    cout << "go -\n";
      FindApproachToTurnRec(next, f_check_end, first_wheel_turn, right_turn, depth + 1);
    }
  }
  
  next.wheel_turn = state.wheel_turn;
  if (next.wheel_turn > -1.0 && next.wheel_turn < 1.0) {
//   cout << "go =\n";
   FindApproachToTurnRec(next, f_check_end, first_wheel_turn, right_turn, depth + 1);
  }
}

bool PathAnalyzer::FindApproachToTurn(PathPattern p) {
  
  const long long int MAX_CHECK_NUMBER = 100000L;
  
  const long long int MAX_RESULT_SIZE = MAX_CHECK_NUMBER;
  long long int results_number = 0L;
  double results[MAX_RESULT_SIZE];
  double first_wheel_turns[MAX_RESULT_SIZE];
  
  StateInTurn start_state;
  start_state.x = car_->getX();
  start_state.y = car_->getY();
  start_state.v_x = car_->getSpeedX();
  start_state.v_y = car_->getSpeedY();
  start_state.wheel_turn = car_->getWheelTurn();
  start_state.car_angle = car_->getAngle();
  
  int car_x = Utils::CoordToTile(car_->getX());
  int car_y = Utils::CoordToTile(car_->getY());
  TrajTilePtr current_tile = TrajTilePtr(new TrajTile(TTT_FORWARD, car_x, car_y, traj_tiles_[0]->orientation));
  double start_tile_angle = 0.;
  switch (traj_tiles_[0]->orientation) {
    case UP:
      start_tile_angle = -PI / 2.;
      break;
    case DOWN:
      start_tile_angle = PI / 2.;
      break;
    case RIGHT:
      start_tile_angle = 0;
      break;
    case LEFT:
      start_tile_angle = PI;
      break;
    default:
      break;
  }
  
  long long int check_number = 0L;
  auto f_check_end = [&] (const StateInTurn& s, double first_wheel_turn) -> bool {
    check_number++;
    if (check_number > MAX_CHECK_NUMBER)
      return true;
    
    const double max_angle_deviation = 15.0 / 180.0 * PI;
    if (p.IsRightTurn()) {
      if (!Utils::IsRightTurn(Utils::AngleToNormal(start_tile_angle - max_angle_deviation), s.car_angle)) {
//        cout << "stop: angle < start_tile_angle on the right turn\n";
        return true;
      }
      if (!Utils::IsRightTurn(s.car_angle, Utils::AngleToNormal(start_tile_angle + PI / 2. + max_angle_deviation))) {
//        cout << "stop: angle > turn right turn angle\n";
        return true;
      }
    } else {
      if (Utils::IsRightTurn(Utils::AngleToNormal(start_tile_angle + max_angle_deviation), s.car_angle)) {
//        cout << "stop: angle > start_tile_angle on the left turn\n";
        return true;
      }
      if (Utils::IsRightTurn(s.car_angle, Utils::AngleToNormal(start_tile_angle - PI / 2. - max_angle_deviation))) {
//        cout << "stop: angle < turn left turn angle\n";
        return true;
      }
    }
    
    const double min_velocity = 0.05;
    if (hypot(s.v_x, s.v_y) < min_velocity) {
//      cout << "stop: too small velocity\n";
      return true;
    }
    
    int inside_tile_index = -1;
    for (int i = 0; i < traj_tiles_.size(); i++) {
      if (traj_tiles_[i]->IsCarInside(s)) {
        inside_tile_index = i;
        break;
      }
    }
    if (current_tile->IsCarInside(s)) {
//      cout << "continue: inside current (not the last) tile\n";
      return false; // ok, inside current (not the last) tile
    }
    if (inside_tile_index < 0) {
//      cout << "stop: out of trajectory\n";
      return true; // out of trajectory
    }
    
    int target_tile_index = p.length() - 2; // one before last
    TrajTilePtr& last_tile = traj_tiles_[p.length() - 1];
    if (inside_tile_index == target_tile_index) {
      double v_out = 0.; // -> max
      double v_to_targ_border = 0.; // velocity to border which we are crashing in. -> min
      switch (last_tile->orientation) {
        case UP:
        case DOWN:
          v_out = abs(s.v_y);
          v_to_targ_border = abs(s.v_x);
          break;
        case RIGHT:
        case LEFT:
          v_out = abs(s.v_x);
          v_to_targ_border = abs(s.v_y);
          break;
        default:
          assert(0);
          break;
      }
      
//      cout << "\n get to target tile! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
//      cout << "check_number: " << check_number << endl;
//      cout << "results_number: " << results_number << endl;
//      cout << "wheel turn: " << s.wheel_turn << endl;
//      Utils::PrintCoord(s.x, s.y);
//      cout << "speed: (" << s.v_x << ", " << s.v_y << ")" << endl;
//      cout << "car angle: " << s.car_angle * 180.0 / PI << endl;
      
      results[results_number] = v_out - 5.0 * v_to_targ_border;
      first_wheel_turns[results_number] = first_wheel_turn;
      results_number++;
      return true;
    }
    
    return false;
  };
  
  double start_wheel_turn = start_state.wheel_turn;
  if (p.IsRightTurn()) {
    start_state.wheel_turn = start_wheel_turn + game_->getCarWheelTurnChangePerTick() * TICK_STEP;
    if (start_state.wheel_turn > -1.0 && start_state.wheel_turn < 1.0)
      FindApproachToTurnRec(start_state, f_check_end, start_state.wheel_turn, p.IsRightTurn());
  } else {
    start_state.wheel_turn = start_wheel_turn - game_->getCarWheelTurnChangePerTick() * TICK_STEP;
    if (start_state.wheel_turn > -1.0 && start_state.wheel_turn < 1.0)
      FindApproachToTurnRec(start_state, f_check_end, start_state.wheel_turn, p.IsRightTurn());
  }
  start_state.wheel_turn = start_wheel_turn;
  FindApproachToTurnRec(start_state, f_check_end, start_state.wheel_turn, p.IsRightTurn());
  
  if (check_number > MAX_CHECK_NUMBER)
    cout << "warning: check number overflow\n";
  
  if (results_number == 0) {
    cout << "error: no results ===========================\n";
    return false;
  }
  
  long long int best_result_index = -1;
  double best_result = -numeric_limits<double>::max();
  double worst_result = numeric_limits<double>::max();
  for (long long int i = 0L; i < results_number; i++) {
    double res = results[i];
    worst_result = min<double>(results[i], worst_result);
    if (results[i] > best_result) {
      best_result = results[i];
      best_result_index = i;
    }
  }
  
  cout << "get best wheel turn: " << first_wheel_turns[best_result_index] << endl;
  cout << "best result: " << best_result << endl;
  cout << "worst result: " << worst_result << endl;
  founded_approach_wheel_turn_ = first_wheel_turns[best_result_index];
  is_found_approach_to_turn_ = true;
  
  return true;
}





