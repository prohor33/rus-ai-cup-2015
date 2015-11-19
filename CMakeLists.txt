cmake_minimum_required(VERSION 2.6)
project(ai)

SET(CMAKE_CXX_FLAGS "-D_MARCH -std=c++11 -O2 -Wall -Wno-unknown-pragmas")

add_executable (ai
    csimplesocket/HTTPActiveSocket.cpp
    csimplesocket/ActiveSocket.cpp
    csimplesocket/PassiveSocket.cpp
    csimplesocket/SimpleSocket.cpp
    model/Bonus.cpp
    model/Car.cpp
    model/CircularUnit.cpp
    model/Game.cpp
    model/Move.cpp
    model/OilSlick.cpp
    model/Player.cpp
    model/PlayerContext.cpp
    model/Projectile.cpp
    model/RectangularUnit.cpp
    model/Unit.cpp
    model/World.cpp
    MyStrategy.cpp
    RemoteProcessClient.cpp
    Runner.cpp
    Strategy.cpp
    BonusUser.cpp
    Mover.cpp
    PathAnalyzer.cpp
    PathFinder.cpp
    PathPattern.cpp
    TrajTile.cpp
    Utils.cpp
)
