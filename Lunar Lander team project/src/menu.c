/*
 * menu.c
 *
 *  Created on: 2013-11-23
 */

#include "menu.h"

Menu main_menu  = NOTHING;
Options_cfg opt_cfg = NOTHING;
Opt_audio opt_audio = NOTHING;

extern int getId;
extern controle scontrole;
extern controle pushedCtrl;
extern Application app;
extern inputBuf input;
extern XTft TftInstance;
extern Etat etat;
extern char prompt[64];

bool ValidMapId(unsigned char *id)
{
	size_t i = 0;
	for(i = 0; i < summary.levelSummaryArrayLen; ++i)
		if(strcmp((char*)id, summary.arrLevelsSummary[i]->id) == 0)
			return true;
	return false;
}

void checkMenu(){
	switch (main_menu){
	/*case retry:
		main_menu = etat_start;
		snprintf(prompt, 64, "Level not valid renter level ID then press enter: ");
		stdout_write_char_array(prompt, strlen(prompt));
		break;
	case etat_start:
		if(scontrole.start){
			snprintf(prompt, 64, "%s\n", input.buf);
			stdout_write_char_array(prompt, strlen(prompt));
			printBuf(input.buf, input.bufSize);
			pushedCtrl.start = RELEASED;
			scontrole.start = RELEASED;

			if(ValidMapId(input.buf))
			{
				TftWriteString("Downloading ...\n");
				DownloadApplicationData(input.buf);
				TftWriteString("Download OK\n");
				XTft_ClearScreen(&TftInstance);

				XTft_Background(LandBMP.Image, LandBMP.Width, LandBMP.Height);
				XTft_ShowCapsule(LanderBMP.Image, LanderBMP.Width, LanderBMP.Height);
				main_menu = play;
				input.bufSize = 0;
			}
			else{
				main_menu = retry;
				input.bufSize = 0;
			}
		}
		break;*/
	case play:

		// add function for displaying play menu

		//InitPhysics();
		//etat = computing;
		break;
	case continu_playing:

		// add function for displaying continu_playing

		break;
	case options:

		//add function for displaying option menu

		switch (opt_cfg){
		case player_id:
			break;
		case audio:
			switch (opt_audio){
			case volume:
				break;
			case balance:
				break;
			default:
				break;
			}

			break;
		case ctrl:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
