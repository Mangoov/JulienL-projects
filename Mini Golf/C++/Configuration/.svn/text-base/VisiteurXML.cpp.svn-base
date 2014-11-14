///////////////////////////////////////////////////////////////////////////
/// @file VisiteurXML.cpp
/// @author Manraj Ashley
/// @date 09/25/2011
/// @version
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "VisiteurXML.h"
#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "ArbreRendu.h"

#include <vector>
#include <string>
/// Pointeur vers l'instance unique de la classe.
VisiteurXML* VisiteurXML::instance_ = 0;
int VisiteurXML::Par_ = 0;
////////////////////////////////////////////////////////////////////////
///	@fn VisiteurXML::VisiteurXML()
/// 
/// Ce constructeur initialise un pointeur representant la racine
///	du document
///
///	@return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurXML::VisiteurXML()
{	
	ficXml_=new TiXmlDocument();

}


////////////////////////////////////////////////////////////////////////
///	@fn VisiteurXML::~VisiteurXML()
///
///	Ce destructeur libère le pointeur initialise par le constructeur
///					
///	@return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurXML::~VisiteurXML()
{
	delete ficXml_;
}
VisiteurXML* VisiteurXML::obtenirInstance()
{
	if(instance_==nullptr)
	{
		instance_=new VisiteurXML();
	}
	return instance_;
}


