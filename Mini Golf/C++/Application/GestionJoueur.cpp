///////////////////////////////////////////////////////////////////////////
/// @file GestionJoueur.cpp
/// @author Manraj Ashley
/// @date 11/01/2011
/// @version
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "GestionJoueur.h"
#include <iostream>
#include <string>
SINGLETON_DECLARATION_CPP(GestionJoueur);
std::string GestionJoueur::nomListeJoueurs="ListeJoueurs.xml";
std::string GestionJoueur::nomListeTournois="ListeTournois.xml";
std::string GestionJoueur::nomListeMultijoueur="Multijoueur.xml";

////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::GestionJoueur()
/// 
/// Ce constructeur initialise un pointeur representant la racine
///	du document
///
///	@return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
GestionJoueur::GestionJoueur()
{	
	joueurXml_=new TiXmlDocument();
	if(utilitaire::fichierExiste(nomListeJoueurs.c_str()))
	{
		joueurXml_->LoadFile(nomListeJoueurs.c_str());
	}
	tournoiXml_=new TiXmlDocument();
	if(utilitaire::fichierExiste(nomListeTournois.c_str()))
	{
		tournoiXml_->LoadFile(nomListeTournois.c_str());
	}
	multijoueurXml_=new TiXmlDocument();
}
////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::~GestionJoueur()
///
///	Ce destructeur libère le pointeur initialise par le constructeur
///					
///	@return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
GestionJoueur::~GestionJoueur()
{
	delete joueurXml_;
	delete tournoiXml_;
	delete multijoueurXml_;
}
////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::ajouterJoueur()
///
///	Cette methode permet d'ajouter un joueur a l'xml correspondant.
///					
///	@param[in] const std::string nomJoueur
///
////////////////////////////////////////////////////////////////////////
void GestionJoueur::ajouterJoueur(const std::string nomJoueur)
{
	TiXmlHandle docHandle(joueurXml_);
	TiXmlElement* child = docHandle.FirstChild("listeJoueurs").ToElement();
	TiXmlElement* JoueurPotentiel = docHandle.FirstChild("listeJoueurs").FirstChildElement(nomJoueur.c_str()).ToElement();
	if(JoueurPotentiel==nullptr)
	{
		TiXmlElement* Joueur = new TiXmlElement(nomJoueur.c_str());
		child->LinkEndChild(Joueur);
		joueurXml_->LinkEndChild(child);
	}
}
////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::ajouterTournoi()
///
///	Cette methode permet d'ajouter un tournoi a l'xml correspondant.
///					
///	@param[in] const std::string nomJoueur
///
////////////////////////////////////////////////////////////////////////
void GestionJoueur::ajouterTournoi(const std::string nomTournoi)
{
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	TiXmlElement* TournoiPotentiel = docHandle.FirstChild("listeTournois").FirstChildElement(nomTournoi.c_str()).ToElement();
	if(TournoiPotentiel==nullptr)
	{
		TiXmlElement* Tournoi = new TiXmlElement(nomTournoi.c_str());
		child->LinkEndChild(Tournoi);
		tournoiXml_->LinkEndChild(child);
	}
}
////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::ajouterParcoursATournoi()
///
///	Cette methode permet d'ajouter un parcours au tournoi dans l'xml de tournoi par defaut.
///					
///	@param[in] const std::string nomTournoi
///	@param[in] const std::string Nomparcours
///
////////////////////////////////////////////////////////////////////////
void GestionJoueur::ajouterParcoursATournoi(const std::string nomTournoi,const std::string Nomparcours)
{
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	if (child==nullptr)
	{
		child= new TiXmlElement("listeTournois");
		tournoiXml_->LinkEndChild(child);
	}
	TiXmlElement* nomTour = docHandle.FirstChild("listeTournois").FirstChild(nomTournoi.c_str()).ToElement();
	if (nomTour!=nullptr)
	{
		TiXmlElement* ParcoursJou = new TiXmlElement(Nomparcours.c_str());
		nomTour->LinkEndChild(ParcoursJou);
	}
	else
	{
		TiXmlElement* nomTour2 = new TiXmlElement(nomTournoi.c_str());
		TiXmlElement* ParcoursJou = new TiXmlElement(Nomparcours.c_str());
		nomTour2->LinkEndChild(ParcoursJou);
		child->LinkEndChild(nomTour2);
	}
	enregistrerFichierTournoi();
}
////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::modifierFicheJoueur(const std::string nomJoueur,
///	   const std::string Parcours,const int Score)
///
///	Cette methode permet d'ajouter une fiche de joueur a l'xml correspondant.
///					
///	@param[in] const std::string nomJoueur
///
////////////////////////////////////////////////////////////////////////

