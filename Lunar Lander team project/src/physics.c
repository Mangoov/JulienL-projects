#include "physics.h"

#define FPS 20



GamePhysics phys;
extern Application app;
extern Bitmap LanderBMP;
extern GlobalConfiguration *globalConfiguration;

int freeze = 0;
//Returns 1 on victory, 0 on nothing, -1 on failure
int checkVictory()
{
	int pointX = (phys.currentYPos)* globalConfiguration->landResolution;
	float leftPointX = (phys.currentYPos)* globalConfiguration->landResolution;
	float Ypoint = phys.currentXPos*globalConfiguration->landResolution + LanderBMP.Height;
	float RightPointX = phys.currentYPos*globalConfiguration->landResolution + LanderBMP.Width;
	size_t i = 0;
	float slope=0;
	float SlopeY;
	float y2y1;
	float x2x1;
	for(i = 0; i < app.landDescription->arr_boundaries_len-1; ++i)
	{
		//Check collision point Gauche
		if((app.landDescription->boundaries[i+1]->horizon >= leftPointX)&&(app.landDescription->boundaries[i]->horizon <= leftPointX))
		{
			y2y1 = app.landDescription->boundaries[i+1]->vertical - app.landDescription->boundaries[i]->vertical;
			x2x1 = app.landDescription->boundaries[i+1]->horizon - app.landDescription->boundaries[i]->horizon;
			slope = y2y1/x2x1;
			SlopeY = slope*(leftPointX-app.landDescription->boundaries[i]->horizon) +  app.landDescription->boundaries[i]->vertical;
			if(Ypoint > SlopeY)
			{
				return checkPlatform(i);
			}

		}
		//Check Collision Milieu
		else if((app.landDescription->boundaries[i+1]->horizon >= pointX)&&(app.landDescription->boundaries[i]->horizon <= pointX))
		{
			//calculate slope
			y2y1 = app.landDescription->boundaries[i+1]->vertical - app.landDescription->boundaries[i]->vertical;
			x2x1 = app.landDescription->boundaries[i+1]->horizon - app.landDescription->boundaries[i]->horizon;
			slope = y2y1/x2x1;
			SlopeY = slope*(pointX-app.landDescription->boundaries[i]->horizon) +  app.landDescription->boundaries[i]->vertical;
			if(Ypoint > SlopeY)
			{
				return checkPlatform(i);
			}
		}

		//Check Collision point Droite
		else if((app.landDescription->boundaries[i+1]->horizon >= RightPointX)&&(app.landDescription->boundaries[i]->horizon <= RightPointX))
		{
			//calculate slope
			y2y1 = app.landDescription->boundaries[i+1]->vertical - app.landDescription->boundaries[i]->vertical;
			x2x1 = app.landDescription->boundaries[i+1]->horizon - app.landDescription->boundaries[i]->horizon;
			slope = y2y1/x2x1;
			SlopeY = slope*(RightPointX-app.landDescription->boundaries[i]->horizon) +  app.landDescription->boundaries[i]->vertical;
			if(Ypoint > SlopeY)
			{
				return checkPlatform(i);
			}
			else return 0;
		}

		else if((app.levelDescription->landerInitPos.left <= 4 || app.levelDescription->landerInitPos.left + LanderBMP.Width >= 637 || app.levelDescription->landerInitPos.top <= 4))
			return 5;
	}
	return 0;
}

int checkPlatform(int indexCollision)
{
	int i;
	for(i = 0;i<app.landDescription->arr_platforms_len;i++)
	{
		if((app.landDescription->platforms[i]->ptIndexLeft == indexCollision)
		&&	(app.landDescription->boundaries[indexCollision+1]->horizon > phys.currentYPos + LanderBMP.Width))
		{
			//Colision detecte dans platforme
			if((phys.verticalSpeed*FPS) > app.landerDescription->breakdownSpeed)
			{
				return -2;

			}
			else
			{
				if(app.landDescription->platforms[i]->value != 0)
				{
					phys.score += app.landDescription->platforms[i]->value;
					app.landDescription->platforms[i]->value=0;
					phys.nbplatforms++;
				}
				freeze = 1;
				phys.horizontalSpeed = 0;
				phys.verticalSpeed = 0;
				XTft_ColorPlatform(app.landDescription->boundaries[indexCollision]->horizon, app.landDescription->boundaries[indexCollision+1]->horizon, app.landDescription->boundaries[indexCollision+1]->vertical);
				return 1;
			}
		}
	}
	return -1;
}

