///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBaton.h
/// @author Jean-Luc Dubeau
/// @date 2011-10-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBATON_H__
#define __ARBRE_USINES_USINENOEUDBATON_H__


#include "UsineNoeud.h"
#include "NoeudBaton.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBaton
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudBaton.
///
/// @author Julien Lapointe
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBaton : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudBaton(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudBaton::UsineNoeudBaton(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBaton::UsineNoeudBaton(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBaton::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBaton::creerNoeud() const
{
   return new NoeudBaton(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDBATON_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
