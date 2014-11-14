///////////////////////////////////////////////////////////////////////////
/// @file NoeudBalle.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDTROU_H__
#define __ARBRE_NOEUDS_NOEUDTROU_H__


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
class NoeudTrou : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudTrou(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudTrou();

   /// Affiche le trou
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
};


#endif // __ARBRE_NOEUDS_NOEUDTROU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
