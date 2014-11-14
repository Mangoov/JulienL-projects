/*
 * menuDisplay.h
 *
 *  Created on: 2013-11-28
 */
#ifndef MENUDISPLAY_H_
#define MENUDISPLAY_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbasic_types.h>
#include <xtft.h>
#include <xparameters.h>
#include <xio.h>
#include "../NetworkInterface/NetworkInterface.h"
#include "physics.h"
#include "video.h"
#include "typedef.h"
#include "icontrole.h"
#include "../Sons/tar.h"
// adresse absolue choisie pour la page vidéo en RAM DDR2
#define TFT_FB_ADDR (XPAR_MPMC_0_MPMC_HIGHADDR - 0x001fffff)
#define TFT_DEVICE_ID	XPAR_TFT_0_DEVICE_ID
/**
 * Color Values.
 */
#define FGCOLOR_VALUE		0x0000FF00	/**< Foreground Color - Green */
#define BGCOLOR_VALUE		0x0		/**< Background Color - Black */
#define WHITECOLOR_VALUE 	0x00FFFFFF	/**< Color - White */


//XTft TftInstance;
//extern Application app;
void displayMenu(Menu main_menu,Options_cfg opt_cfg,Ctrl_cfg ctrl_cfg, Opt_audio opt_audio, bool jeuEnCours);
void displayMenuHeader();
void displayEndGame( int a);
void displayMenuPrincipal(bool jeuEnCours);
void displayMenuJouer();
void displayMenuOptions();
void displayMenuOptionsJoueurSetNom();
void displayMenuOptionsAudio();
void displayMenuOptionsAudioSetVolume();
void displayMenuOptionsAudioSetBalance();
void displayMenuOptionsControles();
void displayMenuOptionsControlesSetDroite();
void displayMenuOptionsControlesSetGauche();
void displayMenuOptionsControlesSetHaut();
void displayMenuOptionsControlesSetPause();
void displayMenuOptionsControlesSetFrontieres();
void displayMenuOptionsControlesSetQuitterTemp();


#endif /* VIDEO_H_ */
