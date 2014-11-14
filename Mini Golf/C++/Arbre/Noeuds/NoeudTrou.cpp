///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTrou.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTrou.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* NoeudTrou::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTrou::NoeudTrou(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTrou::NoeudTrou(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
   factEchelle_ = 1;
   
   // Création d'une liste d'affichage pour toutes les instances du noeud Trou
    if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_TROU) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/newTrou.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_TROU);

		modele_->dessiner();		
		glEndList(); 
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTrou::~NoeudTrou()
///
/// Ce destructeur désallouee la liste d'affichage du trou.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTrou::~NoeudTrou()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTrou::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTrou::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTrou::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudTrou::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
//	modele_->assignerFacteurAgrandissement(factEchelle_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTrou::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTrou::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();

    if(this->estSelectionne())
	{
		glColorMask(1,1,0.1,1); 
		glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
		
		
		glScalef(factEchelle_, factEchelle_, factEchelle_);

		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_TROU);
		
		glColorMask(1,1,1,0);
		
	}
	else
	{
		glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
		glScalef(factEchelle_, factEchelle_, factEchelle_);
		// Affichage du modèle.
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_TROU);
	}
	
   glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////