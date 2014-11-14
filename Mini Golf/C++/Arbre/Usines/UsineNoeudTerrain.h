///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudTerrain.h
/// @author Jean-Luc Dubeau
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDTERRAIN_H__
#define __ARBRE_USINES_USINENOEUDTERRAIN_H__


#include "UsineNoeud.h"
#include "NoeudTerrain.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudTerrain
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudTerrain.
///
/// @author Jean-Luc Dubeau
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudTerrain : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudTerrain(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudTerrain::UsineNoeudTerrain(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudTerrain::UsineNoeudTerrain(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudTerrain::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudTerrain::creerNoeud() const
{
   return new NoeudTerrain(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDTERRAIN_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
