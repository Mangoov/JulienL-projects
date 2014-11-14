//////////////////////////////////////////////////////////////////////////////
/// @file GestionJoueur.h
/// @author Manraj Ashley, quadriciel de base par Jean-Francois Pérusse
/// @date 2011-31-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_GESTIONJOUEUR_H__
#define __APPLICATION_GESTIONJOUEUR_H__

#include "Singleton.h"
#include "Vecteur.h"
#include "tinyxml.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "GestionBalle.h"
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class GestionJoueur
/// @brief Classe de sauvegarde et gestion des joueurs et tournois.(Gestion parti rapide aussi).
///
/// @author Manraj Ashley, quadriciel de base par Jean-Francois Pérusse
/// @date 2011-31-10
///////////////////////////////////////////////////////////////////////////
class GestionJoueur : public Singleton<GestionJoueur>
{
   SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionJoueur);

public:
   ///  Charge le fichier de joueur avec la valeur par defaut
   void chargerFichierJoueur();
   ///  Charge le fichier de tournoi avec la valeur par defaut 
   void chargerFichierTournoi();
   ///  Enregistre le fichier de joueur avec la valeur par defaut
   void enregistrerFichierJoueur();
   ///  Enregistre le fichier de tournoi avec la valeur par defaut
   void enregistrerFichierTournoi();
   ///  Ajoute un joueur au fichier de joueurs avec le nom passe en parametre.
   void ajouterJoueur(const std::string nomJoueur);
   ///  Ajoute un tournoi au fichier de tournoi avec le nom passe en parametre.
   void ajouterTournoi(const std::string nomTournoi);
      ///  Ajoute un parcours au tournoi au fichier de tournoi.
   void ajouterParcoursATournoi(const std::string nomTournoi,const std::string Nomparcours);
   ///  Modifie la fiche de tournoi avec le nom passe en parametre au parcours passe en parametre
   ///  avec pour joueur et score passe en parametre
   void modifierFicheTournoi(const std::string nomTournoi, const std::string Parcours,
	   const std::string nomJoueur,const int Score);
   ///  Modifie la fiche de joueur avec le nom passe en parametre au parcours passe en parametre
   ///  avec le score passe en parametre
   void modifierFicheJoueur(const std::string nomJoueur,
	   const std::string Parcours,const int Score);
   /// Permettra de conserver les informations relative a la partie en cours du joueur a la map donnee.
   void sauvegarderMultijoueur(const std::string NomMap);
   /// Permettra de charger les informations relatives a la partie en cours du joueur.
   void chargerMultijoueur(const std::string nomJoueur);
   ///  Cette methode permet d'obtenir les noms de parcours dans le tournoi donne
   std::vector<std::string> obtenirNomsParcours(const std::string nomTournoi);
   ///  Cette methode permet d'obtenir les noms de tous les tournois present dans la base de donnee
   std::vector<std::string> obtenirNomsTournois();
   ///  Cette methode permet d'obtenir le score du joueur present dans la base de donnee au nom et parcours donnee
   int obtenirMeilleurScoreJoueur(const std::string nomJoueur, const std::string nomParcours);
   /// Cette methode retourne le nombre de joueurs dans le tableau des meilleurs scores.
   int obtenirNombreJoueursTableauMeilleurScore();
   /// Cette methode retourne le nombre de parcours present au joueur du tableau de meilleur score.
   int obtenirNombreParcoursTableauMeilleurScore(const std::string nomJoueur);
   /// Cette methode retourne un vector de string de parcours associes au nom de joueur en parametre.
   std::vector<std::string> obtenirNomsParcoursTableauMeilleurScore(const std::string nomJoueur);
   /// Cette methode permet d'effacer le fichierJoueur contenant les meilleurs scores.
   void effacerFichierJoueur();

   /// Cette fonction retourne le nombre de parcours dans le nomTournoi passe en parametre.
   int obtenirNombreParcours(const std::string nomTournoi);
   /// Cette fonction retourne le nombre de tournoi dans la liste de tournois.
   int obtenirNombreTournois();
   // charger le replay
   void chargerReplay(const std::string nomJoueur);
   // nom de la liste de joueur
   static std::string nomListeJoueurs;
   // nom de la liste de tournoi
   static std::string nomListeTournois;
   // nom liste multijoueur
   static std::string nomListeMultijoueur;

private:
	// constructeur
	GestionJoueur();
	// destructeur
	~GestionJoueur();
	TiXmlDocument* joueurXml_;
	TiXmlDocument* tournoiXml_;
	TiXmlDocument* multijoueurXml_;
	// assigner meilleur score
	int assignerMeilleurScoreTournoi(TiXmlElement* filsTournoi);
};
#endif // __APPLICATION_GESTIONJOUEUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
