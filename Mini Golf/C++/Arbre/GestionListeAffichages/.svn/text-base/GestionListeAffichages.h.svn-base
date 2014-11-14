///////////////////////////////////////////////////////////////////////////
/// @file GestionListeAffichages.h
/// @author Mohammed Benbachir
/// @date 2011-10-27
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////

#ifndef __GESTION_AFFICHAGE_H__
#define __GESTION_AFFICHAGE_H__


#include "Singleton.h"
#include "Modele3D.h"
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

enum type_liste  {
	RIEN,
	LISTE_BALLE,
	LISTE_BATON,
	LISTE_BONUS,
	LISTE_BORDURE,
	LISTE_EAU,
	LISTE_SABLE,
	LISTE_TERRAIN,
	LISTE_TROU,
	LISTE_CUBE,
	LISTE_FLECHE,
	LISTE_CONTOUR,
	LISTE_PORTALBLEU,
	LISTE_PORTALORANGE,
	LISTE_LAMP,
	LISTE_STATUE,
	FIN
};

struct listeAffichage {

	type_liste	typeListe;
	GLuint		liste_;
	bool		estCompiler_;
};

class GestionListeAffichages : public Singleton<GestionListeAffichages>
{
		SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionListeAffichages)
public:

	bool estListeCompiler( type_liste liste );
	void appelListeAffichage( type_liste liste );
	void creeListeAffichage( type_liste liste );
	void supprimerListeAffichage( type_liste liste );
	
private:
	// constructeur privé (il est un singleton)
	GestionListeAffichages();
	~GestionListeAffichages();

	vector<listeAffichage> vecteurListesAffichages_;
};

#endif // __GESTION_AFFICHAGE_H__
