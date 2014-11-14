/*
 * Copyright (c) 2009-2010 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/***************************** Include Files *********************************/

#include <stdio.h>
#include "xparameters.h"
#include "../Configuration/platform.h"
#include "../Configuration/platform_config.h"
#include "icontrole.h"
#include "typedef.h"
#include "physics.h"
#include "video.h"
#include "menu.h"
#include "lwip/init.h"
#include "../NetworkInterface/NetworkInterface.h"
#include "../Sons/tar.h"


/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
 extern XTft TftInstance;
 controle scontrole;				// controle instance
 Etat etat = init;
 Etat tmpEtat;
 extern Menu main_menu;
 extern int getId;
 ac97_core CfgAC97;
 inputBuf input;
 TARArchive archive;
 Application **ppApp;
 Application app;
 Summary summary;
 Bitmap **ppLandBMP, **ppLanderBMP, **ppPreviewBMP;
 Bitmap LandBMP, LanderBMP, PreviewBMP;
 GlobalConfiguration *globalConfiguration;
 extern GamePhysics phys;
 extern controle pushedCtrl;
 extern bool started;
 extern bool menuChange;
 bool bright = false;
 char prompt[64];
 extern int mapID;;
 int totalTime = 0;
 double dServeurScore = 0;
 int victory;
 char playername[64];
 bool land = false;


int main()
{
	/* initialise la platforme */
	init_platform();

	lwip_init();

	/* now enable interrupts */
	platform_enable_interrupts();

	InitNetworkInterface();

	/* Download application data */
	PrintPossibleMap();
	ppApp = AllocApplication(summary.levelSummaryArrayLen);
	ppLandBMP = AllocBimapStrucutures(summary.levelSummaryArrayLen);
	ppLanderBMP = AllocBimapStrucutures(summary.levelSummaryArrayLen);
	ppPreviewBMP = AllocBimapStrucutures(summary.levelSummaryArrayLen);
	DownloadApplicationData();

	/* Setup sound */
	LoadSound();
	ProcessSound();

	while(1){

		if((pushedCtrl.tmpExit) && started && (etat != menu)){
			tmpEtat = etat;
			etat = menu;
			main_menu = NOTHING;
			pushedCtrl.tmpExit = RELEASED;
			menuChange = true;
		}else if((pushedCtrl.tmpExit) && started && (etat == menu)){
			etat = drawBackground;
			main_menu = NOTHING;
			pushedCtrl.tmpExit = RELEASED;
		}else if(pushedCtrl.pause && (etat != etat_pause) && (etat != menu) && (etat != NOTHING)){
			pushedCtrl.pause = RELEASED;
			tmpEtat = etat;
			etat = etat_pause;
		}else if(pushedCtrl.pause && etat == NOTHING){
			pushedCtrl.pause = RELEASED;
			etat = tmpEtat;
			int row,col;


			for(col = 0 ; col < 80; ++col)
			{
				for (row = 0; row<15; ++row)
				{
					XTft_SetPixel(&TftInstance, col,  row,LandBMP.Image[col][row]);
				}
			}
		}
		if(pushedCtrl.bright){
			pushedCtrl.bright = RELEASED;
			if (bright){
				XTft_HideBoundaries();
				bright = false;
			}else{
				XTft_DrawBoundaries();
				bright = true;
			}
		}

		switch (etat){
		case init:
			 XTft_Init(TFT_DEVICE_ID);
			controle_Init();
			etat = menu;

			//PrintPossibleMap();
			//snprintf(prompt, 64, "\nEnter level ID then press enter: ");
			//stdout_write_char_array(prompt, strlen(prompt));
			break;
		case computing:
			started = true;
			applyPhysics(&scontrole);
			etat = checkVic;
			break;
		case menu:
			checkMenu();
		case waiting:
			break;
		case checkVic:
			victory = checkVictory();
			switch(victory)
			{
			case 1:
				/*XTft_SetColor(&TftInstance,0x0000FF00,0x0);
				XTft_SetPos(&TftInstance,220,40);
				TftWriteString("!!!!** WINNER **!!!!!\n");*/
				if(phys.currentFuel <= 0 || totalTime == 0)
				{
					snprintf(playername, 64, "%s", input.buf);
					gameData.playerName = playername;
					gameData.fuelLeft = phys.currentFuel;
					gameData.nbPlatforms = phys.nbplatforms;
					gameData.totalTime = summary.arrLevelsSummary[mapID]->timeLimit - totalTime;
					gameData.totalValue = phys.score;
					dServeurScore = SendGameData(summary.arrLevelsSummary[mapID]->id);
					started = false;
					etat = end;
				}
				else{
					etat = waiting;
					land = true;
				}

				break;
			case 0:
				etat = waiting;
				break;
			case -1:
				/*XTft_SetPos(&TftInstance,220,40);
				XTft_SetColor(&TftInstance,0x00FF0000,0x0);

				TftWriteString("!!! :( CRASH :( !!!!\n");*/
				started = false;
				etat = end;
				break;
			case -2:
				/*XTft_SetPos(&TftInstance,180,40);
				XTft_SetColor(&TftInstance,0x00FF0000,0x0);
				TftWriteString("!!! :( CRASH LANDING :( !!!!\n");*/
				started = false;
				etat = end;
				break;
			case 5:
				/*XTft_SetPos(&TftInstance,240,40);
				XTft_SetColor(&TftInstance,0x00FFFF00,0x0);
				TftWriteString("~~~~~ BORDURE ~~~~~\n");*/
				started = false;
				etat = end;
				break;
			default:
				break;
			}
			break;
		case end:
			started = false;
			break;
		case etat_pause:
			XTft_SetPos(&TftInstance,0,0);
			TftWriteString("PAUSE ...\n");
			etat = NOTHING;
			break;
		case downloading:
			memcpy(&app, ppApp[mapID], sizeof(Application));
			memcpy(&LandBMP, ppLandBMP[mapID], sizeof(Bitmap));
			memcpy(&LanderBMP, ppLanderBMP[mapID], sizeof(Bitmap));
			initPushButton();
			InitPhysics();
			totalTime = summary.arrLevelsSummary[mapID]->timeLimit;
			etat = drawBackground;
		case drawBackground:
			XTft_Background(LandBMP.Image,LandBMP.Width,LandBMP.Height);
			etat = computing;
			break;
		default:
			break;

		}

	}
  
	cleanup_platform();

	return 0;
}
