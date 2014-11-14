//////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.h
/// @author Manraj Ashley, quadriciel de base par Jean-Francois Pérusse
/// @date 2011-31-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONFIGURATION_CONFIGSCENE_H__
#define __CONFIGURATION_CONFIGSCENE_H__


#include "Singleton.h"
#include "Vecteur.h"
#include "tinyxml.h"
#include <string>
#include "Utilitaire.h"
#include <windows.h>
#include <vector>



///////////////////////////////////////////////////////////////////////////
/// @class ConfigScene
/// @brief Les variables de configuration de la classe CScene.
///        C'est une classe singleton.
///
/// @author Manraj Ashley, quadriciel de base par Jean-Francois Pérusse
/// @date 2011-31-10
///////////////////////////////////////////////////////////////////////////
class ConfigScene : public Singleton<ConfigScene>
{
   SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(ConfigScene);

public:
   /// Créer le DOM avec les valeurs.
   void creerDOM( TiXmlNode* node );
   ///  Creer un fichier de configuration avec le string passe en parametre.
   bool chargerFichierConfig(const std::string nomFichier);
   void enregistrerFichierConfig(const std::string nomFichier);
   void forcerSauvegardeConfig();
   void Xmlvide(const std::string nomFichier);
   int* obtenirToucheClavier();
   void modifierToucheClavier(const int gauche,const int droit,const int haut ,const int bas,const int espace);
   std::vector<std::string> obtenirOptionClavier();
   void modifierOptionClavier(const std::string gauche, const std::string droit,const std::string haut,
	   const std::string bas, const std::string espace);
   //Obtenir Parametres de configuration
   inline double obtenirCoefFriSol() const;
   inline double obtenirCoefFriSable() const;
   inline double obtenirCoefRebondMur() const;
   inline double obtenirAccelBonus() const;
   inline int obtenirTailleEditionLargeur() const; 
   inline int obtenirTailleEditionHauteur() const;

   long GetFileSize(const TCHAR *fileName);
   TCHAR* stringToTCHAR(const std::string fileName);
   inline void modifierCoefFriSol(const double CoefFriSol);
   inline void modifierCoefFriSable(const double CoefFriSable);
   inline void modifierCoefRebondMur(const double CoefRebondMur);
   inline void modifierAccelBonus(const double AccelBonus);
   inline void modifierTailleEditionLargeur(const int TailleEditionLargeur); 
   inline void modifierTailleEditionHauteur(const int TailleEditionHauteur);
   inline TiXmlDocument* obtenirConf();
   
   /// Nombre de calculs par image.
   static int CALCULS_PAR_IMAGE;
private:
	ConfigScene();
	~ConfigScene();
	double coefFriSol_;
	double coefFriSable_;
	double coefRebondMur_;
	double accelBonus_;
	int tailleEdition_[2];
	int toucheClavier_[5];
	TiXmlDocument* confXml_;
	std::vector<std::string> toucheOptionClavier_;




};
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::obtenirCoefFriSol()
///
/// Cette fonction permet d obtenir la valeur du coefficient de friction au sol.
///
/// @return : double valeur coefficient de friction au sol
///
////////////////////////////////////////////////////////////////////////
inline double ConfigScene::obtenirCoefFriSol() const
{
   return coefFriSol_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::obtenirCoefFriSable()
///
/// Cette fonction permet d obtenir la valeur du coefficient de friction au sable.
///
/// @return : double valeur coefficient de friction au sable
///
////////////////////////////////////////////////////////////////////////
inline double ConfigScene::obtenirCoefFriSable() const
{
   return coefFriSable_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::obtenirCoefRebondMur()
///
/// Cette fonction permet d obtenir la valeur du coefficient de rebond au mur.
///
/// @return : double valeur coefficient de de rebond au mur
///
////////////////////////////////////////////////////////////////////////
inline double ConfigScene::obtenirCoefRebondMur() const
{
   return coefRebondMur_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::obtenirAccelBonus()
///
/// Cette fonction permet d obtenir la valeur du coefficient accelerateur du bonus.
///
/// @return : double valeur coefficient de accelerateur du bonus.
///
////////////////////////////////////////////////////////////////////////
inline double ConfigScene::obtenirAccelBonus() const
{
   return accelBonus_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ConfigScene::getTailleEditionLargeur()
///
/// Cette fonction permet d obtenir la valeur de la taille d'edition en largeur
///
/// @return : int valeur coefficient de accelerateur du bonus.
///
////////////////////////////////////////////////////////////////////////
inline int ConfigScene::obtenirTailleEditionLargeur() const
{
   return tailleEdition_[0];
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ConfigScene::getTailleEditionHauteur()
///
/// Cette fonction permet d obtenir la valeur de la taille d'edition en hauteur
///
/// @return : int valeur coefficient de accelerateur du bonus.
///
////////////////////////////////////////////////////////////////////////
inline int ConfigScene::obtenirTailleEditionHauteur() const
{
   return tailleEdition_[1];
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::modifierCoefFriSol()
///
/// Cette fonction permet de modifier la valeur de coefficient par defaut du sol.
///
/// @param[in] const double CoefFriSol
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline void ConfigScene::modifierCoefFriSol(const double CoefFriSol)
{
	coefFriSol_=CoefFriSol;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::modifierCoefFriSable()
///
/// Cette fonction permet de modifier la valeur de coefficient par defaut du sable.
///
/// @param[in] const double CoefFriSable
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline void ConfigScene::modifierCoefFriSable(const double CoefFriSable)
{
	coefFriSable_=CoefFriSable;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::modifierCoefRebondMur()
///
/// Cette fonction permet de modifier la valeur de coefficient du rebond sur les murs.
///
/// @param[in] const double CoefRebondMur
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline void ConfigScene::modifierCoefRebondMur(const double CoefRebondMur)
{
	coefRebondMur_=CoefRebondMur;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::modifierAccelBonus()
///
/// Cette fonction permet de modifier la valeur de coefficient accelerateur des bonus
///
/// @param[in] const double AccelBonus
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline void ConfigScene::modifierAccelBonus(const double AccelBonus)
{
	accelBonus_=AccelBonus;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::modifierTailleEditionLargeur()
///
/// Cette fonction permet de modifier la taille de la fenetre d'edition en largeur.
///
/// @param[in] const int TailleEditionLargeur
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline void ConfigScene::modifierTailleEditionLargeur(const int TailleEditionLargeur)
{
	tailleEdition_[0]=TailleEditionLargeur;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::modifierTailleEditionHauteur()
///
/// Cette fonction permet de modifier la taille de la fenetre d'edition en hauteur.
///
/// @param[in] const int TailleEditionHauteur
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline void ConfigScene::modifierTailleEditionHauteur(const int TailleEditionHauteur)
{
	tailleEdition_[1]=TailleEditionHauteur;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ConfigScene::obtenirConf()
///
/// Cette fonction permet de retourner la racine de configuration xml.
///
/// @param[in] const int TailleEditionHauteur
/// @return : aucune
///
////////////////////////////////////////////////////////////////////////
inline TiXmlDocument* ConfigScene::obtenirConf()
{
	return confXml_; 
}

#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
