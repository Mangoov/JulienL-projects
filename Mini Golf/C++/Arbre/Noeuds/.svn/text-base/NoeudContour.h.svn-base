///////////////////////////////////////////////////////////////////////////
/// @file NoeudCONTOUR.h
/// @author Aiman Badr Jaouhar
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCONTOUR_H__
#define __ARBRE_NOEUDS_NOEUDCONTOUR_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudContour
/// @brief Classe qui représente Une Bordure dans l'arbre de rendu
///
/// @author Aiman Badr Jaouhar
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudContour : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudContour(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudContour();

   /// Affiche la bordure
   virtual void afficherConcret() const;
   /// Appel a le calcul de la boite de l'objet
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
   /// Permet d'assigner le facteur d'agrandissement
   void assignerFacteurAgrandissement( float facteur);
   /// Assigne les points de la bordure
   void AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
   ///Calcule les vrais coins de la bordure
   void calculerCoinsBordure(Vecteur3& coinBordureMin,Vecteur3& coinBordureMax);

   Vecteur3 obtenirCoinBordureMax() const;

   Vecteur3 obtenirCoinBordureMin() const;

   void assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax);
private:
   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;


};


#endif // __ARBRE_NOEUDS_NOEUDCONTOUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
