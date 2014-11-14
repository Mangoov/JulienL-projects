///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBalle.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "FacadeModele.h"
#include "GestionJoueur.h"
#include "NoeudBalle.h"
#include "Utilitaire.h"
#include "Sound.h"
#include "GestionListeAffichages.h"
#include "AideCollision.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ConfigScene.h"
Modele3D* NoeudBalle::modele_ = nullptr;
int NoeudBalle::compteurPassageAnimation_ = 0; 
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBalle::NoeudBalle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBalle::NoeudBalle(const std::string& typeNoeud)
	: NoeudComposite(typeNoeud) //, liste_(0xffffffff) 
{

	factEchelle_= 1;
	charger_ = false;
	frappee_ = false;
	tomber_ = true;		
	estDansTrou_ = false;
	estDansEau_ = false;
	facteurForce_ = 0;
	tempsBonus_  = 0;
	vitesseAvantBonus_= 0;
	BonusActive_ = false;
	teleported_ = false;
	countdown_ = -1;
	collisionTrou_ = false;
	nbCout_=0;
	fireworks_ = false;
	vitesse_ = 0;
	normale_ = 0;
	impact_ = 0;
	premierPassageEau_ = true;
	rayon_ = 3.6;
	masse_ = 5;
	coefFriction_ = 0;
	coefRebondMur_ = 0.95;
	ancienDeltaS_ = 0;
	tempsCourant_ = 0;
	tempsPermisEau_ = 0;
	// Création d'une liste d'affichage pour toutes les instances du noeud Balle
	if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_BALLE) )
	{
		
		modele_ = new Modele3D();
		modele_->charger("media/newBalle.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_BALLE);

		modele_->dessiner();		
		glEndList(); 
	}							
	initialiserVitesse(0,0.0);	
	roule_ = false;				
	angleX_ = 0;		

	compteur_ = 0;
	test_ = false;

	if(particle[0][0] == 0)	//Vecteur initialement vide
   {
	   for(int i = 0; i <1000; i++)
	   {
		    particle[i][0] = rand() %100 ;
			particle[i][1] = 0;
			particle[i][2] = 0;
			particle[i][3] = 0;
			particle[i][4] = randomNumber() * NegPos()*60;
			particle[i][5] = randomNumber() * NegPos()*60;
			particle[i][6] = randomNumber() * NegPos()*60;
			//colors
			particle[i][7] = randomNumber();
			particle[i][8] = randomNumber();
			particle[i][9] = randomNumber();
	   }
   }
}

