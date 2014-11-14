///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBalle.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBalle_H__
#define __ARBRE_USINES_USINENOEUDBalle_H__


#include "UsineNoeud.h"
#include "NoeudBalle.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBalle
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudBalle.
///
/// @author Julien Lapointe
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBalle : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudBalle(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudBalle::UsineNoeudBalle(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBalle::UsineNoeudBalle(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBalle::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBalle::creerNoeud() const
{
   return new NoeudBalle(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDBalle_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
