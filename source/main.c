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
#include "cprocessing.h"
#include "header/game.h"
#include "header/utils.h"
#include "header/constants.h"
#include "header/splash.h"


// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void){
	CP_System_SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	CP_Engine_SetNextGameState(splash_init, splash_update, splash_exit);
	CP_Engine_Run(0);
	return 0;
}
