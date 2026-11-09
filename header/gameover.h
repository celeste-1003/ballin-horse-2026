#pragma once

#ifndef GAMEOVER_H
#define GAMEOVER_H

// Loads the images used by the win and lose screens
void gameover_init(void);

// Stores the par and strokes used to calculate the win rank
void gameover_set_results(int par, int strokes);
// Selects the lose screen.
// 0 = Water, 1 = Spikes
void gameover_set_lose(int type);

// Draws the result overlays without clearing the game world
void draw_win_screen(void);
void draw_lose_screen(void);

int get_gameover_rank(void);
void play_rank_sound(int rank);

#endif