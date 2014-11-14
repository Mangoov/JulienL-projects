///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>
#include "VisiteurXML.h"
#include "Vecteur.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisée pour créer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant être présent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = std::string( "" )
		);
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent( NoeudAbstrait* parent );

	/// Obtient la position relative du noeud.
	inline const Vecteur3& obtenirPositionRelative() const;

	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative( const Vecteur3& positionRelative);

	/// Obtient le facteur d'agrandissement
	virtual void assignerFacteurAgrandissement( float facteur);

	/// Assigne le Facteur d'agrandissement
	inline const float obtenirFacteurAgrandissment();

	/// Incremente la rotation
	inline const float obtenirRot();

	/// Assigne un angle de rotation
	inline void assignerRot(float angle);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// Écrit l'état de l'affichage du noeud.
	inline void assignerAffiche( bool affiche );
	/// Vérifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// Écrit l'état de la sélection du noeud.
	inline void assignerSelection( bool selectionne );
	/// Vérifie si le noeud est sélectionné.
	inline bool estSelectionne() const;
	/// Écrit si le noeud peut être sélectionné ou non.
	inline void assignerEstSelectionnable( bool selectionnable );
	/// Vérifie si le noeud est sélectionnable.
	inline bool estSelectionnable() const;
	/// Écrit si le noeud peut être enregistré ou non.
	inline void assignerEstEnregistrable( bool enregistrable );
	/// Vérifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;
	///position lors de la creation du noeud
	inline void assignerPositionInitiale(Vecteur3 posInitiale);
	///retourne la position initiale de l'objet
	inline Vecteur3 obtenirPositionInitiale() const;
	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud passé en paramètre.
	virtual void effacer( const NoeudAbstrait* noeud );
	/// Permet de calculer la boite englobante de l'objet
	virtual void calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher( const std::string& typeNoeud ) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher( const std::string& typeNoeud );
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher( unsigned int indice ) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher( unsigned int indice );


	/// Ajoute un noeud enfant.
	virtual bool ajouter( NoeudAbstrait* enfant );
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;

	/// Changer la sélection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants sélectionnés.
	virtual void effacerSelection();
	/// Sélectionne tous les enfants de même que le noeud.
	virtual void selectionnerTout();
	/// Désélectionne tous les enfants de même que le noeud.
	virtual void deselectionnerTout();
	/// Vérifier si le noeud ou un de ses enfants est sélectionné.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones( bool estForce );
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones( GLenum modePolygones );
	/// Affiche le noeud.
	virtual void afficher() const;
	/// Affiche le noeud de manière concrète.
	virtual void afficherConcret() const;
	/// Anime le noeud.
	virtual void animer( float dt );

	/// Permet au visiteur xml de parcourir le noeud
   /// Permet de calculer la bordure
	virtual void accueillirVisiteurXML(VisiteurXML& visiteur);
   virtual void AssignerDonnes(Vecteur3 p1, Vecteur3 p2);
   ///calcule les vrais coins de la bordure
   virtual void calculerCoinsBordure(Vecteur3& coin1, Vecteur3& coin2);
   /// Obtenir le coin Bordure Max
   virtual Vecteur3 obtenirCoinBordureMin() const;
   /// Obtenir le coin Bordure Min
   virtual Vecteur3 obtenirCoinBordureMax() const;
   ///Assigner coins bordures
   virtual void assignerCoinBordure(Vecteur3 coinMin, Vecteur3 coinMax);
   ///depart de balle
   virtual void initialiserVitesse(double angle, double vitesse);
   ///Retourne la vitesse de la balle
   virtual Vecteur3 obtenirVitesse();
   ///retourne l'angle du baton
   virtual float obtenirAngleCoup() const;

   virtual void assignerAngleCoup(float hit);

   virtual float obtenirForce() const;

   virtual void assignerForce(float hit);
   ///assigne l'etat du baton a pret
   virtual void assignerBatonPret();
   ///Retourne si la balle est dans le trou ou non
   virtual bool verifierEstDansTrou();
   ///Assigne si ball est dans trou
   virtual void setEstDansTrou(bool trou);
   ///Retourne si la balle est dans l'eau ou non
   virtual bool verifierEstDansEau();
   ///Assigne si ball est dans trou
   virtual void setEstDansEau(bool dansEau);
   ///Retourne si le bonus a ete active
   virtual bool obtenirBonusActive();
   ///Assigne si le bonus est active
   virtual void setBonusActive(bool bonus);

	/// Permet de calculer la bordure

	virtual bool obtenirPortalLinked();

	virtual void assignerPortalLinked(bool link);

	virtual void linkPortal(Vecteur3 LinkingPortal);

	virtual Vecteur3 obtenirPosLinkingPortal();

	virtual bool obtenirPortalType();

	virtual void assignerPortalType(bool type);
	///vérifie s'il y a une collision entre deux segments
	virtual bool checkCollision2Segments(const Vecteur3& segment1Point1, const Vecteur3& segment1Point2,const Vecteur3& segment2Point1, const Vecteur3& segment2Point2);
	///test si objet est hors contour
	virtual bool horsContour();

   virtual bool obtenirPortalPowered();

   virtual void assignerPortalPowered(bool power);

   virtual int obtenirPar();

   virtual void assignerPar(int par); 

   Vecteur3 distanceP1P2_;

   virtual void lacher();
