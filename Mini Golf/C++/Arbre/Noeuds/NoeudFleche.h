///////////////////////////////////////////////////////////////////////////
/// @file Noeudfleche.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDFLECHE_H__
#define __ARBRE_NOEUDS_NOEUDFLECHE_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class Noeudfleche
/// @brief Classe qui représente Une fleche dans l'arbre de rendu
///
/// @author Julien Lapointe
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class Noeudfleche : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   Noeudfleche(const std::string& typeNoeud);
   /// Destructeur.
   ~Noeudfleche();

   /// Affiche la fleche
   virtual void afficherConcret() const;
   /// Appel a le calcul de la boite de l'objet
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
   /// Permet d'assigner le facteur d'agrandissement
   void assignerFacteurAgrandissement( float facteur);
   /// Assigne les points de la fleche
   void AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
private:
   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;
};


#endif // __ARBRE_NOEUDS_NOEUDfleche_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
