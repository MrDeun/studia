# Dungeon - Terminal-Based games

OS: Windows

Made with: C++, CMake

You are an explorer, discovering of secrets of a local dungeon, searching for treasure.

### Controls:
 W,S,A,D - Move in four directions.
 
 ### Classes:
 ***Tile*** - contains information about what's on a tile (Player, Wall, Floor, Hole, Treasure, Exit)
 
 ***Labyrinth*** - class that's holding a array of ***Tiles*** and contains a logic for player's interaction. Labyrinth is loaded from{N-1}.txt where N is amount of labyrinth defined in code. (Default - 2)
 
 ***Game*** - contains queue of Labyrinth, loading a new one if player succesfly completed a previous Labyrinth.
  
 ***Terminal Game*** - inheritended from ***Game***  that contains overridden function for interaction with terminal.
