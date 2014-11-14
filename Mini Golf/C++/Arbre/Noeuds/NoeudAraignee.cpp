///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAraignee.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) ,
   angle_(0)
{
   modele_.charger("media/spider.obj");
	//modele_.assignerFacteurAgrandissement(1);
   //modele_.chargerMateriaux();

   // Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
   // USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
   // recréée pour chaque instance d'un noeud, alors que la même pourrait
   // être partagée par toutes les instances d'un même type de noeud.
   /*liste_ = glGenLists(1);
   glNewList(liste_, GL_COMPILE);
	modele_.dessiner();		
   glEndList();*/
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::~NoeudAraignee()
///
/// Ce destructeur désallouee la liste d'affichage de l'araignée.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::~NoeudAraignee()
{
   //glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();

   // Sauvegarde de la matrice.
   glPushMatrix();
   // Révolution autour du centre.
   glRotatef(35, sqrtf(2), sqrtf(2), 0);


   // Affichage du modèle.
   glCallList(liste_);
   // Restauration de la matrice.

   glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::animer(float temps)
{
   // Appel à la version de la classe de base pour l'animation des enfants.
   NoeudComposite::animer(temps);

   // L'araignée oscille selon une période de 4 secondes.
   /*angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
   positionRelative_[1] = 40*sin(utilitaire::DEG_TO_RAD(angle_));*/
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
