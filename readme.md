# Ascii Fantasy Tactics

Simple game in text mode, mix of text adventure and Tactics Battle.  

## How to play

Explore dungeon by using `go north`, `go east`, `go south` and `go west` commands, find the way out.  
Sometimes monsters will attack you, you will need to fight them. In battle mode you can always use `move` and `attack` commands, than choose coordinates in range, ie. `C8`.  
  
![alt text](https://github.com/przem360/ascii-fantasy-tactics/blob/master/screenshot.png?raw=true)

Fighters with *Mage* class hawe spells, you can cast them by using `cast` command than specify ID of a spell, i.e. `fb` for Fire Ball.  
You can also `skip` if you like.

# Build

The game was tested on Linux but since there is no any *weird* dependencies, should also compile on Mac. Just make sure that `build-essential` package is installed and use `make` to build. 