void GestionJoueur::modifierFicheJoueur(const std::string nomJoueur,
	const std::string Parcours,const int Score)
{
	TiXmlHandle docHandle(joueurXml_);
	TiXmlElement* child = docHandle.FirstChild("listeJoueurs").ToElement();
	if (child==nullptr)
	{
		child= new TiXmlElement("listeJoueurs");
		joueurXml_->LinkEndChild(child);
	}
	TiXmlElement* Joueur = (TiXmlElement*)(child->FirstChild(nomJoueur.c_str()));
	TiXmlElement* ParcoursJou = docHandle.FirstChild("listeJoueurs").FirstChild(nomJoueur.c_str()).FirstChild(Parcours.c_str()).ToElement();
	if (Joueur!=nullptr)
	{
		if (ParcoursJou!=nullptr)
		{
			int score;
			score=ParcoursJou->QueryIntAttribute("Score",&score);
			if(Score<score||score==0)
			{
				ParcoursJou->SetAttribute("Score", Score);
			}
		}
		else
		{
			ParcoursJou = new TiXmlElement(Parcours.c_str());
			ParcoursJou->SetAttribute("Score", Score);
			Joueur->LinkEndChild(ParcoursJou);
		}
	}
	else
	{
		Joueur = new TiXmlElement(nomJoueur.c_str());
		ParcoursJou = new TiXmlElement(Parcours.c_str());
		ParcoursJou->SetAttribute("Score", Score);
		Joueur->LinkEndChild(ParcoursJou);
		child->LinkEndChild(Joueur);
	}
	enregistrerFichierJoueur();

}
////////////////////////////////////////////////////////////////////////
///	@fn GestionJoueur::modifierFicheTournoi(const std::string nomTournoi, const std::string Parcours,
///	   const std::string nomJoueur,const int Score)
///
///	Cette methode permet d'ajouter un tournoi a l'xml correspondant.
///					
///	@param[in] const std::string nomJoueur
///
////////////////////////////////////////////////////////////////////////

