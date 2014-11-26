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


### Why

This is a final university project. This game will be in 2D and will use SDL2 library for graphics rendering.
 At the end of trimester, LibreSTR will include :
	- Random Map generation
	- 3 types of grounds units and buildings
	- Little Artificial intelligence for Human VS CPU Match-Up
	- Mods support (Game assets modification)


### To Do
  - GameMap tile Update receptor (remove resource)
  - GroundUnit vision to be handled
  - Building Creation
