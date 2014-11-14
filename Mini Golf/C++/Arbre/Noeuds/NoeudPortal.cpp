///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPortal.cpp
/// @author Julien Lapointe
/// @date 2011-11-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPortal.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* NoeudPortal::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortal::NoeudPortal(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortal::NoeudPortal(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
   factEchelle_ = 1;
   portalPowered_ = true;
    if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_PORTALBLEU) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/portalBleu.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_PORTALBLEU);

		
		modele_->dessiner();		
		glEndList(); 
	}
	if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_PORTALORANGE) )
	{
		modele_->charger("media/portalOrange.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_PORTALORANGE);
		modele_->dessiner();
		glEndList(); 
	 }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortal::~NoeudPortal()
///
/// Ce destructeur désallouee la liste d'affichage du trou.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortal::~NoeudPortal()
{
   glDeleteLists(liste_, 1);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortal::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortal::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortal::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudPortal::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
//	modele_->assignerFacteurAgrandissement(factEchelle_);
}

void NoeudPortal::AssignerDonnes(Vecteur3 p1, Vecteur3 p2)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortal::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortal::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();
   glTranslatef(0,0,6.0);
   if(portalType_==true)
	{
		if(this->estSelectionne())
		{
			glColorMask(1,0,1,0.45); 
			glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
			// Affichage du modèle.
			GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_PORTALBLEU);
			glColorMask(1,1,1,0); 
		}
		else
		{
			glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
			// Affichage du modèle.
			GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_PORTALBLEU);
		}
   }
	else
	{
		if(this->estSelectionne())
		{
			glColorMask(1,0.35,0,0.95); 
			glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
			// Affichage du modèle.
			GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_PORTALORANGE);
			glColorMask(1,1,1,0); 
		}
		else
		{
			glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
			// Affichage du modèle.
			GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_PORTALORANGE);
		}
	}
	
   glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudPortal::animer(float temps)
///
/// Cette fonction met a jour la position de la balle
/// dependament de la vitesse
///
/// @param temps : temps pour l'animation
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudPortal::animer(float temps)
{
	rotationObjet_++;
	if(rotationObjet_>360)
		rotationObjet_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////