void GestionJoueur::modifierFicheTournoi(const std::string nomTournoi, const std::string Parcours,
	   const std::string nomJoueur,const int Score)
{
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	if (child==nullptr)
	{
		child= new TiXmlElement("listeTournois");
		tournoiXml_->LinkEndChild(child);
	}
	int meilleur_score=0;
	TiXmlElement* nomTour = docHandle.FirstChild("listeTournois").FirstChild(nomTournoi.c_str()).ToElement();
	TiXmlElement* ParcoursJou = docHandle.FirstChild("listeTournois").FirstChild(nomTournoi.c_str()).FirstChild(Parcours.c_str()).ToElement();
	if (nomTour!=nullptr)
	{
		if (ParcoursJou!=nullptr)
		{
			int score;
			score=ParcoursJou->QueryIntAttribute("Score",&score);
			if(Score<score||score==0)
			{
				ParcoursJou->SetAttribute("Score", Score);
				ParcoursJou->SetAttribute("Joueur", nomJoueur.c_str());

			}

		}
		else
		{
			ParcoursJou = new TiXmlElement(Parcours.c_str());
			ParcoursJou->SetAttribute("Score", Score);
			ParcoursJou->SetAttribute("Joueur", nomJoueur.c_str());
			nomTour->LinkEndChild(ParcoursJou);
		}
		meilleur_score=assignerMeilleurScoreTournoi(nomTour);
		nomTour->SetAttribute("Meilleur_score",meilleur_score);
	}
	else
	{
		nomTour = new TiXmlElement(nomTournoi.c_str());
		ParcoursJou = new TiXmlElement(Parcours.c_str());
		ParcoursJou->SetAttribute("Score", Score);
		ParcoursJou->SetAttribute("Joueur", nomJoueur.c_str());
		nomTour->SetAttribute("Meilleur_score",0);
		nomTour->LinkEndChild(ParcoursJou);
		child->LinkEndChild(nomTour);
	}
	enregistrerFichierTournoi();

}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::assignerMeilleurScoreTournoi(TiXmlDocument* filsTournoi)
/////
///// Cette fonction retourne le score total des parcours du tournoi.
///// C'est une fonction recursive iterant sur le fils du noeuds tournoi.
/////
///// @return int valeur total du score des sous parcours.
/////
//////////////////////////////////////////////////////////////////////////
int GestionJoueur::assignerMeilleurScoreTournoi(TiXmlElement* Tournoi)
{
	int total_tournoi=0;
	int score_tournoi=0;
	TiXmlElement* objenfant=Tournoi->FirstChildElement();
	if(objenfant!=nullptr)
	{
		for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement() )
		{
			objenfant->QueryIntAttribute("Score",&score_tournoi);
			total_tournoi+=score_tournoi;
		}
	}
	return total_tournoi;
}

