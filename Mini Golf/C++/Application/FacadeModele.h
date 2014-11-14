//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#define GLEW_STATIC
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include "Vecteur.h"
#include "BoiteEnvironnement.h"
#include "VueLibre.h"
#include "VueOrtho.h"
#include "VuePerspective.h"
#include "VueOrbite.h"
#include "VueCiel.h"

class NoeudAbstrait;
class ArbreRenduINF2990;
class VisiteurXML;
class GestionJoueur;
namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Libère l'instance unique de la classe.
   static void libererInstance();
   /// Crée un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration à partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Libère le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du modèle.
   void afficher() const;
   /// Affiche la base du contenu du modèle.
   void afficherBase() const;
   /// Indique que la fenêtre doit être réaffichée sans le faire directement.
   void rafraichirFenetre() const;
   /// Sauvegarder l'arbre courant dans le fichier passe en parametre.
   bool enregistrerXml(std::string nomfichier,int Nbpar ) const;
   /// Charger l'xml dans l'arbre courant
   void chargerXml(std::string nomfichier);

   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
   /// Retourne les noeuds Selectiones de rendu de la scène
   inline const  std::list<NoeudAbstrait*> FacadeModele::obtenirNoeudsSlection() const;
   /// Retourne le string du nom du joueur courant jouant au jeu 
   inline std::string obtenirJoueurCourant() const;
   ///Retourne la chaine de caracteres de la map courante
   inline std::string obtenirMapCourante() const;
   /// Réinitialise la scène.
   void reinitialiser();

   /// Anime la scène.
   void animer(float temps);

   ///Convertir les coordonnes de la souries en coordonnes 3d
   Vecteur3 pos3Dvirtuelle(int sourisX, int sourisY);
   ///selection par ckick
   void  selectionClick(int sourisX, int sourisY, int modeSelection);
   ///selection avec rectangle elastique
   void  selectionRectangle(int startX, int startY, int endX, int endY);
   ///rotater le noeud selectionne
   void  rotationSelection(float angle);
   ///Assigne un facteur d'agrandissement
   void  facteurSelection(float angle);
   ///cree le noeud selectionne par l'utilisateur
   bool  creationObjet(int objet, double sourisX, double sourisY, double souris2X, double souris2Y);
   ///supprime la selection
   void  deleteSelection();
   ///deplacer le noeud selectionne
   void  deplacementSelection(int startX, int startY, int currentX, int currentY);
   ///dupliquer le noeud selectionne
   void  duplicationSelection();
   ///vider l'arbre au complet
   void  viderArbre();
   ///Copie les elements selectionnes
   void  manipulerObjet(int X, int Y, int Z, int rotation, int facteur);
   ///selection de la balle
   bool  clickBalle(int x, int y);
   ///modifier les parametres de la fleche
   void  modifierFleche(int x, int y);
   ///creation de la fleche representant le vecteur force
   void  creerFleche();
   ///effacer la fleche apres avoir tiré
   void  effacerFleche();
   ///modifier les parametres de la fleche a l'aide des touches du clavier
   void  modifierFlecheTouche(int x);
   ///modifie le mode entre jeu et edition
   void  modifierMode(bool modeJeu);
   ///changer la vue entre mode ortho et perspective
   void changerVue(int);
   ///vérifie si le joueur a rentré la balle dans le trou
   bool  verifierVictoire();
   ///vérifie s'il y a une collision entre deux segments
   bool checkCollision2Segments(const Vecteur3& segment1Point1, const Vecteur3& segment1Point2,const Vecteur3& segment2Point1, const Vecteur3& segment2Point2);
   ///retourne le handle vers le Device Context
   HDC obtenirContexte();
   ///retourne la distance entre la balle et le trou
   GLdouble obtenirDistanceBalleTrou() const;
   ///calcule la collision du trou avec les obstacles
   bool calculerCollisionTrouObstacles(Vecteur3 positionTrou);
   ///faire le skybox
   void skybox();
   ///Obtenir le type de la vue courante
   int getTypeVue();
   /// type de la vue
   char * typeVue_;
   ///retourne le nombre de coups
   GLuint obtenirNombreCoups() const;
     /// Assigne le nombre de coups a la valeur int passe en parametre. 
   inline void assignerNombreCoups(int NombreCoups);
   ///assigne le nom du joueur
   void assignerNomJoueur(std::string nomJoueur);
   ///assigne la map 
   void assignerNomMap(std::string nomMap);
   void setPar(int par);
   void initialiserNuanceurs();
   char * textFileRead( const char *fn );
   GLuint progPhong_;
   bool soleilLeve;
   bool getMode();
   inline bool obtenirModeReplay() const;
   inline void assignerModeReplay(bool modeReplay);

