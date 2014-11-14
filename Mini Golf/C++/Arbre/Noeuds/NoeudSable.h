///////////////////////////////////////////////////////////////////////////
/// @file NoeudBordure.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDSABLE_H__
#define __ARBRE_NOEUDS_NOEUDSABLE_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudSable
/// @brief Classe qui représente Un obstacle sable dans l'arbre de rendu
///
/// @author Julien Lapointe
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudSable : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudSable(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudSable();

   /// Affiche la obstacle
   virtual void afficherConcret() const;
   /// Permet d'assigner le facteur d'agrandissement
   void assignerFacteurAgrandissement( float facteur);
   /// Appel a le calcul de la boite de l'objet
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
private:
   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;
   //float factEchelle_;
   int coefFriction_;
};


#endif // __ARBRE_NOEUDS_NOEUDOB_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
