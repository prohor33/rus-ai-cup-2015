# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/prohor/Code/rus-ai-cup-2015

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/prohor/Code/rus-ai-cup-2015

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/local/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/prohor/Code/rus-ai-cup-2015/CMakeFiles /Users/prohor/Code/rus-ai-cup-2015/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/prohor/Code/rus-ai-cup-2015/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ai

# Build rule for target.
ai: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ai
.PHONY : ai

# fast build rule for target.
ai/fast:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/build
.PHONY : ai/fast

BonusUser.o: BonusUser.cpp.o
.PHONY : BonusUser.o

# target to build an object file
BonusUser.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/BonusUser.cpp.o
.PHONY : BonusUser.cpp.o

BonusUser.i: BonusUser.cpp.i
.PHONY : BonusUser.i

# target to preprocess a source file
BonusUser.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/BonusUser.cpp.i
.PHONY : BonusUser.cpp.i

BonusUser.s: BonusUser.cpp.s
.PHONY : BonusUser.s

# target to generate assembly for a file
BonusUser.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/BonusUser.cpp.s
.PHONY : BonusUser.cpp.s

Mover.o: Mover.cpp.o
.PHONY : Mover.o

# target to build an object file
Mover.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Mover.cpp.o
.PHONY : Mover.cpp.o

Mover.i: Mover.cpp.i
.PHONY : Mover.i

# target to preprocess a source file
Mover.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Mover.cpp.i
.PHONY : Mover.cpp.i

Mover.s: Mover.cpp.s
.PHONY : Mover.s

# target to generate assembly for a file
Mover.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Mover.cpp.s
.PHONY : Mover.cpp.s

MyStrategy.o: MyStrategy.cpp.o
.PHONY : MyStrategy.o

# target to build an object file
MyStrategy.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/MyStrategy.cpp.o
.PHONY : MyStrategy.cpp.o

MyStrategy.i: MyStrategy.cpp.i
.PHONY : MyStrategy.i

# target to preprocess a source file
MyStrategy.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/MyStrategy.cpp.i
.PHONY : MyStrategy.cpp.i

MyStrategy.s: MyStrategy.cpp.s
.PHONY : MyStrategy.s

# target to generate assembly for a file
MyStrategy.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/MyStrategy.cpp.s
.PHONY : MyStrategy.cpp.s

PathAnalyzer.o: PathAnalyzer.cpp.o
.PHONY : PathAnalyzer.o

# target to build an object file
PathAnalyzer.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathAnalyzer.cpp.o
.PHONY : PathAnalyzer.cpp.o

PathAnalyzer.i: PathAnalyzer.cpp.i
.PHONY : PathAnalyzer.i

# target to preprocess a source file
PathAnalyzer.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathAnalyzer.cpp.i
.PHONY : PathAnalyzer.cpp.i

PathAnalyzer.s: PathAnalyzer.cpp.s
.PHONY : PathAnalyzer.s

# target to generate assembly for a file
PathAnalyzer.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathAnalyzer.cpp.s
.PHONY : PathAnalyzer.cpp.s

PathFinder.o: PathFinder.cpp.o
.PHONY : PathFinder.o

# target to build an object file
PathFinder.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathFinder.cpp.o
.PHONY : PathFinder.cpp.o

PathFinder.i: PathFinder.cpp.i
.PHONY : PathFinder.i

# target to preprocess a source file
PathFinder.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathFinder.cpp.i
.PHONY : PathFinder.cpp.i

PathFinder.s: PathFinder.cpp.s
.PHONY : PathFinder.s

# target to generate assembly for a file
PathFinder.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathFinder.cpp.s
.PHONY : PathFinder.cpp.s

PathPattern.o: PathPattern.cpp.o
.PHONY : PathPattern.o

# target to build an object file
PathPattern.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathPattern.cpp.o
.PHONY : PathPattern.cpp.o

PathPattern.i: PathPattern.cpp.i
.PHONY : PathPattern.i

# target to preprocess a source file
PathPattern.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathPattern.cpp.i
.PHONY : PathPattern.cpp.i

PathPattern.s: PathPattern.cpp.s
.PHONY : PathPattern.s

# target to generate assembly for a file
PathPattern.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/PathPattern.cpp.s
.PHONY : PathPattern.cpp.s

RemoteProcessClient.o: RemoteProcessClient.cpp.o
.PHONY : RemoteProcessClient.o

# target to build an object file
RemoteProcessClient.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/RemoteProcessClient.cpp.o
.PHONY : RemoteProcessClient.cpp.o

