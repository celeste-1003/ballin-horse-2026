#pragma once

#include "cprocessing.h"
#include "header/constants.h"

//just enum of different tile types
typedef enum TileType {
    tileGrass, //0
    tileStart, //1
    tileWall, //2
    tileWater, //3
    tileHole, //4
    tileSand, //5
    tileSpike, //6
    tileStickyWall //7  
} TileType;

// struct of what compromises of a level
typedef struct Level {

    //2D array so i can draw easily, ai helped me formulate this array cuz nvr really taught before
    TileType  tiles[GRID_ROW][GRID_COL]; 
    CP_Vector ballStart;
    CP_Vector hole;
    int       par;

} Level;

void     Level_Load(Level* lvl, const char* layout[GRID_ROW], int par);
TileType Level_GetTile(const Level* lvl, int col, int row);
void     Level_Draw(const Level* lvl);