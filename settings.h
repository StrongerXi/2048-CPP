//
//  settings.h
//  2048AI
//
//  Created by Ryan Guo on 12/6/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.
//

#ifndef settings_h
#define settings_h

const int BOARD_SIZE = 4;

const int TILE_BASE_VALUE = 2;

const float TILE_2_PROBABILITY = 0.9;
const float TILE_4_PROBABILITY = 0.1;



const int evalMatrix1[4][4] =
{{8192,4096,2048,1024},
	{64,128,256,512},
	{32,16,8,4},
	{-1,0,1,2}};

const int evalMatrix[4][4] =
{{1024,256,32,-32},
	{256,32,-32,-128},
	{32,-32,-128,-512},
	{-32,-128,-512,-1024}};


const int64_t DEAD_PENALTY = -10000;


enum Direction{
	up,
	down,
	left,
	right
};

const Direction directionIterator[] = {up,down,left,right};

#endif /* settings_h */