RemoteProcessClient.i: RemoteProcessClient.cpp.i
.PHONY : RemoteProcessClient.i

# target to preprocess a source file
RemoteProcessClient.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/RemoteProcessClient.cpp.i
.PHONY : RemoteProcessClient.cpp.i

RemoteProcessClient.s: RemoteProcessClient.cpp.s
.PHONY : RemoteProcessClient.s

# target to generate assembly for a file
RemoteProcessClient.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/RemoteProcessClient.cpp.s
.PHONY : RemoteProcessClient.cpp.s

Runner.o: Runner.cpp.o
.PHONY : Runner.o

# target to build an object file
Runner.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Runner.cpp.o
.PHONY : Runner.cpp.o

Runner.i: Runner.cpp.i
.PHONY : Runner.i

# target to preprocess a source file
Runner.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Runner.cpp.i
.PHONY : Runner.cpp.i

Runner.s: Runner.cpp.s
.PHONY : Runner.s

# target to generate assembly for a file
Runner.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Runner.cpp.s
.PHONY : Runner.cpp.s

Strategy.o: Strategy.cpp.o
.PHONY : Strategy.o

# target to build an object file
Strategy.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Strategy.cpp.o
.PHONY : Strategy.cpp.o

Strategy.i: Strategy.cpp.i
.PHONY : Strategy.i

# target to preprocess a source file
Strategy.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Strategy.cpp.i
.PHONY : Strategy.cpp.i

Strategy.s: Strategy.cpp.s
.PHONY : Strategy.s

# target to generate assembly for a file
Strategy.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Strategy.cpp.s
.PHONY : Strategy.cpp.s

TrajTile.o: TrajTile.cpp.o
.PHONY : TrajTile.o

# target to build an object file
TrajTile.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/TrajTile.cpp.o
.PHONY : TrajTile.cpp.o

TrajTile.i: TrajTile.cpp.i
.PHONY : TrajTile.i

# target to preprocess a source file
TrajTile.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/TrajTile.cpp.i
.PHONY : TrajTile.cpp.i

TrajTile.s: TrajTile.cpp.s
.PHONY : TrajTile.s

# target to generate assembly for a file
TrajTile.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/TrajTile.cpp.s
.PHONY : TrajTile.cpp.s

Utils.o: Utils.cpp.o
.PHONY : Utils.o

# target to build an object file
Utils.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Utils.cpp.o
.PHONY : Utils.cpp.o

Utils.i: Utils.cpp.i
.PHONY : Utils.i

# target to preprocess a source file
Utils.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Utils.cpp.i
.PHONY : Utils.cpp.i

Utils.s: Utils.cpp.s
.PHONY : Utils.s

# target to generate assembly for a file
Utils.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/Utils.cpp.s
.PHONY : Utils.cpp.s

csimplesocket/ActiveSocket.o: csimplesocket/ActiveSocket.cpp.o
.PHONY : csimplesocket/ActiveSocket.o

# target to build an object file
csimplesocket/ActiveSocket.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/ActiveSocket.cpp.o
.PHONY : csimplesocket/ActiveSocket.cpp.o

csimplesocket/ActiveSocket.i: csimplesocket/ActiveSocket.cpp.i
.PHONY : csimplesocket/ActiveSocket.i

# target to preprocess a source file
csimplesocket/ActiveSocket.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/ActiveSocket.cpp.i
.PHONY : csimplesocket/ActiveSocket.cpp.i

csimplesocket/ActiveSocket.s: csimplesocket/ActiveSocket.cpp.s
.PHONY : csimplesocket/ActiveSocket.s

# target to generate assembly for a file
csimplesocket/ActiveSocket.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/ActiveSocket.cpp.s
.PHONY : csimplesocket/ActiveSocket.cpp.s

csimplesocket/HTTPActiveSocket.o: csimplesocket/HTTPActiveSocket.cpp.o
.PHONY : csimplesocket/HTTPActiveSocket.o

# target to build an object file
csimplesocket/HTTPActiveSocket.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/HTTPActiveSocket.cpp.o
.PHONY : csimplesocket/HTTPActiveSocket.cpp.o

csimplesocket/HTTPActiveSocket.i: csimplesocket/HTTPActiveSocket.cpp.i
.PHONY : csimplesocket/HTTPActiveSocket.i

# target to preprocess a source file
csimplesocket/HTTPActiveSocket.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/HTTPActiveSocket.cpp.i
.PHONY : csimplesocket/HTTPActiveSocket.cpp.i

