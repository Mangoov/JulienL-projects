///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortal.h
/// @author Julien Lapointe
/// @date 2011-11-05
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPORTAL_H__
#define __ARBRE_NOEUDS_NOEUDPORTAL_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudTrou
/// @brief Classe qui représente Un Trou dans l'arbre de rendu
///
/// @author Julien Lapointe
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudPortal : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudPortal(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudPortal();

   /// Affiche le trou
   virtual void afficherConcret() const;
   /// Permet d'assigner le facteur d'agrandissement
   void assignerFacteurAgrandissement( float facteur);
   /// Appel a le calcul de la boite de l'objet
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
   /// Assigne les points de la bordure
   void AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
   void animer(float temps);
private:
   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;
   //float factEchelle_;
};


#endif // __ARBRE_NOEUDS_NoeudPortal_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
