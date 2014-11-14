//////////////////////////////////////////////// 
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"

#include "Utilitaire.h"
//#include "VisiteurXML.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
   const std::string& type //= std::string( "" )
   ) :
   type_(type) ,
   modePolygones_(GL_FILL) ,
   positionRelative_(0) ,
   affiche_(true) ,
   selectionne_(false) ,
   selectionnable_(true) ,
   enregistrable_(true) ,
   parent_(0),
   rotationObjet_(0),
   factEchelle_(1),
   portalLinked_(false)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide déclaré virtuel pour les classes dérivées.  La
/// libération des afficheurs n'est pas la responsabilité de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
   return 1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerFacteurAgrandissement( float facteur)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par défaut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par défaut de la classe de base.
///
/// @param[in] noeud : Le noeud à effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
///
/// Cette fonction permet de faire l'appel a la fonction calculerBoiteEnglobante
///	de la class modele3d. 
///
///
/// @param[in] coinMin : Vecteur3 représentant le coin minimum
///
/// @param[in] coinMax : Vecteur3 représentant le coin maximum
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donné parmi le noeud
/// lui-même et ses enfants.
///
/// Elle retourne donc le noeud lui-même si son type est celui passé en
/// paramètre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
{
   if (typeNoeud == type_)
	  return this;
   else
	  return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donné parmi le noeud
/// lui-même et ses enfants.
///
/// Elle retourne donc le noeud lui-même si son type est celui passé en
/// paramètre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
{
   if (typeNoeud == type_)
	  return this;
   else
	  return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-ème enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// dernière ne possède pas d'enfant.
///
/// @param[in] indice : L'indice du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-ème enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// dernière ne possède pas d'enfant.
///
/// @param[in] indice : L'indice du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant à ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud à ajouter.
///
/// @return Vrai si l'ajout a bien été effectué, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
   return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien été effectué, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'état de sélection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
   selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont sélectionnés parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction sélectionne le noeud et ses enfants.
///
/// Elle ne fait que sélectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
   assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction désélectionne le noeud et ses enfants.
///
/// Elle ne fait que désélectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
   selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction vérifie si le noeud ou un de ses enfants est
/// sélectionné.
///
/// Elle ne fait que regarder si le noeud est sélectionné, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud sélectionné, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
   return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est sélectionné ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode même si le
///                      noeud n'est pas sélectionné.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones( bool estForce )
{
   if ( ( estForce ) || ( estSelectionne() ) ) {
	  if ( modePolygones_ == GL_FILL )
		 modePolygones_ =  GL_LINE;
	  else if ( modePolygones_ == GL_LINE )
		 modePolygones_ = GL_POINT;
	  else
		 modePolygones_ = GL_FILL;
   }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
{
   // Le mode par défaut si on passe une mauvaise valeur est GL_FILL
   if ( (modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT) ) {
	  modePolygones = GL_FILL;
   }

   modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// généralement à faire pour l'affichage, c'est-à-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit à sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'état.
///
/// L'affichage comme tel est confié à la fonction afficherConcret(),
/// appelée par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher() const
{
   if (affiche_) {
	  glPushMatrix();
	  glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

	  // La translation de la position relative
	  glTranslated(
		 positionRelative_[0], positionRelative_[1], positionRelative_[2]
	  );
	  
	  // Assignation du mode d'affichage des polygones
	  glPolygonMode( GL_FRONT_AND_BACK, modePolygones_ );
	  
	  // Affichage concret
	  afficherConcret();
	  
	  // Restauration
	  glPopAttrib();
	  glPopMatrix();
   }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.  Elle est
/// appelée par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise à être surcharger par
/// les classes dérivées.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer( float dt )
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::AssignerDonnes(Vecteur3 p1, Vecteur3 p2)
///
/// Cette fonction calcule les donnees necessaire pour
/// l'affichage de la bordure
///
/// Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// @param[in] p1 : position virtuelle du premier click
/// @param[in] p2 : position virtuelle du deuxieme click
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::AssignerDonnes(Vecteur3 p1, Vecteur3 p2)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::calculerCoinsBordure(Vecteur3& coin1, Vecteur3& coin2)
///
/// Cette fonction calcule les vrais coins de la bordure
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// @param[in] p1 : premier coin
/// @param[in] p2 : deuxieme coin
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::calculerCoinsBordure(Vecteur3& coin1, Vecteur3& coin2)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudAbstrait::obtenirCoinBordureMin() const
///
/// Cette fonction retourne le coin min de la bordure
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudAbstrait::obtenirCoinBordureMin() const
{
	return Vecteur3(0,0,0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudAbstrait::obtenirCoinBordureMax() const
///
/// Cette fonction retourne le coin max de la bordure
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudAbstrait::obtenirCoinBordureMax() const
{
	return Vecteur3(0,0,0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax)
///
/// Cette fonction assigne les coins de la bordure
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe bordure
///
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::initialiserVitesse(double angle, double vitesse)
///
/// Cette fonction calcule donne une vitesse v0 à la balle
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe balle
///
/// @param[in] angle : angle par rapport a l'axe des X
/// @param[in] vitesse : vitesse initiale
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::initialiserVitesse(double angle, double vitesse)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLfloat NoeudAbstrait::obtenirAngleCoup() const
///
/// Cette fonction retourne l'angle du baton
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe baton
///
///
/// @return angle baton.
///
////////////////////////////////////////////////////////////////////////
float NoeudAbstrait::obtenirAngleCoup() const
{
	return angleBaton_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLfloat NoeudAbstrait::obtenirAngleCoup() const
///
/// Cette fonction retourne la force du baton
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe baton
///
///
/// @return angle baton.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerAngleCoup(float hit)
{
	angleBaton_ = hit;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn float NoeudAbstrait::obtenirForce() const
///
/// Cette fonction retourne la force du baton
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe baton
///
///
/// @return angle baton.
///
////////////////////////////////////////////////////////////////////////
float NoeudAbstrait::obtenirForce() const
{
	return force_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerAngleCoup(float hit)
///
/// Cette fonction retourne l'angle du baton
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe baton
///
///
/// @return angle baton.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerForce(float hit)
{
	force_ = hit;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerBatonPret() const
///
/// Cette fonction assigne l'etat du baton a pret
/// 
///
/// 
///
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerBatonPret()
{
	batonPret_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::verifierEstDansTrou() const
///
/// Cette fonction retourne si notre balle est dans le trou
/// 
///
/// @return Si balle est dans le trou ou non
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::verifierEstDansTrou()
{
	return estDansTrou_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setEstDansTrou() const
///
/// Cette fonction assigne l'etat de la balle a dans trou
/// 
///
/// @return Si balle est dans le trou ou non
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setEstDansTrou(bool trou)
{
	estDansTrou_ = trou;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::verifierEstDansEau() const
///
/// Cette fonction vérifie si la balle est dans l'eau
/// 
///
/// @return Si balle est dans l'eau ou non
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::verifierEstDansEau()
{
	return estDansEau_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setEstDansEau() const
///
/// Cette fonction assigne l'etat de la balle a dans eau
/// 
///
/// @return Si balle est dans le trou ou non
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setEstDansEau(bool dansEau)
{
	estDansEau_ = dansEau;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudAbstrait::obtenirBonusActive() const
///
/// Cette fonction retourne si le bonus est active
///
/// @return bool si bonus active
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::obtenirBonusActive()
{
	return BonusActive_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudAbstrait::obtenirBonusActive() const
///
/// Cette fonction set si le bonus est active
///

/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setBonusActive(bool bonus)
{
	BonusActive_ = bonus;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::obtenirPortalLinked()
///
/// Cette fonction set si le portal est linked avec un autre
///

/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::obtenirPortalLinked()
{
	return portalLinked_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalLinked(bool link)
///
/// Cette fonction set si le portal est linked avec un autre
///

/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerPortalLinked(bool link)
{
	portalLinked_ = link;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalLinked(bool link)
///
/// Cette fonction link le portal avec un autre
///

/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::linkPortal(Vecteur3 LinkingPortal)
{
	PositionLinkingPortal_ = LinkingPortal;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalLinked(bool link)
///
/// Cette fonction retourne le link du portal
///

/// @return link du portal
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudAbstrait::obtenirPosLinkingPortal()
{
	return PositionLinkingPortal_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::obtenirPortalType()
///
/// Cette fonction retourne le type du portal
///

/// @return type du portal
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::obtenirPortalType()
{
	return portalType_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalType(bool type)
///
/// Cette fonction assigne le type du portal
///

/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerPortalType(bool type)
{
	portalType_ = type;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::obtenirPortalPowered()
///
/// Cette fonction retourne si le portal est powered ou non
///

/// @return type du portal
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::obtenirPortalPowered()
{
	return portalPowered_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalPowered(bool power)
///
/// Cette fonction assigne si le portal est powered ou non
///

/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerPortalPowered(bool power)
{
	portalPowered_ = power;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalPowered(bool power)
///
/// Cette fonction retourne le par du terrain
///

/// @return par
///
////////////////////////////////////////////////////////////////////////
int NoeudAbstrait::obtenirPar()
{
	return par_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortalPowered(bool power)
///
/// Cette fonction assigner le par du terrain
///

/// @return par
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerPar(int par)
{
	par_ = par;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::obtenirVitesse()
///
/// Cette fonction retourne la vitesse courrante de la balle
/// 
///
///  Elle ne fait rien pour cette classe et vise à être surcharger par
/// la classe balle
///
///
/// @return Vitesse de la balle.
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudAbstrait::obtenirVitesse()
{
	return vitesse_;
}
///////////////////////////////////////////////////////////////////////
///
/// @ void NoeudAbstrait::accueillirVisiteurXML(VisiteurXML& visiteur)
///
/// permet au visiteur xml de parcourir le noeud
///
/// @param[in] visiteur : Le visiteur xml
///
/// @return Aucune
///
//////////////////////////////////////////////////////////////////////
void NoeudAbstrait::accueillirVisiteurXML(VisiteurXML& visiteur)
{
	visiteur.visiterNoeudAbstrait(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstraitcheckCollision2Segments(Vecteur3 segment1Point1, Vecteur3 segment1Point2,Vecteur3 segment2Point1, Vecteur3 segment2Point2)
///
/// Cette methode permet de detecter une collision entre deux segments
///
///	@param[in]	segments : booléen indiquant si la collision existe
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::checkCollision2Segments(const Vecteur3& segment1Point1, const Vecteur3& segment1Point2,const Vecteur3& segment2Point1, const Vecteur3& segment2Point2)
{
	double ud, ua, ub;
	ua = 0;

	ud = (segment2Point2[1] - segment2Point1[1]) * (segment1Point2[0] - segment1Point1[0]) - (segment2Point2[0] - segment2Point1[0]) * (segment1Point2[1] - segment1Point1[1]);
	if(ud != 0) {

		ua = ((segment2Point2[0] - segment2Point1[0]) * (segment1Point1[1] - segment2Point1[1]) - (segment2Point2[1] - segment2Point1[1]) * (segment1Point1[0] - segment2Point1[0])) / ud;
		ub = ((segment1Point2[0] - segment1Point1[0]) * (segment1Point1[1] - segment2Point1[1]) - (segment1Point2[1] - segment1Point1[1]) * (segment1Point1[0] - segment2Point1[0])) / ud;
		if (ua < 0 || ua > 1 || ub < 0 || ub > 1) ua = 0;
	}
	else
		return false; //même pente

	return ua == 0 ? false : true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::horsContour()
///
/// Cette methode permet de verifier si un objet est hors contour
///
///	@param[in]	booléen indiquant si hors contour
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::horsContour()
{
	unsigned int compteurContour = 0;
	Vecteur3 coinContourMin, coinContourMax;
	Vecteur3 positionXmax(positionRelative_[0] + 500,positionRelative_[1],positionRelative_[2]);
	NoeudAbstrait* noeud = this;
	do
	{
		noeud = noeud->obtenirParent();
	}while(noeud->obtenirType() != "racine");

	for(unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			if(noeud->chercher(i)->obtenirType() == "contour")
			{
				
				coinContourMin = noeud->chercher(i)->obtenirCoinBordureMin();
				coinContourMax = noeud->chercher(i)->obtenirCoinBordureMax();

	
					if(checkCollision2Segments(positionRelative_, positionXmax,coinContourMin,coinContourMax) == true)
					{
						compteurContour++;
					}

			}
		}
	if(compteurContour %2 != 0 )
	{
		return false;
	}
	else
	{
		if(compteurContour == 2)//cas deux contours en intersection , on regarde à gauche
		{
			positionXmax[0] = positionRelative_[0] - 500;
			for(unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
			{
				if(noeud->chercher(i)->obtenirType() == "contour")
				{

					coinContourMin = noeud->chercher(i)->obtenirCoinBordureMin();
					coinContourMax = noeud->chercher(i)->obtenirCoinBordureMax();


					if(checkCollision2Segments(positionRelative_, positionXmax,coinContourMin,coinContourMax) == true)
					{
						compteurContour++;
					}

				}
			}
		}

		if(compteurContour %2 != 0)
			return false;

		return true;
	}
}

void NoeudAbstrait::lacher()
{

}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
