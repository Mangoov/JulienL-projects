///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudSable.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDSABLE_H__
#define __ARBRE_USINES_USINENOEUDSABLE_H__


#include "UsineNoeud.h"
#include "NoeudSable.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudSable
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudSable.
///
/// @author Julien Lapointe
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudSable : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudSable(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudSable::UsineNoeudSable(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudSable::UsineNoeudSable(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudSable::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudSable::creerNoeud() const
{
   return new NoeudSable(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDSable_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
