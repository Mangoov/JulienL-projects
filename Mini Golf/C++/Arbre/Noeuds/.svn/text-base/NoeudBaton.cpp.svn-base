///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBaton.cpp
/// @author Jean-Luc Dubeau
/// @date 2011-10-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBaton.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* NoeudBaton::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBaton::NoeudBaton(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBaton::NoeudBaton(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
    
    factEchelle_ = 1;
	batonPret_ = false;
	
	// Création d'une liste d'affichage pour toutes les instances du noeud Baton
	if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_BATON) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/baton.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_BATON);

		modele_->dessiner();		
		glEndList(); 
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBaton::~NoeudBaton()
///
/// Ce destructeur désallouee la liste d'affichage du baton.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBaton::~NoeudBaton()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBaton::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBaton::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBaton::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBaton::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	modele_->assignerFacteurAgrandissement(factEchelle_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBaton::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBaton::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();
   
   glRotatef(90,0,0,1);
   float angle;
   angle = (factEchelle_/10) * 90;
   glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
	glTranslatef(0,-6.5,0);
	//glTranslatef(0,0,47);
	glTranslatef(0,0,63);
	glRotatef(-angle, 1, 0.0, 0);
	//glTranslatef(0,0,-47);
	glTranslatef(0,0,-63);
   glScalef(1, 1, 0.70);
   // Affichage du modèle.
   GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_BATON);
	
   glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBaton::animer(float temps)
///
/// Cette fonction met a jour la position du baton
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudBaton::animer(float temps)
{
	//if(batonPret_ == false)
	//{
	//	float force = 2000*factEchelle_;
	//	vitTemps = force / 5 * 0.02 ; //v = 0 + a*t  et a = F/m : 5 = masse, 0.02 = dt
	//}
	
	if(factEchelle_ <= 0)
	{
		batonPret_ = false;
	/*	NoeudAbstrait* noeud = this;
		do
		{
			noeud = noeud->obtenirParent();
		}while(noeud->obtenirType() != "racine");
		noeud = noeud->chercher("balle");
		float angle = 180 + rotationObjet_;
		noeud ->initialiserVitesse(angle, vitTemps);
		}*/}
	if(batonPret_ == true && factEchelle_ > 0)
	{
		factEchelle_ -= 0.5;
		if(factEchelle_<0)
		{
			factEchelle_ = 0;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
