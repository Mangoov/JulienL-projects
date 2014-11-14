///////////////////////////////////////////////////////////////////////////
/// @file NoeudBonus.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBONUS_H__
#define __ARBRE_NOEUDS_NOEUDBONUS_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonus
/// @brief Classe qui représente Un Bonus dans l'arbre de rendu
///
/// @author Julien Lapointe
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBonus : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudBonus(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudBonus();

   /// Affiche la bonus
   virtual void afficherConcret() const;
   /// Appel a le calcul de la boite de l'objet
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
   /// Permet d'assigner le facteur d'agrandissement
   void assignerFacteurAgrandissement( float facteur);
   /// update de la position
   void animer(float temps);
private:
   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;
};


#endif // __ARBRE_NOEUDS_NOEUDBONUS_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
