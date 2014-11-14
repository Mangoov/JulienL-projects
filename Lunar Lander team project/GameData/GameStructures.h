///////////////////////////////////////////////////////////////////////////
/// @file GameStructures.h
/// @date 2013-11
/// @description Définition des structures de données du jeu.
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _GAMESTRUCTURES_H_
#define _GAMESTRUCTURES_H_

/* Description de tableau (objet JSON) */
typedef struct LanderPosition_t
{
	int top; 	/* position verticale du coin supérieur gauche de la capsule (haut commence à 0) [0..479] */
	int left; 	/* position horizontale du coin supérieur gauche de la capsule (gauche commence à 0) [0..639] */
} LanderPosition;

typedef struct LanderSpeed_t
{
	float x; /* composante horizontale scalaire de la vitesse (m/s) (positif signifie vers la droite) */
	float y; /* composante verticale scalaire de la vitesse (m/s) (positif signifie vers le haut) */
} LanderSpeed;

typedef struct LevelDescription_t { /* Décrit un tableau */
	char *name; 					/* nom du tableau */
	char *author; 					/* nom de l'auteur de ce tableau (anonyme si absent) */
	char *landId; 					/* ID du terrain du tableau */
	char *landerId; 				/* ID de la capsule du tableau */
	LanderPosition landerInitPos; 	/* position initiale de la capsule */
	LanderSpeed landerInitSpeed; 	/* vitesse initiale de la capsule */
	float landerInitFuel; 			/* quantité initiale de carburant de la capsule (kg) */
	int timeLimit; 					/* temps limite du tableau (secondes) [1..] (aucune limite de temps si absent) */
} LevelDescription;


/* Description de terrain (objet JSON) */
typedef struct Boundaries_t
{
	int horizon; 	/* position horizontale du point (gauche commence à 0) [0..639] */
	int vertical; 	/* position verticale du point (haut commence à 0) [0..479] */
} Boundaries;

typedef struct Platforms_t
{
	int ptIndexLeft; 	/* index du point le plus à gauche de la plateforme dans le tableau boundaries */
	int value; 			/* valeur de la plateforme */
} Platforms;

typedef struct LandDescription_t { /* Décrit un terrain. */
	char *name; 				/* nom du terrain */
	char *author; 				/* nom de l'auteur de ce terrain (anonyme si absent) */
	char *imgId; 				/* ID de l'image d'arrière-plan associée au terrain */
	float gravity; 				/* accélération gravitationnelle appliquée (m/s² ou N/kg) */
	Boundaries **boundaries; 	/* tableau de points spécifiant, de gauche à droite, la frontière du terrain */
	Platforms **platforms; 		/* tableau spécifiant toutes les plateformes où doit se poser la capsule pour ce tableau */
	unsigned int arr_boundaries_len;
	unsigned int arr_platforms_len;
} LandDescription;


/* Description de capsule (objet JSON) */
typedef struct Dimensions_t { /* objet de dimension de la capsule */
	int width; 	/* largeur (pixels) [1..]*/
	int height;	/* hauteur (pixels) [1..] */
} Dimensions;

typedef struct LanderDescription_t { /* Décrit une capsule. */
	char *name; 			/* nom de la capsule */
	char *author; 			/* nom de l'auteur de cette capsule (anonyme si absent) */
	float netMass; 			/* masse de la capsule sans carburant (kg) */
	Dimensions dimensions; 	/* dimension de la capsule */
	float exhaustSpeed; 	/* vitesse d’éjection de l’échappement du carburant (m/s) */
	float fuelExpense; 		/* dépense de carburant par seconde lorsqu’un jet est activé (kg/s) */
	float breakdownSpeed; 	/* vitesse scalaire pour laquelle une collision avec la frontière du terrain est fatale, plateforme ou non (m/s) */
} LanderDescription;


/* Configuration globale (objet JSON) */
typedef struct GlobalConfiguration_t { /* Configuration globale à télécharger au lancement de l’application. */
	float landResolution; /* résolution de tous les terrains (pixel/m) */
} GlobalConfiguration;


/* Sommaire de tableau (objet JSON) */
typedef struct SummaryDescription_t
{
	char *id; 				/* identifiant unique du tableau */
	char *name; 			/* nom du tableau */
	char *author; 			/* auteur du tableau (anonyme si absent) */
	float landerInitFuel; 	/* quantité initiale de carburant de la capsule du tableau (kg) */
	int timeLimit; 			/* temps limite du tableau (secondes) [1..] ( */
	int topScore; 			/* meilleur score du tableau (points) */
} SummaryDescription;


/* Données de jeu (objet JSON) */
typedef struct GameData_t
{
	char *playerName; 	/* nom du joueur qui a réussi le tableau */
	int totalTime; 		/* temps total de jeu (secondes) */
	float fuelLeft; 	/* quantité de carburant restant à la fin de la partie (kg) */
	int nbPlatforms; 	/* nombre de plateformes distinctes où la capsule s'est posée avec succès */
	int totalValue; 	/* valeur totale de la partie (points) */
} GameData;

typedef struct LevelsSummary_t
{
	char *id;
	char *name;
	char *author;
	float landerInitFuel;
	int timeLimit;
	double score;
} LevelsSummary;

#endif /* GAMESTRUCTURES_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
