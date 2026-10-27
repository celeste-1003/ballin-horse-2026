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
            case 'H': lvl->hole.position = CP_Vector_Set((col + 0.5f) * TILE_SIZE, (row + 0.5f) * TILE_SIZE);
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

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_NoStroke();

    for (int row = 0; row < GRID_ROW; row++) {
        for (int col = 0; col < GRID_COL; col++) {
            int isDark = ((row + col) % 2 == 0);

            switch (lvl->tiles[row][col]) {
            case tileWall:
                CP_Settings_Fill(CP_Color_Create(110, 110, 115, 255));
                break;
            case tileSand:
                if ((row + col) % 2 == 0) CP_Settings_Fill(CP_Color_Create(220, 200, 130, 255));
                else                      CP_Settings_Fill(CP_Color_Create(232, 213, 145, 255));
                break;
            case tileWater:
                if ((row + col) % 2 == 0) CP_Settings_Fill(CP_Color_Create(60, 120, 200, 255));
                else                      CP_Settings_Fill(CP_Color_Create(75, 135, 215, 255));
                break;
            default:
                if ((row + col) % 2 == 0) CP_Settings_Fill(CP_Color_Create(60, 160, 70, 255));
                else                      CP_Settings_Fill(CP_Color_Create(72, 175, 82, 255));
                break;
            }

            CP_Graphics_DrawRect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE),
                TILE_SIZE, TILE_SIZE);
        }
    }

    /* Hole on top of the tiles (DrawCircle takes a diameter) */
    CP_Settings_Fill(CP_Color_Create(20, 20, 20, 255));
    CP_Graphics_DrawCircle(lvl->hole.position.x, lvl->hole.position.y, (float)HOLE_DIAMETER);
}