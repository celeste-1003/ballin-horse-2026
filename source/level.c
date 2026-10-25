#include <math.h>
#include "cprocessing.h"
#include "header/constants.h"
#include "header/level.h"

void Level_Load(Level* lvl, const char* layout[GRID_ROW], int par) {

    lvl->par = par;

    for (int row = 0; row < GRID_ROW; row++) {
        for (int col = 0; col < GRID_COL; col++) {
            char c = layout[row][col];
            TileType type = tileGrass;

            switch (c) {
            case '#': type = tileWall;	break;
            case 's': type = tileSand;  break;
            case 'w': type = tileWater; break;
            case 'B': lvl->ballStart = CP_Vector_Set((col + 0.5f) * TILE_SIZE, (row + 0.5f) * TILE_SIZE);
                break;
            case 'H': lvl->hole.pos = CP_Vector_Set((col + 0.5f) * TILE_SIZE, (row + 0.5f) * TILE_SIZE);
                break;
            }

            lvl->tiles[row][col] = type;
        }
    }
}

TileType Level_GetTile(const Level* lvl, int col, int row) {
    if (col < 0 || col >= GRID_COL || row < 0 || row >= GRID_ROW) {
        return tileWall;
    }
    return lvl->tiles[row][col];
}

void Level_Draw(const Level* lvl) {
    for (int row = 0; row < GRID_ROW; row++) {
        for (int col = 0; col < GRID_ROW; col++) {
            switch (lvl->tiles[row][col]) {
                case tileWall: CP_Settings_Fill(CP_Color_Create(110, 70, 40, 255)); break;
                case tileSand: CP_Settings_Fill(CP_Color_Create(220, 200, 130, 255)); break;
                case tileWater: CP_Settings_Fill(CP_Color_Create(60, 120, 200, 255)); break;
            default: CP_Settings_Fill(CP_Color_Create(60, 160, 70, 255)); break;
            }

        CP_Graphics_DrawRect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE),TILE_SIZE, TILE_SIZE);
        
        }

}