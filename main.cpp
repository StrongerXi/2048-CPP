//
//  main.cpp
//  2048AI
//
//  Created by Ryan Guo on 12/5/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#include <iostream>
#include "gameboard.h"
#include <ctime>
#include <cstdlib>


//TODO:
// Create a client for interactive gaming
// Create the ai and simulation classes.

int main(int argc, const char * argv[]) {
	
	GameBoard board0 = GameBoard();
	
	GameBoard board1 = GameBoard(5);
	
	srand(time(0));

	

	std::cout<< board0.toString() << "\n";
	
	board1.moveRight();
	std::cout<< board1.toString() << "\n";
	
	board1.moveUp();
	board1.generateNewTile();
	board1.generateNewTile();
	board1.generateNewTile();
	board1.generateNewTile();
	board1.generateNewTile();
	board1.generateNewTile();
	board1.generateNewTile();
	board1.generateNewTile();
	
	
	std::cout<< board1.toString() << "\n";
	
	
	
	return 0;
}
