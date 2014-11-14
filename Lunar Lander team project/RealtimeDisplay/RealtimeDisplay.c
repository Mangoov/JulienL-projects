/*
 * RealtimeDisplay.c
 *
 *  Created on: 2013-11-25
 */

#include "RealtimeDisplay.h"

extern int totalTime;
GamePhysics phys;

void displayRealTimeData()
{
	displayVH();
	displayVV();
	displayCarb();
	displayAlt();
	displayScore();
	displayTime();
}

void displayVH() {
	char tab[30];
	sprintf(tab, "[Vitesse horizontale] %.1f", phys.horizontalSpeed);
	XTft_WriteTextExt(tab,0,20,WHITECOLOR_VALUE,BGCOLOR_VALUE);
}

void displayVV() {
	char tab[30];
	sprintf(tab, "[Vitesse verticale] %.1f", phys.verticalSpeed);
	XTft_WriteTextExt(tab,0,32,WHITECOLOR_VALUE,BGCOLOR_VALUE);
}

void displayCarb() {
	char tab[30];
	sprintf(tab, "[Carburant] %.1f", phys.currentFuel);
	XTft_WriteTextExt(tab,0,44,WHITECOLOR_VALUE,BGCOLOR_VALUE);
}

void displayAlt() {
	char tab[30];
	sprintf(tab, "[Altitude] %.1f", phys.altitude);
	XTft_WriteTextExt(tab,0,56,WHITECOLOR_VALUE,BGCOLOR_VALUE);

}

void displayScore() {
	char tab[30];
	sprintf(tab, "[Points] %.1f", phys.score);
	XTft_WriteTextExt(tab,470,20,WHITECOLOR_VALUE,BGCOLOR_VALUE);
}


void displayTime() {
	char tab[30];
	sprintf(tab, "[Temps restant] %.1f", (float)totalTime);
	XTft_WriteTextExt(tab,470,32,WHITECOLOR_VALUE,BGCOLOR_VALUE);
}


