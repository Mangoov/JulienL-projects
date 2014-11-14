///////////////////////////////////////////////////////////////////////////
/// @file GameStructures.h
/// @date 2013-11
/// @description D�finition des structures de donn�es du jeu.
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
	int top; 	/* position verticale du coin sup�rieur gauche de la capsule (haut commence � 0) [0..479] */
	int left; 	/* position horizontale du coin sup�rieur gauche de la capsule (gauche commence � 0) [0..639] */
} LanderPosition;

typedef struct LanderSpeed_t
{
	float x; /* composante horizontale scalaire de la vitesse (m/s) (positif signifie vers la droite) */
	float y; /* composante verticale scalaire de la vitesse (m/s) (positif signifie vers le haut) */
} LanderSpeed;

typedef struct LevelDescription_t { /* D�crit un tableau */
	char *name; 					/* nom du tableau */
	char *author; 					/* nom de l'auteur de ce tableau (anonyme si absent) */
	char *landId; 					/* ID du terrain du tableau */
	char *landerId; 				/* ID de la capsule du tableau */
	LanderPosition landerInitPos; 	/* position initiale de la capsule */
	LanderSpeed landerInitSpeed; 	/* vitesse initiale de la capsule */
	float landerInitFuel; 			/* quantit� initiale de carburant de la capsule (kg) */
	int timeLimit; 					/* temps limite du tableau (secondes) [1..] (aucune limite de temps si absent) */
} LevelDescription;


/* Description de terrain (objet JSON) */
typedef struct Boundaries_t
{
	int horizon; 	/* position horizontale du point (gauche commence � 0) [0..639] */
	int vertical; 	/* position verticale du point (haut commence � 0) [0..479] */
} Boundaries;

typedef struct Platforms_t
{
	int ptIndexLeft; 	/* index du point le plus � gauche de la plateforme dans le tableau boundaries */
	int value; 			/* valeur de la plateforme */
} Platforms;

typedef struct LandDescription_t { /* D�crit un terrain. */
	char *name; 				/* nom du terrain */
	char *author; 				/* nom de l'auteur de ce terrain (anonyme si absent) */
	char *imgId; 				/* ID de l'image d'arri�re-plan associ�e au terrain */
	float gravity; 				/* acc�l�ration gravitationnelle appliqu�e (m/s� ou N/kg) */
	Boundaries **boundaries; 	/* tableau de points sp�cifiant, de gauche � droite, la fronti�re du terrain */
	Platforms **platforms; 		/* tableau sp�cifiant toutes les plateformes o� doit se poser la capsule pour ce tableau */
	unsigned int arr_boundaries_len;
	unsigned int arr_platforms_len;
} LandDescription;


/* Description de capsule (objet JSON) */
typedef struct Dimensions_t { /* objet de dimension de la capsule */
	int width; 	/* largeur (pixels) [1..]*/
	int height;	/* hauteur (pixels) [1..] */
} Dimensions;

typedef struct LanderDescription_t { /* D�crit une capsule. */
	char *name; 			/* nom de la capsule */
	char *author; 			/* nom de l'auteur de cette capsule (anonyme si absent) */
	float netMass; 			/* masse de la capsule sans carburant (kg) */
	Dimensions dimensions; 	/* dimension de la capsule */
	float exhaustSpeed; 	/* vitesse d��jection de l��chappement du carburant (m/s) */
	float fuelExpense; 		/* d�pense de carburant par seconde lorsqu�un jet est activ� (kg/s) */
	float breakdownSpeed; 	/* vitesse scalaire pour laquelle une collision avec la fronti�re du terrain est fatale, plateforme ou non (m/s) */
} LanderDescription;


/* Configuration globale (objet JSON) */
typedef struct GlobalConfiguration_t { /* Configuration globale � t�l�charger au lancement de l�application. */
	float landResolution; /* r�solution de tous les terrains (pixel/m) */
} GlobalConfiguration;


/* Sommaire de tableau (objet JSON) */
typedef struct SummaryDescription_t
{
	char *id; 				/* identifiant unique du tableau */
	char *name; 			/* nom du tableau */
	char *author; 			/* auteur du tableau (anonyme si absent) */
	float landerInitFuel; 	/* quantit� initiale de carburant de la capsule du tableau (kg) */
	int timeLimit; 			/* temps limite du tableau (secondes) [1..] ( */
	int topScore; 			/* meilleur score du tableau (points) */
} SummaryDescription;


/* Donn�es de jeu (objet JSON) */
typedef struct GameData_t
{
	char *playerName; 	/* nom du joueur qui a r�ussi le tableau */
	int totalTime; 		/* temps total de jeu (secondes) */
	float fuelLeft; 	/* quantit� de carburant restant � la fin de la partie (kg) */
	int nbPlatforms; 	/* nombre de plateformes distinctes o� la capsule s'est pos�e avec succ�s */
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