////////////////////////////////////////////////////////////////////////
///	@fn VisiteurXML::libererInstance()
///
/// Implementation Singleton pour le gestionnaire XML.
/// Permet d'obtenir l'instance.
/// 
///
///	@return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::libererInstance()
{
	delete instance_;
	instance_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXML::visiterNoeudAbstrait(NoeudAbstrait* noeud)
///
/// Cette methode visite un noeud abstrait et cree l'element xml
///	correspondant.
///
///	@param[in]	noeud : noeud abstrait a visiter
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::visiterNoeudAbstrait(NoeudAbstrait* noeud)
{	
	TiXmlHandle docHandle(ficXml_);
	{
		if(noeud->estEnregistrable()==true)
		{
			if (noeud->obtenirType().compare("\0")!=0)
			{
				std::string parametre= noeud->obtenirType();
				int obtenirNombreEnfants=noeud->obtenirNombreEnfants();
				float obtenirFacteurAgrandissement=noeud->obtenirFacteurAgrandissment();
				float obtenirFacteurRotation=noeud->obtenirRot();
				TiXmlElement* elementScene = new TiXmlElement(parametre.c_str());
				TiXmlElement* elementAbstrait= new TiXmlElement("abstrait");
				if(parametre=="terrain")
				{
					elementAbstrait->SetAttribute("par",Par_);
				}
				parametre=boolToString(noeud->estAffiche());
				elementAbstrait->SetAttribute("estAffiche",parametre.c_str());
				parametre=boolToString(noeud->estSelectionnable());
				elementAbstrait->SetAttribute("estSelectionnable",parametre.c_str());
				parametre=boolToString(false);
				elementAbstrait->SetAttribute("estSelectionne",parametre.c_str());
				parametre=noeud->obtenirNombreEnfants();
				elementAbstrait->SetAttribute("obtenirNombreEnfants",obtenirNombreEnfants);
				elementAbstrait->SetDoubleAttribute("obtenirFacteurAgrandissment",obtenirFacteurAgrandissement);
				elementAbstrait->SetDoubleAttribute("obtenirFacteurRotation",obtenirFacteurRotation);
				parametre=boolToString(noeud->obtenirPortalLinked());
				elementAbstrait->SetAttribute("isPortalLinked",parametre.c_str());
				parametre=boolToString(noeud->obtenirPortalType());
				elementAbstrait->SetAttribute("PortalType",parametre.c_str());

				double parametreVec0=noeud->obtenirPositionRelative()[0];
				double parametreVec1= noeud->obtenirPositionRelative()[1];
				double parametreVec2= noeud->obtenirPositionRelative()[2];
				double parametreBorMin0=noeud->obtenirCoinBordureMin()[0];
				double parametreBorMin1= noeud->obtenirCoinBordureMin()[1];
				double parametreBorMin2= noeud->obtenirCoinBordureMin()[2];
				double parametreBorMax0= noeud->obtenirCoinBordureMax()[0];
				double parametreBorMax1= noeud->obtenirCoinBordureMax()[1];
				double parametreBorMax2= noeud->obtenirCoinBordureMax()[2];
				double positionPorta0 = noeud->obtenirPosLinkingPortal()[0];
				double positionPorta1 = noeud->obtenirPosLinkingPortal()[1];
				double positionPorta2 = noeud->obtenirPosLinkingPortal()[2];

				elementAbstrait->SetDoubleAttribute("parametreVec0",parametreVec0);
				elementAbstrait->SetDoubleAttribute("parametreVec1",parametreVec1);
				elementAbstrait->SetDoubleAttribute("parametreVec2",parametreVec2);
				elementAbstrait->SetDoubleAttribute("parametreBorMin0",parametreBorMin0);

				elementAbstrait->SetDoubleAttribute("parametreBorMin1",parametreBorMin1);
				elementAbstrait->SetDoubleAttribute("parametreBorMin2",parametreBorMin2);
				elementAbstrait->SetDoubleAttribute("parametreBorMax0",parametreBorMax0);
				elementAbstrait->SetDoubleAttribute("parametreBorMax1",parametreBorMax1);
				elementAbstrait->SetDoubleAttribute("parametreBorMax2",parametreBorMax2);

				elementAbstrait->SetDoubleAttribute("PositionPortal0",positionPorta0);
				elementAbstrait->SetDoubleAttribute("PositionPortal1",positionPorta1);
				elementAbstrait->SetDoubleAttribute("PositionPortal2",positionPorta2);

				elementScene->LinkEndChild(elementAbstrait);
				ficXml_->LinkEndChild(elementScene);
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXML::visiterNoeudComposite(NoeudComposite* noeud)
///
/// Cette methode visite un noeud composite et ses enfants de facon
/// recursive. 
///
///	@param[in]	noeud : noeud composite a visiter
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::visiterNoeudComposite(NoeudComposite* noeud)
{
	TiXmlHandle docHandle(ficXml_);
	{
		if(noeud->estEnregistrable()==true)
		{
			if (noeud->obtenirType().compare("\0")!=0)// Peu importe le nombre d'enfant du noeud composite 
				// l arbre se charge d'appeler visiter sur les noeuds enfants
			{
				std::string parametre= noeud->obtenirType();
				int obtenirNombreEnfants=noeud->obtenirNombreEnfants();
				float obtenirFacteurAgrandissement=noeud->obtenirFacteurAgrandissment();
				float obtenirFacteurRotation=noeud->obtenirRot();
				TiXmlElement* elementScene = new TiXmlElement(parametre.c_str());
				TiXmlElement* elementCompo= new TiXmlElement("composite");
				parametre=boolToString(noeud->estAffiche());
				elementCompo->SetAttribute("estAffiche",parametre.c_str());
				parametre=boolToString(noeud->estSelectionnable());
				elementCompo->SetAttribute("estSelectionnable",parametre.c_str());
				parametre=boolToString(false);
				elementCompo->SetAttribute("estSelectionne",parametre.c_str());
				parametre=noeud->obtenirNombreEnfants();
				elementCompo->SetAttribute("obtenirNombreEnfants",obtenirNombreEnfants);
				elementCompo->SetDoubleAttribute("obtenirFacteurAgrandissment",obtenirFacteurAgrandissement);
				elementCompo->SetDoubleAttribute("obtenirFacteurRotation",obtenirFacteurRotation);
				double parametreVec0=noeud->obtenirPositionRelative()[0];
				double parametreVec1= noeud->obtenirPositionRelative()[1];
				double parametreVec2= noeud->obtenirPositionRelative()[2];
				elementCompo->SetDoubleAttribute("parametreVec0",parametreVec0);
				elementCompo->SetDoubleAttribute("parametreVec1",parametreVec1);
				elementCompo->SetDoubleAttribute("parametreVec2",parametreVec2);
				elementScene->LinkEndChild(elementCompo);
				ficXml_->LinkEndChild(elementScene);
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXML::ecrireFichier(ArbreRendu* arbre,std::string nomFichier)
///
/// Cette methode ecrit un fichier xml ayant pour nom nomFichier contenant la configuration
///	du jeu.
///
///	@param[in]	arbre : Arbre courant de l'arbre de rendu
///	@param[in]	nomFichier : nom du fichier xml
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::ecrireFichier(ArbreRendu* arbre,std::string nomFichier)
{
	ficXml_->Clear();
	for( unsigned int i = 0; i < (arbre->obtenirNombreEnfants()); i++)
	{
		if(arbre->chercher(i) != NULL)
		{

			if(arbre->chercher(i)->estEnregistrable())
			{
				arbre->chercher(i)->accueillirVisiteurXML((*obtenirInstance()));
			}
		}
	}
	ficXml_->SaveFile(nomFichier.c_str());
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXML::effacerArbreXml()
///
/// Cette methode efface l'arbre de pointeurs de l'xml.
///
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::effacerArbreXml()
{
	ficXml_->Clear();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXML::assignerPar(const int Par)
///
/// Cette methode permet d'assigner le par
///
///	@param[in]	Par : le valeur du Par
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::assignerPar(const int Par)
{
	Par_=Par;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn TiXmlDocument* VisiteurXML::obtenirArbreXML()
///
/// Cette methode permet l'acces a l arbre XML
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
TiXmlDocument* VisiteurXML::obtenirArbreXML() const
{
	return ficXml_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn TiXmlDocument* VisiteurXML::lireFichierXML(ArbreRendu* arbre,std::string nomFichier)
///
/// Cette methode permet d'ouvrir une carte sauvegardee en XML pour la charger dans
/// l'arbre de rendu.
///	@param[in]	arbre : Arbre courant de l'arbre de rendu
///	@param[in]	nomFichier : nom du fichier xml
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::lireFichierXML(ArbreRendu* arbre,std::string nomFichier)
{
	ficXml_->Clear();
	ficXml_->LoadFile(nomFichier.c_str());
	TiXmlHandle docHandle(ficXml_);
	TiXmlElement* child = docHandle.FirstChild().ToElement();
	if (child!=NULL)
	{
		for( child; child; child=child->NextSiblingElement() )
		{
			chargerInfo(arbre,child);
		}
	}
	ficXml_->Clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn TiXmlDocument* VisiteurXML::chargerInfo(ArbreRendu* arbre,TiXmlElement* noeud)
///
/// Cette methode permet de loader les informations d'un noeud et de ses enfants dans l'arbre passe en parametres.
///	@param[in]	arbre : Arbre courant de l'arbre de rendu
///	@param[in]	noeud : noeud ayant probablement des enfants
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::chargerInfo(ArbreRendu* arbre,TiXmlElement* noeud)
{
	TiXmlElement* obj;
	TiXmlElement* objenfant;
	std::string name ,estAffiche,estSelectionnable,estSelectionne;
	int obtenirNombreEnfants, Par=0;
	bool estAffiche_=false,estSelectionnable_=false,estSelectionne_=false,isPortalLinked_=false, portalType_=false;
	double parametreVec0, parametreVec1, parametreVec2;
	double parametreBorMin0, parametreBorMin1, parametreBorMin2;
	double parametreBorMax0, parametreBorMax1, parametreBorMax2;
	double PositionPortal0, PositionPortal1, PositionPortal2;
	double facteurAgrandissement,obtenirFacteurRotation;
	float facteurAgrandissementConverti,obtenirFacteurRotationConverti;
	Vecteur3 position,coinBordureMin,coinBordureMax;
	NoeudAbstrait* noeudAjout;
	NoeudComposite* noeudCompo,noeudCompoInf;

	name=noeud->Value();
	obj=noeud->FirstChildElement();
	std::string etatobj=obj->Value();
	//Obtention des parametres du noeud
	if(etatobj.compare("abstrait")==0)//Un noeud abstrait sans enfant
	{
		estAffiche=obj->Attribute("estAffiche");
		if(estAffiche.compare("0")==0)
		{
			estAffiche_=false;
		}
		else
		{
			if(estAffiche.compare("1")==0)
				estAffiche_=true;
			else
				std::cerr << "Erreur : estAffiche : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
		}
		estSelectionnable=obj->Attribute("estSelectionnable");
		if(estSelectionnable.compare("0")==0)
		{
			estSelectionnable_=false;
		}
		else
		{
			if(estSelectionnable.compare("1")==0)
				estSelectionnable_=true;
			else
				std::cerr << "Erreur : estSelectionnable : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
		}
		estSelectionne=obj->Attribute("estSelectionne");
		if(estSelectionne.compare("0")==0)
		{
			estSelectionne_=false;
		}
		else
		{
			if(estSelectionne.compare("1")==0)
				estSelectionne_=true;
			else
				std::cerr << "Erreur : estSelectionne : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
		}
		std::string isPortalLinked=obj->Attribute("isPortalLinked");
		if(isPortalLinked.compare("0")==0)
		{
			isPortalLinked_=false;
		}
		else
		{
			if(isPortalLinked.compare("1")==0)
				isPortalLinked_=true;
			else
				std::cerr << "Erreur : estSelectionne : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
		}


		std::string portalType=obj->Attribute("PortalType");
		if(portalType.compare("0")==0)
		{
			portalType_=false;
		}
		else
		{
			if(portalType.compare("1")==0)
				portalType_=true;
			else
				std::cerr << "Erreur : estSelectionne : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
		}

		obj->QueryIntAttribute("obtenirNombreEnfants",&obtenirNombreEnfants);
		obj->QueryDoubleAttribute("obtenirFacteurAgrandissment",&facteurAgrandissement);
		obj->QueryDoubleAttribute("parametreVec0",&parametreVec0);
		obj->QueryDoubleAttribute("parametreVec1",&parametreVec1);
		obj->QueryDoubleAttribute("parametreVec2",&parametreVec2);
		obj->QueryDoubleAttribute("parametreBorMin0",&parametreBorMin0);
		obj->QueryDoubleAttribute("parametreBorMin1",&parametreBorMin1);
		obj->QueryDoubleAttribute("parametreBorMin2",&parametreBorMin2);
		obj->QueryDoubleAttribute("parametreBorMax0",&parametreBorMax0);
		obj->QueryDoubleAttribute("parametreBorMax1",&parametreBorMax1);
		obj->QueryDoubleAttribute("parametreBorMax2",&parametreBorMax2);

		obj->QueryDoubleAttribute("PositionPortal0",&PositionPortal0);
		obj->QueryDoubleAttribute("PositionPortal1",&PositionPortal1);
		obj->QueryDoubleAttribute("PositionPortal2",&PositionPortal2);

		obj->QueryDoubleAttribute("obtenirFacteurRotation",&obtenirFacteurRotation);
		//Creation du noeud a ajouter a l arbre
		noeudAjout=arbre->creerNoeud(name);
		noeudAjout->assignerAffiche(estAffiche_);
		noeudAjout->assignerEstSelectionnable(estSelectionnable_);
		noeudAjout->assignerEstEnregistrable(true);
		noeudAjout->assignerSelection(estSelectionne_);
		position[0]=parametreVec0;position[1]=parametreVec1;position[2]=parametreVec2;
		coinBordureMin[0]=parametreBorMin0;coinBordureMin[1]=parametreBorMin1;coinBordureMin[2]=parametreBorMin2;
		coinBordureMax[0]=parametreBorMax0;coinBordureMax[1]=parametreBorMax1;coinBordureMax[2]=parametreBorMax2;
		noeudAjout->assignerPositionRelative(position);
		noeudAjout->assignerCoinBordure(coinBordureMin,coinBordureMax);
		noeudAjout->assignerPortalLinked(isPortalLinked_);

		noeudAjout->assignerPortalType(portalType_);
		

		position[0]=PositionPortal0;position[1]=PositionPortal1;position[2]=PositionPortal2;
		noeudAjout->linkPortal(position);
		facteurAgrandissementConverti=(float) facteurAgrandissement;
		obtenirFacteurRotationConverti=(float) obtenirFacteurRotation;
		noeudAjout->assignerFacteurAgrandissement(facteurAgrandissementConverti);
		noeudAjout->assignerRot(obtenirFacteurRotationConverti);
		if(name=="terrain")
		{
			obj->QueryIntAttribute("par",&Par);
			noeudAjout->assignerPar(Par);
		}
		arbre->ajouter(noeudAjout);
	}
	else
	{

		if(etatobj.compare("composite")==0&&obj->NoChildren()==true)//Un objet composite sans enfant
		{
			estAffiche=obj->Attribute("estAffiche");
			if(estAffiche.compare("0")==0)
			{
				estAffiche_=false;
			}
			else
			{
				if(estAffiche.compare("1")==0)
					estAffiche_=true;
				else
					std::cerr << "Erreur : estAffiche : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
			}
			estSelectionnable=obj->Attribute("estSelectionnable");
			if(estSelectionnable.compare("0")==0)
			{
				estSelectionnable_=false;
			}
			else
			{
				if(estSelectionnable.compare("1")==0)
					estSelectionnable_=true;
				else
					std::cerr << "Erreur : estSelectionnable : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
			}
			estSelectionne=obj->Attribute("estSelectionne");
			if(estSelectionne.compare("0")==0)
			{
				estSelectionne_=false;
			}
			else
			{
				if(estSelectionne.compare("1")==0)
					estSelectionne_=true;
				else
					std::cerr << "Erreur : estSelectionne : chargement XML : attribut inexistant ou de valeur incorrect" << std::endl;
			}
			obj->QueryIntAttribute("obtenirNombreEnfants",&obtenirNombreEnfants);
			obj->QueryDoubleAttribute("obtenirFacteurAgrandissment",&facteurAgrandissement);
			obj->QueryDoubleAttribute("obtenirFacteurRotation",&obtenirFacteurRotation);
			obj->QueryDoubleAttribute("parametreVec0",&parametreVec0);
			obj->QueryDoubleAttribute("parametreVec1",&parametreVec1);
			obj->QueryDoubleAttribute("parametreVec2",&parametreVec2);
			//Creation du noeud a ajouter a l arbre
			noeudCompo=new NoeudComposite(name);
			noeudCompo->assignerAffiche(estAffiche_);
			noeudCompo->assignerEstSelectionnable(estSelectionnable_);
			noeudCompo->assignerEstEnregistrable(true);
			noeudCompo->assignerSelection(estSelectionne_);
			position[0]=parametreVec0;position[1]=parametreVec1;position[2]=parametreVec2;
			noeudCompo->assignerPositionRelative(position);
			
			facteurAgrandissementConverti=(float) facteurAgrandissement;
			obtenirFacteurRotationConverti=(float) obtenirFacteurRotation;
			noeudCompo->assignerFacteurAgrandissement(facteurAgrandissementConverti);
			noeudCompo->assignerRot(obtenirFacteurRotationConverti);
			arbre->ajouter(noeudCompo);
		}
		else if(etatobj.compare("composite")==0&&obj->NoChildren()==false)//Un noeud composite avec des enfants
		{
			objenfant=obj->FirstChildElement();
			if(objenfant!=NULL)
			{
				for( objenfant; objenfant; objenfant=objenfant->NextSiblingElement() )
				{
					chargerInfo(arbre,objenfant);
				}
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn TiXmlDocument* VisiteurXML::boolToString(const bool valeur)
///
/// Cette methode permet de transformer un booleen en un string contenant
/// la valeur binaire correspondante.
///
///	@param[in]	valeur: valeur à convertir
///				
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
std::string VisiteurXML::boolToString(const bool valeur)
{
	if(valeur==true)
	{
		return "1";
	}
	else
	{
		return "0";
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn TiXmlDocument* VisiteurXML::effacerFichierXml(const std::string nomFichierEffacer)
///
/// Cette methode permet de detruire un fichier xml existant.
/// la valeur binaire correspondante.
///
///	@param[in]	valeur: valeur à convertir
///				
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXML::effacerFichierXml(const std::string nomFichierEffacer)
{
	if(utilitaire::fichierExiste(nomFichierEffacer))
	{
		remove(nomFichierEffacer.c_str());
		ficXml_->Clear();
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn TiXmlDocument* VisiteurXML::obtenirPardeMap(const std::string map)
///
/// Cette methode permet d'obtenir le par de la map passe en parametre.
///
///	@param[in]	const std::string map
///				
///
/// @return int Par de la map.
///
////////////////////////////////////////////////////////////////////////
int VisiteurXML::obtenirPardeMap(const std::string map)
{
	ficXml_->Clear();
	ficXml_->LoadFile(map.c_str());
	TiXmlHandle docHandle(ficXml_);
	TiXmlElement* child = docHandle.FirstChild("terrain").ToElement();
	TiXmlElement* obj= docHandle.FirstChild("terrain").FirstChild("abstrait").ToElement();
	int Par;
	if(child !=nullptr)
	{
		if(obj!=nullptr)
		{
			obj->QueryIntAttribute("par",&Par);
		}
	}
	return Par;
	ficXml_->Clear();
}

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////