///////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDARAIGNEE_H__
#define __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudAraignee
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudAraignee : public NoeudComposite
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudAraignee(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudAraignee();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );


private:
   /// Mod�le 3D correspondant � ce noeud.
   Modele3D modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;

   /// Angle dans le sinus de l'oscillation
   float angle_;

};


#endif // __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
