///////////////////////////////////////////////////////////////////////////
/// @file Jeu.h
/// @author Mohammed Benbachir
/// @date 2011-10-28
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __JEU_H__
#define __JEU_H__

#include "Joueur.h"
#include <vector>

#include <string>



class Jeu 
{
		
public:
		
	static Jeu* obtenirInstance();
	static void libererInstance();

	void ajouterJoueur(std::string nom);
	//int obtenirNombreJoueurs();
	void obtenirScoreJoueurs(int scores[]);
	void obtenirNomJoueurs(std::string nom[]);
	
	
private:

	Jeu();
	~Jeu();

	static Jeu* instance_;

	bool tournoiTermine_;
	std::vector<Joueur> joueurs_;
};

#endif // __JEU_H__