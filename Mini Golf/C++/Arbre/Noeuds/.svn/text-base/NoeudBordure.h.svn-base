///////////////////////////////////////////////////////////////////////////
/// @file NoeudBordure.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBORDURE_H__
#define __ARBRE_NOEUDS_NOEUDBORDURE_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBordure
/// @brief Classe qui représente Une Bordure dans l'arbre de rendu
///
/// @author Julien Lapointe
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBordure : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudBordure(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudBordure();

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
   ///Retourne les coins bordure maximale
   Vecteur3 obtenirCoinBordureMax() const;
   ///Retourne les coins bordure minimale
   Vecteur3 obtenirCoinBordureMin() const;

   void assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax);

   
private:
   /// Modèle 3D correspondant à ce noeud.
   static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;
   // ///vrai coin min de la bordure
   //Vecteur3 coinBordureMin_;
   /////vrai coin max de la bordure
   //Vecteur3 coinBordureMax_;
   
};


#endif // __ARBRE_NOEUDS_NOEUDBORDURE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