//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::enregistrerFichierJoueur(const std::string nomFichier)
/////
///// Cette fonction ecrit les informations des joueurs courants dans le nom
///// de fichier par defaut.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::enregistrerFichierJoueur()
{
	joueurXml_->SaveFile( nomListeJoueurs.c_str() );
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::enregistrerFichierTournoi(const std::string nomFichier)
/////
///// Cette fonction ecrit les informations des joueurs courants dans le nom
///// de fichier par defaut.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::enregistrerFichierTournoi()
{
	tournoiXml_->SaveFile(nomListeTournois.c_str());
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::chargerFichierJoueur()
/////
///// Cette fonction ecrit les informations des joueurs courants dans le nom
///// de fichier par defaut.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::chargerFichierJoueur()
{
	joueurXml_->LoadFile( nomListeJoueurs.c_str() );
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::chargerFichierTournoi()
/////
///// Cette fonction ecrit les informations des joueurs courants dans le nom
///// de fichier par defaut.
/////
///// @return Aucune.
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::chargerFichierTournoi()
{
	tournoiXml_->LoadFile(nomListeTournois.c_str());
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn int GestionJoueur::obtenirNombreParcours(const std::string nomTournoi)
/////
///// Cette fonction retourne le nombre de parcours present dans le fichier
///// TiXmlDocument* tournoiXml_ present sous le tournoi passe en parametre.
/////
/////	@param[in] const std::string nomTournoi
///// @return int nombre de parcours dans tournoiXml_ ayant pour 
///// nom de tournoi la valeur en parametre.
/////
//////////////////////////////////////////////////////////////////////////
int GestionJoueur::obtenirNombreParcours(const std::string nomTournoi)
{
	int nbtotalParcours=0;
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	TiXmlElement* tournoi=child->FirstChildElement(nomTournoi.c_str());
	TiXmlElement* objenfant=tournoi->FirstChildElement();
	if(tournoi!=nullptr)
	{
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				nbtotalParcours+=1;			
			}

		}
	}
	return nbtotalParcours; 
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn int GestionJoueur::obtenirNombreTournois()
/////
///// Cette fonction retourne le nombre de tournois present dans le fichier
///// TiXmlDocument* tournoiXml_
/////
///// @return int nombre de tournois dans tournoiXml_.
/////
//////////////////////////////////////////////////////////////////////////
int GestionJoueur::obtenirNombreTournois()
{
	int nbtotalTournoi=0;
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	TiXmlElement* objenfant=child->FirstChildElement();
	if(child!=nullptr)
	{
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				nbtotalTournoi+=1;			
			}
		}
	}
	return nbtotalTournoi; 
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn std::vector<std::string> GestionJoueur::obtenirNomsParcours(const std::string nomTournoi)
/////
///// Cette fonction retourne le vector de string contenant les
/////
///// @param[in] const std::string nomTournoi
///// @return std::vector<std::string> pointeur au tableau de string de taille obtenirNombreParcours
/////
//////////////////////////////////////////////////////////////////////////
std::vector<std::string> GestionJoueur::obtenirNomsParcours(const std::string nomTournoi)
{
	std::vector<std::string> temp;
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	TiXmlElement* tournoi=child->FirstChildElement(nomTournoi.c_str());
	if(tournoi!=nullptr)
	{
		TiXmlElement* objenfant=tournoi->FirstChildElement();
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				temp.push_back(objenfant->Value());			
			}
		}
	}
	return temp; 
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn std::vector<std::string> GestionJoueur::obtenirNomsTournois()
/////
///// Cette fonction retourne un vector de string
/////
///// @return std::vector<std::string> Des tournois present dans le fichier.
/////
//////////////////////////////////////////////////////////////////////////

std::vector<std::string> GestionJoueur::obtenirNomsTournois()
{
	std::vector<std::string> temp;
	TiXmlHandle docHandle(tournoiXml_);
	TiXmlElement* child = docHandle.FirstChild("listeTournois").ToElement();
	if(child!=nullptr)
	{
		TiXmlElement* objenfant=child->FirstChildElement();
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				temp.push_back(objenfant->Value());			
			}
		}
	}
	return temp;
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn int GestionJoueur::obtenirNombreJoueursTableauMeilleurScore()
/////
///// Cette fonction retourne un int du nombre de joueurs dans le fichier joueurXml_
/////
///// @return int joueurs present dans le fichier joueurXml_.
/////
//////////////////////////////////////////////////////////////////////////
int GestionJoueur::obtenirNombreJoueursTableauMeilleurScore()
{
	int nbtotalJoueur=0;
	TiXmlHandle docHandle(joueurXml_);
	TiXmlElement* child = docHandle.FirstChild("listeJoueurs").ToElement();
	TiXmlElement* objenfant=child->FirstChildElement();
	if(child!=nullptr)
	{
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				nbtotalJoueur+=1;			
			}
		}
	}
	return nbtotalJoueur;
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn int GestionJoueur::obtenirNombreParcoursTableauMeilleurScore(const std::string nomJoueur)
/////
///// Cette fonction retourne un int du nombre de parcours assigne au joueur en parametre dans le fichier joueurXml_
/////
///// @return int parcours assigne au joueur en parametre present dans le fichier joueurXml_.
/////
//////////////////////////////////////////////////////////////////////////
int GestionJoueur::obtenirNombreParcoursTableauMeilleurScore(const std::string nomJoueur)
{
	int nbtotalParcours=0;
	TiXmlHandle docHandle(joueurXml_);
	TiXmlElement* child = docHandle.FirstChild("listeJoueurs").FirstChild(nomJoueur.c_str()).ToElement();
	TiXmlElement* objenfant=child->FirstChildElement();
	if(child!=nullptr)
	{
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				nbtotalParcours+=1;			
			}
		}
	}
	return nbtotalParcours;
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn std::vector<std::string> GestionJoueur::obtenirNomsParcoursTableauMeilleurScore(const std::string nomJoueur)
/////
///// Cette fonction retourne les noms de parcours present sous le joueur
/////
///// @return std::vector<std::string> parcours presents sous le joueur dans joueurXML_.
/////
//////////////////////////////////////////////////////////////////////////
std::vector<std::string> GestionJoueur::obtenirNomsParcoursTableauMeilleurScore(const std::string nomJoueur)
{
	std::vector<std::string> temp;
	TiXmlHandle docHandle(joueurXml_);
	TiXmlElement* child = docHandle.FirstChild("listeJoueurs").FirstChild(nomJoueur.c_str()).ToElement();
	if(child!=nullptr)
	{
		TiXmlElement* objenfant=child->FirstChildElement();
		if(objenfant!=nullptr)
		{
			for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement())
			{
				temp.push_back(objenfant->Value());			
			}
		}
	}
	return temp;

}


