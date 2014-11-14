///////////////////////////////////////////////////////////////////////////
/// @file Joueur.cpp
/// @author Mohammed Benbachir
/// @date 2011-10-28
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////


#include "Jeu.h"



Jeu* Jeu::instance_ = 0;

Jeu::Jeu()
{
	tournoiTermine_ = false;
}

Jeu::~Jeu()
{}

Jeu* Jeu::obtenirInstance()
{
	if(instance_ == nullptr)
		instance_ = new Jeu();

	return instance_;
}

void Jeu::libererInstance()
{
	delete instance_;
	instance_ = 0;
}

void Jeu::ajouterJoueur(std::string nom)
{
	joueurs_.push_back(Joueur(nom));
}

//int Jeu::obtenirNombreJoueurs()
//{
//	return joueurs_.size();
//}

void Jeu::obtenirScoreJoueurs(int scores[])
{
	for(int i = 0; i < joueurs_.size() ; i++)
		scores[i] = joueurs_[i].obtenirScoreTrou();
}

void Jeu::obtenirNomJoueurs(std::string nom[])
{
	for(int i = 0; i < joueurs_.size() ; i++)
		nom[i] = joueurs_[i].obtenirNomJoueur();
}