#include <math.h>
#include "cprocessing.h"
#include "header/constants.h"
#include "header/level.h"
#include "header/assets.h"
#include "header/draw.h"



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
			case 'x': type = tileSpike; break;
			case 'S': type = tileStickyWall; break;
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
				draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, BG_Grey);
                break;
            case tileSand:
                if ((row + col) % 2 == 0) draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, Light_Sand);
                else                      draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, Dark_Sand);
                break;
            case tileWater:
                if ((row + col) % 2 == 0) draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, Water);
                else                      draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, Dark_Water);
                break;
            case tileSpike:
                draw_spikes((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, CP_Color_Create(100, 100, 100, 255));
                break;
            case tileStickyWall:
                draw_stickywall((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, CP_Color_Create(150, 150, 150, 255));
                break;
            default:
                if ((row + col) % 2 == 0) draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, Grass);
                else                      draw_rect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE, Dark_Grass);
                break;
            }

           // CP_Graphics_DrawRect((float)(col * TILE_SIZE), (float)(row * TILE_SIZE),
               // TILE_SIZE, TILE_SIZE);
        }
    }

    /* Hole on top of the tiles (DrawCircle takes a diameter) */
    CP_Settings_Fill(CP_Color_Create(20, 20, 20, 255));
    CP_Graphics_DrawCircle(lvl->hole.position.x, lvl->hole.position.y, (float)HOLE_DIAMETER);
}