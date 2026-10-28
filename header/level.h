#pragma once
#include "header/constants.h"

typedef struct Hole {
	CP_Vector position;
	//float radius;
} Hole;

/*!
@brief applies friction to movement vector that slows horse fella down depending on how long it moves
*//*______________________________________________________________*/
//array 
typedef enum TileType {
	tileGrass,
	tileStart,
	tileWall,
	tileWater,
	tileHole,
	tileSand
} TileType;

typedef struct Level {
	TileType  tiles[GRID_ROW][GRID_COL];
	CP_Vector ballStart;
	Hole	  hole;
	int		  par;
} Level;

void     Level_Load(Level* lvl, const char* layout[GRID_ROW], int par);
TileType Level_GetTile(const Level* lvl, int col, int row);
void     Level_Draw(const Level* lvl);