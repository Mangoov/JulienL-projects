///////////////////////////////////////////////////////////////////////////
/// @file GameUtils.h
/// @date 2013-11
/// @description Fonctions utilitaires pour g�rer les structures de donn�es du jeu
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _GAMEUTILS_H_
#define _GAMEUTILS_H_

/* Includes */
#include <stdlib.h> /* malloc, free */
#include "GameStructures.h"

////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LevelDescription_new
//						Initialise un nouveau tableau.
// PARAMETRES: 			name:				Nom du terrain.
// 						author: 			Nom de l'auteur de ce terrain (anonyme si absent).
// 						landId: 			ID du terrain du tableau.
// 						landerId: 			ID de la capsule du tableau.
// 						landerInitPos: 		Position initiale de la capsule.
// 						landerInitSpeed: 	Vitesse initiale de la capsule.
// 						landerInitFuel: 	Quantit� initiale de carburant de la capsule (kg).
// 						timeLimit: 			Temps limite du tableau (secondes) [1..].
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant un tableau de jeu.
// REMARQUE:            Appel� lors de la s�rialisation � partir d'un objet JSON repr�sentant un tableau.
////////////////////////////////////////////////////////////////////////////////
LevelDescription* LevelDescription_new
(
		char *name,
		char *author,
		char *landId,
		char *landerId,
		LanderPosition landerInitPos,
		LanderSpeed landerInitSpeed,
		float landerInitFuel,
		int timeLimit
);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LevelDescription_free
//						Sert � d�sallouer la m�moire d'un tableu du jeu.
// PARAMETRES: 			levelDescription: Tableau du jeu � d�sallouer
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Le pointeur levelDescription sera � NULL apr�s l'ex�cution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void LevelDescription_free(LevelDescription* levelDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LandDescription_new
//						Initialise un nouveau terrain.
// PARAMETRES: 			name:				Nom du terrain.
// 						author: 			Nom de l'auteur de ce terrain (anonyme si absent).
// 						imgId: 				ID de l'image d'arri�re-plan associ�e au terrain.
// 						gravity: 			Acc�l�ration gravitationnelle appliqu�e (m/s� ou N/kg).
// 						boundaries: 		Tableau de points sp�cifiant, de gauche � droite, la fronti�re du terrain.
// 						platforms: 			Tableau sp�cifiant toutes les plateformes o� doit se poser la capsule pour ce tableau.
// 						arr_boundaries_len: Nombre de fronti�res.
// 						arr_platforms_len: 	Nombres de plateformes.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant un terrain de jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant un terrain.
////////////////////////////////////////////////////////////////////////////////
LandDescription* LandDescription_new
(
		char *name,
		char *author,
		char *imgId,
		float gravity,
		Boundaries **boundaries,
		Platforms **platforms,
		unsigned int arr_boundaries_len,
		unsigned int arr_platforms_len
);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		FieldDescription_free
//						Sert � d�sallouer la m�moire d'un terrain de jeu
// PARAMETRES: 			fieldDescription: Terrain de jeu � d�sallouer
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur fieldDescription sera � NULL apr�s l'ex�cution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void LandDescription_free(LandDescription* landDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CreateBoundries
//						Cr�er un tableau 2D de fronti�res.
// PARAMETRES: 			arr_platforms_len: Taille du tableau de fronti�res.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur un tableau 2D de fronti�res.
// REMARQUE:            Sert � initialiser le tableau 2D de fronti�res d'un terrain.
////////////////////////////////////////////////////////////////////////////////
Boundaries** CreateBoundries(unsigned int arr_boundaries_len);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CreatePlatforms
//						Cr�er un tableau 2D de plateformes.
// PARAMETRES: 			arr_platforms_len: Taille du tableau de plateformes.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur un tableau 2D de plateformes.
// REMARQUE:            Sert � initialiser le tableau 2D de plateformes d'un terrain.
////////////////////////////////////////////////////////////////////////////////
Platforms** CreatePlatforms(unsigned int arr_platforms_len);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		SummaryDescription_new
//						Initialise une structure contenant la description d'une capsule.
// PARAMETRES: 			name: 			Nom de la capsule.
// 						author: 		Nom de l'auteur de cette capsule (anonyme si absent).
// 						netMass: 		Masse de la capsule sans carburant (kg).
// 						dimensions:  	Dimension de la capsule.
// 						exhaustSpeed: 	Vitesse d��jection de l��chappement du carburant (m/s).
// 						fuelExpense:	D�pense de carburant par seconde lorsqu�un jet est activ� (kg/s).
//						breakdownSpeed: Vitesse scalaire pour laquelle une collision avec la fronti�re du terrain est fatale, plateforme ou non (m/s).
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la description d'une capsule.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant une capsule.
////////////////////////////////////////////////////////////////////////////////
LanderDescription* LanderDescription_new
(
		char *name,
		char *author,
		int netMass,
		Dimensions dimensions,
		int exhaustSpeed,
		int fuelExpense,
		float breakdownSpeed
);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CapsuleDescription_free
//						Sert � d�sallouer la m�moire pour la description d'une capsule.
// PARAMETRES: 			capsuleDescription: Donn�es de jeu � d�sallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur capsuleDescription sera � NULL apr�s l'ex�cution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void LanderDescription_free(LanderDescription* landerDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GlobalConfiguration_new
//						Initialise une structure contenant la configuration globale de l'application.
// PARAMETRES: 			landResolution: r�solution de tous les terrains (pixel/m)
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant la configuration globale de l'application.
////////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* GlobalConfiguration_new(float landResolution);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GlobalConfiguration_free
//						Sert � d�sallouer la m�moire pour la configuration globale de l'application.
// PARAMETRES: 			summaryDescription: Donn�es de jeu � d�sallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur globalConfiguration sera � NULL apr�s l'ex�cution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void GlobalConfiguration_free(GlobalConfiguration* globalConfiguration);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		SummaryDescription_new
//						Initialise une structure contenant le sommaire d'un tableau.
// PARAMETRES: 			id: 			Identifiant unique du tableau.
// 						name: 			Nom du tableau.
// 						author: 		Auteur du tableau (anonyme si absent).
// 						landerInitFuel: Quantit� initiale de carburant de la capsule du tableau (kg).
// 						timeLimit: 		Temps limite du tableau (secondes) [1..].
// 						topScore:		Meilleur score du tableau (points).
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant les donn�es de du jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant le sommaire d'un tableau.
////////////////////////////////////////////////////////////////////////////////
SummaryDescription* SummaryDescription_new
(
		char *id,
		char *name,
		char *author,
		float landerInitFuel,
		int timeLimit,
		int topScore
);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		SummaryDescription_free
//						Sert � d�sallouer la m�moire pour le sommaire d'un tableau.
// PARAMETRES: 			summaryDescription: Donn�es de jeu � d�sallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur summaryDescription sera � NULL apr�s l'ex�cution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void SummaryDescription_free(SummaryDescription* summaryDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GameData_new
//						Initialise une structure contenant les donn�es de jeu.
// PARAMETRES: 			playerName; 	Nom du joueur qui a r�ussi le tableau.
// 						totalTime; 		Temps total de jeu (secondes).
// 						fuelLeft; 		Quantit� de carburant restant � la fin de la partie (kg).
// 						nbPlatforms; 	Nombre de plateformes distinctes o� la capsule s'est pos�e avec succ�s.
// 						totalValue; 	Naleur totale de la partie (points).
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant les donn�es de du jeu.
// REMARQUE:            Appel� lors de la s�rialisation de l'objet � partir d'un objet JSON repr�sentant les donn�es de jeu.
////////////////////////////////////////////////////////////////////////////////
GameData* GameData_new(
		char *playerName,
		int totalTime,
		float fuelLeft,
		int nbPlatforms,
		int totalValue
);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GameData_free
//						Sert � d�sallouer la m�moire pour les donn�es de jeu.
// PARAMETRES: 			gameData: Donn�es de jeu � d�sallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:
////////////////////////////////////////////////////////////////////////////////
void GameData_free(GameData* gameData);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LevelsSummary_new
//						Sommaire de tableau
// PARAMETRES: 			gameData: Donn�es de jeu � d�sallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:
////////////////////////////////////////////////////////////////////////////////
LevelsSummary* LevelsSummary_new
(
		char *id,
		char *name,
		char *author,
		float landerInitFuel,
		int timeLimit,
		int score
);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LevelsSummary_free
//						Sert � d�sallouer la m�moire pour le sommaire des tableaux.
// PARAMETRES: 			levelsSummary: Sommaire des tableaux � d�sallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:
////////////////////////////////////////////////////////////////////////////////
void LevelsSummary_free(LevelsSummary* levelsSummary);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CreateLevelSummaryArray
//						Cr�er un tableau de sommaire de tableau
// PARAMETRES: 			unsigned int array_len: Nombre de tableau.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:			Un pointeur vers le tableau de sommaire de tableau.
////////////////////////////////////////////////////////////////////////////////
LevelsSummary** CreateLevelSummaryArray(unsigned int array_len);

#endif /* _GAMEUTILS_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
