///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBordure.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBordure.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* NoeudBordure::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBordure::NoeudBordure(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBordure::NoeudBordure(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
    
	
	// Création d'une liste d'affichage pour toutes les instances du noeud Bordure
   if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_BORDURE) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/murtest.obj");
		modele_->assignerFacteurAgrandissement(1);
		
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_BORDURE);

		modele_->dessiner();		
		glEndList(); 
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBordure::~NoeudBordure()
///
/// Ce destructeur désallouee la liste d'affichage du bordure.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBordure::~NoeudBordure()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBordure::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBordure::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
	//Vecteur3 basGauche,hautGauche,basDroit,hautDroit;

	//if( 0.0 <= rotationObjet_ && rotationObjet_ <= 90.0)
	//{
	//	basGauche[0] = coinBordureMin_[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basGauche[1] = coinBordureMin_[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_));			
	//	basDroit[0] = coinBordureMax_[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basDroit[1] = coinBordureMax_[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautGauche[0] = coinBordureMin_[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautGauche[1] = coinBordureMin_[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautDroit[0] = coinBordureMax_[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautDroit[1] = coinBordureMax_[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_));
	//}

	//if(90.0 < rotationObjet_ && rotationObjet_ <= 180.0)
	//{
	//	hautGauche[0] = coinBordureMin_[0] - 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautGauche[1] = coinBordureMin_[1] - 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));			
	//	hautDroit[0]  = coinBordureMax_[0] - 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautDroit[1]  = coinBordureMax_[1] - 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basGauche[0]  = coinBordureMin_[0] + 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basGauche[1]  = coinBordureMin_[1] + 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));			
	//	basDroit[0]   = coinBordureMax_[0] + 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basDroit[1]   = coinBordureMax_[1] + 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationObjet_));

	//}

	//if(-180 < rotationObjet_ && rotationObjet_ <= -90)
	//{
	//	hautGauche[0] = coinBordureMin_[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);
	//	hautGauche[1] = coinBordureMin_[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);			
	//	hautDroit[0]  = coinBordureMax_[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);
	//	hautDroit[1]  = coinBordureMax_[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);
	//	basGauche[0]  = coinBordureMin_[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);
	//	basGauche[1]  = coinBordureMin_[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);			
	//	basDroit[0]   = coinBordureMax_[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);
	//	basDroit[1]   = coinBordureMax_[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationObjet_) + utilitaire::PI);

	//}

	//if(-90 < rotationObjet_ && rotationObjet_ < 0)
	//{
	//	basGauche[0] = coinBordureMin_[0] - 2.5*sin(-utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basGauche[1] = coinBordureMin_[1] - 2.5*cos(-utilitaire::DEG_TO_RAD(rotationObjet_));			
	//	basDroit[0] = coinBordureMax_[0] - 2.5*sin(-utilitaire::DEG_TO_RAD(rotationObjet_));
	//	basDroit[1] = coinBordureMax_[1] - 2.5*cos(-utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautGauche[0] = coinBordureMin_[0] + 2.5*sin(-utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautGauche[1] = coinBordureMin_[1] + 2.5*cos(-utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautDroit[0] = coinBordureMax_[0] + 2.5*sin(-utilitaire::DEG_TO_RAD(rotationObjet_));
	//	hautDroit[1] = coinBordureMax_[1] + 2.5*cos(-utilitaire::DEG_TO_RAD(rotationObjet_));

	//}
	//basGauche[2] = 0.0;
	//hautDroit[2] = 2.5;
	//coinMin = basGauche;
	//coinMax = hautDroit;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn  void NoeudBordure::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBordure::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	modele_->assignerFacteurAgrandissement(factEchelle_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBordure::AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
///
/// Cette Fonction assigne les points de la bordure
///
/// @param[in] p1 : premier point
/// @param[in] p2 : premier point
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBordure::AssignerDonnes(Vecteur3 p1, Vecteur3 p2)
{

	////Calcul de l'angle de rotation
	float x, y, hyp, objLength;
	x = abs(p1[0] - p2[0]);
	y = abs(p1[1] - p2[1]);
	Vecteur3 coinMin, coinMax, pos;
	float rot;
	rot = atan(y/x)* 180 / 3.14159265;
	if(p1[0]>p2[0])
	{
		rot = 180-rot;
	} 
	if(p1[1]>p2[1])
	{
		rot = -rot;
	}

	rotationObjet_ = rot;
	
	///Calcul facteur agrandissement
	hyp = sqrtf(x*x+y*y);
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
	objLength = abs(coinMax[0] - coinMin[0]);
	
	factEchelle_ = hyp / objLength;
	//factEchelle_ = hyp / objLength/9;

	///Assigner position relative
	pos[0] = (p1[0]-p2[0])/2;
	pos[1] = (p1[1]-p2[1])/2;
	pos[2] = 0;
	assignerPositionRelative(p1);
	assignerPositionInitiale(p1);
	assignerFacteurAgrandissement(factEchelle_);
	//vrais coins
	coinBordureMin_ = p1;
	coinBordureMax_ = p2;
	distanceP1P2_ = p2 - p1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBordure::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBordure::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();
	glTranslatef(0,0,2.0);
    if(this->estSelectionne())
	{
		 glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
	   glDepthMask(false);                               //Disable du buffer depthmask

		glEnable(GL_STENCIL_TEST);                        //Enable Stencil test
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDepthMask(true);

		glScalef(factEchelle_, 3, 3);
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BORDURE); 

	    glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);


		Vecteur3 point, point2;
	    modele_->calculerBoiteEnglobante(point, point2);
		glEnable(GL_BLEND);
		glColor4f(1,0,0,0.5);
	    glBegin(GL_QUADS);						
		glVertex3d(point[0]*factEchelle_*2, point2[1]*factEchelle_, 2.0);		
		glVertex3d(point[0]*factEchelle_*2,point[1]*factEchelle_, 2.0);		
		glVertex3d(point2[0]*factEchelle_*2,point[1]*factEchelle_, 2.0);
		glVertex3d(point2[0]*factEchelle_*2,point2[1]*factEchelle_, 2.0);
	    glEnd();
		glDisable(GL_STENCIL_TEST);
		
	}
	else
	{
	   glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
	   glScalef(factEchelle_, 3, 3);
		// Affichage du modèle.
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BORDURE);
	}
	
   glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBordure::calculerCoinsBordure(Vecteur3& coinBordureMin,Vecteur3& coinBordureMax)
///
/// Cette fonction calcule les vrais coins de la bordure
///
/// @param coinBordureMin : le coin min de la bordure
/// @param coinBordureMax : le coin max de la bordure
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBordure::calculerCoinsBordure(Vecteur3& coinBordureMin,Vecteur3& coinBordureMax)
{
	coinBordureMin = coinBordureMin_;
	coinBordureMax = coinBordureMax_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudBordure::obtenirCoinBordureMin() const
///
/// Cette fonction retourne le coin min de la bordure
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudBordure::obtenirCoinBordureMin() const
{
	return coinBordureMin_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudBordure::obtenirCoinBordureMax() const
///
/// Cette fonction retourne le coin min de la bordure
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudBordure::obtenirCoinBordureMax() const
{
	return coinBordureMax_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBordure::assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax)
///
/// Cette fonction assigne les coins de la bordure
/// 
/// @param coinMin : le coin min du bordure
/// @param coinMax : le coin max du bordure
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBordure::assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax)
{
	if(coinMax.estNul() == true)
		coinBordureMax_ = distanceP1P2_ +  coinMin;
	else
		coinBordureMax_ = coinMax;
	coinBordureMin_ = coinMin;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////