//////////////////////////////////////////////////////////////////////////
/////
///// @fn int GestionJoueur::obtenirMeilleurScoreJoueur(const std::string nomJoueur, const std::string nomParcours)
/////
///// Cette fonction retourne un int du nombre de parcours assigne au joueur en parametre dans le fichier joueurXml_
/////
///// @return int parcours assigne au joueur en parametre present dans le fichier joueurXml_.
/////
//////////////////////////////////////////////////////////////////////////
int GestionJoueur::obtenirMeilleurScoreJoueur(const std::string nomJoueur, const std::string nomParcours)
{
	int score=0;
	TiXmlHandle docHandle(joueurXml_);
	TiXmlElement* child = docHandle.FirstChild("listeJoueurs").FirstChild(nomJoueur.c_str()).ToElement();
	if(child!=nullptr)
	{
		TiXmlElement* objenfant=child->FirstChild(nomParcours.c_str())->ToElement();
		if(objenfant!=nullptr)
		{
			objenfant->QueryIntAttribute("Score",&score);
		}
	}
	return score;
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::sauvegarderMultijoueur(const std::string NomMap)
/////
///// Cette methode de controle permet de sauvegarder les informations relatives au joueur pour pouvoir les retablir par replay et multijoueur.
/////
///// @return NILL
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::sauvegarderMultijoueur(const std::string NomMap)
{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	std::string nomJoueurCourant=facade->obtenirJoueurCourant();
	ArbreRenduINF2990* arbre=facade->obtenirArbreRenduINF2990();
	Vecteur3 positioncourante,positionPrecedente;
	double anglePrecedent,forcePredecent;
	int NombreCoups = facade->obtenirNombreCoups();
	NoeudAbstrait* Noeud;
	Noeud=arbre->chercher("balle");
	positioncourante = Noeud->obtenirPositionRelative();
	positionPrecedente = Noeud->obtenirPositionInitiale();
	anglePrecedent = Noeud->obtenirAngleCoup();
	forcePredecent = Noeud->obtenirForce();			
	double angleAlea=GestionBalle::obtenirAngleAlea();
	
	
	TiXmlHandle docHandle(multijoueurXml_);
	TiXmlElement* child = docHandle.FirstChild(nomJoueurCourant.c_str()).ToElement();
	if (child==nullptr)
	{
		child= new TiXmlElement(nomJoueurCourant.c_str());
		multijoueurXml_->LinkEndChild(child);
	}
	double courantVec0= positioncourante[0];
	double courantVec1= positioncourante[1];
	double courantVec2= positioncourante[2];
	double precedentVec0= positionPrecedente[0];
	double precedentVec1= positionPrecedente[1];
	double precedentVec2= positionPrecedente[2];
	child->SetAttribute("MapCourante",NomMap.c_str());
	child->SetAttribute("NombreCoups",NombreCoups);
	child->SetDoubleAttribute("courantVec0",courantVec0);
	child->SetDoubleAttribute("courantVec1",courantVec1);
	child->SetDoubleAttribute("courantVec2",courantVec2);
	child->SetDoubleAttribute("precedentVec0",precedentVec0);
	child->SetDoubleAttribute("precedentVec1",precedentVec1);
	child->SetDoubleAttribute("precedentVec2",precedentVec2);
	child->SetDoubleAttribute("anglePrecedent",anglePrecedent);
	child->SetDoubleAttribute("forcePredecent",forcePredecent);
	child->SetDoubleAttribute("angleAlea",angleAlea);
	GestionBalle::reSeedAlea();
	GestionBalle::allowDeviation();
	multijoueurXml_->SaveFile(nomListeMultijoueur.c_str());
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::chargerMultijoueur(const std::string nomJoueur)
/////
///// Cette methode de controle permet de charger les informations relatives au joueur pour pouvoir les retablir en multijoueur.
/////
///// @param[in] const std::string nomJoueur
///// @return NILL
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::chargerMultijoueur(const std::string nomJoueur)
{
	//multijoueurXml_->LoadFile(nomListeMultijoueur.c_str());
	//FacadeModele* facade=FacadeModele::obtenirInstance();
	//ArbreRenduINF2990* arbre=facade->obtenirArbreRenduINF2990();
	//TiXmlHandle docHandle(multijoueurXml_);
	//TiXmlElement* child = docHandle.FirstChild(nomJoueur.c_str()).ToElement();
	//if(child!=nullptr)
	//{
	//	double courantVec0, courantVec1, courantVec2;
	//	double precedentVec0, precedentVec1, precedentVec2;
	//	double anglePrecedent, forcePredecent;
	//	Vecteur3 courant, precedent;
	//	child->QueryDoubleAttribute("courantVec0",&courantVec0);
	//	child->QueryDoubleAttribute("courantVec1",&courantVec1);
	//	child->QueryDoubleAttribute("courantVec2",&courantVec2);
	//	child->QueryDoubleAttribute("precedentVec0",&precedentVec0);
	//	child->QueryDoubleAttribute("precedentVec1",&precedentVec1);
	//	child->QueryDoubleAttribute("precedentVec2",&precedentVec2);
	//	std::string Map = child->Attribute("MapCourante");
	//	int NombreCoups;
	//	child->QueryIntAttribute("NombreCoups",&NombreCoups);
	//	child->QueryDoubleAttribute("anglePrecedent",&anglePrecedent);
	//	child->QueryDoubleAttribute("forcePredecent",&forcePredecent);
	//	facade->chargerXml(Map);
	//	facade->assignerNomJoueur(nomJoueur);
	//	facade->assignerNombreCoups(NombreCoups);
	//	courant[0]=courantVec0;courant[1]=courantVec1;courant[2]=courantVec2;
	//	precedent[0]=precedentVec0;precedent[1]=precedentVec1;precedent[2]=precedentVec2;
	//	arbre->assignerPositionInitiale(precedent);
	//	arbre->assignerPositionRelative(courant);
	//	arbre->assignerAngleCoup(anglePrecedent);
	//	arbre->assignerForce(forcePredecent);
	//}
	multijoueurXml_->LoadFile(nomListeMultijoueur.c_str());
	FacadeModele* facade=FacadeModele::obtenirInstance();
	ArbreRenduINF2990* arbre=facade->obtenirArbreRenduINF2990();
	TiXmlHandle docHandle(multijoueurXml_);
	TiXmlElement* child = docHandle.FirstChild(nomJoueur.c_str()).ToElement();
	if(child!=nullptr)
	{
		//double courantVec0, courantVec1, courantVec2;
		double precedentVec0, precedentVec1, precedentVec2;
		double anglePrecedent, forcePredecent;
		Vecteur3 courant, precedent;
		//child->QueryDoubleAttribute("courantVec0",&courantVec0);
		//child->QueryDoubleAttribute("courantVec1",&courantVec1);
		//child->QueryDoubleAttribute("courantVec2",&courantVec2);
		child->QueryDoubleAttribute("precedentVec0",&precedentVec0);
		child->QueryDoubleAttribute("precedentVec1",&precedentVec1);
		child->QueryDoubleAttribute("precedentVec2",&precedentVec2);
		std::string Map = child->Attribute("MapCourante");
		int NombreCoups;
		child->QueryIntAttribute("NombreCoups",&NombreCoups);
		child->QueryDoubleAttribute("anglePrecedent",&anglePrecedent);
		child->QueryDoubleAttribute("forcePredecent",&forcePredecent);
		facade->chargerXml(Map);
		facade->assignerNomJoueur(nomJoueur);
		facade->assignerNombreCoups(NombreCoups);
		//courant[0]=courantVec0;courant[1]=courantVec1;courant[2]=courantVec2;
		precedent[0]=precedentVec0;precedent[1]=precedentVec1;precedent[2]=precedentVec2;
		//arbre->assignerPositionInitiale(precedent);
		//arbre->assignerPositionRelative(courant);
		//arbre->assignerAngleCoup(anglePrecedent);
		//arbre->assignerForce(forcePredecent);
		facade->obtenirInstance()->assignerModeReplay(true);
		facade->creerFleche();
		facade->effacerFleche();
		arbre->chercher("baton")->assignerFacteurAgrandissement(0);
		arbre->chercher("balle")->assignerPositionRelative(precedent);
		arbre->chercher("balle")->initialiserVitesse(anglePrecedent,forcePredecent);

		

	}
}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::chargerMultijoueur(const std::string nomJoueur)
/////
///// Cette methode de controle permet de charger les informations necessaires a effectuer un replay.
///// @param[in] const std::string nomJoueur
///// @return NILL
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::chargerReplay(const std::string nomJoueur)
{
	multijoueurXml_->LoadFile(nomListeMultijoueur.c_str());
	FacadeModele* facade=FacadeModele::obtenirInstance();
	ArbreRenduINF2990* arbre=facade->obtenirArbreRenduINF2990();
	TiXmlHandle docHandle(multijoueurXml_);
	TiXmlElement* child = docHandle.FirstChild(nomJoueur.c_str()).ToElement();
	if(child!=nullptr)
	{
		double precedentVec0, precedentVec1, precedentVec2;
		double anglePrecedent, forcePredecent,angleAlea;
		Vecteur3 courant, precedent;
		child->QueryDoubleAttribute("precedentVec0",&precedentVec0);
		child->QueryDoubleAttribute("precedentVec1",&precedentVec1);
		child->QueryDoubleAttribute("precedentVec2",&precedentVec2);
		std::string Map = child->Attribute("MapCourante");
		int NombreCoups;
		child->QueryIntAttribute("NombreCoups",&NombreCoups);
		child->QueryDoubleAttribute("anglePrecedent",&anglePrecedent);
		child->QueryDoubleAttribute("forcePredecent",&forcePredecent);
		child->QueryDoubleAttribute("angleAlea",&angleAlea);
		GestionBalle::modifierAngleAlea(angleAlea);
		facade->chargerXml(Map);
		facade->assignerNomJoueur(nomJoueur);
		facade->assignerNombreCoups(NombreCoups);
		precedent[0]=precedentVec0;precedent[1]=precedentVec1;precedent[2]=precedentVec2;

		facade->obtenirInstance()->assignerModeReplay(true);
		facade->creerFleche();
		facade->effacerFleche();
		arbre->chercher("baton")->assignerFacteurAgrandissement(0);
		arbre->chercher("balle")->assignerPositionRelative(precedent);
		arbre->chercher("balle")->initialiserVitesse(anglePrecedent,forcePredecent);
	}

}
//////////////////////////////////////////////////////////////////////////
/////
///// @fn void GestionJoueur::effacerFichierJoueur()
/////
///// Cette methode permet d'effacer le fichier Joueur de tableau de meilleurs scores.
///// @return NILL
/////
//////////////////////////////////////////////////////////////////////////
void GestionJoueur::effacerFichierJoueur()
{
	if(utilitaire::fichierExiste(nomListeJoueurs.c_str()))
	{
		joueurXml_->Clear();
		remove(nomListeJoueurs.c_str());	
	}
}
/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
