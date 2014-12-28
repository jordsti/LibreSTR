LibreSTR
========
LibreSTR is a open source real-time strategy game. 


### Features

	- Game Unit attributes are specified with text file
	- A MapEditor will be bundled with the game
	- Random Map Generation
	- Basic Artificial Intelligence
	- Possibility to modify the game with text file
	- Maybe a multiplayer !!

### How to build

This project is using the lastest version of StiGame (available at https://github.com/jordsti/stigame).

LibreSTR depends on SDL2, SDL2-image, SDL2-ttf, SDL2-gfx and SDL2-net. This is tested on both Linux and Windows.

We are currently using CMake for the Makefile generation. 

So this build this projet, you need to build StiGame first, and after you can build LibreSTR with CMake.

** write up a little more about this ! **

#### Windows Build
1. Fetch the last StiGame version from GitHub (https://github.com/jordsti/stigame)
2. Download SDL2 libraries and headers, there's currently a Zip package with all this here :  https://docs.google.com/uc?authuser=0&id=0B_P5byse05MmS01LUi1HcEdsZnc&export=download
3. Extract this package into StiGame root **and** LibreSTR root
4. Build StiGame
5. Build LibreSTR

#### Linux Build
1. Install the SDL2-*-dev package from your repository.
  * SDL2-image, SDL2-gfx, SDL2-ttf, SDL2-net
2. Grab StiGame from GitHub (https://github.com/jordsti/stigame)
3. Build StiGame
4. Build LibreSTR
5. To Run LibreSTR, add the directory of compiled StiGame.so to the LD_LIBRARY_PATH variable, so ld will be able to find it!


### Nightly Builds

A binary is available and compiled at each days at this website http://ci.sticode.org/


### Why

This is a final university project. 
This game will be in 2D and will use SDL2 library for graphics rendering.
At the end of trimester, LibreSTR will include :
	
	- Random Map generation
	- 3 types of grounds units and buildings
	- ~~Little Artificial intelligence for Human VS CPU Match-Up~~ Delayed
	- Mods support (Game assets modification)


### To Do
  - GameMap tile Update receptor (remove resource)
  - Key to center view arround selected unit
  - Loading State
  - Change BuildTask endPoint to a nearest extremity of the building (little bug)
  - Win Condition (Player Unit Count == 0 -> loss)
  - awful segfault, random appearance...!!
  - BuilTask use middle pt of building and maybe remove the half of hypotenuse
  - Console one line is hidden ? (bug)
  - attack speed
  - Unit cancellation
  - Worker button fix,  2 cols, 2 rows

#### Possible in the future
  - Idle worker selector
  - Player's Unit position to be draw on the minimap !
  - MapEvent Listener for Dead Unit
  - ...

