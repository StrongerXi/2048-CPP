//
//  gameClient.cpp
//  2048AI
//
//  Created by Ryan Guo on 12/6/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//


#include <stdio.h>
#include "iostream"
#include "gameClient.hpp"


GameClient::GameClient(){
	board = new GameBoard();
}

GameClient::~GameClient(){
	delete board;
}


void GameClient::run(){
	
	// Initiate the game with two random tiles
	board->generateNewTile();
	board->generateNewTile();
	
	
	std::cout<< board->toString();
	
	char input = ' ';
	
	while(input != 'q' && !board->checkMate()){
		input = std::cin.get();
		switch (input) {
			case 'w': board->moveUp();
				board->generateNewTile();
				break;
			case 's': board->moveDown();
				board->generateNewTile();
				break;
			case 'a': board->moveLeft();
				board->generateNewTile();
				break;
			case 'd': board->moveRight();
				board->generateNewTile();
				break;
		}
		std::cout<< board->toString();
	}
	
	
	std::cout<< board->toString();
	
}

