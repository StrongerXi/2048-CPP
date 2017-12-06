//
//  gameboard.cpp
//  2048AI
//
//  Created by Ryan Guo on 12/5/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#include <stdio.h>
#include "gameboard.h"
#include <iostream>

const float TILE_2_PROBABILITY = 0.7;
const float TILE_4_PROBABILITY = 0.3;



GameBoard::GameBoard(int8_t size)
:SIZE(size)
{
	rows = new int**[size];
	cols = new int**[size];
	
	for(int rindex = 0; rindex < size; rindex++){
		rows[rindex] = new int*[size];
		for(int cindex = 0; cindex < size; cindex++){
			rows[rindex][cindex] = new int (1);
		}
	}
	
	for(int cindex = 0; cindex < size; cindex++){
		cols[cindex] = new int*[size];
		for(int rindex=0; rindex<size; rindex++){
			cols[cindex][rindex] = rows[rindex][cindex];
		}
	}
	score = 0;
	
}

GameBoard::~GameBoard(){
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			delete rows[row][col];
		}
		delete[] rows[row];
		delete[] cols[row];
	}
	
	delete[] rows;
	delete[] cols;
}


int32_t GameBoard::moveUp(){
	push2DArrayLeft(cols);
	int32_t score = merge2DArrayLeft(cols);
	push2DArrayLeft(cols);
	return score;
}

int32_t GameBoard::moveDown(){
	push2DArrayRight(cols);
	int32_t score = merge2DArrayRight(cols);
	push2DArrayRight(cols);
	return score;
}

int32_t GameBoard::moveLeft(){
	push2DArrayLeft(rows);
	int32_t score = merge2DArrayLeft(rows);
	push2DArrayLeft(rows);
	return score;
}

int32_t GameBoard::moveRight(){
	push2DArrayRight(rows);
	int32_t score = merge2DArrayRight(rows);
	push2DArrayRight(rows);
	return score;
}



void GameBoard::push2DArrayLeft(int***& arr2D){
	for(int index = 0; index < SIZE; index++){
		pushArrayLeft(arr2D[index]);
	}
}

int32_t GameBoard::merge2DArrayLeft(int***& arr2D){
	int32_t score = 0;
	for(int index = 0; index < SIZE; index++){
		score += mergeArrayLeft(arr2D[index]);
	}
	return score;
}


// Treats the numbers in the arr as a row
// then push them leftwards WITHOUT MERGING
// starting from leftmost index, look towards the right for the first
// non-empty number, then moves that number to the current index, and set that number to 0
void GameBoard::pushArrayLeft(int**& arr){
	
	for(int currentIndex = 0; currentIndex<SIZE; currentIndex++){
		
		if(*arr[currentIndex] != 0) continue;
		
		for(int searchIndex = currentIndex+1; searchIndex<SIZE; searchIndex++){
			if(*arr[searchIndex] != 0){
				*arr[currentIndex] = *arr[searchIndex];
				*arr[searchIndex] = 0;
				break;
			}
		}
	}
}

// Merge the values in array towards the left
// This gives priority, to identical and adjacent tiles,
// while reading from the left to right
// PRE-CONDITION: The non-empty tiles in the row must all be located adjacently on the left
// VIOLATION: [2, 0, 2, 0], [0, 2, 2, 2], [2, 2, 0, 2]...
int32_t GameBoard::mergeArrayLeft(int**& arr){
	
	int32_t score = 0;
	int index = 1;
	
	while(index < SIZE){
		if (*arr[index] == 0) break;
		
		if (*arr[index] == *arr[index-1]){
			*arr[index-1] *= 2;
			*arr[index] = 0;
			score += *arr[index-1];
			index += 2;
		}else{
			index++;
		}
	}
	return score;
}





void GameBoard::push2DArrayRight(int***& arr2D){
	for(int index = 0; index < SIZE; index++){
		pushArrayRight(arr2D[index]);
	}
}

int32_t GameBoard::merge2DArrayRight(int***& arr2D){
	int32_t score = 0;
	for(int index = 0; index < SIZE; index++){
		score += mergeArrayRight(arr2D[index]);
	}
	return score;
}


// Treats the numbers in the arr as a row
// then push them Rightwards WITHOUT MERGING
// starting from Rightmost index, look towards the right for the first
// non-empty number, then moves that number to the current index, and set that number to 0
void GameBoard::pushArrayRight(int**& arr){
	
	for(int currentIndex = SIZE-1; currentIndex >= 0; currentIndex--){
		
		if(*arr[currentIndex] != 0) continue;
		
		for(int searchIndex = currentIndex-1; searchIndex >= 0; searchIndex--){
			if(*arr[searchIndex] != 0){
				*arr[currentIndex] = *arr[searchIndex];
				*arr[searchIndex] = 0;
				break;
			}
		}
	}
}

// Merge the values in array towards the Right
// This gives priority, to identical and adjacent tiles,
// while reading from the Right to right
// PRE-CONDITION: The non-empty tiles in the row must all be located adjacently on the Right
// VIOLATION: [2, 0, 2, 0], [0, 2, 2, 2], [2, 2, 0, 2]...
int32_t GameBoard::mergeArrayRight(int**& arr){
	
	int32_t score = 0;
	int index = SIZE-2;
	
	while(index >= 0){
		if (*arr[index] == 0) break;
		
		if (*arr[index] == *arr[index+1]){
			*arr[index+1] *= 2;
			*arr[index] = 0;
			score += *arr[index+1];
			index -= 2;
		}else{
			index--;
		}
	}
	return score;
}


// Generate a random tile on one of the empty tiles
// the value of tile is determined by chance and constants
void GameBoard::generateNewTile(){
	int empty_count = getEmptyCount();
	
	int ith_empty = rand() % empty_count;
	
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			if(*rows[row][col] == 0){
				if(ith_empty == 0){
					int random = rand() % 101;
					float chance = (float) random/101;
					*rows[row][col] = (chance < TILE_2_PROBABILITY) ? 2:4;
					return;
				}
				ith_empty--;
			}
		}
	}
}


int GameBoard::getEmptyCount()const{
	int count = 0;
	for(int row = 0; row < SIZE; row++){
		for(int col=0; col < SIZE; col++){
			count += *rows[row][col] == 0 ? 1 : 0;
		}
	}
	return count;
}

int32_t GameBoard::getScore()const{
	return score;
}




std::string GameBoard::toString() const{
	
	std::string str = "";
	
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			str += std::to_string(*rows[row][col]);
			str += "\t";
		}
		str += "\n\n";
	}
		
	
	return str;
}

