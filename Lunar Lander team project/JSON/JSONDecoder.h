///////////////////////////////////////////////////////////////////////////
/// @file JSONDecoder.h
/// @date 2013-11
/// @description Sérialisation des structures de données du jeu à partir du serveur Web.
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _JSONDECODER_H_
#define _JSONDECODER_H_

/* Includes */
#include <stdio.h> /* size_t*/
#include <string.h> /* strlen */
#include "../GameData/GameUtils.h"
#include "../jansson/jansson.h"


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LevelsSummary
//						Initialise une structure contenant la description d'tableau de jeu.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant le tableau du jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant un tableau.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LevelsSummary** GetLevelsSummary(char *text, size_t *arrLen);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetLevelDescription
//						Initialise une structure contenant la description d'tableau de jeu.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant le tableau du jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant un tableau.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LevelDescription* GetLevelDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetLandDescription
//						Initialise une structure contenant la description d'un terrain.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit un terrain.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant le terrain du jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant un terrain.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LandDescription* GetLandDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetCapsuleDescription
//						Initialise une structure contenant la description d'une capsule.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit  d'une capsule.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant le terrain du jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant une capsule.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LanderDescription* GetLanderDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetGlobalConfiguration
//						Initialise une structure contenant la configuration globale l’application.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit la configuration globale l’application.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale l’application.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant la configuration globale l’application.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* GetGlobalConfiguration(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetSummaryDescription
//						Initialise une structure contenant le sommaire d'un tableau.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit le sommaire d'un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant le sommaire d'un tableau.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant le sommaire d'un tableau.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
SummaryDescription* GetSummaryDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		PackGameData
//						Initialise une structure JSON contenant la chaîne de caractère à envoyer au serveur.
// PARAMETRES: 			GameData *gameData: cette structure contient les données à envoyer au serveur dans le cas d'une partie réussie.
// VALEUR DE RETOUR:    Une chaîne de caractère représentant l'objet JSON.
// REMARQUE:            Aucune
////////////////////////////////////////////////////////////////////////////////
const char* PackGameData(GameData *gameData);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetScore
//						DÉcode l'objet JSON qui contient le score enoyé par le serveur.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit le sommaire d'un tableau.
// VALEUR DE RETOUR:    Une chaîne de caractère représentant l'objet JSON.
// REMARQUE:            À la suite de l'envoye des données de fin de partie.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
double GetScore(char *text);


#endif /* _JSONDECODER_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
