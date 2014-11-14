///////////////////////////////////////////////////////////////////////////
/// @file Joueur.cpp
/// @author Mohammed Benbachir
/// @date 2011-10-28
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////
#include "Joueur.h"


Joueur::Joueur(std::string nom)
{
	nom_ = nom;
	scoreTrou_ = 0;
	scoreTournoi_ = 0;
}

Joueur::~Joueur()
{}



std::string Joueur::obtenirNomJoueur()
{
	return nom_;
}


int Joueur::obtenirScoreTrou()
{
	return scoreTrou_;
	
} 

int Joueur::obtenirScoreTournoi()
{
	return scoreTournoi_;
}

void Joueur::incrementerScoreTrou(int increment)
{	
	scoreTrou_ += increment;
}

void Joueur::incrementerScoreTournoi(int increment)
{	
	scoreTournoi_ += increment;
}

void Joueur::resetScoreTrou()
{	
	scoreTrou_ = 0;
}

void Joueur::resetScoreTournoi()
{	
	scoreTournoi_ = 0;
}
