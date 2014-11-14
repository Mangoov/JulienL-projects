/*
 * physics.h
 *
 *  Created on: 2013-11-11
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <stdio.h>
#include <string.h>
#include "icontrole.h" //pour obtenir la struct des game inputs
#include "../NetworkInterface/NetworkInterface.h"



typedef struct GamePhysics_
{
	float horizontalSpeed;
	float verticalSpeed;
	float currentMass; //Cette valeur (lors de l'initialisation) vient de l'addition de capsule.netMass et tableau landerInitFuel.
	float exhaustSpeed;
	float fuelExpenseFPS;
	float deltaVhoriz;
	float deltaVverti;
	float deltaM;
	float gravityFPS;
	float currentXPos;
	float currentYPos;
	float currentFuel;
	float altitude;
	float score;
	int nbplatforms;
} GamePhysics;
int checkVictory();
void InitPhysics();
void applyPhysics(controle* input);
int checkPlatform(int indexCollision);


#endif /* PHYSICS_H_ */
