///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBonus.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBonus.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* NoeudBonus::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::NoeudBonus(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonus::NoeudBonus(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
    factEchelle_ = 1;
	
	// Création d'une liste d'affichage pour toutes les instances du noeud Bonus
	if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_BONUS) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/bonus.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_BONUS);

		modele_->dessiner();		
		glEndList(); 
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::~NoeudBonus()
///
/// Ce destructeur désallouee la liste d'affichage du bonus.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonus::~NoeudBonus()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonus::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonus::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	modele_->assignerFacteurAgrandissement(factEchelle_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonus::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();
	
    if(this->estSelectionne())
	{
		glColorMask(1,0,0,0.85); 
		glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
		glScalef(factEchelle_, factEchelle_, factEchelle_);
		// Affichage du modèle.
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BONUS);
		glColorMask(1,1,1,0.0); 
	}
	else
	{
		glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
		glScalef(factEchelle_, factEchelle_, factEchelle_);
		// Affichage du modèle.
		//glCallList(liste_);
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BONUS);
	}
	
   glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudBalle::animer(float temps)
///
/// Cette fonction met a jour la position de la balle
/// dependament de la vitesse
///
/// @param temps : temps pour l'animation
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::animer(float temps)
{
	rotationObjet_++;
	if(rotationObjet_>360)
		rotationObjet_ = 0;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
