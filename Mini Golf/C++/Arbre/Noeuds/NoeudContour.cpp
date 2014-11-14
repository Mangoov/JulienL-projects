///////////////////////////////////////////////////////////////////////////////
/// @file NoeudContour.cpp
/// @author Aiman Badr Jaouhar
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudContour.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* NoeudContour::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudContour::NoeudContour(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudContour::NoeudContour(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) 
{
    
	

   if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_CONTOUR) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/contour.obj");
		modele_->assignerFacteurAgrandissement(1);
		
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_CONTOUR);

		modele_->dessiner();		
		glEndList(); 
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudContour::~NoeudContour()
///
/// Ce destructeur désallouee la liste d'affichage du bordure.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudContour::~NoeudContour()
{
   //glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudContour::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
///
/// Appel a le calcul de la boite de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudContour::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn  void NoeudContour::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudContour::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	modele_->assignerFacteurAgrandissement(factEchelle_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudContour::AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
///
/// Cette Fonction assigne les points de la bordure
///
/// @param[in] p1 : premier point
/// @param[in] p2 : premier point
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudContour::AssignerDonnes(Vecteur3 p1, Vecteur3 p2)
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
	pos[2] = -2;
	assignerPositionRelative(p1);

	//vrais coins
	coinBordureMin_ = p1;
	coinBordureMax_ = p2;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudContour::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudContour::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();
   glTranslatef(0,0,-0.2);
    if(this->estSelectionne())
	{
		 glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
	   glDepthMask(false);                               //Disable du buffer depthmask

		glEnable(GL_STENCIL_TEST);                        //Enable Stencil test
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDepthMask(true);

		glScalef(factEchelle_, 3, 3);
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_CONTOUR); 

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
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_CONTOUR);
	}
	
   glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudContour::calculerCoinsBordure(Vecteur3& coinBordureMin,Vecteur3& coinBordureMax)
///
/// Cette fonction calcule les vrais coins de la bordure
///
/// @param coinBordureMin : le coin min de la bordure
/// @param coinBordureMax : le coin max de la bordure
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudContour::calculerCoinsBordure(Vecteur3& coinBordureMin,Vecteur3& coinBordureMax)
{
	coinBordureMin = coinBordureMin_;
	coinBordureMax = coinBordureMax_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudContour::obtenirCoinBordureMin() const
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
Vecteur3 NoeudContour::obtenirCoinBordureMin() const
{
	return coinBordureMin_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudContour::obtenirCoinBordureMax() const
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
Vecteur3 NoeudContour::obtenirCoinBordureMax() const
{
	return coinBordureMax_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudContour::assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax)
///
/// Cette fonction assigne les coins de la bordure
/// 
/// @param coinMin : le coin min de la bordure
/// @param coinMax : le coin max de la bordure
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudContour::assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax)
{
	coinBordureMax_ = coinMax;
	coinBordureMin_ = coinMin;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////