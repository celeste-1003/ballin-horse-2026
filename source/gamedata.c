#include "header/gamedata.h"
#include <stdio.h>

#define SAVE_FILE_NAME "save.dat"
#define TEMP_FILE_NAME "save.tmp"

GameData gGameData = { 1, 0 };

void GameData_Init(void) {
    // Attempt to load existing save data; if missing, initialize defaults
    if (!GameData_Load()) {
        gGameData.highest_stage_unlocked = 1; // Default to Stage 1
        gGameData.high_score = 0;
        GameData_Save();
    }
}

int GameData_Save(void) {
    // 1. Open and write to the temporary file
    FILE* file = fopen(TEMP_FILE_NAME, "wb");
    if (!file) {
        return 0; // Failed to create temp file
    }

    size_t written = fwrite(&gGameData, sizeof(GameData), 1, file);
    fclose(file);

    if (written != 1) {
        remove(TEMP_FILE_NAME); // Clean up incomplete file
        return 0;
    }

    // 2. Safely swap temp file to the actual save file
    remove(SAVE_FILE_NAME); // Necessary on Windows before renaming
    if (rename(TEMP_FILE_NAME, SAVE_FILE_NAME) != 0) {
        return 0;
    }

    return 1; // Success
}

int GameData_Load(void) {
    FILE* file = fopen(SAVE_FILE_NAME, "rb");
    if (!file) {
        return 0; // File does not exist yet
    }

    size_t read_count = fread(&gGameData, sizeof(GameData), 1, file);
    fclose(file);

    if (read_count != 1) {
        return 0; // Corrupted or incomplete file
    }

    // Sanity check: Ensure stage is at least 1
    if (gGameData.highest_stage_unlocked < 1) {
        gGameData.highest_stage_unlocked = 1;
    }

    return 1;
}

int GameData_IsStageUnlocked(int stage_num) {
    // Stage 1 is ALWAYS accessible, even if a save file is missing or broken
    if (stage_num <= 1) {
        return 1;
    }
    return stage_num <= gGameData.highest_stage_unlocked;
}

void GameData_OnStageCleared(int cleared_stage) {
    // If the stage just cleared was the highest reached, unlock the next stage
    if (cleared_stage == gGameData.highest_stage_unlocked) {
        gGameData.highest_stage_unlocked = cleared_stage + 1;
        GameData_Save(); // Save immediately so progress isn't lost
    }
}