private:

   /// Constructeur par défaut.
   FacadeModele();
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie.  Déclaré mais non défini pour éviter qu'il soit
   /// généré par le compilateur.
   FacadeModele(const FacadeModele&);
   /// Opérateur d'assignation.  Déclaré mais non défini pour éviter qu'il
   /// soit généré par le compilateur.
   FacadeModele& operator =(const FacadeModele&);

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_;
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_;
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_;

   /// Vue courante de la scène.
   vue::Vue* vue_;

   vue::VueLibre* vueLibre_;
   vue::VueOrtho* vueOrtho_;
   vue::VueCiel* vueCiel_;
   vue::VueOrbite* vueOrbite_;

   /// Arbre de rendu contenant les différents objets de la scène.
   ArbreRenduINF2990* arbre_;

   ///Vecteur qui contiennent les pointeurs aux noeuds selectionnes
   std::list<NoeudAbstrait*> noeudsSelectiones_;

   ///Pointeur vers fleche si celui ci existe
   NoeudAbstrait* fleche_;
   ///creation balle
   bool isBalle_;
   ///creation trou
   bool isTrou_;
   ///mode jeu
   bool modeJeu_;
   ///angle utilise pour la direction de l'impact avec la fleche
   float angle_;
   ///force appliquée à la balle
   float force_;
   ///permet le controle du baton avec les touches du clavier
   bool flecheKeyboard_;

   float angleSoleil_;

   GLfloat positionSoleil[4];

   GLfloat ValeurAmbiante[4];

   GLfloat positionLune[4];

   GLuint frappes_;

   utilitaire::BoiteEnvironnement* skybox_;

   
   std::string nomJoueur_;
   std::string nomMap_;

   float alphaBlend_;

	float compteur_;
	bool test_;
	bool tomber_;
	bool estModeReplay_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::noeudsSelectiones() const
///
/// Cette fonction retourne les noeuds Selectiones de rendu de la scène (version constante
/// de la fonction).
///
/// @return noeudsSelectiones_.
///
////////////////////////////////////////////////////////////////////////
inline const  std::list<NoeudAbstrait*> FacadeModele::obtenirNoeudsSlection() const
{
   return noeudsSelectiones_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::string FacadeModele::obtenirJoueurCourant()
///
/// Cette fonction retourne le nom du joueur courant
///
/// @return le nom du joueur courant.
///
////////////////////////////////////////////////////////////////////////
inline std::string FacadeModele::obtenirJoueurCourant()	const
{
   return nomJoueur_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::string FacadeModele::obtenirMapCourante()	const
///
/// Cette fonction retourne le nom de la map courante
///
/// @return le nom du joueur courant.
///
////////////////////////////////////////////////////////////////////////
inline std::string FacadeModele::obtenirMapCourante()	const
{
   return nomMap_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerNombreCoups(int NombreCoups)
///
/// Cette fonction assigne le nombre de cours a l'arbre du joueur courant 
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerNombreCoups(int NombreCoups)
{
	frappes_=NombreCoups;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline boolFacadeModele::obtenirModeReplay() const
///
/// Cette fonction retourne le mode du replay
///
/// @return le mode de replay.
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirModeReplay()	const
{
   return estModeReplay_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerModeReplay(bool modeReplay)
///
/// Cette fonction assigne le mode replay
///
/// @return void.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerModeReplay(bool modeReplay)
{
	estModeReplay_=modeReplay;
}

#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
