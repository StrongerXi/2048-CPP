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

	Direction expectiMaxMove(int8_t depth)const;
	int64_t expectiMax(const GameBoard& board, int8_t depth, bool mover)const;
	
private:
	
	GameBoard* board;
	int8_t depth_to_search;

	// Calculates a score that represents the "fitness" of input board state
	// Heuristics....
};

#endif /* AI_hpp */
