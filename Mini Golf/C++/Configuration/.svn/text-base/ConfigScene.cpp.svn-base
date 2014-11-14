////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author Manraj Ashley, quadriciel de base par Jean-Francois Pérusse
/// @date 2011-30-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <stdio.h>
#include <iostream>

SINGLETON_DECLARATION_CPP(ConfigScene);

/// Nombre de calculs par image.
int ConfigScene::CALCULS_PAR_IMAGE   = 50;
////////////////////////////////////////////////////////////////////////
///	@fn ConfigScene::ConfigScene()
/// 
/// Ce constructeur initialise un pointeur representant la racine
///	du document
///
///	@return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::ConfigScene()
{
	confXml_=new TiXmlDocument();
	Xmlvide("configuration.xml");
}
////////////////////////////////////////////////////////////////////////
///	@fn ConfigScene::~ConfigScene()
///
///	Ce destructeur libère le pointeur initialise par le constructeur
///					
///	@return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::~ConfigScene()
{
	delete confXml_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::creerDOM ( TiXmlNode& node ) const
///
/// Cette fonction écrit les valeurs de la configuration dans un élément XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::creerDOM ( TiXmlNode* node )
{
	// Créer le noeud 'configuration'
	TiXmlElement* elementConfiguration = new TiXmlElement("configuration");

	// Créer le noeud scene et définir ses attributs
	TiXmlElement* elementScene = new TiXmlElement("CScene");
	elementScene->SetAttribute("Calculs_par_image", 20);
	CALCULS_PAR_IMAGE=20;
	elementScene->SetDoubleAttribute("CoefFriSol",2);
	coefFriSol_=2;
	elementScene->SetDoubleAttribute("CoefFriSable",6);
	coefFriSable_=6;
	elementScene->SetDoubleAttribute("CoefRebondMur",0.95);
	coefRebondMur_=0.95;
	elementScene->SetDoubleAttribute("AccelBonus",0);
	accelBonus_=0;
	elementScene->SetAttribute("TailleEditionLargeur", 500);//Placeholder a modifier
	elementScene->SetAttribute("TailleEditionHauteur", 500);
	toucheClavier_[0]=37;
	toucheClavier_[1]=39;
	toucheClavier_[2]=38;
	toucheClavier_[3]=40;
	toucheClavier_[4]=32;
	tailleEdition_[0]=500;
	tailleEdition_[1]=500;
	toucheOptionClavier_.push_back("gauche");
	toucheOptionClavier_.push_back("droit");
	toucheOptionClavier_.push_back("haut");
	toucheOptionClavier_.push_back("bas");
	toucheOptionClavier_.push_back("espace");
	elementScene->SetAttribute("toucheClavierGauche", 37);
	elementScene->SetAttribute("toucheClavierDroit", 39);
	elementScene->SetAttribute("toucheClavierHaut", 38);
	elementScene->SetAttribute("toucheClavierBas", 40);
	elementScene->SetAttribute("toucheClavierEspace", 32);
	elementScene->SetAttribute("toucheOptionGauche", toucheOptionClavier_[0].c_str());
	elementScene->SetAttribute("toucheOptionDroit", toucheOptionClavier_[1].c_str());
	elementScene->SetAttribute("toucheOptionHaut", toucheOptionClavier_[2].c_str());
	elementScene->SetAttribute("toucheOptionBas", toucheOptionClavier_[3].c_str());
	elementScene->SetAttribute("toucheOptionEspace", toucheOptionClavier_[4].c_str());

	
	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementScene);

	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de libérer la mémoire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	node->LinkEndChild(elementConfiguration);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ConfigScene::chargerFichierConfig( const std::string nomFichier)
///
/// Cette fonction lit de nomFichier les parametres de configuration courant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool ConfigScene::chargerFichierConfig(const std::string nomFichier)
{
	// Lire à partir du fichier de configuration
	confXml_->LoadFile(nomFichier.c_str());
	// Tenter d'obtenir le noeud 'Configuration'
	const TiXmlElement* elementConfiguration = (TiXmlElement*)(confXml_->FirstChild("configuration"));
	if (elementConfiguration != NULL) 
	{
		// Tenter d'obtenir les elements de configurations de la scene.
		const TiXmlElement* elementScene = (TiXmlElement*)(elementConfiguration->FirstChild("CScene"));
		if (elementScene != NULL) 
		{
			if (elementScene->QueryIntAttribute("Calculs_par_image", &ConfigScene::CALCULS_PAR_IMAGE) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : CALCULS_PAR_IMAGE : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryDoubleAttribute("CoefFriSol", &coefFriSol_) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : CoefFriSol : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryDoubleAttribute("CoefFriSable", &coefFriSable_) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : CoefFriSable : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryDoubleAttribute("CoefRebondMur", &coefRebondMur_) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : CoefRebondMur : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryDoubleAttribute("AccelBonus", &accelBonus_) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : AccelBonus : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("TailleEditionLargeur", &tailleEdition_[0]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : TailleEditionLargeur : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("TailleEditionHauteur", &tailleEdition_[1]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : TailleEditionHauteur : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("toucheClavierGauche", &toucheClavier_[0]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : toucheClavierGauche : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("toucheClavierDroit", &toucheClavier_[1]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : toucheClavierDroit : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("toucheClavierHaut", &toucheClavier_[2]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : toucheClavierHaut : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("toucheClavierBas", &toucheClavier_[3]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : toucheClavierBas : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			if (elementScene->QueryIntAttribute("toucheClavierEspace", &toucheClavier_[4]) != TIXML_SUCCESS)
			{
				std::cerr << "Erreur : toucheClavierEspace : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				return false;
			}
			const char* toucheOptionTemp0;
			const char* toucheOptionTemp1;
			const char* toucheOptionTemp2;
			const char* toucheOptionTemp3;
			const char* toucheOptionTemp4;
			toucheOptionClavier_.clear();
			toucheOptionTemp0=elementScene->Attribute("toucheOptionGauche");
			toucheOptionClavier_.push_back(std::string(toucheOptionTemp0));
			toucheOptionTemp1=elementScene->Attribute("toucheOptionDroit");
			toucheOptionClavier_.push_back(std::string(toucheOptionTemp1));
			toucheOptionTemp2=elementScene->Attribute("toucheOptionHaut");
			toucheOptionClavier_.push_back(std::string(toucheOptionTemp2));
			toucheOptionTemp3=elementScene->Attribute("toucheOptionBas");
			toucheOptionClavier_.push_back(std::string(toucheOptionTemp3));
			toucheOptionTemp4=elementScene->Attribute("toucheOptionEspace");
			toucheOptionClavier_.push_back(std::string(toucheOptionTemp4));
		}
	}
	return true;



}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::ecrireFichierConfig(const std::string nomFichier)
///
/// Cette fonction ecrit les valeurs de la configuration courante dans le nom
/// de fichier passe en parametre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::enregistrerFichierConfig(const std::string nomFichier)
{
	TiXmlHandle docHandle(confXml_);

	// Tenter d'obtenir les elements de configurations de la scene.
	TiXmlElement* elementScene = docHandle.FirstChild("configuration").FirstChild("CScene").ToElement();
	elementScene->SetAttribute("Calculs_par_image", CALCULS_PAR_IMAGE);
	elementScene->SetDoubleAttribute("CoefFriSol",coefFriSol_);
	elementScene->SetDoubleAttribute("CoefFriSable",coefFriSable_);
	elementScene->SetDoubleAttribute("CoefRebondMur",coefRebondMur_);
	elementScene->SetDoubleAttribute("AccelBonus",accelBonus_);
	elementScene->SetAttribute("TailleEditionLargeur", tailleEdition_[0]);
	elementScene->SetAttribute("TailleEditionHauteur", tailleEdition_[1]);
	elementScene->SetAttribute("toucheClavierGauche", toucheClavier_[0]);
	elementScene->SetAttribute("toucheClavierDroit", toucheClavier_[1]);
	elementScene->SetAttribute("toucheClavierHaut", toucheClavier_[2]);
	elementScene->SetAttribute("toucheClavierBas", toucheClavier_[3]);
	elementScene->SetAttribute("toucheClavierEspace", toucheClavier_[4]);
	elementScene->SetAttribute("toucheOptionGauche", toucheOptionClavier_[0].c_str());
	elementScene->SetAttribute("toucheOptionDroit", toucheOptionClavier_[1].c_str());
	elementScene->SetAttribute("toucheOptionHaut", toucheOptionClavier_[2].c_str());
	elementScene->SetAttribute("toucheOptionBas", toucheOptionClavier_[3].c_str());
	elementScene->SetAttribute("toucheOptionEspace", toucheOptionClavier_[4].c_str());
	

	//// Adjoindre le noeud 'configuration' au noeud principal
	//// (Rappel : pas besoin de libérer la mémoire de elementConfiguration
	//// puisque toutes les fonctions Link... le font pour nous)
	confXml_->SaveFile( nomFichier.c_str() );
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::forcerSauvegardeConfig()
///
/// Cette fonction ecrit les valeurs de la configuration courante dans le nom
/// de fichier par defaut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::forcerSauvegardeConfig()
{
	enregistrerFichierConfig("configuration.xml");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::GetFileSize(const TCHAR *fileName)
///
/// Cette fonction ecrit les valeurs de la configuration courante dans le nom
/// de fichier passe en parametre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
long ConfigScene::GetFileSize(const TCHAR *fileName)
{
	bool                        fOk;
    WIN32_FILE_ATTRIBUTE_DATA   fileInfo;

    if (fileName==NULL)
        return -1;

    fOk = GetFileAttributesEx(fileName, GetFileExInfoStandard, (void*)&fileInfo);
    if (!fOk)
        return -1;
    assert(0 == fileInfo.nFileSizeHigh);
    return (long)fileInfo.nFileSizeLow;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn TCHAR* ConfigScene::stringToTCHAR(const std::string fileName)
///
/// Cette fonction ecrit les valeurs de la configuration courante dans le nom
/// de fichier passe en parametre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
TCHAR* ConfigScene::stringToTCHAR(const std::string fileName)
{
	TCHAR *param=new TCHAR[fileName.size()+1];
	param[fileName.size()]=0;
	//As much as we'd love to, we can't use memcpy() because
	//sizeof(TCHAR)==sizeof(char) may not be true:
	std::copy(fileName.begin(),fileName.end(),param);
	return param;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::Xmlvide(std::string nomFichier)
///
/// Cette fonction teste si l'xml existe ou si il est vide pour y
/// mettre des donnees par defaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::Xmlvide(const std::string nomFichier)
{
	if(utilitaire::fichierExiste(nomFichier)&&GetFileSize(stringToTCHAR(nomFichier))==0)
	{
		remove(nomFichier.c_str());
		creerDOM(confXml_);
		forcerSauvegardeConfig();

	}
	else if(!utilitaire::fichierExiste(nomFichier))
	{
			creerDOM(confXml_);
			forcerSauvegardeConfig();
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::obtenirToucheClavier(std::string nomFichier)
///
/// Cette fonction permet d'obtenir l'int code des touches du clavier.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
int* ConfigScene::obtenirToucheClavier()
{
	int toucheClavier[5];
	toucheClavier[0]=toucheClavier_[0];
	toucheClavier[1]=toucheClavier_[1];
	toucheClavier[2]=toucheClavier_[2];
	toucheClavier[3]=toucheClavier_[3];
	toucheClavier[4]=toucheClavier_[4];
	return toucheClavier;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::modifierToucheClavier(const int gauche,const int droit,const int haut ,const int bas,const int espace)
///
/// Cette fonction modifie les valeurs de touche de clavier assignee pour le mouvement du club.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::modifierToucheClavier(const int gauche,const int droit,const int haut ,const int bas,const int espace)
{
	toucheClavier_[0]=gauche;
	toucheClavier_[1]=droit;
	toucheClavier_[2]=haut;
	toucheClavier_[3]=bas;
	toucheClavier_[4]=espace;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn std::string * ConfigScene::obtenirOptionClavier()
///
/// Cette fonction permet l'obtention des informations liees aux touches du claviers.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
std::vector<std::string> ConfigScene::obtenirOptionClavier()
{
	//std::vector<std::string> toucheClavier;
	//toucheClavier.push_back(toucheOptionClavier_[0]);
	//toucheClavier.push_back(toucheOptionClavier_[1]);
	//toucheClavier.push_back(toucheOptionClavier_[2]);
	//toucheClavier.push_back(toucheOptionClavier_[3]);
	//toucheClavier.push_back(toucheOptionClavier_[4]);
	//std::string valeur[]={toucheOptionClavier_[0],toucheOptionClavier_[1],toucheOptionClavier_[2],toucheOptionClavier_[3],toucheOptionClavier_[4]};
	//toucheClavier.insert(toucheClavier.begin(),valeur,valeur+5);
	return toucheOptionClavier_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::modifierToucheClavier(const int gauche,const int droit,const int haut ,const int bas,const int espace)
///
/// Cette fonction modifie les valeurs des options de clavier
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::modifierOptionClavier(const std::string gauche, const std::string droit,const std::string haut,
	   const std::string bas, const std::string espace)
{
	std::vector<std::string> temp;
	temp.push_back(gauche);
	temp.push_back(droit);
	temp.push_back(haut);
	temp.push_back(bas);
	temp.push_back(espace);
	toucheOptionClavier_=temp;	
}






///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
