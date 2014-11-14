///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudEau.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDEAU_H__
#define __ARBRE_USINES_USINENOEUDEAU_H__


#include "UsineNoeud.h"
#include "NoeudEau.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudEau
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudEau.
///
/// @author Julien Lapointe
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudEau : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudEau(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudEau::UsineNoeudEau(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudEau::UsineNoeudEau(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudEau::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudEau::creerNoeud() const
{
   return new NoeudEau(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDEau_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
