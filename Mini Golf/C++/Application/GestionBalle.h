///////////////////////////////////////////////////////////////////////////
/// @file GestionBalle.h
/// @author Aiman Badr & Julien Lapointe
/// @date 2011-10-21
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////



#ifndef __APPLICATION_GESTIONBALLE_H__
#define __APPLICATION_GESTIONBALLE_H__

class NoeudBalle;
#include "FacadeModele.h"
#include "aideCollision.h"
#include "Utilitaire.h"
#include "NoeudBalle.h"



///////////////////////////////////////////////////////////////////////////
/// @class GestionBalle
/// @brief Classe qui représente les deplacements de la balle
///
/// @author Aiman Badr Jaouhar & Julien Lapointe
/// @date 2011-10-21
///////////////////////////////////////////////////////////////////////////
class GestionBalle
{
public:

	//detection collision balle et bordure
	 
	GestionBalle();
	~GestionBalle();
	///verifie les collisions de la balle
	aidecollision::DetailsCollision checkCollisionBordure(NoeudBalle* noeudballe, float temps);
	static double obtenirAngleAlea() ;
	static void reSeedAlea();
	static void modifierAngleAlea(double AngleAlea);
	static void allowDeviation();
private:
	static double angleAleatoire_;
	static bool allowDeviation_;
};

#endif // __APPLICATION_GESTIONBALLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
