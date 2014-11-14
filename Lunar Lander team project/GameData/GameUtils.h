///////////////////////////////////////////////////////////////////////////
/// @file GameUtils.h
/// @date 2013-11
/// @description Fonctions utilitaires pour gérer les structures de données du jeu
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
// 						landerInitFuel: 	Quantité initiale de carburant de la capsule (kg).
// 						timeLimit: 			Temps limite du tableau (secondes) [1..].
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant un tableau de jeu.
// REMARQUE:            Appelé lors de la sérialisation à partir d'un objet JSON représentant un tableau.
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
//						Sert à désallouer la mémoire d'un tableu du jeu.
// PARAMETRES: 			levelDescription: Tableau du jeu à désallouer
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Le pointeur levelDescription sera à NULL après l'exécution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void LevelDescription_free(LevelDescription* levelDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LandDescription_new
//						Initialise un nouveau terrain.
// PARAMETRES: 			name:				Nom du terrain.
// 						author: 			Nom de l'auteur de ce terrain (anonyme si absent).
// 						imgId: 				ID de l'image d'arrière-plan associée au terrain.
// 						gravity: 			Accélération gravitationnelle appliquée (m/s² ou N/kg).
// 						boundaries: 		Tableau de points spécifiant, de gauche à droite, la frontière du terrain.
// 						platforms: 			Tableau spécifiant toutes les plateformes où doit se poser la capsule pour ce tableau.
// 						arr_boundaries_len: Nombre de frontières.
// 						arr_platforms_len: 	Nombres de plateformes.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant un terrain de jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant un terrain.
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
//						Sert à désallouer la mémoire d'un terrain de jeu
// PARAMETRES: 			fieldDescription: Terrain de jeu à désallouer
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur fieldDescription sera à NULL après l'exécution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void LandDescription_free(LandDescription* landDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CreateBoundries
//						Créer un tableau 2D de frontières.
// PARAMETRES: 			arr_platforms_len: Taille du tableau de frontières.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur un tableau 2D de frontières.
// REMARQUE:            Sert à initialiser le tableau 2D de frontières d'un terrain.
////////////////////////////////////////////////////////////////////////////////
Boundaries** CreateBoundries(unsigned int arr_boundaries_len);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CreatePlatforms
//						Créer un tableau 2D de plateformes.
// PARAMETRES: 			arr_platforms_len: Taille du tableau de plateformes.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur un tableau 2D de plateformes.
// REMARQUE:            Sert à initialiser le tableau 2D de plateformes d'un terrain.
////////////////////////////////////////////////////////////////////////////////
Platforms** CreatePlatforms(unsigned int arr_platforms_len);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		SummaryDescription_new
//						Initialise une structure contenant la description d'une capsule.
// PARAMETRES: 			name: 			Nom de la capsule.
// 						author: 		Nom de l'auteur de cette capsule (anonyme si absent).
// 						netMass: 		Masse de la capsule sans carburant (kg).
// 						dimensions:  	Dimension de la capsule.
// 						exhaustSpeed: 	Vitesse d’éjection de l’échappement du carburant (m/s).
// 						fuelExpense:	Dépense de carburant par seconde lorsqu’un jet est activé (kg/s).
//						breakdownSpeed: Vitesse scalaire pour laquelle une collision avec la frontière du terrain est fatale, plateforme ou non (m/s).
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la description d'une capsule.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant une capsule.
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
//						Sert à désallouer la mémoire pour la description d'une capsule.
// PARAMETRES: 			capsuleDescription: Données de jeu à désallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur capsuleDescription sera à NULL après l'exécution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void LanderDescription_free(LanderDescription* landerDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GlobalConfiguration_new
//						Initialise une structure contenant la configuration globale de l'application.
// PARAMETRES: 			landResolution: résolution de tous les terrains (pixel/m)
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant la configuration globale de l'application.
////////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* GlobalConfiguration_new(float landResolution);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GlobalConfiguration_free
//						Sert à désallouer la mémoire pour la configuration globale de l'application.
// PARAMETRES: 			summaryDescription: Données de jeu à désallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur globalConfiguration sera à NULL après l'exécution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void GlobalConfiguration_free(GlobalConfiguration* globalConfiguration);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		SummaryDescription_new
//						Initialise une structure contenant le sommaire d'un tableau.
// PARAMETRES: 			id: 			Identifiant unique du tableau.
// 						name: 			Nom du tableau.
// 						author: 		Auteur du tableau (anonyme si absent).
// 						landerInitFuel: Quantité initiale de carburant de la capsule du tableau (kg).
// 						timeLimit: 		Temps limite du tableau (secondes) [1..].
// 						topScore:		Meilleur score du tableau (points).
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant les données de du jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant le sommaire d'un tableau.
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
//						Sert à désallouer la mémoire pour le sommaire d'un tableau.
// PARAMETRES: 			summaryDescription: Données de jeu à désallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            Le pointeur summaryDescription sera à NULL après l'exécution de la fonction.
////////////////////////////////////////////////////////////////////////////////
void SummaryDescription_free(SummaryDescription* summaryDescription);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		GameData_new
//						Initialise une structure contenant les données de jeu.
// PARAMETRES: 			playerName; 	Nom du joueur qui a réussi le tableau.
// 						totalTime; 		Temps total de jeu (secondes).
// 						fuelLeft; 		Quantité de carburant restant à la fin de la partie (kg).
// 						nbPlatforms; 	Nombre de plateformes distinctes où la capsule s'est posée avec succès.
// 						totalValue; 	Naleur totale de la partie (points).
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant les données de du jeu.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant les données de jeu.
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
//						Sert à désallouer la mémoire pour les données de jeu.
// PARAMETRES: 			gameData: Données de jeu à désallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:
////////////////////////////////////////////////////////////////////////////////
void GameData_free(GameData* gameData);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LevelsSummary_new
//						Sommaire de tableau
// PARAMETRES: 			gameData: Données de jeu à désallouer.
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
//						Sert à désallouer la mémoire pour le sommaire des tableaux.
// PARAMETRES: 			levelsSummary: Sommaire des tableaux à désallouer.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:
////////////////////////////////////////////////////////////////////////////////
void LevelsSummary_free(LevelsSummary* levelsSummary);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		CreateLevelSummaryArray
//						Créer un tableau de sommaire de tableau
// PARAMETRES: 			unsigned int array_len: Nombre de tableau.
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:			Un pointeur vers le tableau de sommaire de tableau.
////////////////////////////////////////////////////////////////////////////////
LevelsSummary** CreateLevelSummaryArray(unsigned int array_len);

#endif /* _GAMEUTILS_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
