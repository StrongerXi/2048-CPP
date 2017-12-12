//
//  AI.hpp
//  2048AI
//
//  Created by Ryan Guo on 12/6/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include "gameboard.h"
#include <unordered_set>

class AI{
	
public:
	
	AI();
	~AI();
	
	void simulate(int8_t depth);
	
	// Using Alpha-Beta pruning to speed up minimax algorithm
	// This function returns the best-case score for the maximizer if it's true
	int64_t ABminimax(const GameBoard& board, int8_t depth, int64_t alpha, int64_t beta, bool maximizer)const;
	
	Direction ABminimaxMove(int8_t depth)const;
	
	
	Direction expectiMaxMove(int8_t depth)const;
	
	int64_t expectiMax(const GameBoard& board, int8_t depth, bool mover)const;
	
private:
	
	GameBoard* board;
	
	int8_t depth_to_search;
	
	// Calculates a score that represents the "fitness" of input board state
	// Heuristics....
	int64_t boardEvaluation(const GameBoard*)const;
	
};





#endif /* AI_hpp */
