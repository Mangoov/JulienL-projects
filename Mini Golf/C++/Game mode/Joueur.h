///////////////////////////////////////////////////////////////////////////
/// @file Joueur.h
/// @author Mohammed Benbachir
/// @date 2011-10-28
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include <string>





class Joueur 
{
		
public:
	Joueur(std::string nom);
	~Joueur();

	std::string obtenirNomJoueur();
	int obtenirScoreTrou();
	int obtenirScoreTournoi();

	void incrementerScoreTrou(int increment);
	void incrementerScoreTournoi(int increment);

	void resetScoreTrou();
	void resetScoreTournoi();
	
private:

	std::string nom_;
	int scoreTrou_;
	int scoreTournoi_;


};

#endif // __JOUEUR_H__
