//
//  AI.cpp
//  2048AI
//
//  Created by Ryan Guo on 12/6/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#include "AI.hpp"
#include <cmath>
#include "settings.h"
#include <iostream>

AI::AI(){
	board = new GameBoard();
}

AI::~AI(){
	delete board;
}

void AI::simulate(int8_t depth){
	
	depth_to_search = (depth+1)*2;
	
	board->generateNewTile();
	board->generateNewTile();
	
	//std::cout<< board->toString();
	
	while(!board->checkMate()){
		Direction dir =  board->score > 60000 ? expectiMaxMove(depth+1) : expectiMaxMove(depth);
		board->score += board->moveInDir(dir);
		board->generateNewTile();
		std::cout<< board->toString();
	}
	
	std::cout<< board->toString();
	
	
}


Direction AI::ABminimaxMove(int8_t depth)const{
	
	Direction bestMove = up;
	int32_t bestScore = std::numeric_limits<int32_t>::min();
	
	for(Direction dir : directionIterator){
		if(board->boardMoveableIn(dir)){
			
			GameBoard* newBoard = new GameBoard(*board);
			int32_t temp = newBoard->moveInDir(dir);
			
			temp += ABminimax(newBoard, depth*2-1, std::numeric_limits<int64_t>::min(),
								std::numeric_limits<int64_t>::max(), false);
			
			
			std::cout<<dir<<" with score " <<temp << "\n";
			
			if(temp > bestScore) {
				bestScore = temp;
				bestMove = dir;
			}
			delete newBoard;
		}
	}
	
	return bestMove;
}





int64_t AI::ABminimax(const GameBoard* board, int8_t depth, int64_t alpha, int64_t beta, bool maximizer)const{
	
	if(depth == 0){
		return boardEvaluation(board);
	}
	
	if(board->checkMate() || !board->maxTileInTLCorner()){
		
		int64_t sum = 0;
		
		for(int row = 0; row < board->getSize(); row++){
			for(int col = 0; col < board->getSize(); col++){
				sum += board->getValueAt(row, col);
			}
		}
		
		return -sum;
	}
	
	if (maximizer){
		int64_t potentialHigherAlpha = std::numeric_limits<int64_t>::min();
		
		for(Direction dir : directionIterator){
			if(board->boardMoveableIn(dir)){
				
				
				GameBoard* newBoard = new GameBoard(*board);
				
				int32_t score = newBoard->moveInDir(dir);
				
				score += ABminimax(newBoard, depth-1, alpha, beta, false);
				
				potentialHigherAlpha = potentialHigherAlpha > score ? potentialHigherAlpha : score;
				
				alpha = alpha > potentialHigherAlpha ? alpha : potentialHigherAlpha;
				
				if(alpha >= beta) break;
			}
		}
		return potentialHigherAlpha;
	}
	// else minimizer/computer
	
	int64_t potentialLowerBeta = std::numeric_limits<int64_t>::max();
	
	for(int row = 0; row < board->getSize(); row++){
		
		for(int col = 0; col < board->getSize(); col++){
			
			if(board->getValueAt(row,col) == 0){
				
				int64_t combinedWeightScore = 0;
				
				GameBoard* baseBoard = new GameBoard(*board);
				baseBoard->setValueAt(TILE_BASE_VALUE, row, col);
				combinedWeightScore += TILE_2_PROBABILITY * ABminimax(baseBoard, depth-1, alpha, beta, true);
				
				GameBoard* doubleBaseBoard = new GameBoard(*board);
				doubleBaseBoard->setValueAt(2*TILE_BASE_VALUE, row, col);
				combinedWeightScore += TILE_4_PROBABILITY * ABminimax(doubleBaseBoard, depth-1, alpha, beta, true);
				
				potentialLowerBeta = potentialLowerBeta < combinedWeightScore ? potentialLowerBeta : combinedWeightScore;
		
				beta = beta < potentialLowerBeta ? alpha : potentialLowerBeta;
				
				if(alpha >= beta) break;
			}
		}
	}
	
	return potentialLowerBeta;
}



Direction AI::expectiMaxMove(int8_t depth)const{
	
	Direction bestMove = up;
	int32_t bestScore = std::numeric_limits<int32_t>::min();
	
	for(Direction dir : directionIterator){
		if(board->boardMoveableIn(dir)){
			
			GameBoard newBoard = GameBoard(*board);
			int32_t temp = newBoard.moveInDir(dir);
			
			temp += expectiMax(newBoard, depth*2-1, false);
			
			//std::cout<<dir<<" with score " <<temp << "\n";
			
			if(temp > bestScore) {
				bestScore = temp;
				bestMove = dir;
			}
		}
	}
	
	return bestMove;
}


int64_t AI::expectiMax(const GameBoard& board, int8_t depth, bool mover)const{
	
	if(depth == 0){
		return boardEvaluation(&board);
	}
	
	if(board.checkMate() || !board.maxTileInTLCorner()){
		
		int64_t sum = 0;
		
		for(int row = 0; row < board.getSize(); row++){
			for(int col = 0; col < board.getSize(); col++){
				sum += board.getValueAt(row, col);
			}
		}
		
		return -(sum * depth * depth);
	}
	
	if(mover){
		
		int64_t maxScore = std::numeric_limits<int64_t>::min();
		
		
		for(const Direction dir : directionIterator){
			if(board.boardMoveableIn(dir)){
				
				int64_t scoreInDir = 0;
				
				GameBoard newBoard = GameBoard(board);
				
				scoreInDir += newBoard.moveInDir(dir);
				
				scoreInDir += expectiMax(newBoard, depth-1, false);
				
				maxScore = scoreInDir > maxScore ? scoreInDir : maxScore;
			}
		}
		return maxScore;
	}
	
	
	// else if computer's move
	
	int count = 0;
	int64_t expectedSum = 0;
	
	for(int row = 0; row < board.getSize(); row++){
		
		for(int col = 0; col < board.getSize(); col++){
		
			if (board.getValueAt(row, col) == 0){
				count++;

				GameBoard baseBoard = GameBoard(board);
				baseBoard.setValueAt(TILE_BASE_VALUE, row, col);
				int64_t baseTileScore = expectiMax(baseBoard, depth-1, true);
				
				expectedSum += (TILE_2_PROBABILITY * baseTileScore);
				
				if(depth_to_search - depth < 6){
					
					//GameBoard* doubleBaseBoard = new GameBoard(*board);
					baseBoard.setValueAt(2*TILE_BASE_VALUE, row, col);
	
					int64_t doubleBaseTileScore = expectiMax(baseBoard, depth-1, true);
					expectedSum += (TILE_4_PROBABILITY * doubleBaseTileScore);
				}
			}
		}
	}
	
	
	return expectedSum/count;
}




int64_t AI::boardEvaluation(const GameBoard* board)const{
	
	int64_t fitness = 0;
	
	for(int row = 0; row < board->getSize(); row++){
		for(int col = 0; col < board->getSize(); col++){
			fitness += evalMatrix[row][col] * board->getValueAt(row, col);
		}
	}
	
	return fitness;
}
