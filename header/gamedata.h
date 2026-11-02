#ifndef GAMEDATA_H
#define GAMEDATA_H

typedef struct {
    int highest_stage_unlocked; // e.g., 1 by default
    int high_score;
} GameData;

// Global game data instance
extern GameData gGameData;

// Function prototypes
void GameData_Init(void);
int  GameData_Load(void);
int  GameData_Save(void);
int  GameData_IsStageUnlocked(int stage_num);
void GameData_OnStageCleared(int cleared_stage);

#endif // GAMEDATA_H