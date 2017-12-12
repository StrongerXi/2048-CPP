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
#include "settings.h"

class GameBoard{
	
	
	
public:
	
	GameBoard(int8_t size = 4);
	GameBoard(GameBoard const &);
	~GameBoard();
	
	int32_t moveInDir(Direction);
	
	// Move Board based on rule of 2048
	int32_t moveLeft();
	int32_t moveRight();
	int32_t moveUp();
	int32_t moveDown();
	
	// Determine whether the board is dead
	// (no more move available in any direction)
	bool checkMate() const;
	
	// Check whether the board is moveable in specific direction
	bool boardMoveableIn(Direction)const;
	
	
	// Generate a new Tile with random value on the board
	void generateNewTile();
	
	int getEmptyCount() const;
	
	int getValueAt(int row, int col) const;
	
	void setValueAt(int value, int row, int col);
	
	// Return the string representation of the board, including score
	std::string toString() const;
	
	// Return a new board that has the same state as current Board
	GameBoard copyBoard() const;
	
	int32_t getScore() const;
	
	int8_t getSize() const;
	
	// Returns true if the maximum tile value is in the top left corner
	bool maxTileInTLCorner()const;
	
	
	int** getTable()const;
	
	int boardSum()const;
	
	int32_t score;

	
private:
	
	bool checkTileMoveable(int row, int col)const;
	
	void pushArrayLeft(int*[BOARD_SIZE]);
	int32_t mergeArrayLeft(int*[BOARD_SIZE]);
	void push2DArrayLeft(int*[BOARD_SIZE][BOARD_SIZE]);
	int32_t merge2DArrayLeft(int*[BOARD_SIZE][BOARD_SIZE]);
	
	void pushArrayRight(int*[BOARD_SIZE]);
	int32_t mergeArrayRight(int*[BOARD_SIZE]);
	void push2DArrayRight(int*[BOARD_SIZE][BOARD_SIZE]);
	int32_t merge2DArrayRight(int*[BOARD_SIZE][BOARD_SIZE]);
	
	// Determine whether an given array can be moved/merged towards
	// right or left
	bool canArrayMoveRight(int*[BOARD_SIZE]) const;
	bool canArrayMoveLeft(int*[BOARD_SIZE]) const;
	
	
	// Check whether board is moveable in each direction
	bool canMoveLeft() const;
	bool canMoveRight() const;
	bool canMoveUp() const;
	bool canMoveDown() const;
	
	
	
	const int8_t SIZE;
	
	int board[BOARD_SIZE][BOARD_SIZE];
	int* rows[BOARD_SIZE][BOARD_SIZE];
	int* cols[BOARD_SIZE][BOARD_SIZE];
};


#endif /* gameboard_h */
