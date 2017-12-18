//
//  settings.h
//  2048AI
//
//  Created by Ryan Guo on 12/6/17.
//  Copyright © 2017 Ryan Guo. All rights reserved.

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

const int evalMatrix4[4][4] =
{	{23,14,11,4},
	{17,12,10,3},
	{14,11,8,2},
	{11,8,5,1}};

const int evalMatrix2[4][4] =
{{512,256,64,16},
	{256,32,-32,-128},
	{64,-32,-128,-512},
	{16,-128,-512,-1024}};

const int evalMatrix5[4][4] =
	{{80,40,20,4},
	{60,30,15,3},
	{40,20,10,2},
	{25,10,5,1}};

const int evalMatrix3[4][4] =
{	{320,80,40,4},
	{160,40,20,3},
	{80,20,10,2},
	{15,10,5,1}};

const int evalMatrix6[4][4] =
{	{45,40,26,4},
	{34,30,23,3},
	{27,24,20,2},
	{11,8,5,1}};

const int evalMatrixx[4][4] =
{	{45,40,36,4},
	{32,28,24,3},
	{20,17,14,2},
	{11,8,5,1}};

const int evalMatrix[4][4] =
{	{45,40,36,32},
	{25,22,20,17},
	{14,11,9,7},
	{4,2,1,0}};




const int64_t DEAD_PENALTY = -10000;


enum Direction{
	up,
	down,
	left,
	right
};

const Direction directionIterator[] = {up,down,left,right};

#endif /* settings_h */
