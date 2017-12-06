//
//  gameClient.hpp
//  2048AI
//
//  Created by Ryan Guo on 12/6/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#ifndef gameClient_hpp
#define gameClient_hpp

#include "gameboard.h"

class GameClient{
	
public:
	
	GameClient();
	~GameClient();
	
	// Start running the game in console
	// receive keyboard input of following chars:
	// w, s, a, d -> up, down, left, right
	// This triggers movement
	// for each movement, the board and score is printed out.
	void run();
	
	
private:
	
	enum Direction{
		up,
		down,
		left,
		right
	};
	
	GameBoard* board;
	
	void move(Direction dir);
	
};

#endif /* gameClient_hpp */



