//
//  gameboard.h
//  2048AI
//
//  Created by Ryan Guo on 12/5/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#ifndef gameboard_h
#define gameboard_h

#include <cstdint>
#include <string>

class GameBoard{
	
	
public:
	
	GameBoard(int8_t size = 4);
	~GameBoard();
	
	
	// Move Board based on rule of 2048
	int32_t moveLeft();
	int32_t moveRight();
	int32_t moveUp();
	int32_t moveDown();
	
	bool checkMate() const;
	
	// Check whether board is moveable in each direction
	bool canMoveLeft() const;
	bool canMoveRight() const;
	bool canMoveUp() const;
	bool canMoveDown() const;
	
	void generateNewTile();
	int getEmptyCount() const;
	
	std::string toString() const;
	
	// Return a new board that has the same state as current Board
	GameBoard copyBoard() const;
	
	int32_t getScore() const;
	
private:
	
	void pushArrayLeft(int**&);
	int32_t mergeArrayLeft(int**&);
	void push2DArrayLeft(int***&);
	int32_t merge2DArrayLeft(int***&);
	
	void pushArrayRight(int**&);
	int32_t mergeArrayRight(int**&);
	void push2DArrayRight(int***&);
	int32_t merge2DArrayRight(int***&);
	
	
	
	const int8_t SIZE;
	
	int*** rows;
	int*** cols;
	
	int32_t score;
};


#endif /* gameboard_h */