csimplesocket/HTTPActiveSocket.s: csimplesocket/HTTPActiveSocket.cpp.s
.PHONY : csimplesocket/HTTPActiveSocket.s

# target to generate assembly for a file
csimplesocket/HTTPActiveSocket.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/HTTPActiveSocket.cpp.s
.PHONY : csimplesocket/HTTPActiveSocket.cpp.s

csimplesocket/PassiveSocket.o: csimplesocket/PassiveSocket.cpp.o
.PHONY : csimplesocket/PassiveSocket.o

# target to build an object file
csimplesocket/PassiveSocket.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/PassiveSocket.cpp.o
.PHONY : csimplesocket/PassiveSocket.cpp.o

csimplesocket/PassiveSocket.i: csimplesocket/PassiveSocket.cpp.i
.PHONY : csimplesocket/PassiveSocket.i

# target to preprocess a source file
csimplesocket/PassiveSocket.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/PassiveSocket.cpp.i
.PHONY : csimplesocket/PassiveSocket.cpp.i

csimplesocket/PassiveSocket.s: csimplesocket/PassiveSocket.cpp.s
.PHONY : csimplesocket/PassiveSocket.s

# target to generate assembly for a file
csimplesocket/PassiveSocket.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/PassiveSocket.cpp.s
.PHONY : csimplesocket/PassiveSocket.cpp.s

csimplesocket/SimpleSocket.o: csimplesocket/SimpleSocket.cpp.o
.PHONY : csimplesocket/SimpleSocket.o

# target to build an object file
csimplesocket/SimpleSocket.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/SimpleSocket.cpp.o
.PHONY : csimplesocket/SimpleSocket.cpp.o

csimplesocket/SimpleSocket.i: csimplesocket/SimpleSocket.cpp.i
.PHONY : csimplesocket/SimpleSocket.i

# target to preprocess a source file
csimplesocket/SimpleSocket.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/SimpleSocket.cpp.i
.PHONY : csimplesocket/SimpleSocket.cpp.i

csimplesocket/SimpleSocket.s: csimplesocket/SimpleSocket.cpp.s
.PHONY : csimplesocket/SimpleSocket.s

# target to generate assembly for a file
csimplesocket/SimpleSocket.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/csimplesocket/SimpleSocket.cpp.s
.PHONY : csimplesocket/SimpleSocket.cpp.s

model/Bonus.o: model/Bonus.cpp.o
.PHONY : model/Bonus.o

# target to build an object file
model/Bonus.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Bonus.cpp.o
.PHONY : model/Bonus.cpp.o

model/Bonus.i: model/Bonus.cpp.i
.PHONY : model/Bonus.i

# target to preprocess a source file
model/Bonus.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Bonus.cpp.i
.PHONY : model/Bonus.cpp.i

model/Bonus.s: model/Bonus.cpp.s
.PHONY : model/Bonus.s

# target to generate assembly for a file
model/Bonus.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Bonus.cpp.s
.PHONY : model/Bonus.cpp.s

model/Car.o: model/Car.cpp.o
.PHONY : model/Car.o

# target to build an object file
model/Car.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Car.cpp.o
.PHONY : model/Car.cpp.o

model/Car.i: model/Car.cpp.i
.PHONY : model/Car.i

# target to preprocess a source file
model/Car.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Car.cpp.i
.PHONY : model/Car.cpp.i

model/Car.s: model/Car.cpp.s
.PHONY : model/Car.s

# target to generate assembly for a file
model/Car.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Car.cpp.s
.PHONY : model/Car.cpp.s

model/CircularUnit.o: model/CircularUnit.cpp.o
.PHONY : model/CircularUnit.o

# target to build an object file
model/CircularUnit.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/CircularUnit.cpp.o
.PHONY : model/CircularUnit.cpp.o

model/CircularUnit.i: model/CircularUnit.cpp.i
.PHONY : model/CircularUnit.i

# target to preprocess a source file
model/CircularUnit.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/CircularUnit.cpp.i
.PHONY : model/CircularUnit.cpp.i

model/CircularUnit.s: model/CircularUnit.cpp.s
.PHONY : model/CircularUnit.s

# target to generate assembly for a file
model/CircularUnit.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/CircularUnit.cpp.s
.PHONY : model/CircularUnit.cpp.s

model/Game.o: model/Game.cpp.o
.PHONY : model/Game.o

# target to build an object file
model/Game.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Game.cpp.o
.PHONY : model/Game.cpp.o

