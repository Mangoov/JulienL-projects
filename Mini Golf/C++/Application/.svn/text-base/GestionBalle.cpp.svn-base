///////////////////////////////////////////////////////////////////////////////
/// @file GestionBalle.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////	

#include "GestionBalle.h"
#include <cmath>
#include "Sound.h"
#include "ConfigScene.h"

double GestionBalle::angleAleatoire_=((double (rand()) / double(RAND_MAX)) * (utilitaire::PI/4 + utilitaire::PI/4)) - utilitaire::PI/4;
bool GestionBalle::allowDeviation_=true;
////////////////////////////////////////////////////////////////////////
///
/// @fn aidecollision::DetailsCollision GestionBalle::checkCollisionBordure(NoeudBalle* noeudBalle)
///
/// vérifie les collisions de la balle avec les differents obstacles
///
/// @param[in] noeudBalle 
/// 
///
/// @return structure contenant les détails de collision
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision GestionBalle::checkCollisionBordure(NoeudBalle* noeudBalle, float temps)
{
	aidecollision::DetailsCollision detail;
	detail.type = aidecollision::COLLISION_AUCUNE;
	NoeudAbstrait* noeud = noeudBalle;

	if(noeudBalle->obtenirBonusActive() == true)
	{
		float time = noeudBalle->obtenirtempsBonus();
		time = time - temps;
		noeudBalle->ModifierTempsBonus(time);
		if(time<=0)
		{
			noeudBalle->setBonusActive(false);
			Vecteur3 vitesseCourrante = noeudBalle->obtenirVitesse();
			Vecteur3 vitesseInitiale = noeudBalle->obtenirVitesseAvantBonus();
			vitesseCourrante.normaliser();
			/*if(vitesseCourrante[0] < 0)
			{
			vitesseInitiale[0] = -abs(vitesseInitiale[0]);
			}
			if(vitesseCourrante[1] < 0)
			{
			vitesseInitiale[1] = -abs(vitesseInitiale[1]);
			}*/
			vitesseCourrante *= vitesseInitiale.norme();
			noeudBalle->modifierVitesse(vitesseCourrante);
		}
	}
	double rotationBordure;
	Vecteur3 posRelativeBordure,posRelativeTrou,posRelativeBonus,posRelativeEau,coinBordureMin,coinBordureMax,basGauche,hautGauche,basDroit,hautDroit;			
	do
	{
		noeud = noeud->obtenirParent();
	}while(noeud->obtenirType() != "racine");

	for(int i = 0; i<noeud->obtenirNombreEnfants(); i++)
	{
		if(noeud->chercher(i)->obtenirType() == "bordure" || noeud->chercher(i)->obtenirType() == "contour")
		{


			posRelativeBordure = noeud->chercher(i)->obtenirPositionRelative();
			rotationBordure = (double) noeud->chercher(i)->obtenirRot();
			noeud->chercher(i)->calculerCoinsBordure(coinBordureMin,coinBordureMax);


			if( 0.0 <= rotationBordure && rotationBordure <= 90.0)
			{
				basGauche[0] = coinBordureMin[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[1] = coinBordureMin[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));			
				basDroit[0] = coinBordureMax[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				basDroit[1] = coinBordureMax[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[0] = coinBordureMin[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[1] = coinBordureMin[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[0] = coinBordureMax[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[1] = coinBordureMax[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));
			}

			if(90.0 < rotationBordure && rotationBordure <= 180.0)
			{
				hautGauche[0] = coinBordureMin[0] - 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[1] = coinBordureMin[1] - 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));			
				hautDroit[0]  = coinBordureMax[0] - 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[1]  = coinBordureMax[1] - 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[0]  = coinBordureMin[0] + 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[1]  = coinBordureMin[1] + 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));			
				basDroit[0]   = coinBordureMax[0] + 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				basDroit[1]   = coinBordureMax[1] + 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));

			}

			if(-180 < rotationBordure && rotationBordure <= -90)
			{
				hautGauche[0] = coinBordureMin[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				hautGauche[1] = coinBordureMin[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);			
				hautDroit[0]  = coinBordureMax[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				hautDroit[1]  = coinBordureMax[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				basGauche[0]  = coinBordureMin[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				basGauche[1]  = coinBordureMin[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);			
				basDroit[0]   = coinBordureMax[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				basDroit[1]   = coinBordureMax[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);

			}

			if(-90 < rotationBordure && rotationBordure < 0)
			{
				basGauche[0] = coinBordureMin[0] - 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[1] = coinBordureMin[1] - 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));			
				basDroit[0] = coinBordureMax[0] - 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				basDroit[1] = coinBordureMax[1] - 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[0] = coinBordureMin[0] + 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[1] = coinBordureMin[1] + 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[0] = coinBordureMax[0] + 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[1] = coinBordureMax[1] + 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));

			}



			detail = aidecollision::calculerCollisionSegment(basGauche,basDroit,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type!= 0)
			{		
				Sound::obtenirInstance()->jouerCollision();
				return detail;
			}
			detail = aidecollision::calculerCollisionSegment(hautGauche,hautDroit,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type!= 0)
			{					
				Sound::obtenirInstance()->jouerCollision();
				return detail;
			}
			detail = aidecollision::calculerCollisionSegment(basGauche,hautGauche,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type!= 0)
			{	
				Sound::obtenirInstance()->jouerCollision();
				return detail;
			}
			detail = aidecollision::calculerCollisionSegment(basDroit,hautDroit,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type!= 0)
			{					
				Sound::obtenirInstance()->jouerCollision();
				return detail;
			}

		}

		else if (noeud->chercher(i)->obtenirType() == "portal"&& noeudBalle->obtenirTeleported() == false)
		{
			posRelativeTrou = noeud->chercher(i)->obtenirPositionRelative();
			detail = aidecollision::calculerCollisionSphere(posRelativeTrou,/*noeudBalle->obtenirRayon()*/6.0,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon());
			if(detail.type != 0 && detail.enfoncement >= noeudBalle->obtenirRayon() + noeudBalle->obtenirRayon()/5 && noeud->chercher(i)->obtenirPortalPowered() == true )
			{
				NoeudAbstrait* root = noeudBalle;
				do
				{
					root = root->obtenirParent();
				}while(root->obtenirType() != "racine");

				Vecteur3 postemp = root->chercher(i)->obtenirPosLinkingPortal();

				for(int i = 0; i<root->obtenirNombreEnfants(); i++)
				{
					if(root->chercher(i)->obtenirPositionRelative() == postemp)
					{
						root->chercher(i)->assignerPortalPowered(false);
					}
					else if(root->chercher(i)->obtenirType() == "portal")
					{
						root->chercher(i)->assignerPortalPowered(true);
					}

				}

				 noeudBalle->assignerPositionRelative(noeud->chercher(i)->obtenirPosLinkingPortal());
					//noeudBalle->assignerTeleported(true);
					
					Sound::obtenirInstance()->jouerPortal();
					return detail;
		   }
		}
		else if (noeud->chercher(i)->obtenirType() == "trou")
		{
			posRelativeTrou = noeud->chercher(i)->obtenirPositionRelative();
			detail = aidecollision::calculerCollisionSphere(posRelativeTrou,/*noeudBalle->obtenirRayon()*/6.0,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon());

			if(detail.type != 0 && detail.enfoncement >= noeudBalle->obtenirRayon() + noeudBalle->obtenirRayon()/5)
			{
				if(noeudBalle->obtenirVitesse().norme() < 140)
				{
					noeudBalle->assignerPositionRelative(posRelativeTrou);
					noeudBalle->assignerCountdown(11);
					noeudBalle->assignerCollisionTrou(true);
					Sound::obtenirInstance()->jouerTrou();

					return detail;
				}
				else
				{
					if(allowDeviation_ == true){
						noeudBalle->modifierVitesse(noeudBalle->obtenirVitesse().tourner(angleAleatoire_,Vecteur3(0,0,1)));
						allowDeviation_ = false;
					}
					
					return detail;
				}
			}
			else if(detail.type != 0 && detail.enfoncement >= noeudBalle->obtenirRayon()/5 && noeudBalle->obtenirVitesse().norme() < 40)
			{
				double norme = noeudBalle->obtenirVitesse().norme() + 5;

				Vecteur3 newOrientation = Vecteur3(posRelativeTrou[0] - noeudBalle->obtenirPositionRelative()[0],
					posRelativeTrou[1] - noeudBalle->obtenirPositionRelative()[1],
					posRelativeTrou[2] - noeudBalle->obtenirPositionRelative()[2]);
				newOrientation.normaliser();
				noeudBalle->modifierVitesse(newOrientation*norme);
			}
		}
		else if(noeud->chercher(i)->obtenirType() == "bonus")
		{

			posRelativeBonus = noeud->chercher(i)->obtenirPositionRelative();
			detail = aidecollision::calculerCollisionSphere(posRelativeBonus,8.0,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon());
			//Collision
			if(detail.type != 0)
			{
				//On active les effets du bonus
				if(noeudBalle->obtenirBonusActive() == false)
				{
					//noeud->chercher(i)->setBonusActive(true);
					noeudBalle->setBonusActive(true);
					noeudBalle->ModifierTempsBonus(1.0);
					Vecteur3 vitesse(noeudBalle->obtenirVitesse());
					noeudBalle->setVitesseAvantBonus(vitesse);
					float angle = atan2f(abs(vitesse[1]),abs(vitesse[0]));
					Vecteur3 impulsion;

					impulsion[1] = ConfigScene::obtenirInstance()->obtenirAccelBonus()*sin(angle);
					if(vitesse[1]<0)
					{
						impulsion[1] = -impulsion[1];
					}

					impulsion[0] = ConfigScene::obtenirInstance()->obtenirAccelBonus()*cos(angle);
					if(vitesse[0]<0)
					{
						impulsion[0] = -impulsion[0];
					}
					noeudBalle->modifierVitesse(impulsion);
					Sound::obtenirInstance()->jouerBonus();
					return detail;
				}

				if(noeudBalle->obtenirBonusActive() == true)
				{
					noeudBalle->ModifierTempsBonus(1.0);

					noeudBalle->ModifierTempsBonus(1.0);
					Vecteur3 vitesse(noeudBalle->obtenirVitesse());
					float angle = atan2f(abs(vitesse[1]),abs(vitesse[0]));
					Vecteur3 impulsion;

					impulsion[1] = ConfigScene::obtenirInstance()->obtenirAccelBonus()*sin(angle);
					if(vitesse[1]<0)
					{
						impulsion[1] = -impulsion[1];
					}

					impulsion[0] = ConfigScene::obtenirInstance()->obtenirAccelBonus()*cos(angle);
					if(vitesse[0]<0)
					{
						impulsion[0] = -impulsion[0];
					}
					noeudBalle->modifierVitesse(impulsion);
					Sound::obtenirInstance()->jouerBonus();
				}
				/*Vecteur3 boost(noeudBalle->obtenirVitesse());
				double normeBoost = boost.norme();
				if(0 <= normeBoost &&  normeBoost <= 40 )
				{
				boost *= 4;
				}
				else if(40 < normeBoost)
				{
				boost *= 2;
				}
				noeudBalle->modifierVitesse(boost);
				noeud->effacer(noeud->chercher(i));
				return detail;			*/	
			}
		}
		else if(noeud->chercher(i)->obtenirType() == "eau")
		{
			posRelativeEau = noeud->chercher(i)->obtenirPositionRelative();
			Vecteur3 minEau, maxEau;
			noeud->chercher(i)->calculerBoite(minEau, maxEau);
			minEau *= noeud->chercher(i)->obtenirFacteurAgrandissment();
			maxEau *= noeud->chercher(i)->obtenirFacteurAgrandissment();
			float rotationEau = noeud->chercher(i)->obtenirRot();
			float longueur = utilitaire::ABS((float)2*minEau[0]);
			//Vecteur3 hautGauche;
			////coin bas droit
			//Vecteur3 basDroit;
			////coin bas gauche
			//Vecteur3 basGauche;
			////coin haut droit
			//Vecteur3 hautDroit;
			

			//coin haut gauche
			Vecteur3 hautGauche(posRelativeEau[0] - utilitaire::ABS(minEau[0]),posRelativeEau[1]+utilitaire::ABS(maxEau[1]),0);
			//coin bas droit
			Vecteur3 basDroit(posRelativeEau[0]+utilitaire::ABS(maxEau[0]),posRelativeEau[1] - utilitaire::ABS(minEau[1]),0);
			//coin bas gauche
			Vecteur3 basGauche(posRelativeEau[0]-utilitaire::ABS(minEau[0]),posRelativeEau[1] - utilitaire::ABS(minEau[1]),0);
			//coin haut droit
			Vecteur3 hautDroit(posRelativeEau[0]+utilitaire::ABS(maxEau[0]),posRelativeEau[1] + utilitaire::ABS(maxEau[1]),0);
			//if( 0.0 <= rotationEau && rotationEau <= 90.0)
			//{
			//	basGauche[0]  = (posRelativeEau[0]-utilitaire::ABS((float)minEau[0])) + longueur*sin(utilitaire::DEG_TO_RAD(rotationEau));
			//	basGauche[1]  = (posRelativeEau[1]-utilitaire::ABS((float)minEau[1])) - longueur*cos(utilitaire::DEG_TO_RAD(rotationEau));			
			//	basDroit[0]   = (posRelativeEau[0]+utilitaire::ABS((float)maxEau[0])) + longueur*sin(utilitaire::DEG_TO_RAD(rotationEau));
			//	basDroit[1]   = (posRelativeEau[1]-utilitaire::ABS((float)minEau[1])) - longueur*cos(utilitaire::DEG_TO_RAD(rotationEau));	
			//	hautGauche[0] = (posRelativeEau[0]-utilitaire::ABS((float)minEau[0])) - longueur*sin(utilitaire::DEG_TO_RAD(rotationEau));
			//	hautGauche[1] = (posRelativeEau[1]+utilitaire::ABS((float)maxEau[1])) + longueur*cos(utilitaire::DEG_TO_RAD(rotationEau));	
			//	hautDroit[0]  = (posRelativeEau[0]+utilitaire::ABS((float)maxEau[0])) - longueur*sin(utilitaire::DEG_TO_RAD(rotationEau));
			//	hautDroit[1]  = (posRelativeEau[1]+utilitaire::ABS((float)maxEau[1])) + longueur*cos(utilitaire::DEG_TO_RAD(rotationEau));
			//}
			if(rotationEau != 0.0f){
				float Cos = cos(utilitaire::DEG_TO_RAD(-rotationEau));
				float Sin = sin(utilitaire::DEG_TO_RAD(-rotationEau));

				float basGauche0 = posRelativeEau[0]+(basGauche[0]-posRelativeEau[0])*Cos+(basGauche[1]-posRelativeEau[1])*Sin;
				float basGauche1 = posRelativeEau[1]-(basGauche[0]-posRelativeEau[0])*Sin+(basGauche[1]-posRelativeEau[1])*Cos;
				basGauche[0] = basGauche0;
				basGauche[1] = basGauche1;


				float basDroit0 = posRelativeEau[0]+(basDroit[0]-posRelativeEau[0])*Cos+(basDroit[1]-posRelativeEau[1])*Sin;
				float basDroit1 = posRelativeEau[1]-(basDroit[0]-posRelativeEau[0])*Sin+(basDroit[1]-posRelativeEau[1])*Cos;
				basDroit[0] = basDroit0;
				basDroit[1] = basDroit1;


				float hautGauche0 = posRelativeEau[0]+(hautGauche[0]-posRelativeEau[0])*Cos+(hautGauche[1]-posRelativeEau[1])*Sin;
				float hautGauche1 = posRelativeEau[1]-(hautGauche[0]-posRelativeEau[0])*Sin+(hautGauche[1]-posRelativeEau[1])*Cos;
				hautGauche[0] = hautGauche0;
				hautGauche[1] = hautGauche1;

				float hautDroit0 = posRelativeEau[0]+(hautDroit[0]-posRelativeEau[0])*Cos+(hautDroit[1]-posRelativeEau[1])*Sin;
				float hautDroit1 = posRelativeEau[1]-(hautDroit[0]-posRelativeEau[0])*Sin+(hautDroit[1]-posRelativeEau[1])*Cos;
				hautDroit[0] = hautDroit0;
				hautDroit[1] = hautDroit1;
			}

			detail = aidecollision::calculerCollisionSegment(basGauche,hautGauche,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type != 0)
			{
				if(noeudBalle->obtenirPremierPassageEau() == true)
					noeudBalle->setEstDansEau(true);
				Sound::obtenirInstance()->jouerEau();
				return detail;
			}
			detail = aidecollision::calculerCollisionSegment(basGauche,basDroit,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type != 0)
			{
				if(noeudBalle->obtenirPremierPassageEau() == true)
					noeudBalle->setEstDansEau(true);
				Sound::obtenirInstance()->jouerEau();
				return detail;
			}
			detail = aidecollision::calculerCollisionSegment(hautGauche,hautDroit,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type != 0)
			{
				if(noeudBalle->obtenirPremierPassageEau() == true)
					noeudBalle->setEstDansEau(true);
				Sound::obtenirInstance()->jouerEau();
				return detail;
			}
			detail = aidecollision::calculerCollisionSegment(hautDroit,basDroit,noeudBalle->obtenirPositionRelative(),noeudBalle->obtenirRayon(),true);
			if(detail.type != 0)
			{
				if(noeudBalle->obtenirPremierPassageEau() == true)
					noeudBalle->setEstDansEau(true);
				Sound::obtenirInstance()->jouerEau();
				return detail;
			}

		}

	}

	//noeudBalle->assignerTeleported(false);
	return detail;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double GestionBalle::obtenirAngleAlea()
