///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "Usines/UsineNoeudBalle.h"
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeudAraignee.h"
#include "Usines/UsineNoeudConeCube.h"
//#include "Usines/UsineNoeudBalle.h" Pour eviter la mauvaise inclusion de glew
#include "Usines/UsineNoeudBordure.h"
#include "Usines/UsineNoeudFleche.h"
#include "Usines/UsineNoeudSable.h"
#include "Usines/UsineNoeudEau.h"
#include "Usines/UsineNoeudTrou.h"
#include "Usines/UsineNoeudBonus.h"
#include "Usines/UsineNoeudTerrain.h"
#include "Usines/UsineNoeudBaton.h"
#include "Usines/UsineNoeudContour.h"
#include "Usines/UsineNoeudPortal.h"
#include "EtatOpenGL.h"


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE = "Araignee";
/// La chaîne représentant le type des conecube
const std::string ArbreRenduINF2990::NOM_CONECUBE = "conecube";
/// La chaîne représentant le type des balles
const std::string ArbreRenduINF2990::NOM_BALLE = "balle";
/// La chaîne représentant le type des bordure
const std::string ArbreRenduINF2990::NOM_BORDURE = "bordure";
/// La chaîne représentant le type le sable
const std::string ArbreRenduINF2990::NOM_SABLE = "sable";
/// La chaîne représentant le type le eau
const std::string ArbreRenduINF2990::NOM_EAU = "eau";
/// La chaîne représentant le type des trou
const std::string ArbreRenduINF2990::NOM_TROU = "trou";
/// La chaîne représentant le type des bonus
const std::string ArbreRenduINF2990::NOM_BONUS = "bonus";
/// La chaîne représentant le type du terrain
const std::string ArbreRenduINF2990::NOM_TERRAIN = "terrain";
/// La chaîne représentant le type du baton
const std::string ArbreRenduINF2990::NOM_BATON = "baton";
/// La chaîne représentant le type du baton
const std::string ArbreRenduINF2990::NOM_FLECHE = "fleche";

const std::string ArbreRenduINF2990::NOM_CONTOUR = "contour";

const std::string ArbreRenduINF2990::NOM_PORTAL = "portal";
////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
   // Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeudAraignee(NOM_ARAIGNEE));
	ajouterUsine(NOM_BALLE, new UsineNoeudBalle(NOM_BALLE));
	ajouterUsine(NOM_BORDURE, new UsineNoeudBordure(NOM_BORDURE));
	ajouterUsine(NOM_EAU, new UsineNoeudEau(NOM_EAU));
	ajouterUsine(NOM_SABLE, new UsineNoeudSable(NOM_SABLE));
	ajouterUsine(NOM_TROU, new UsineNoeudTrou(NOM_TROU));
	ajouterUsine(NOM_BONUS, new UsineNoeudBonus(NOM_BONUS));
	ajouterUsine(NOM_CONECUBE, new UsineNoeudConeCube(NOM_CONECUBE));
	ajouterUsine(NOM_TERRAIN, new UsineNoeudTerrain(NOM_TERRAIN));
	ajouterUsine(NOM_BATON, new UsineNoeudBaton(NOM_BATON));
	ajouterUsine(NOM_FLECHE, new UsineNoeudfleche(NOM_FLECHE));
	ajouterUsine(NOM_CONTOUR, new UsineNoeudContour(NOM_CONTOUR));
	ajouterUsine(NOM_PORTAL, new UsineNoeudPortal(NOM_PORTAL));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
   // On vide l'arbre
   vider();

    // On ajoute un noeud pour que le terrain s'affiche
	//NoeudAbstrait* noeud = creerNoeud(NOM_TERRAIN);

	//ajouter(noeud);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
