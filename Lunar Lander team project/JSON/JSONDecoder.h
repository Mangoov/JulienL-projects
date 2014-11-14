///////////////////////////////////////////////////////////////////////////
/// @file JSONDecoder.h
/// @date 2013-11
/// @description S�rialisation des structures de donn�es du jeu � partir du serveur Web.
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
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant le tableau du jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant un tableau.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LevelsSummary** GetLevelsSummary(char *text, size_t *arrLen);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetLevelDescription
//						Initialise une structure contenant la description d'tableau de jeu.
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant le tableau du jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant un tableau.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LevelDescription* GetLevelDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetLandDescription
//						Initialise une structure contenant la description d'un terrain.
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit un terrain.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant le terrain du jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant un terrain.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LandDescription* GetLandDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetCapsuleDescription
//						Initialise une structure contenant la description d'une capsule.
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit  d'une capsule.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant le terrain du jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant une capsule.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
LanderDescription* GetLanderDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetGlobalConfiguration
//						Initialise une structure contenant la configuration globale l�application.
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit la configuration globale l�application.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale l�application.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant la configuration globale l�application.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* GetGlobalConfiguration(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetSummaryDescription
//						Initialise une structure contenant le sommaire d'un tableau.
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit le sommaire d'un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant le sommaire d'un tableau.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant le sommaire d'un tableau.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
SummaryDescription* GetSummaryDescription(char *text);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		PackGameData
//						Initialise une structure JSON contenant la cha�ne de caract�re � envoyer au serveur.
// PARAMETRES: 			GameData *gameData: cette structure contient les donn�es � envoyer au serveur dans le cas d'une partie r�ussie.
// VALEUR DE RETOUR:    Une cha�ne de caract�re repr�sentant l'objet JSON.
// REMARQUE:            Aucune
////////////////////////////////////////////////////////////////////////////////
const char* PackGameData(GameData *gameData);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GetScore
//						D�code l'objet JSON qui contient le score enoy� par le serveur.
// PARAMETRES: 			text: Corps de la requ�te HTTP qui contient l'objet JSON qui d�crit le sommaire d'un tableau.
// VALEUR DE RETOUR:    Une cha�ne de caract�re repr�sentant l'objet JSON.
// REMARQUE:            � la suite de l'envoye des donn�es de fin de partie.
//						Le buffer text sera d�sallou� � la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
double GetScore(char *text);


#endif /* _JSONDECODER_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