void InitPhysics()
{
	phys.horizontalSpeed = app.levelDescription->landerInitSpeed.x/FPS;
	phys.verticalSpeed = app.levelDescription->landerInitSpeed.y/FPS;
	phys.currentMass = app.levelDescription->landerInitFuel + app.landerDescription->netMass;
	phys.currentFuel = app.levelDescription->landerInitFuel;
	phys.exhaustSpeed = app.landerDescription->exhaustSpeed;
	phys.fuelExpenseFPS = app.landerDescription->fuelExpense / FPS;
	phys.deltaVhoriz = 0;
	phys.deltaVverti = 0;
	phys.deltaM = 0;
	phys.gravityFPS = app.landDescription->gravity/(FPS*FPS);
	phys.currentXPos = app.levelDescription->landerInitPos.top / globalConfiguration->landResolution;
	phys.currentYPos = app.levelDescription->landerInitPos.left / globalConfiguration->landResolution;
	phys.altitude = 480 - phys.currentYPos;
	phys.score = 0;
	phys.nbplatforms = 0;
}


void applyPhysics(controle* input)
{

	//Cas ou le touche de power fusee est activé
	if(input->up == true && input->left == true)
	{
		//exhaust = phys.exhaustSpeed/2.0;
		phys.deltaM = phys.fuelExpenseFPS;
		phys.deltaVverti = - (phys.verticalSpeed - phys.exhaustSpeed/2.0)*(phys.deltaM/(phys.currentMass));
		phys.deltaVhoriz = (phys.horizontalSpeed - phys.exhaustSpeed/2.0)*(phys.deltaM/(phys.currentMass));
		phys.currentFuel = phys.currentFuel - phys.fuelExpenseFPS;
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		freeze = 0;
	}
	else if(input->up == true && input->right == true)
	{
		//exhaust = phys.exhaustSpeed/2;
		phys.deltaM = phys.fuelExpenseFPS;
		phys.deltaVverti = - (phys.verticalSpeed - phys.exhaustSpeed/2.0)*(phys.deltaM/(phys.currentMass));
		phys.deltaVhoriz = (phys.horizontalSpeed + phys.exhaustSpeed/2.0)*(phys.deltaM/(phys.currentMass));
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		phys.currentFuel = phys.currentFuel - phys.fuelExpenseFPS;
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		freeze = 0;
	}
	else if(input->up == true)
	{
		phys.deltaM = phys.fuelExpenseFPS;
		phys.deltaVverti = - (phys.verticalSpeed - phys.exhaustSpeed)*(phys.deltaM/(phys.currentMass));
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		phys.currentFuel = phys.currentFuel - phys.fuelExpenseFPS;
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		freeze = 0;
	}
	else if(input->left == true)
	{
		phys.deltaM = phys.fuelExpenseFPS;
		phys.deltaVhoriz = (phys.horizontalSpeed - phys.exhaustSpeed)*(phys.deltaM/(phys.currentMass));
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		phys.currentFuel = phys.currentFuel - phys.fuelExpenseFPS;
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
	}
	else if(input->right == true)
	{
		phys.deltaM = phys.fuelExpenseFPS;
		phys.deltaVhoriz = (phys.horizontalSpeed + phys.exhaustSpeed)*(phys.deltaM/(phys.currentMass));
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
		phys.currentFuel = phys.currentFuel - phys.fuelExpenseFPS;
		phys.currentMass = phys.currentMass - phys.fuelExpenseFPS;
	}
	if(phys.currentFuel<=0)
	{
		phys.currentFuel=0;
		phys.exhaustSpeed = 0;
	}

	//Ajust Speeds
	phys.horizontalSpeed = phys.horizontalSpeed + phys.deltaVhoriz/FPS;
	phys.verticalSpeed = phys.verticalSpeed - phys.deltaVverti/FPS + phys.gravityFPS;

	//Ajust postion
	if(freeze == 0)
	{
		phys.currentXPos = (phys.currentXPos + phys.verticalSpeed);
		phys.currentYPos = (phys.currentYPos + phys.horizontalSpeed);
	}
	phys.altitude = 480 - phys.currentYPos;
	//Reset the acceleration
	phys.deltaVhoriz = 0;
	phys.deltaVverti = 0;
}
