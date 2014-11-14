///////////////////////////////////////////////////////////////////////////
/// @file GestionListeAffichages.cpp
/// @author Mohammed Benbachir
/// @date 2011-10-27
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////

#include "GestionListeAffichages.h"

// declaration avec un macro (voir Singleton.h)
SINGLETON_DECLARATION_CPP(GestionListeAffichages)

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionListeAffichages::GestionListeAffichages()
///
/// Constructeur par défaut
///
/// @return  
///
////////////////////////////////////////////////////////////////////////
GestionListeAffichages::GestionListeAffichages()
{
	type_liste typeListe = RIEN;
	listeAffichage listeAffichage;
	GLuint liste = 1;

	while(typeListe != FIN )
	{
		listeAffichage.estCompiler_ = false;
		listeAffichage.typeListe = typeListe;
		listeAffichage.liste_ = liste;
		vecteurListesAffichages_.push_back(listeAffichage);
		liste++;
		typeListe = (type_liste)(typeListe + 1 );
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionListeAffichages::~GestionListeAffichages()
///
/// decription 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
GestionListeAffichages::~GestionListeAffichages()
{
	for(size_t i = 0; i< vecteurListesAffichages_.size() ; ++i )
	{
		glDeleteLists(vecteurListesAffichages_[i].liste_, 1); // on detruit les listes
	}
	vecteurListesAffichages_.clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionListeAffichages::estListeCompiler( type_liste liste )
///
/// decription 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
bool GestionListeAffichages::estListeCompiler( type_liste liste )
{
	return vecteurListesAffichages_[liste].estCompiler_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionListeAffichages::appelListeAffichage( type_liste liste )
///
/// decription 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void GestionListeAffichages::appelListeAffichage( type_liste liste )
{
	glCallList( vecteurListesAffichages_[liste].liste_ );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionListeAffichages::creeListeAffichage( type_liste liste )
///
/// decription 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void GestionListeAffichages::creeListeAffichage( type_liste liste )
{
	vecteurListesAffichages_[(GLuint)liste].estCompiler_ = true;
	//lien entre la liste et le type_liste
	vecteurListesAffichages_[(GLuint)liste].liste_ = glGenLists(1);
	glNewList( vecteurListesAffichages_[liste].liste_, GL_COMPILE);
	
} 

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionListeAffichages::supprimerListeAffichage( type_liste liste )
///
/// decription 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void GestionListeAffichages::supprimerListeAffichage( type_liste liste )
{
	vecteurListesAffichages_[(GLuint)liste].estCompiler_ = false;
	glDeleteLists(vecteurListesAffichages_[(GLuint)liste].liste_, 1);
}