model/Game.i: model/Game.cpp.i
.PHONY : model/Game.i

# target to preprocess a source file
model/Game.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Game.cpp.i
.PHONY : model/Game.cpp.i

model/Game.s: model/Game.cpp.s
.PHONY : model/Game.s

# target to generate assembly for a file
model/Game.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Game.cpp.s
.PHONY : model/Game.cpp.s

model/Move.o: model/Move.cpp.o
.PHONY : model/Move.o

# target to build an object file
model/Move.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Move.cpp.o
.PHONY : model/Move.cpp.o

model/Move.i: model/Move.cpp.i
.PHONY : model/Move.i

# target to preprocess a source file
model/Move.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Move.cpp.i
.PHONY : model/Move.cpp.i

model/Move.s: model/Move.cpp.s
.PHONY : model/Move.s

# target to generate assembly for a file
model/Move.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Move.cpp.s
.PHONY : model/Move.cpp.s

model/OilSlick.o: model/OilSlick.cpp.o
.PHONY : model/OilSlick.o

# target to build an object file
model/OilSlick.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/OilSlick.cpp.o
.PHONY : model/OilSlick.cpp.o

model/OilSlick.i: model/OilSlick.cpp.i
.PHONY : model/OilSlick.i

# target to preprocess a source file
model/OilSlick.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/OilSlick.cpp.i
.PHONY : model/OilSlick.cpp.i

model/OilSlick.s: model/OilSlick.cpp.s
.PHONY : model/OilSlick.s

# target to generate assembly for a file
model/OilSlick.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/OilSlick.cpp.s
.PHONY : model/OilSlick.cpp.s

model/Player.o: model/Player.cpp.o
.PHONY : model/Player.o

# target to build an object file
model/Player.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Player.cpp.o
.PHONY : model/Player.cpp.o

model/Player.i: model/Player.cpp.i
.PHONY : model/Player.i

# target to preprocess a source file
model/Player.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Player.cpp.i
.PHONY : model/Player.cpp.i

model/Player.s: model/Player.cpp.s
.PHONY : model/Player.s

# target to generate assembly for a file
model/Player.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Player.cpp.s
.PHONY : model/Player.cpp.s

model/PlayerContext.o: model/PlayerContext.cpp.o
.PHONY : model/PlayerContext.o

# target to build an object file
model/PlayerContext.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/PlayerContext.cpp.o
.PHONY : model/PlayerContext.cpp.o

model/PlayerContext.i: model/PlayerContext.cpp.i
.PHONY : model/PlayerContext.i

# target to preprocess a source file
model/PlayerContext.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/PlayerContext.cpp.i
.PHONY : model/PlayerContext.cpp.i

model/PlayerContext.s: model/PlayerContext.cpp.s
.PHONY : model/PlayerContext.s

# target to generate assembly for a file
model/PlayerContext.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/PlayerContext.cpp.s
.PHONY : model/PlayerContext.cpp.s

model/Projectile.o: model/Projectile.cpp.o
.PHONY : model/Projectile.o

# target to build an object file
model/Projectile.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Projectile.cpp.o
.PHONY : model/Projectile.cpp.o

model/Projectile.i: model/Projectile.cpp.i
.PHONY : model/Projectile.i

# target to preprocess a source file
model/Projectile.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Projectile.cpp.i
.PHONY : model/Projectile.cpp.i

model/Projectile.s: model/Projectile.cpp.s
.PHONY : model/Projectile.s

# target to generate assembly for a file
model/Projectile.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Projectile.cpp.s
.PHONY : model/Projectile.cpp.s

model/RectangularUnit.o: model/RectangularUnit.cpp.o
.PHONY : model/RectangularUnit.o

# target to build an object file
model/RectangularUnit.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/RectangularUnit.cpp.o
.PHONY : model/RectangularUnit.cpp.o

model/RectangularUnit.i: model/RectangularUnit.cpp.i
.PHONY : model/RectangularUnit.i

# target to preprocess a source file
model/RectangularUnit.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/RectangularUnit.cpp.i
.PHONY : model/RectangularUnit.cpp.i

model/RectangularUnit.s: model/RectangularUnit.cpp.s
.PHONY : model/RectangularUnit.s

# target to generate assembly for a file
model/RectangularUnit.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/RectangularUnit.cpp.s
.PHONY : model/RectangularUnit.cpp.s

model/Unit.o: model/Unit.cpp.o
.PHONY : model/Unit.o

# target to build an object file
model/Unit.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Unit.cpp.o
.PHONY : model/Unit.cpp.o

