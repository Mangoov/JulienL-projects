///////////////////////////////////////////////////////////////////////////
/// @file NoeudTerrain.h
/// @author Jean-Luc Dubeau
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDTERRAIN_H__
#define __ARBRE_NOEUDS_NOEUDTERRAIN_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudTerrain
/// @brief Classe qui représente le fond dans l'arbre de rendu
///
/// @author Jean-Luc Dubeau
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudTerrain : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudTerrain(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudTerrain();

   /// Affiche le terrain
   virtual void afficherConcret() const;

   ///Changer le facteur d'agrandissement
   void ChangerFactEchelle(float NouveauFacteur);

   ///Calculer la boite englobante
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);

private:

   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;   
   ///Coefficient de friction
   int coefFriction_;
   unsigned int textureTerrain_;
};


#endif // __ARBRE_NOEUDS_NOEUDTERRAIN_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
