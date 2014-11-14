///////////////////////////////////////////////////////////////////////////
/// @file VisiteurXML.h
/// @author Manraj Ashley
/// @date 09/25/2011
/// @version
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __CONFIGURATION_VISITEURXML_H__
#define __CONFIGURATION_VISITEURXML_H__

// Pour l'utilisation de tinyxml
#include "tinyxml.h"
#include "Utilitaire.h"
#include <vector>
#include <string>
///////////////////////////////////////////////////////////////////////////
/// @class 	VisiteurXML
/// @brief 	Cette classe est en charge de la gestion des noeuds et de leur 
///	traitement XML. Cette implementation est choisi pour reduire la repetition de code
/// similaire dans les noeuds.
/// @author 09/25/2011
/// @date 
///////////////////////////////////////////////////////////////////////////

class VisiteurXML
{
	friend class NoeudAbstrait;
	friend class NoeudComposite;
	friend class ArbreRendu;
public :
	
	///Implementation du patron singleton.
	static VisiteurXML* obtenirInstance();
	///Permet de liberer l'instance du patron singleton.
	static void libererInstance();

	///Methode pour visiter un noeud abstrait
	void visiterNoeudAbstrait(NoeudAbstrait* noeud);
	///Methode pour visiter un noeud composite
	void visiterNoeudComposite(NoeudComposite* noeud);
	///Methode pour charger un arbre de rendu a partir d'un fichier XML.
	void lireFichierXML(ArbreRendu* arbre,std::string nomFichier);
	///Permet l'écriture d'un fichier xml
	void ecrireFichier(ArbreRendu* arbre,std::string nomFichier);
	///Accesseur de ficXml_
	TiXmlDocument* obtenirArbreXML() const;
	///Permet de traiter le noeud parent ayant des enfants ou des siblings pour la lecture
	void chargerInfo(ArbreRendu* arbre,TiXmlElement* noeud);
	/// Fonction transformant un booleen a un string 0 pour false 1 pour true
   std::string boolToString(const bool valeur);
   /// Fonction effacant le fichier passe en parametre si existant.
   void effacerFichierXml(const std::string nomFichierEffacer);
   /// Permet d'effacer l'arbre de pointeurs Xml courant dans le TiXmlDocument 
   void effacerArbreXml();
   /// Permet d'assigner le par.
   void assignerPar(const int Par);
   int obtenirPardeMap(const std::string map);

private :
	TiXmlDocument* ficXml_;
	///Constructeur par défaut
	VisiteurXML();
	///Destructeur
	~VisiteurXML();
	///instance unique du visiteur XML
	static VisiteurXML* instance_;
	static int Par_;
};
#endif  // __CONFIGURATION_VISITEURXML_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////