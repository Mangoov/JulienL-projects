///////////////////////////////////////////////////////////////////////////////
/// @file Noeudfleche.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Noeudfleche.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

Modele3D* Noeudfleche::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn Noeudfleche::Noeudfleche(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Noeudfleche::Noeudfleche(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{

	// Création d'une liste d'affichage pour toutes les instances du noeud Fleche
	if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_FLECHE) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/fleche.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_FLECHE);

		modele_->dessiner();		
		glEndList(); 
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Noeudfleche::~Noeudfleche()
///
/// Ce destructeur désallouee la liste d'affichage du fleche.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Noeudfleche::~Noeudfleche()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Noeudfleche::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Noeudfleche::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn  void Noeudfleche::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Noeudfleche::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	if(factEchelle_ > 10)
		factEchelle_ = 10;
	if(factEchelle_ < 1)
		factEchelle_ = 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Noeudfleche::AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
///
/// Cette Fonction assigne les points de la fleche
///
/// @param[in] p1 : premier point
/// @param[in] p2 : premier point
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Noeudfleche::AssignerDonnes(Vecteur3 p1, Vecteur3 p2)
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
	if(factEchelle_ > 10)
		factEchelle_ = 10;
	///Assigner position relative
	pos[0] = (p1[0]-p2[0])/2;
	pos[1] = (p1[1]-p2[1])/2;
	pos[2] = 0;
	assignerPositionRelative(p1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Noeudfleche::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Noeudfleche::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   
   // Affichage du rectangle de chargement (vide)
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
   glPushMatrix();

   glRotatef(rotationObjet_,0,0,1);
   glTranslatef(0,10,0);
   glPushAttrib(GL_CURRENT_BIT);
   glDisable(GL_LIGHTING); 
   glDisable(GL_TEXTURE_2D);
   glColor3f(0,0,0);
   glBegin(GL_QUADS);
		glVertex3d(-3,0, 1.5);
		glVertex3d(-3,5, 1.5);
		glVertex3d(-30,5, 1.5);
		glVertex3d(-30,0, 1.5);
   glEnd();
   glPopAttrib();
   glPopMatrix();

   // Affichage du rectangle de chargement plein
   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
   glPushMatrix();
   glPushAttrib(GL_CURRENT_BIT);
   //glColor3f(0,0,0);
   glRotatef(rotationObjet_,0,0,1);
   glTranslatef(0,10,0);

   glBegin(GL_QUADS);
		glColor3f(1,1,0);glVertex3d(-3,0, 1.5);
		glColor3f(1,1,0);glVertex3d(-3,5, 1.5);
		glColor3f(1,0,0);glVertex3d(-factEchelle_ * 3 ,5, 1.5);	
		glColor3f(1,0,0);glVertex3d(-factEchelle_ * 3 ,0, 1.5);
   glEnd();
   glPopAttrib();
   glPopMatrix();

   glEnable(GL_TEXTURE_2D);
   glEnable(GL_LIGHTING);
   // Sauvegarde de la matrice.													
   glPushMatrix();
	
		
	   glRotatef(rotationObjet_+90, 0.0, 0.0, 1.0);
	   glTranslatef(0,5,0);
	   glScalef(1, factEchelle_/3, 1);

		// Affichage du modèle.
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_FLECHE);
	
   glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////