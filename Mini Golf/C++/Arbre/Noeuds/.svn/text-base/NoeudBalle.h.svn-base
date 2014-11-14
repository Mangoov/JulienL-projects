///////////////////////////////////////////////////////////////////////////
/// @file NoeudBalle.h
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBALLE_H__
#define __ARBRE_NOEUDS_NOEUDBALLE_H__

class GestionBalle;
#include "GestionBalle.h"
#include "NoeudComposite.h"
#include "Modele3D.h"


#include <GL/gl.h>
#include <GL/glu.h>
#include <ctime>
#include <cmath>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudBalle
/// @brief Classe qui représente Une balle dans l'arbre de rendu
///
/// @author Julien Lapointe
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBalle : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudBalle(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudBalle();

   /// Appel a le calcul de la boite de l'objet
   void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
   /// Permet d'assigner le facteur d'agrandissement
   void assignerFacteurAgrandissement( float facteur);
   /// Affiche la balle
   virtual void afficherConcret() const;

   /// Verifie sur quelle sorte de surface on est
   bool checkFacteurFriction();
   /// Initialise la vitesse initiale
   void initialiserVitesse(double angle, double vitesse);
   /// update de la position
   void animer(float temps);
   ///retourne le rayon de la balle
   double obtenirRayon() const;
   ///retourne la vitesse de la balle
   Vecteur3 obtenirVitesse() const;
   ///modifier la vitesse de la balle
   void modifierVitesse(Vecteur3 vitesse);
   	// Charger le vecteur force 
   void charger();
   // lacher la balle 
   void lacher();

   /// Fonction qui verifie si la balle est prete a s'animer
   bool checkBaton();
   
   bool obtenirTeleported();
   void assignerTeleported(bool teleported);
   
   float obtenirtempsBonus();
   void ModifierTempsBonus(float temps);
   Vecteur3 obtenirVitesseAvantBonus();
   void setVitesseAvantBonus(Vecteur3 vitesse);
   int NegPos();
   float randomNumber();
   //verifie premier passage de la balle dans l'eau
   bool obtenirPremierPassageEau() const
   {
	   return premierPassageEau_;
   }

   void assignerCountdown(float count);
   void assignerCollisionTrou(bool trou); 
	
private:
   /// Modèle 3D correspondant à ce noeud.
	static Modele3D* modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   //GLuint liste_;
   GestionBalle* collisionBalle;
   double masse_;
   //double vitesseX_, vitesseY_;
   double angleX_, angleY_;
   double coefRebondMur_,coefFriction_, ForceFriction_;
   float tempsPermisEau_,tempsCritiqueCollision_,tempsCourant_, tempsPrecedent_;
   double rayon_;
   Vecteur3 axeRotation_;
   Vecteur3 Friction_;
   Vecteur3 normale_;
   Vecteur3 impact_;
   //Vecteur3 vitesse_;
   Vecteur3 deltaS_;
   Vecteur3 ancienDeltaS_;
   Vecteur3 vitesseAvant_;
   Vecteur3 posRelativeAvantEau_;
   
   float particle[1000][10];
   float facteurForce_;

   bool roule_; 
   bool charger_;
   bool frappee_;
   bool tomber_;
   bool teleported_;
   bool premierPassageEau_;
   float	tempsBonus_;
   Vecteur3 vitesseAvantBonus_;
   double	countdown_;
   bool collisionTrou_;
   int nbCout_;

   float compteur_;
   bool test_;
   bool fireworks_;
   static int compteurPassageAnimation_;
};


#endif // __ARBRE_NOEUDS_NOEUDBALLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