protected:
	/// Type du noeud.
	std::string      type_;
	Vecteur3         vitesse_;
	/// Mode d'affichage des polygones.
	GLenum           modePolygones_;

	/// Position relative du noeud.
	Vecteur3         positionRelative_;

	///facteur de rotation de l'objet
	float			rotationObjet_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_;

	/// Sélection du noeud.
	bool             selectionne_;

	/// Vrai si le noeud est sélectionnable.
	bool             selectionnable_;

	/// Détermine si l'objet peut être sauvegardé en XML.
	bool             enregistrable_;

	///facteur d'echelle de l'objet
	float			factEchelle_;

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_;

	///vrai coin min de la bordure
	Vecteur3			coinBordureMin_;

	///vrai coin max de la bordure
	Vecteur3			coinBordureMax_;

   ///angle du baton
   float			angleBaton_;

   float			force_;

   ///booleen indiquant l'etat du baton
   bool				batonPret_;

	///boolean indiquand si la balle est dans le trou
	bool				estDansTrou_;

	///boolean indiquand si la balle est dans l'eau ou non
	bool				estDansEau_;

	bool				BonusActive_;

	bool				portalLinked_;

	Vecteur3         PositionLinkingPortal_;

	bool				portalType_;

	Vecteur3			positionInitiale_;

   bool				portalPowered_;

   int				par_;

};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_       = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const Vecteur3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const Vecteur3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const Vecteur3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const Vecteur3& positionRelative
	)
{
	positionRelative_ = positionRelative;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'obtenir le facteur d'agrandissement
///
/// @param facteur : aucun
///
/// @return facteur echelle
///
////////////////////////////////////////////////////////////////////////
inline const float NoeudAbstrait::obtenirFacteurAgrandissment()
{
	return factEchelle_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerRot(float angle)
///
/// Incremente rotationObjet 
/// 
/// @param[in] angle: angle de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerRot(float angle)
{
	rotationObjet_ = angle;
	if(rotationObjet_>=360)
		rotationObjet_ = rotationObjet_ - 360;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const float NoeudAbstrait::obtenirRot()
///
/// Cette fonction permet d'obtenir le facteur de rotation
///
/// @return angle de rotation.
///
////////////////////////////////////////////////////////////////////////
inline const float NoeudAbstrait::obtenirRot()
{
	return rotationObjet_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une chaîne représentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'état affiché ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche( bool affiche )
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'état que le noeud se fait afficher ou non.
///
/// @return L'état affiché ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection( bool selectionne )
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'état d'être sélectionné ou non du noeud.
///
/// @return L'état sélectionné ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'état d'être sélectionnable ou non du noeud.
///
/// @param selectionnable : L'état sélectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
{
	selectionnable_ = selectionnable;
	selectionne_    = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'état d'être sélectionnable ou non du noeud.
///
/// @return L'état sélectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'état d'être entregistrable ou non du noeud.
///
/// @param enregistrable : L'état enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'état d'être enregistrable en XML ou non du
/// noeud.
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionInitiale(Vecteur3 posInitiale)
///
/// Cette methode permet d'assigner la position initiale d'un noeud
///
///	@param[in]	posInitiale : position après création de l'objet
/// @return None.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionInitiale(Vecteur3 posInitiale)
{
	positionInitiale_ = posInitiale;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline Vecteur3 NoeudAbstrait::obtenirPositionInitiale() const
///
/// Cette methode permet de retourner la position initiale d'un noeud
///
/// @return Position initiale.
///
////////////////////////////////////////////////////////////////////////
inline Vecteur3 NoeudAbstrait::obtenirPositionInitiale() const
{
	return positionInitiale_;
}

#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
