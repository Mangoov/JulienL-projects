/*
 * menuDisplay.c
 *
 *  Created on: 2013-11-28
 */


#include "menuDisplay.h"


extern inputBuf input;
extern controle bindCtrl;
extern int vertical_opt;
extern bool change;
extern int vol_opt;
extern int bal_opt;
extern bool menuChange;
extern bool errorCheckControles;
static inputBuf controleBuf;
extern  Bitmap **ppLandBMP, **ppLanderBMP, **ppPreviewBMP;
extern bool started;
extern int mapID;
extern double dServeurScore;


void displayMenu(Menu main_menu,Options_cfg opt_cfg,Ctrl_cfg ctrl_cfg, Opt_audio opt_audio, bool jeuEnCours)
{
	change = false;

	if (menuChange)
		XTft_ClearZone(82,40, 558, 448, BGCOLOR_VALUE);
	menuChange = false;

	if(errorCheckControles){
		XTft_WriteTextExt("Erreur: Verifiez l'unicite des controles ...",200, 360, 0x00FF0000, BGCOLOR_VALUE);
		errorCheckControles = false;
	}

	if (main_menu == NOTHING )
		displayMenuPrincipal(started);
	else if (main_menu == play)
		displayMenuJouer();

	else if (main_menu == options && opt_cfg == NOTHING)
		displayMenuOptions();

	else if (main_menu == options && opt_cfg == player_id)
		displayMenuOptionsJoueurSetNom();

	else if (main_menu == options && opt_cfg == audio && opt_audio == NOTHING )
		 displayMenuOptionsAudio();
	else if (main_menu == options && opt_cfg == audio && opt_audio == volume )
		displayMenuOptionsAudioSetVolume();
	else if (main_menu == options && opt_cfg == audio && opt_audio == balance )
		displayMenuOptionsAudioSetBalance();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == NOTHING )
		displayMenuOptionsControles();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == right )
		displayMenuOptionsControlesSetDroite();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == left )
		displayMenuOptionsControlesSetGauche();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == up )
		displayMenuOptionsControlesSetHaut();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == ctrl_pause )
		displayMenuOptionsControlesSetPause();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == ctrl_bright )
		displayMenuOptionsControlesSetFrontieres();
	else if (main_menu == options && opt_cfg == ctrl && ctrl_cfg == esc )
		displayMenuOptionsControlesSetQuitterTemp();

	else if (main_menu == options && opt_cfg == ctrl)
		displayMenuOptionsJoueurSetNom();

}
void displayMenuHeader()
{
	XTft_WriteTextExt("Lunar Lander",265, 40, 0x00FF0000, BGCOLOR_VALUE);
	XTft_WriteTextExt("Livrable 2 - Equipe 3",230, 55, 0x0066B2FF, BGCOLOR_VALUE);
	XTft_DrawLines(100,80,540,80,0x000000CD);
}

