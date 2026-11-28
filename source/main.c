//---------------------------------------------------------
// file:	main.c
// author:	[Biagtas Andrew Kim Capao]
// email:	[biagtas.a]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// Copyright © 2026 DigiPen, All rights reserved.
//---------------------------------------------------------

// libraries
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "cprocessing.h"
#include "header/game.h"
#include "header/utils.h"
#include "header/constants.h"
#include "header/splash.h"
#include "header/gamedata.h"

int main(void){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameData_Init();
	CP_System_SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	CP_Engine_SetNextGameState(splash_init, splash_update, splash_exit);

#ifdef _DEBUG
	CP_Engine_Run(1);
#else
	CP_Engine_Run(0);
#endif
	return 0;
}