float NoeudBalle::randomNumber()
{
	float random = rand()%1000;
	random = random/1000;
	return random;
}
int NoeudBalle::NegPos()
{
	int NegPos = rand()%2;
		if(NegPos == 0)
			NegPos = -1;
		else
			NegPos = 1;
		return NegPos;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBalle::~NoeudBalle()
///
/// Ce destructeur désallouee la liste d'affichage de la balle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBalle::~NoeudBalle()
{
	//glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBalle::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void void NoeudBalle::assignerCollisionTrou(bool trou)
///
/// Assigne la valeur de la collision du trou
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::assignerCollisionTrou(bool trou)
{
	collisionTrou_ = trou;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	modele_->assignerFacteurAgrandissement(factEchelle_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::initialiserVitesse(float angle, float vitesse)
///
/// Cette fonction permet d'assigner la vitesse initiale a la balle
///
/// @param angle : L'angle de la frappe
/// @param vitesse : vitesse de la frappe
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::initialiserVitesse(double angle, double vitesse)
{
	positionInitiale_ = positionRelative_;
	nbCout_++;
	assignerForce(vitesse);
	assignerAngleCoup(angle);
	vitesse_[0] = vitesse * cos(utilitaire::DEG_TO_RAD(angle));
	vitesse_[1] = vitesse * sin(utilitaire::DEG_TO_RAD(angle));
	roule_ = true;
	
	//rayon_ = 1.8;
	rayon_ = 3.6;
	masse_ = 5;
	coefFriction_ = 0;
	coefRebondMur_ = 0.95;
	deltaS_ = Vecteur3(0,0,0);
	//vitesse_ = Vecteur3(0,0,0);
	premierPassageEau_ = true;
	tempsCourant_ = tempsPrecedent_ = 0;

	normale_ = Vecteur3(positionRelative_[0],positionRelative_[1],2*rayon_);
	normale_.normaliser(); 
	impact_ = Vecteur3(vitesse_[0],vitesse_[1],vitesse_[2]);
	impact_.normaliser();
	//normale_ = Vecteur3(positionRelative_[0],positionRelative_[1],2*rayon_);
	//normale_.normaliser(); 
	//impact_ = Vecteur3(vitesse_[0],vitesse_[1],vitesse_[2]);
	//impact_.normaliser();
	//axeRotation_ = produitVectoriel(normale_,impact_); // r = n X v
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBalle::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::afficherConcret() const
{

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.													
	glPushMatrix();
	glTranslatef(0,0,3.8);
	//faire tourner la balle autour d'elle même

	glRotated(angleX_ * (360.0/utilitaire::PI), axeRotation_[0],axeRotation_[1],0);

	if(countdown_ == -1 || countdown_>7)
	{
		if(this->estSelectionne())
		{

			glColorMask(1,0,0,1.0); 
			//glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
			glScalef(factEchelle_, factEchelle_, factEchelle_);
			// Affichage du modèle.
			GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BALLE);
			glColorMask(1,1,1,0); 
		}
		else
		{
			//glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
			glScalef(factEchelle_, factEchelle_, factEchelle_);
			// Affichage du modèle.
			GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BALLE);
		}
	}

	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	if(countdown_<7)
	{
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glPointSize(2);
		glBegin(GL_POINTS);
		for(int i = 0; i <1000; i++)
		{
			glColor3f(particle[i][7], particle[i][8], particle[i][9]);
			glVertex3f(particle[i][1], particle[i][2], particle[i][3]);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBalle::checkBaton()
///
/// Cette check le baton
///
/// @return true/false.
///
////////////////////////////////////////////////////////////////////////
bool NoeudBalle::checkBaton()
{
	NoeudAbstrait* noeud = this;
	do
	{
		noeud = noeud->obtenirParent();
	}while(noeud->obtenirType() != "racine");

	noeud = noeud->chercher("baton");
	if(noeud != nullptr)
	{
		if(noeud->obtenirFacteurAgrandissment() <= 0)
		{
			return true;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBalle::obtenirTeleported()
///
/// Retourne si la balle a ete teleported sur ce coup
///
/// @return true/false.
///
////////////////////////////////////////////////////////////////////////
bool NoeudBalle::obtenirTeleported()
{
	return teleported_;
}

void NoeudBalle::assignerCountdown(float count)
{
	countdown_ = count;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBalle::assignerTeleported(bool teleported)
///
/// Assigne si la balle a ete teleported
///
/// @return true/false.
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::assignerTeleported(bool teleported)
{
	teleported_ = teleported;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBalle::checkFacteurFriction()
///
/// Cette fonction verifie sur quelle surface nous sommes
/// Et applique le coefficient de friction en consequences
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
bool NoeudBalle::checkFacteurFriction()
{
	unsigned int compteurObstacle = 0;
	NoeudAbstrait* noeud = this;
	do
	{
		noeud = noeud->obtenirParent();
	}while(noeud->obtenirType() != "racine");

	Vecteur3  min, max, posRelativeSable;
	Vecteur3 positionXmax(positionRelative_[0] + 500,positionRelative_[1],positionRelative_[2]);
	//float facteur;
	//coord = this->obtenirFacteurAgrandissment();
	for(unsigned int i = 0; i<noeud->obtenirNombreEnfants(); i++)
	{
		if(noeud->chercher(i)->obtenirType() == "sable" )
		{
			noeud->chercher(i)->calculerBoite(min, max);
			posRelativeSable = noeud->chercher(i)->obtenirPositionRelative();
			float rotationSable = noeud->chercher(i)->obtenirRot();
			//coin haut gauche
			Vecteur3 hautGauche(posRelativeSable[0] - utilitaire::ABS( (float)min[0]),posRelativeSable[1] + utilitaire::ABS( (float)max[1]),0);
			//coin bas droit
			Vecteur3 basDroit(posRelativeSable[0] + utilitaire::ABS( (float)max[0]),posRelativeSable[1] - utilitaire::ABS( (float)(min[1])),0);
			//coin bas gauche
			Vecteur3 basGauche(posRelativeSable[0] - utilitaire::ABS( (float)min[0]),posRelativeSable[1] - utilitaire::ABS( (float)min[1]),0);
			//coin haut droit
			Vecteur3 hautDroit(posRelativeSable[0] + utilitaire::ABS( (float)max[0]),posRelativeSable[1] + utilitaire::ABS( (float)max[1]),0);

			if(rotationSable != 0.0f){
				float Cos = cos(utilitaire::DEG_TO_RAD(-rotationSable));
				float Sin = sin(utilitaire::DEG_TO_RAD(-rotationSable));

				float basGauche0 = posRelativeSable[0]+(basGauche[0]-posRelativeSable[0])*Cos+(basGauche[1]-posRelativeSable[1])*Sin;
				float basGauche1 = posRelativeSable[1]-(basGauche[0]-posRelativeSable[0])*Sin+(basGauche[1]-posRelativeSable[1])*Cos;
				basGauche[0] = basGauche0;
				basGauche[1] = basGauche1;


				float basDroit0 = posRelativeSable[0]+(basDroit[0]-posRelativeSable[0])*Cos+(basDroit[1]-posRelativeSable[1])*Sin;
				float basDroit1 = posRelativeSable[1]-(basDroit[0]-posRelativeSable[0])*Sin+(basDroit[1]-posRelativeSable[1])*Cos;
				basDroit[0] = basDroit0;
				basDroit[1] = basDroit1;


				float hautGauche0 = posRelativeSable[0]+(hautGauche[0]-posRelativeSable[0])*Cos+(hautGauche[1]-posRelativeSable[1])*Sin;
				float hautGauche1 = posRelativeSable[1]-(hautGauche[0]-posRelativeSable[0])*Sin+(hautGauche[1]-posRelativeSable[1])*Cos;
				hautGauche[0] = hautGauche0;
				hautGauche[1] = hautGauche1;

				float hautDroit0 = posRelativeSable[0]+(hautDroit[0]-posRelativeSable[0])*Cos+(hautDroit[1]-posRelativeSable[1])*Sin;
				float hautDroit1 = posRelativeSable[1]-(hautDroit[0]-posRelativeSable[0])*Sin+(hautDroit[1]-posRelativeSable[1])*Cos;
				hautDroit[0] = hautDroit0;
				hautDroit[1] = hautDroit1;
			}

			if(checkCollision2Segments(positionRelative_, positionXmax,hautGauche,hautDroit) == true)
			{
				compteurObstacle++;
			}
			if(checkCollision2Segments(positionRelative_, positionXmax,hautGauche,basGauche) == true)
			{
				compteurObstacle++;
			}
			if(checkCollision2Segments(positionRelative_, positionXmax,basGauche,basDroit) == true)
			{
				compteurObstacle++;
			}
			if(checkCollision2Segments(positionRelative_, positionXmax,basDroit,hautDroit) == true)
			{
				compteurObstacle++;
			}

			if(compteurObstacle % 2 != 0)
			{
				Sound::obtenirInstance()->jouerSable();
				double fricSable = ConfigScene::obtenirInstance()->obtenirCoefFriSable();
				if(coefFriction_ != fricSable){
					coefFriction_ = fricSable;
					return true;
				}
				else{
					coefFriction_ = fricSable;
					return false;
				}
			}
			else
				compteurObstacle = 0;
		}
		//if(noeud->chercher(i)->obtenirType() == "sable")
		//{
		//	noeud->chercher(i)->calculerBoite(min, max);
		//	posRelativeSable = noeud->chercher(i)->obtenirPositionRelative();
		//	float rotationSable = noeud->chercher(i)->obtenirRot();
		//	//coin haut gauche
		//	Vecteur3 hautGauche(posRelativeSable[0] - utilitaire::ABS( (float)min[0]),posRelativeSable[1] + utilitaire::ABS( (float)max[1]),0);
		//	//coin bas droit
		//	Vecteur3 basDroit(posRelativeSable[0] + utilitaire::ABS( (float)max[0]),posRelativeSable[1] - utilitaire::ABS( (float)(min[1])),0);
		//	//coin bas gauche
		//	Vecteur3 basGauche(posRelativeSable[0] - utilitaire::ABS( (float)min[0]),posRelativeSable[1] - utilitaire::ABS( (float)min[1]),0);
		//	//coin haut droit
		//	Vecteur3 hautDroit(posRelativeSable[0] + utilitaire::ABS( (float)max[0]),posRelativeSable[1] + utilitaire::ABS( (float)max[1]),0);
		//	//segments sable
		//	Vecteur3 segmentDroite = hautDroit - basDroit;
		//	Vecteur3 segmentGauche = hautGauche - basGauche;
		//	Vecteur3 segmentHaut = hautGauche - hautDroit;
		//	Vecteur3 segmentBas = basGauche - basDroit;
		//	if(rotationSable != 0.0f){
		//		float Cos = cos(utilitaire::DEG_TO_RAD(-rotationSable));
		//		float Sin = sin(utilitaire::DEG_TO_RAD(-rotationSable));

		//		float basGauche0 = posRelativeSable[0]+(basGauche[0]-posRelativeSable[0])*Cos+(basGauche[1]-posRelativeSable[1])*Sin;
		//		float basGauche1 = posRelativeSable[1]-(basGauche[0]-posRelativeSable[0])*Sin+(basGauche[1]-posRelativeSable[1])*Cos;
		//		basGauche[0] = basGauche0;
		//		basGauche[1] = basGauche1;


		//		float basDroit0 = posRelativeSable[0]+(basDroit[0]-posRelativeSable[0])*Cos+(basDroit[1]-posRelativeSable[1])*Sin;
		//		float basDroit1 = posRelativeSable[1]-(basDroit[0]-posRelativeSable[0])*Sin+(basDroit[1]-posRelativeSable[1])*Cos;
		//		basDroit[0] = basDroit0;
		//		basDroit[1] = basDroit1;


		//		float hautGauche0 = posRelativeSable[0]+(hautGauche[0]-posRelativeSable[0])*Cos+(hautGauche[1]-posRelativeSable[1])*Sin;
		//		float hautGauche1 = posRelativeSable[1]-(hautGauche[0]-posRelativeSable[0])*Sin+(hautGauche[1]-posRelativeSable[1])*Cos;
		//		hautGauche[0] = hautGauche0;
		//		hautGauche[1] = hautGauche1;

		//		float hautDroit0 = posRelativeSable[0]+(hautDroit[0]-posRelativeSable[0])*Cos+(hautDroit[1]-posRelativeSable[1])*Sin;
		//		float hautDroit1 = posRelativeSable[1]-(hautDroit[0]-posRelativeSable[0])*Sin+(hautDroit[1]-posRelativeSable[1])*Cos;
		//		hautDroit[0] = hautDroit0;
		//		hautDroit[1] = hautDroit1;
		//	}


		//	/*if(aidecollision::calculerCollisionSegment(basGauche,hautGauche,positionRelative_,rayon_,true).type!= 0
		//		||aidecollision::calculerCollisionSegment(basGauche,basDroit,positionRelative_,rayon_,true).type!= 0
		//		||aidecollision::calculerCollisionSegment(hautGauche,hautDroit,positionRelative_,rayon_,true).type!= 0
		//		||aidecollision::calculerCollisionSegment(hautDroit,basDroit,positionRelative_,rayon_,true).type!= 0)
		//	{*/

		//		Sound::obtenirInstance()->jouerSable();
		//		double fricSable = ConfigScene::obtenirInstance()->obtenirCoefFriSable();
		//		if(coefFriction_ != fricSable){
		//			coefFriction_ = fricSable;
		//			return true;
		//		}
		//		else{
		//			coefFriction_ = fricSable;
		//			return false;
		//		}
		//	//}	
		//}

	}
	double fricTerrain = ConfigScene::obtenirInstance()->obtenirCoefFriSol();
	if(coefFriction_ != fricTerrain)
	{
		coefFriction_ = fricTerrain;
		return true;
	}
	else
	{
		coefFriction_ = fricTerrain;
		return false;
	}

}



////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudBalle::animer(float temps)
///
/// Cette fonction met a jour la position de la balle
/// dependament de la vitesse
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::animer(float temps)
{
	
	if(FacadeModele::obtenirInstance()->getMode() && compteurPassageAnimation_ == 0)
	{
		if(tomber_ && roule_ == false) 
		{
			if(test_ == false)
			{
				if(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] > 500)
				{
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerZ(2,false);

				}
				if(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] > 300 && FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] <= 500)
				{
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerZ(7,false);
					if((FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] > 300) == false)
						test_ = true;
				}
			}
			else
			{

				if(compteur_ < 120){
					compteur_ += 3;
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(3,0);
				}
				else if(compteur_ >= 120 && compteur_ < 150)
				{
					compteur_ += 0.5;
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(0.5,0);
				}
				else if(compteur_ >= 150 && compteur_ < 210)
				{
					compteur_ += 3;
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(3,0);
				}
				else if(compteur_ >= 210 && compteur_ < 240)
				{
					compteur_ += 0.5;
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(0.5,0);
				}
				else if(compteur_ >= 240 && compteur_ < 330)
				{
					compteur_ += 3;
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(3,0);
				}
				else if(compteur_ >= 330 && compteur_ < 360)
				{
					compteur_ += 0.5;
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(0.5,0);


				}
				else if(compteur_ >= 360)
				{	
					if(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] < 600)
					{
						FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerZ(-10,false);
						if((FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] < 600) == false)
						{
							tomber_ = false;
							compteurPassageAnimation_++;
						}
					}
				}

			}
		}
		
	}

	if(FacadeModele::obtenirInstance()->obtenirDistanceBalleTrou() < 40 && roule_ == true)
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().animation(this->obtenirPositionRelative());
	

	if(  FacadeModele::obtenirInstance()->obtenirDistanceBalleTrou() > 40 && roule_ == true)
	{
		
		if(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] >= 40 && FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] < 200 )
			FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerZ(-3,false);
	}
	else if (  FacadeModele::obtenirInstance()->obtenirDistanceBalleTrou() < 40 && roule_ == false)
	{
		if(FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().obtenirPosition()[2] < 200 )
			FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerZ(-3,false);
	}

	if(countdown_ == 11&&nbCout_ == 2)
		Sound::obtenirInstance()->jouerHoleInOne();
	if(countdown_> 7 )
	{

		positionRelative_[2] += 1;
		countdown_-=(temps*2);
	}
	if(countdown_ <= 7 && countdown_>-1)
	{
		if(countdown_ >= 5.5 && fireworks_ == false)
		{
			Sound::obtenirInstance()->jouerFeuArtifices();
			fireworks_ = true;
		}
		for(int i = 0; i <1000; i++)
	   {
		    particle[i][0] -= (temps)*100;
		    particle[i][1] += ( particle[i][4]*(temps));
		    particle[i][2] += ( particle[i][5]*(temps));
		    particle[i][3] += ( particle[i][6]*(temps));
		    particle[i][6] -= (40*(temps));

		   if( particle[i][0] <= 0)				//Cas ou particule meurt
		   {
			particle[i][0] = rand() %100 ;
			particle[i][1] = 0;
			particle[i][2] = 0;
			particle[i][3] = 0;
			particle[i][4] = randomNumber() * NegPos()*60;
			particle[i][5] = randomNumber() * NegPos()*60;
			particle[i][6] = randomNumber() * NegPos()*60;
			//colors
			particle[i][7] = randomNumber();
			particle[i][8] = randomNumber();
			particle[i][9] = randomNumber();
		   }
		}
		countdown_-=(temps*2);
		if(countdown_<-1)
		{
			estDansTrou_ = true;
		}
	}

	if(roule_ == false)
	{
		assignerTeleported(false);
	}
	if(checkBaton())
	{
		
		if(roule_ == true)
		{
			//diminue la performance mais necessaire pour pas faire "snapper" la balle
			axeRotation_ = produitVectoriel(normale_,impact_); // r = n X v  
			if(checkFacteurFriction())
			{
				Friction_ = - impact_;
				ForceFriction_ =   coefFriction_ * masse_ * 6; //  µk * ( -m * (g) ) [g = -6]	
				Friction_ *= ForceFriction_;
			}
			if(tempsCourant_ == 0)
			{
				posRelativeAvantEau_ = positionRelative_;
			}
			tempsCourant_ += temps;
			ancienDeltaS_ = deltaS_;

			deltaS_[0] = (vitesse_[0] * temps) - (0.5 * (Friction_[0]/masse_)*(temps*temps)); //Delta-s = v*dt - 1/2 * Ff/m * (dt)²
			deltaS_[1] = (vitesse_[1] * temps) - (0.5 * (Friction_[1]/masse_)*(temps*temps));
			
			positionRelative_[0] += deltaS_[0]; 
			positionRelative_[1] += deltaS_[1];
			angleX_+= (deltaS_.norme() / (2*utilitaire::PI*rayon_)); // Delta-theta = |Delta-s| / 2*PI*r


			vitesseAvant_ = vitesse_;
			vitesse_[0] = vitesseAvant_[0] + (Friction_[0]/masse_)*temps;//Delta-v = v - Ff/m * t;
			vitesse_[1] = vitesseAvant_[1] + (Friction_[1]/masse_)*temps;

			if(roule_ == false)
			{
				int bullshit = 1;
			}
			aidecollision::DetailsCollision detail  = collisionBalle->checkCollisionBordure(this, temps);
			if(detail.type != 0 && detail.type != 4)
			{
				if(verifierEstDansEau() == false)
				{
					positionRelative_[0] -= deltaS_[0]; 
					positionRelative_[1] -= deltaS_[1];
					tempsCritiqueCollision_ = tempsCourant_;
					vitesse_ = calculerReflexion(vitesse_,detail.direction);
					normale_ = Vecteur3(0,0,2*rayon_);
					normale_.normaliser(); 
					impact_ = Vecteur3(vitesse_[0],vitesse_[1],vitesse_[2]);
					impact_.normaliser();
					axeRotation_ = produitVectoriel(normale_,impact_); // r = n X v
					Friction_ = - impact_;
					ForceFriction_ =   coefFriction_ * masse_ * 6; //  µk * ( -m * (g) ) [g = -6]	
					Friction_ *= ForceFriction_;
					vitesse_*=  (ConfigScene::obtenirInstance()->obtenirCoefRebondMur()) / 100;
					
				}
				else if(premierPassageEau_ == true)
				{
					premierPassageEau_ = false;
					tempsPermisEau_ = tempsCourant_ + 0.1f;
					//posRelativeAvantEau_ = positionRelative_;
					//posRelativeAvantEau_[0] -= deltaS_[0]; 
					//posRelativeAvantEau_[1] -= deltaS_[1];
					
				}
			}
			if(detail.type == 4 && detail.enfoncement >= rayon_ + rayon_/3 &&vitesse_.norme() < 140 && collisionTrou_ == true)
			{
				deltaS_ = Vecteur3(0,0,0);
				vitesse_ = Vecteur3(0,0,0);
				Friction_ = Vecteur3(0,0,0);
				vitesseAvant_ = Vecteur3(0,0,0);				
				roule_ = false;
				
			}

			if((utilitaire::DANS_INTERVALLE(deltaS_[0],-0.06,0.06) && utilitaire::DANS_INTERVALLE(deltaS_[1],-0.06,0.06) ) || ((ancienDeltaS_.estNul()==false  && !utilitaire::DANS_INTERVALLE(tempsCourant_,tempsCritiqueCollision_,tempsCritiqueCollision_ + 0.2) && utilitaire::SIGN(ancienDeltaS_[0]) != utilitaire::SIGN(deltaS_[0]) && utilitaire::SIGN(ancienDeltaS_[1]) != utilitaire::SIGN(deltaS_[1]))) )
			{
				deltaS_ = Vecteur3(0,0,0);
				vitesse_ = Vecteur3(0,0,0);
				Friction_ = Vecteur3(0,0,0);
				vitesseAvant_ = Vecteur3(0,0,0);				
				roule_ = false;				
				GestionJoueur::obtenirInstance()->sauvegarderMultijoueur(FacadeModele::obtenirInstance()->obtenirMapCourante());
				
			}

			tempsPrecedent_ = tempsCourant_; 

			if(tempsCourant_ >= tempsPermisEau_ && tempsPermisEau_ > 0)
			{
				setEstDansEau(false);
				tempsPermisEau_= 0;
				//setEstDansEau(false);
				deltaS_ = Vecteur3(0,0,0);
				vitesse_ = Vecteur3(0,0,0);
				Friction_ = Vecteur3(0,0,0);
				vitesseAvant_ = Vecteur3(0,0,0);
				positionRelative_ = posRelativeAvantEau_;
				roule_ = false;
				GestionJoueur::obtenirInstance()->sauvegarderMultijoueur(FacadeModele::obtenirInstance()->obtenirMapCourante());
				
			}
		}
		if(roule_ == false)
		{
			int bullshit = 1;
		}
	}
	if(FacadeModele::obtenirInstance()->obtenirModeReplay() == true && roule_ == false)
	{
		FacadeModele::obtenirInstance()->assignerModeReplay(false);
	}

	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBalle::obtenirRayon() const
///
/// Cette fonction retourne le rayon de la balle
///
/// @return rayon
///
////////////////////////////////////////////////////////////////////////
double NoeudBalle::obtenirRayon() const
{
	return rayon_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudBalle::obtenirVitesse() const
///
/// Cette fonction retourne la vitesse de la balle
///
/// @return vitesse
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudBalle::obtenirVitesse() const
{
	return vitesse_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBalle::obtenirtempsBonus()
///
/// Cette fonction retourne si le temps du bonus
///
/// @return bool si bonus active
///
////////////////////////////////////////////////////////////////////////
float NoeudBalle::obtenirtempsBonus()
{
	return tempsBonus_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBalle::ModifierTempsBonus() const
///
/// Cette fonction permet d'activer le bonus
///

/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::ModifierTempsBonus(float temps)
{
	tempsBonus_ = temps;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBalle::obtenirVitesseAvantBonus() const
///
/// Cette fonction permet de retourner la vitesse avant le bonus
///

/// @return vitesse avant le bonus
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudBalle::obtenirVitesseAvantBonus()
{
	return vitesseAvantBonus_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBalle::obtenirVitesseAvantBonus() const
///
/// Cette fonction permet de retourner la vitesse avant le bonus
///

/// @return vitesse avant le bonus
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::setVitesseAvantBonus(Vecteur3 vitesse)
{
	vitesseAvantBonus_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBalle::modifierVitesse(Vecteur3 vitesse) 
///
/// Cette fonction retourne la vitesse de la balle
///
/// @return vitesse
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::modifierVitesse(Vecteur3 vitesse) 
{
	vitesse_[0] = vitesse[0];
	vitesse_[1] = vitesse[1];
	vitesse_[2] = vitesse[2];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBalle::charger()
///
/// Cette fonction commence a charger le vecteur force
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::charger()
{
	if ((vitesse_[0]==0) && (vitesse_[1]==0))
	{
		charger_ = true;
		facteurForce_ = 0;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBalle::charger()
///
/// Cette fonction relache la balle, convertissant le vecteur force en vitesse
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void NoeudBalle::lacher()
{
	tomber_ = true;
	test_ = false;
	compteur_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