void displayMenuPrincipal(bool jeuEnCours)
{
	XTft_DrawLines(100,35,540,35,0x000000CD);
	XTft_DrawLines(100,450,540,450,0x000000CD);

	XTft_DrawLines(80,57,80,430,0x000000CD);
	XTft_DrawLines(560,57,560,430,0x000000CD);
	displayMenuHeader();

	XTft_WriteTextExt("Menu Principal",100, 90, 0x00808080, BGCOLOR_VALUE);
	if (jeuEnCours)
	{
		if (vertical_opt==1)
			XTft_WriteTextExt("Jouer",100, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
		else
			XTft_WriteTextExt("Jouer",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
		if (vertical_opt==2)
			XTft_WriteTextExt("(Reprendre la partie)",100, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
		else
			XTft_WriteTextExt("(Reprendre la partie)",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
		if (vertical_opt==3)
			XTft_WriteTextExt("Options",100, 260, FGCOLOR_VALUE, BGCOLOR_VALUE);
		else
			XTft_WriteTextExt("Options",100, 260, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	}
	else
	{
		if (vertical_opt==1)
			XTft_WriteTextExt("Jouer",100, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
		else
			XTft_WriteTextExt("Jouer",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);

		if (vertical_opt==2)
			XTft_WriteTextExt("Options",100, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
		else
			XTft_WriteTextExt("Options",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	}
}

void displayMenuJouer()
{
	char cfuel[25],ctimeLimit[25], cscore[25], cnum[25];
	displayMenuHeader();
	XTft_WriteTextExt("Menu Principal -> Jouer",100, 90, 0x00808080, BGCOLOR_VALUE);
	XTft_Preview(ppPreviewBMP[vertical_opt-1]->Image,ppPreviewBMP[vertical_opt-1]->Width,ppPreviewBMP[vertical_opt-1]->Height,100,180);

	sprintf(cfuel, "%d",(int)summary.arrLevelsSummary[vertical_opt-1]->landerInitFuel);
	sprintf(ctimeLimit, "%d",summary.arrLevelsSummary[vertical_opt-1]->timeLimit);
	sprintf(cscore,"%d",dServeurScore);

	XTft_WriteTextExt("Titre : ",270, 180, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt("Auteur : ",270, 192, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt("Carburant : ",270, 204, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt("Temps : ",270, 216, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt("Score : ",270, 228, 0x00FFFFFF, BGCOLOR_VALUE);

	XTft_ClearZone(400,180,540,250,0x0);
	XTft_WriteTextExt(summary.arrLevelsSummary[vertical_opt-1]->name,400, 180, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt(summary.arrLevelsSummary[vertical_opt-1]->author,400, 192, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt(cfuel,400, 204, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt(ctimeLimit,400, 216, 0x00FFFFFF, BGCOLOR_VALUE);
	XTft_WriteTextExt(cscore,400, 228, 0x00FFFFFF, BGCOLOR_VALUE);

	sprintf(cnum,"Terrain %d sur %d",vertical_opt, summary.levelSummaryArrayLen);
	XTft_WriteTextExt(cnum,230, 410, 0x00FFFFFF, BGCOLOR_VALUE);
}

void displayMenuOptions()
{

	displayMenuHeader();
	XTft_WriteTextExt("Menu Principal -> Options ",100, 90, 0x00808080, BGCOLOR_VALUE);
	if (vertical_opt==1)
		XTft_WriteTextExt("Joueur",100, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Joueur",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);

	if (vertical_opt==2)
		XTft_WriteTextExt("Audio",100, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Audio",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);

	if (vertical_opt==3)
		XTft_WriteTextExt("Controles",100, 260, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Controles",100, 260, WHITECOLOR_VALUE, BGCOLOR_VALUE);
}



void displayMenuOptionsJoueurSetNom()
{
	displayMenuHeader();
	XTft_WriteTextExt("Menu Principal -> Options -> Joueur ",100, 90, 0x00808080, BGCOLOR_VALUE);
	XTft_WriteTextExt("Modifier votre nom : ",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	XTft_SetColor(&TftInstance,FGCOLOR_VALUE, BGCOLOR_VALUE );
	XTft_SetPos(&TftInstance,100,250);
	int i;
	XTft_ClearZone(100, 250, 250, 260, BGCOLOR_VALUE);
	for (i =0;i<input.bufSize;++i)
		XTft_Write(&TftInstance,input.buf[i] );
}

void displayMenuOptionsAudio()
{

	displayMenuHeader();
	char buf[50];
	XTft_WriteTextExt("Menu Principal -> Options  -> Audio",100, 90, 0x00808080, BGCOLOR_VALUE);
	if (vertical_opt==1)
		XTft_WriteTextExt("Ajuster volume  : ",100, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Ajuster volume  : ",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	switch (vol_opt)
	{
		case 0: XTft_WriteTextExt("Muet",245, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 1: XTft_WriteTextExt(" Min",245, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 2: XTft_WriteTextExt(" Med",245, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 3: XTft_WriteTextExt(" Max",245, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
	}

	if (vertical_opt==2)
		XTft_WriteTextExt("Ajuster balance : ",100, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Ajuster balance : ",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);

	switch (bal_opt)
	{
		case 0: XTft_WriteTextExt("Gauche",245, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 1: XTft_WriteTextExt("Centre",245, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 2: XTft_WriteTextExt("Droite",245, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
			break;
	}

}

void displayMenuOptionsAudioSetVolume()
{
	XTft_WriteTextExt("Ajuster volume  : ",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	switch (vol_opt)
	{
		case 0: XTft_WriteTextExt("Muet",245, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 1: XTft_WriteTextExt(" Min",245, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 2: XTft_WriteTextExt(" Med",245, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
			break;
		case 3: XTft_WriteTextExt(" Max",245, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
			break;
	}
}

void displayMenuOptionsAudioSetBalance()
{
	XTft_WriteTextExt("Ajuster balance : ",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	switch (bal_opt)
		{
			case 0: XTft_WriteTextExt("Gauche",245, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
				break;
			case 1: XTft_WriteTextExt("Centre",245, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
				break;
			case 2: XTft_WriteTextExt("Droite",245, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
				break;
		}
}

inputBuf checkChar(unsigned int x){
	inputBuf controleBuf2;

	switch (x){
	case 1:
		sprintf(controleBuf2.buf, "Haut");
		controleBuf2.bufSize = 4;
		break;
	case 2:
		sprintf(controleBuf2.buf, "Droit");
		controleBuf2.bufSize = 5;
		break;
	case 3:
		sprintf(controleBuf2.buf, "Bas");
		controleBuf2.bufSize = 3;
		break;
	case 4:
		sprintf(controleBuf2.buf, "Gauche");
		controleBuf2.bufSize = 6;
		break;
	case 9:
		sprintf(controleBuf2.buf, "Tab");
		controleBuf2.bufSize = 3;
		break;
	case 27:
		sprintf(controleBuf2.buf, "Esc");
		controleBuf2.bufSize = 3;
		break;
	case 32:
		sprintf(controleBuf2.buf, "Espace");
		controleBuf2.bufSize = 6;
		break;
	case 8:
		sprintf(controleBuf2.buf, "BackSpace");
		controleBuf2.bufSize = 9;
		break;
	case 10:
		break;
	default:
		sprintf(controleBuf2.buf, "%c",x);
		controleBuf2.bufSize = 1;
		break;
	}
	return controleBuf2;
}

void displayMenuOptionsControles()
{
	displayMenuHeader();
	XTft_WriteTextExt("Menu Principal -> Options -> Controles ",100, 90, 0x00808080, BGCOLOR_VALUE);

	if (vertical_opt==1)
		XTft_WriteTextExt("Aller vers le droite :",100, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Aller vers le droite :",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.right & RELEASE_MASK));
	XTft_ClearZone(470, 220, 525, 235, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);


	if (vertical_opt==2)
		XTft_WriteTextExt("Aller vers le gauche :",100, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Aller vers le gauche :",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.left & RELEASE_MASK));
	XTft_ClearZone(470, 240, 525, 255, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);


	if (vertical_opt==3)
		XTft_WriteTextExt("Aller vers le haut :",100, 260, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Aller vers le haut :",100, 260, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.up & RELEASE_MASK));
	XTft_ClearZone(470, 260, 525, 275, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 260, WHITECOLOR_VALUE, BGCOLOR_VALUE);


	if (vertical_opt==4)
		XTft_WriteTextExt("Pause :",100, 280, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Pause :",100, 280, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.pause & RELEASE_MASK));
	XTft_ClearZone(470, 280, 525, 295, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 280, WHITECOLOR_VALUE, BGCOLOR_VALUE);


	if (vertical_opt==5)
		XTft_WriteTextExt("Afficher frontiere et plateformes :",100, 300, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Afficher frontiere et plateformes :",100, 300, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.bright & RELEASE_MASK));
	XTft_ClearZone(470, 300, 525, 315, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 300, WHITECOLOR_VALUE, BGCOLOR_VALUE);


	if (vertical_opt==6)
		XTft_WriteTextExt("Quitter temporairement la partie :",100, 320, FGCOLOR_VALUE, BGCOLOR_VALUE);
	else
		XTft_WriteTextExt("Quitter temporairement la partie :",100, 320, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.tmpExit & RELEASE_MASK));
	XTft_ClearZone(470, 320, 525, 335, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 320, WHITECOLOR_VALUE, BGCOLOR_VALUE);
}

void displayMenuOptionsControlesSetDroite()
{
	XTft_WriteTextExt("Aller vers le droite :",100, 220, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.right & RELEASE_MASK));
	XTft_ClearZone(470, 220, 525, 235, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 220, FGCOLOR_VALUE, BGCOLOR_VALUE);
}
void displayMenuOptionsControlesSetGauche()
{
	XTft_WriteTextExt("Aller vers le gauche :",100, 240, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.left & RELEASE_MASK));
	XTft_ClearZone(470, 240, 525, 255, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 240, FGCOLOR_VALUE, BGCOLOR_VALUE);
}
void displayMenuOptionsControlesSetHaut()
{
	XTft_WriteTextExt("Aller vers le haut :",100, 260, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.up & RELEASE_MASK));
	XTft_ClearZone(470, 260, 525, 270, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 260, FGCOLOR_VALUE, BGCOLOR_VALUE);
}
void displayMenuOptionsControlesSetPause()
{
	XTft_WriteTextExt("Pause :",100, 280, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.pause & RELEASE_MASK));
	XTft_ClearZone(470, 280, 525, 295, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 280, FGCOLOR_VALUE, BGCOLOR_VALUE);
}
void displayMenuOptionsControlesSetFrontieres()
{
	XTft_WriteTextExt("Afficher frontiere et plateformes :",100, 300, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.bright & RELEASE_MASK));
	XTft_ClearZone(470, 300, 525, 315, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 300, FGCOLOR_VALUE, BGCOLOR_VALUE);
}
void displayMenuOptionsControlesSetQuitterTemp()
{
	XTft_WriteTextExt("Quitter temporairement la partie :",100, 320, WHITECOLOR_VALUE, BGCOLOR_VALUE);
	controleBuf = checkChar((bindCtrl.tmpExit & RELEASE_MASK));
	XTft_ClearZone(470, 320, 525, 335, BGCOLOR_VALUE);
	XTft_WriteTextExt2(controleBuf,470, 320, FGCOLOR_VALUE, BGCOLOR_VALUE);
}

void displayEndGame( int a)
{
	XTft_ClearZone(82,40, 558, 448, BGCOLOR_VALUE);
	XTft_DrawLines(100,35,540,35,0x000000CD);
	XTft_DrawLines(100,450,540,450,0x000000CD);
	XTft_DrawLines(80,57,80,430,0x000000CD);
	XTft_DrawLines(560,57,560,430,0x000000CD);
	displayMenuHeader();
	XTft_WriteTextExt("Fin de la partie... ",100, 90, 0x00808080, BGCOLOR_VALUE);
	switch(a)
	{
		case 1:
			XTft_WriteTextExt("Partie reussie",200, 115, 0x0000FF00, BGCOLOR_VALUE);
			InitCurrentSound(WIN);
			break;
		case -1 :
			XTft_WriteTextExt("!!! :( CRASH :( !!!!",200, 115, 0x00FF0000, BGCOLOR_VALUE);
			InitCurrentSound(CRASH);
			break;
		case -2:
			XTft_WriteTextExt("!!! :( CRASH LANDING :( !!!!",200, 115, 0x00FF0000, BGCOLOR_VALUE);
			InitCurrentSound(CRASH);
			break;
		case 5:
			XTft_WriteTextExt("~~~~~ BORDURE ~~~~~",200, 115, 0x00808080, BGCOLOR_VALUE);
			InitCurrentSound(FAIL);
			break;
	}
	XTft_WriteTextExt("Appuyez sur Entree pour continuer...",100, 410, 0x00808080, BGCOLOR_VALUE);
}
