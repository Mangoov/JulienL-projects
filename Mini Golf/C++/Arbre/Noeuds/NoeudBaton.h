///////////////////////////////////////////////////////////////////////////
/// @file NoeudBaton.h
/// @author Jean-Luc Dubeau
/// @date 2011-10-21
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBATON_H__
#define __ARBRE_NOEUDS_NOEUDBATON_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBaton
/// @brief Classe qui représente un baton dans l'arbre de rendu
///
/// @author Jean-Luc Dubeau
/// @date 2011-10-21
///////////////////////////////////////////////////////////////////////////
class NoeudBaton : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudBaton(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudBaton();

   /// Affiche la baton
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
   float vitTemps;
};


#endif // __ARBRE_NOEUDS_NOEUDBATON_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
