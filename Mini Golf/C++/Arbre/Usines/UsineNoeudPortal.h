///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPortal.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPORTAL_H__
#define __ARBRE_USINES_USINENOEUDPORTAL_H__


#include "UsineNoeud.h"
#include "NoeudPortal.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPortal
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudPortal.
///
/// @author Julien Lapointe
/// @date 2011-09-11
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPortal : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudPortal(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudPortal::UsineNoeudPortal(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudPortal::UsineNoeudPortal(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPortal::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPortal::creerNoeud() const
{
   return new NoeudPortal(obtenirNom());
}


#endif // __ARBRE_USINES_USINENOEUDPortal_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