model/Unit.i: model/Unit.cpp.i
.PHONY : model/Unit.i

# target to preprocess a source file
model/Unit.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Unit.cpp.i
.PHONY : model/Unit.cpp.i

model/Unit.s: model/Unit.cpp.s
.PHONY : model/Unit.s

# target to generate assembly for a file
model/Unit.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/Unit.cpp.s
.PHONY : model/Unit.cpp.s

model/World.o: model/World.cpp.o
.PHONY : model/World.o

# target to build an object file
model/World.cpp.o:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/World.cpp.o
.PHONY : model/World.cpp.o

model/World.i: model/World.cpp.i
.PHONY : model/World.i

# target to preprocess a source file
model/World.cpp.i:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/World.cpp.i
.PHONY : model/World.cpp.i

model/World.s: model/World.cpp.s
.PHONY : model/World.s

# target to generate assembly for a file
model/World.cpp.s:
	$(MAKE) -f CMakeFiles/ai.dir/build.make CMakeFiles/ai.dir/model/World.cpp.s
.PHONY : model/World.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... ai"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... BonusUser.o"
	@echo "... BonusUser.i"
	@echo "... BonusUser.s"
	@echo "... Mover.o"
	@echo "... Mover.i"
	@echo "... Mover.s"
	@echo "... MyStrategy.o"
	@echo "... MyStrategy.i"
	@echo "... MyStrategy.s"
	@echo "... PathAnalyzer.o"
	@echo "... PathAnalyzer.i"
	@echo "... PathAnalyzer.s"
	@echo "... PathFinder.o"
	@echo "... PathFinder.i"
	@echo "... PathFinder.s"
	@echo "... PathPattern.o"
	@echo "... PathPattern.i"
	@echo "... PathPattern.s"
	@echo "... RemoteProcessClient.o"
	@echo "... RemoteProcessClient.i"
	@echo "... RemoteProcessClient.s"
	@echo "... Runner.o"
	@echo "... Runner.i"
	@echo "... Runner.s"
	@echo "... Strategy.o"
	@echo "... Strategy.i"
	@echo "... Strategy.s"
	@echo "... TrajTile.o"
	@echo "... TrajTile.i"
	@echo "... TrajTile.s"
	@echo "... Utils.o"
	@echo "... Utils.i"
	@echo "... Utils.s"
	@echo "... csimplesocket/ActiveSocket.o"
	@echo "... csimplesocket/ActiveSocket.i"
	@echo "... csimplesocket/ActiveSocket.s"
	@echo "... csimplesocket/HTTPActiveSocket.o"
	@echo "... csimplesocket/HTTPActiveSocket.i"
	@echo "... csimplesocket/HTTPActiveSocket.s"
	@echo "... csimplesocket/PassiveSocket.o"
	@echo "... csimplesocket/PassiveSocket.i"
	@echo "... csimplesocket/PassiveSocket.s"
	@echo "... csimplesocket/SimpleSocket.o"
	@echo "... csimplesocket/SimpleSocket.i"
	@echo "... csimplesocket/SimpleSocket.s"
	@echo "... model/Bonus.o"
	@echo "... model/Bonus.i"
	@echo "... model/Bonus.s"
	@echo "... model/Car.o"
	@echo "... model/Car.i"
	@echo "... model/Car.s"
	@echo "... model/CircularUnit.o"
	@echo "... model/CircularUnit.i"
	@echo "... model/CircularUnit.s"
	@echo "... model/Game.o"
	@echo "... model/Game.i"
	@echo "... model/Game.s"
	@echo "... model/Move.o"
	@echo "... model/Move.i"
	@echo "... model/Move.s"
	@echo "... model/OilSlick.o"
	@echo "... model/OilSlick.i"
	@echo "... model/OilSlick.s"
	@echo "... model/Player.o"
	@echo "... model/Player.i"
	@echo "... model/Player.s"
	@echo "... model/PlayerContext.o"
	@echo "... model/PlayerContext.i"
	@echo "... model/PlayerContext.s"
	@echo "... model/Projectile.o"
	@echo "... model/Projectile.i"
	@echo "... model/Projectile.s"
	@echo "... model/RectangularUnit.o"
	@echo "... model/RectangularUnit.i"
	@echo "... model/RectangularUnit.s"
	@echo "... model/Unit.o"
	@echo "... model/Unit.i"
	@echo "... model/Unit.s"
	@echo "... model/World.o"
	@echo "... model/World.i"
	@echo "... model/World.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

