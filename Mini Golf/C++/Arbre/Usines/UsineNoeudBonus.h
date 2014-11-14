///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBonus.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBonus_H__
#define __ARBRE_USINES_USINENOEUDBonus_H__


#include "UsineNoeud.h"
#include "NoeudBonus.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBonus
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudBonus.
///
/// @author Julien Lapointe
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBonus : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudBonus(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudBonus::UsineNoeudBonus(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBonus::UsineNoeudBonus(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBonus::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBonus::creerNoeud() const
{
   return new NoeudBonus(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDBonus_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