///
/// Cette fonction retourne l'angle Aleatoire en utilisation pour la balle
///
/// @return la valeur de l'angle aleatoire
///
////////////////////////////////////////////////////////////////////////
 double GestionBalle::obtenirAngleAlea() 
{
	return angleAleatoire_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn static void GestionBalle::modifierAngleAlea(const double AngleAlea)
///
/// Cette fonction modifie l'angle Aleatoire en utilisation pour la balle
///
/// @return NILL
///
////////////////////////////////////////////////////////////////////////
 void GestionBalle::modifierAngleAlea(double AngleAlea)
{
	angleAleatoire_=AngleAlea;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn static void GestionBalle::reSeedAlea()
///
/// Appel pour reseeder la valeur aleatoire de l'angle pour tourner lorsque l'on frappe trop fort.
///
/// @return NILL
///
////////////////////////////////////////////////////////////////////////
void GestionBalle::reSeedAlea()
{
	angleAleatoire_=((double (rand()) / double(RAND_MAX)) * (utilitaire::PI/4 + utilitaire::PI/4)) - utilitaire::PI/4;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn static void GestionBalle::allowDeviation()
///
/// Appel pour permettre d'applique l'angle aleatoire a nouveau.
///
/// @return NILL
///
////////////////////////////////////////////////////////////////////////
void GestionBalle::allowDeviation()
{
	allowDeviation_=true;
}
