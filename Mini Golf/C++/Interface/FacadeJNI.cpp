///////////////////////////////////////////////////////////////////////////////
/// @file FacadeJNI.cpp
/// @author Martin Bisson
/// @date 2007-08-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "FacadeModele.h"
#include "jawt_md.h"
#include "JAWT_Info.h"
#include "FreeImage.h"
#include "FacadeJNI.h"
#include "Vecteur.h"
#include "Vue.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "ConfigScene.h"
#include "GestionJoueur.h"
#include "Sound.h"
#include "GestionListeAffichages.h"
#include "BancTests.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction initialise un contexte OpenGL dans la fenêtre
/// identifiée par le canvas AWT passé en paramètre.  Cette fonction doit
/// être la première à être appelée, car la création de l'objet du modèle
/// C++ s'attend à avoir un contexte OpenGL valide.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel créer le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Obtenir la poignée ("handle") vers la fenêtre.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();
	
   // On pourrait lancer une exception à la place...
   if(hWnd == 0)
      return;

	FacadeModele::obtenirInstance()->initialiserOpenGL(hWnd);
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1libererOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction libère le contexte OpenGL dans la fenêtre identifiée
/// par le canvas AWT passé en paramètre.  Cette fonction doit être la
/// dernière à être appelée, car elle libère également l'objet du modèle
/// C++.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel créer le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1libererOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Ce code vérouille le canvas et ne doit donc pas être enlevé, même s'il
   // semble inutile à première vue.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();

   // On pourrait lancer une exception à la place...
   if(hWnd == 0)
      return;

   FacadeModele::obtenirInstance()->libererOpenGL();
	
	
   // Désinitialisation de la façade.  Le fait de le faire après la
   // désinitialisation du contexte OpenGL aura pour conséquence que la
   // libération des listes d'affichages, par InterfaceJava, sera faite une fois que
   // le contexte n'existera plus, et sera donc sans effet.
   FacadeModele::libererInstance();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1dessinerOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction affiche la scène dans la fenêtre identifiée par le
/// canvas AWT passé en paramètre.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel créer le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1dessinerOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Ce code vérouille le canvas et ne doit donc pas être enlevé, même s'il
   // semble inutile à première vue.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();

   if(hWnd == 0)
      return;

   // Affiche la scène.
   FacadeModele::obtenirInstance()->afficher();


   // Temporaire: pour détecter les erreurs OpenGL
   aidegl::verifierErreurOpenGL();

}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1redimensionnerFenetre(JNIEnv* env, jclass, jint largeur, jint hauteur)
///
/// Cette fonction doit être appelée lorsque la fenêtre est
/// redimensionnée afin d'ajuster les paramètres de la machine à états
/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
///
/// @param[in] largeur : La nouvelle largeur de la fenêtre.
/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1redimensionnerFenetre
  (JNIEnv* env, jclass, jint largeur, jint hauteur)
{
   FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
      Vecteur2i(0,0),
      Vecteur2i(largeur, hauteur)
      );
   FacadeModele::obtenirInstance()->rafraichirFenetre();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1animer(JNIEnv* env, jclass, jfloat temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1animer
  (JNIEnv* env, jclass, jfloat temps)
{
   FacadeModele::obtenirInstance()->animer(temps);
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomIn(JNIEnv* env, jclass,jint pourcentage)
///
/// Cette fonction applique un zoom avant sur le présent volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomIn
  (JNIEnv* env, jclass, jint pourcentage)
{
   FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn( pourcentage);
   FacadeModele::obtenirInstance()->rafraichirFenetre();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomOut(JNIEnv* env, jclass, jint pourcentage)
///
/// Cette fonction applique un zoom arrière sur le présent volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomOut
  (JNIEnv* env, jclass, jint pourcentage)
{
   FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut(pourcentage);
   FacadeModele::obtenirInstance()->rafraichirFenetre();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_obtenirAffichagesParSeconde(JNIEnv* env, jclass)
///
/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
///
/// @return Le nombre d'affichage par seconde.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_obtenirAffichagesParSeconde
  (JNIEnv* env, jclass)
{
   return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1executerTests(JNIEnv* env, jclass)
///
/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
///
/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1executerTests
  (JNIEnv * env, jclass)
{
   bool reussite = BancTests::obtenirInstance()->executer();

   // Visual Studio interprète le code de retour 0 comme une réussite et le code
	// de retour 1 comme un échec. Nous transmettons le code de retour à Java
	// qui le transmet directement comme code de sortie du programme.
   return reussite ? 0 : 1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deplacerXY(JNIEnv* env, jclass, jdouble deplacementX, jdouble deplacementY)
///
/// Cette fonction permet de déplacer la fenêtre virtuelle
///
/// @param[in]  deplacementX : le déplacement en @a x.
/// @param[in]  deplacementY : le déplacement en @a y.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deplacerXY(JNIEnv* env, jclass, jdouble deplacementX, jdouble deplacementY)
{
  FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY); 
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomerInElastique(JNIEnv * env, jclass, jint coin1x, jint coin1y, jint coin2x, jint coin2y )
///
/// Cette fonction permet de zoomer selon un rectangle élastique
///
/// @param[in]  coin1x
/// @param[in]  coin1y
/// @param[in]  coin2x
/// @param[in]  coin2y
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomerInElastique(JNIEnv * env, jclass,  jint coin1x, jint coin1y, jint coin2x, jint coin2y )

{
	Vecteur2i coin1(coin1x, coin1y);
	Vecteur2i coin2(coin2x, coin2y);

	FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(coin1, coin2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomerOutElastique(JNIEnv * env, jclass, jint coin1x, jint coin1y, jint coin2x, jint coin2y )
///
/// Cette fonction permet de zoomer selon un rectangle élastique
///
/// @param[in]  coin1x
/// @param[in]  coin1y
/// @param[in]  coin2x
/// @param[in]  coin2y
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1zoomerOutElastique(JNIEnv * env, jclass,  jint coin1x, jint coin1y, jint coin2x, jint coin2y )

{
	Vecteur2i coin1(coin1x, coin1y);
	Vecteur2i coin2(coin2x, coin2y);

	FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(coin1, coin2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserRectangleElastique(JNIEnv * env, jclass, jint pointx, jint pointy )
///
/// Cette fonction permet d initialiser le rectangle elastique
///
/// @param[in]  pointx
/// @param[in]  pointy
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserRectangleElastique(JNIEnv * env, jclass,  jint pointx, jint pointy )

{
	Vecteur2i point(pointx, pointy);
	aidegl::initialiserRectangleElastique(point);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1mettreAJourRectangleElastique(JNIEnv *env, jclass,  jint pointAncragex, jint pointAncragey, jint pointAvantx, jint pointAvanty, jint pointApresx, jint pointApresy )
///
/// Cette fonction met à jour la position du rectangle élastique en
/// effaçant le rectangle précédent pour le remplacer par un nouveau.
///
/// @param[in] pointAncragex 
/// @param[in] pointAncragey : Point initial de localisation du rectangle.
/// @param[in] pointAvantx 
/// @param[in] pointAvanty   : Autre coin du rectangle avant la mise à jour.
/// @param[in] pointApresx
/// @param[in] pointApresy  : Autre coin du rectangle après la mise à jour.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1mettreAJourRectangleElastique(JNIEnv * env, jclass,  jint pointAncragex, jint pointAncragey, jint pointAvantx, jint pointAvanty, jint pointApresx, jint pointApresy  )

{
	Vecteur2i pointAncrage(pointAncragex, pointAncragey);
	Vecteur2i pointAvant(pointAvantx,pointAvanty);   
	Vecteur2i pointApres(pointApresx,pointApresy);
	aidegl::mettreAJourRectangleElastique(pointAncrage,pointAvant,pointApres);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1terminerRectangleElastique(JNIEnv *env, jclass,  jint pointAncragex, jint pointAncragey, jint pointFinalx, jint pointFinaly )
///
/// Cette fonction termine le mode de rendu du rectangle élastique en
/// restaurant l'état de la machine OpenGL à ce qu'il était.
///
/// @param[in] pointAncragex : Point initial de localisation du rectangle.
/// @param[in] pointAncragey : Point initial de localisation du rectangle.
/// @param[in] pointFinalx   : Point final de localisation du rectangle.
/// @param[in] pointFinaly   : Point final de localisation du rectangle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1terminerRectangleElastique(JNIEnv * env, jclass,  jint pointAncragex, jint pointAncragey, jint pointFinalx, jint pointFinaly)

{
	Vecteur2i pointAncrage(pointAncragex, pointAncragey);
	Vecteur2i pointFinal(pointFinalx,pointFinaly);
	aidegl::terminerRectangleElastique(pointAncrage,pointFinal);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1selectionClick(JNIEnv *env, jclass, jint sourisX, jint sourisY, jint modeSelection)
///
///	Selectionne un objet base sur les paremetres x et y 
///
/// @param[in] sourisX : composante en x de la souris.
/// @param[in] sourisY : composante en y de la souris.
/// @param[in] modeSelection : 0 selection simple
///							   1 selection multiple
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1selectionClick(JNIEnv * env, jclass,  jint sourisX, jint sourisY, jint modeSelection)

{
	FacadeModele::obtenirInstance()->selectionClick(sourisX,sourisY,modeSelection);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1selectionRectangle(JNIEnv *env, jclass, jint startX, jint startY, jint endX, jint endY)
///
///	Selectionne un objet base sur les paremetres x et y du debut et de fin
///
/// @param[in] startX : composante en x de la souris au début
/// @param[in] startY : composante en y de la souris au début
/// @param[in] endX : composante en x de la souris à la fin
/// @param[in] endY : composante en y de la souris à la fin
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1selectionRectangle(JNIEnv * env, jclass, jint startX, jint startY, jint endX, jint endY)

{
	FacadeModele::obtenirInstance()->selectionRectangle(startX, startY, endX, endY);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1rotationSelection(JNIEnv *env, jclass, jfloat angle)
///
/// Effectue une rotation sur tous les objets selectionnés
///
/// @param[in] angle: angle de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1rotationSelection(JNIEnv * env, jclass, jfloat angle)

{
	FacadeModele::obtenirInstance()->rotationSelection(angle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1facteurSelection(JNIEnv *env,jclass, jfloat facteur)
///
/// Assigne le facteur d'agrandissement aux objets selectionnés
///
/// @param[in] facteur: le facteur d'agrandissement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1facteurSelection(JNIEnv * env, jclass, jfloat facteur)

{
	FacadeModele::obtenirInstance()->facteurSelection(facteur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1creationObject(JNIEnv *env, jclass,jint object, jdouble sourisX, jdouble sourisY, jdouble souris2X, jdouble souris2Y)
///
///	Permet de creer les objets et les ajouter à l'arbre lorsqu'on est dans le mode d'edition
/// 
/// @param[in] object  : entier indiquant le type d'objet à créer
/// @param[in] sourisX : coordonnée X de la souris (premier point)
///	@param[in] sourisY : coordonnée Y de la souris (premier point)
///	@param[in] souris2X: coordonnée X de la souris (second point)
///	@param[in] souris2Y: coordonnée Y de la souris (second point)
///
/// @return booléen indiquant si l'objet est crée avec succès.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1creationObject(JNIEnv * env, jclass, jint object, jdouble sourisX, jdouble sourisY, jdouble souris2X, jdouble souris2Y)

{
	return FacadeModele::obtenirInstance()->creationObjet(object,sourisX,sourisY,souris2X,souris2Y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deleteSelection(JNIEnv *env, jclass)
///
/// Delete les objets selectionnes
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deleteSelection(JNIEnv * env, jclass)

{
	FacadeModele::obtenirInstance()->deleteSelection();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deplacementSelection(JNIEnv *env, jclass, jint startX, jint startY, jint sourisX, jint sourisY )
///
/// Deplace les objets selectionnés
///
/// @param[in] startX : coordonnée X de la souris (premier point)
///	@param[in] startY : coordonnée Y de la souris (premier point)
///	@param[in] sourisX: coordonnée X de la souris (second point)
///	@param[in] sourisY: coordonnée Y de la souris (second point)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deplacementSelection(JNIEnv *env, jclass, jint startX, jint startY, jint sourisX, jint sourisY)

{
	FacadeModele::obtenirInstance()->deplacementSelection(startX, startY, sourisX, sourisY);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1duplicationSelection(JNIEnv *env, jclass)
///
/// Duplique les objets selectionnés
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1duplicationSelection(JNIEnv *env, jclass)
{
	FacadeModele::obtenirInstance()->duplicationSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1viderSelection(JNIEnv *env, jclass)
///
/// Désélectionne les objets selectionnes
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1viderSelection(JNIEnv *env, jclass)

{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	arbre->deselectionnerTout();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1viderArbre(JNIEnv *env, jclass)
///
/// Delete tous les objets
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1viderArbre(JNIEnv *env, jclass)

{
	FacadeModele::obtenirInstance()->reinitialiser();
	VisiteurXML* gestionnaire=VisiteurXML::obtenirInstance();
	gestionnaire->effacerArbreXml();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jintArray Java_ca_polymtl_inf2990_InterfaceJava_fctC_1convertirCoordonneesSouris(JNIEnv *env, jclass, jint SourisX, jint SourisY)
///
///
/// @param[in] SourisX : coordonnée X de la souris
///	@param[in] SourisY : coordonnée Y de la souris
///
/// convertit les coordonnees de cloture de la souris en coordonnees virtuelles
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jintArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1convertirCoordonneesSouris(JNIEnv *env, jclass, jint SourisX, jint SourisY)

{
	Vecteur3 curseur(0,0,0);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(SourisX,SourisY,curseur);

	jintArray resultat;
	 resultat = env->NewIntArray(2);
 if (resultat == NULL) {
     return NULL; /* plus de mémoire */
 }
 int i; 
 //remplir un tableau temporaire utilisé pour peupler le tableau d'entier Java
 jint fill[2];
 for (i = 0; i < 2; i++) {
     fill[i] = (int)curseur[i]; 
 }

 //deplacer le contenu du tableau temporaire à resultat
 env->SetIntArrayRegion(resultat,0,2,fill);
 return resultat;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jintArray Java_ca_polymtl_inf2990_InterfaceJava_fctC_1recevoirInformation(JNIEnv *env, jclass)
///
/// Envoie les informations pertinantes d'un objet pour pouvoir les afficher dans 
/// une boite de dialogue
/// 
/// @return un jintarray contenant: la position relative de l'objet, la rotation de cet objet et son facteur d'agrandissement
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jintArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1recevoirInformation(JNIEnv *env, jclass)

{
	jintArray resultat;
			 resultat = env->NewIntArray(5);
		 if (resultat == NULL) {
			 return NULL; /* plus de mémoire */
		 }
	jint fill[5];
	fill[2] = -1;
	if(FacadeModele::obtenirInstance()->obtenirNoeudsSlection().size() == 1) 
	{
		std::list<NoeudAbstrait*> select ;
		select = FacadeModele::obtenirInstance()->obtenirNoeudsSlection();
		select.begin();
		Vecteur3 position;
		position = (*select.begin())->obtenirPositionRelative();
		int rotation = (int)(*select.begin())->obtenirRot();

		int facteur = (int)(*select.begin())->obtenirFacteurAgrandissment();

		
		 //remplir un tableau temporaire utilisé pour peupler le tableau d'entier Java
		 fill[0] = (int)position[0];
		 fill[1] = (int)position[1];
		 fill[2] = (int)position[2];
		 fill[3] = rotation;
		 fill[4] = facteur;
		
	}
	 //deplacer le contenu du tableau temporaire à resultat
	env->SetIntArrayRegion(resultat,0,5,fill);
	return resultat;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn JNIEXPORT jintArray Java_ca_polymtl_inf2990_InterfaceJava_fctC_1manipulerObjet(JNIEnv *env, jclass, jint X, jint Y, jint Z, jint rotation, jint facteur)
///
///	Copie les elements selectionnes
///
/// @param[in] X : nouvelle position relative en X
/// @param[in] Y : nouvelle position relative en Y
/// @param[in] Z : nouvelle position relative en Z
/// @param[in] rotation : nouveau angle de rotation
/// @param[in] facteur : nouveau facteur de redimenssion
///
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1manipulerObjet(JNIEnv *env, jclass, jint X, jint Y, jint Z, jint rotation, jint facteur)
{
	FacadeModele::obtenirInstance()->manipulerObjet(X,Y,Z,rotation,facteur);
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jboolean Java_ca_polymtl_inf2990_InterfaceJava_fctC_1enregistrerXml(JNIEnv *env, jclass, jstring nomDoc)
///
/// Appelle la fonction enregistrerXml de la facade pour enregistrer l'arbre de rendu courant dans un fichier XML.
///
/// @param[in] nomDoc : nom du document xml
///
/// @return booleen vrai ou faux si nous avons pu enregistrer le fichier XML
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1enregistrerXml(JNIEnv *env, jclass, jstring nomDoc, jint Par)

{
	const char* cstr=env->GetStringUTFChars(nomDoc,0);
	std::string nomdocument=cstr;
	FacadeModele* facade=FacadeModele::obtenirInstance();
	jboolean success = facade->enregistrerXml(nomdocument, Par);
	env->ReleaseStringUTFChars(nomDoc,cstr);
	return success;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerXml(JNIEnv *env, jclass, jstring nomDoc)
///
/// Appelle la fonction chargerXml de la facade pour charger l'arbre de rendu dans l'environnement OpenGL.
///
/// @param[in] nomDoc : nom du document xml
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerXml(JNIEnv *env, jclass, jstring nomDoc)

{
	const char* cstr=env->GetStringUTFChars(nomDoc,0);
	std::string nomdocument=cstr;
	FacadeModele* facade=FacadeModele::obtenirInstance();
	facade->chargerXml(nomdocument);
	env->ReleaseStringUTFChars(nomDoc,cstr);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1clickBalle(JNIEnv *env, jclass, int X, int Y)
///
/// Cette methode permet de verifier si la balle a ete cliquer
///
///	@param[in]	x : position x du click
///	@param[in]	y : position y du click		
/// @return bool si l'utilisateur a clicker sur la balle
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1clickBalle(JNIEnv *env, jclass, jint X, jint Y)

{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	return facade->clickBalle(X,Y);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn jboolean JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1verifierVictoire(JNIEnv *env, jclass)
///
/// Cette methode permet de verifier si la balle est dans le trou
///
/// @return bool si la balle est dans le trou
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1verifierVictoire(JNIEnv *env, jclass)

{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	return facade->verifierVictoire();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1creerFleche(JNIEnv *env, jclass)
///
/// Cette methode ajoute une fleche a l'arbre de rendu
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1creerFleche(JNIEnv *env, jclass)
{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	facade->creerFleche();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1effacerFleche(JNIEnv *env, jclass)
///
/// Cette methode efface une fleche a l'arbre de rendu

/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1effacerFleche(JNIEnv *env, jclass)
{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	facade->effacerFleche();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFleche(JNIEnv *env, jclass, jint x, jint y)
///
/// Cette methode permet de mettre les bons parametres a la fleche
///
///	@param[in]	x : position x du click
///	@param[in]	y : position y du click		
/// @return void
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFleche(JNIEnv *env, jclass, jint x, jint y)
{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	facade->modifierFleche(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFlecheTouche(JNIEnv *env, jclass, jint x)
///
/// Cette methode permet de mettre les bons parametres a la fleche
///
///	@param[in]	x : touche appuyer par le clavier
/// @return void
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFlecheTouche(JNIEnv *env, jclass, jint x)
{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	facade->modifierFlecheTouche(x);
}

/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1changerMode(JNIEnv *env, jclass, jboolean)
///
/// Cette methode permet d'indiqué si nous sommes dans le mode jeu ou non
///
/// @param[in]	modeJeu : booléen indiquant si on est dans le mode jeu		
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1changerMode(JNIEnv *env, jclass, jboolean modeJeu)
{
	FacadeModele::obtenirInstance()->modifierMode(modeJeu);
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirFrictionSol(JNIEnv *, jclass)
///
/// Cette envoie au java le facteur de friction du terrain
///
/// @return jint: facteur friction terrain
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirFrictionSol
  (JNIEnv *, jclass)
{
	return (int)ConfigScene::obtenirInstance()->obtenirCoefFriSol();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFrictionSol(JNIEnv *, jclass, jint coefFrictionSol)
///
/// Cette methode permet de modifier le facteur de friction du sol dans le gestionaire xml
///
/// @param[in]	jint : nouveau coefficient du sol
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFrictionSol
  (JNIEnv *, jclass, jint coefFrictionSol)
{
	ConfigScene::obtenirInstance()->modifierCoefFriSol(coefFrictionSol);
}

/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirFrictionSable(JNIEnv *, jclass)
///
/// Cette envoie au java le facteur de friction du Sable
///
/// @return jint: facteur friction Sable
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirFrictionSable
  (JNIEnv *, jclass)
{
	return (int)ConfigScene::obtenirInstance()->obtenirCoefFriSable();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFrictionSable(JNIEnv *, jclass, jint coefFrictionSable)
///
/// Cette methode permet de modifier le facteur de friction du sol dans le gestionaire xml
///
/// @param[in]	jint : nouveau coefficient du sol
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFrictionSable
  (JNIEnv *, jclass, jint coefFrictionSable)
{
	ConfigScene::obtenirInstance()->modifierCoefFriSable(coefFrictionSable);
}




/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirRebondMur(JNIEnv *, jclass)
///
/// Cette envoie au java le coefficient de rebond du mur
///
/// @return jint: coefficient de rebond du mur
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirRebondMur
  (JNIEnv *, jclass)
{
	return (int)ConfigScene::obtenirInstance()->obtenirCoefRebondMur();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierRebondMur(JNIEnv *, jclass, jint coefRebondMur)
///
/// Cette methode permet de modifier le coefficient de rebond du mur dans le gestionaire xml
///
/// @param[in]	jint : nouveau coefficient de rebond du mur
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierRebondMur
  (JNIEnv *, jclass, jint coefRebondMur)
{
	ConfigScene::obtenirInstance()->modifierCoefRebondMur(coefRebondMur);
}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirAccelerationBonus(JNIEnv *, jclass)
///
/// Cette envoie au java l'accélération causé par le bonus
///
/// @return jint: coefficient de rebond du mur
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirAccelerationBonus
  (JNIEnv *, jclass)
{
	return (int)ConfigScene::obtenirInstance()->obtenirAccelBonus();
}




/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierAccelerationBonus(JNIEnv *, jclass, jint accelBonus)
///
/// Cette methode permet de modifier l'accélération causé par le bonus dans le gestionaire xml
///
/// @param[in]	jint : nouvelle accélération
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierAccelerationBonus
  (JNIEnv *, jclass, jint accelBonus)
{
	ConfigScene::obtenirInstance()->modifierAccelBonus(accelBonus);
}


//////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirTailleEditionHauteur(JNIEnv *, jclass)
///
/// Cette envoie au java la hauteur de la zone d'édition
///
/// @return jint: la hauteur de la zone d'édition
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirTailleEditionHauteur
  (JNIEnv *, jclass)
{
	return ConfigScene::obtenirInstance()->obtenirTailleEditionHauteur();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierAccelerationBonus(JNIEnv *, jclass, jint tailleEditionHauteur)
///
/// Cette methode permet de modifier l'acceleration bonus
///
/// @param[in]	jint : la hauteur de la zone d'édition
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierTailleEditionHauteur
  (JNIEnv *, jclass, jint tailleEditionHauteur)
{
	ConfigScene::obtenirInstance()->modifierTailleEditionHauteur(tailleEditionHauteur);
}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirTailleEditionHauteur(JNIEnv *, jclass)
///
/// Cette envoie au java la taille de la zone d'édition
///
/// @return jint: taille de la zone d'édition
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirTailleEditionLargeur
  (JNIEnv *, jclass)
{
	return ConfigScene::obtenirInstance()->obtenirTailleEditionLargeur();
}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierAccelerationBonus(JNIEnv *, jclass, jint tailleEditionHauteur)
///
/// Cette methode permet de modifier la hauteur de la zone d'édition dans le gestionaire xml
///
/// @param[in]	jint : la hauteur de la zone d'édition
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierTailleEditionLargeur
  (JNIEnv *, jclass, jint tailleEditionLargeur)
{
	ConfigScene::obtenirInstance()->modifierTailleEditionLargeur(tailleEditionLargeur);
}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1forcerSauvergardeConfig(JNIEnv *, jclass)
///
/// Cette fonction cause la sauvegarde du fichier Config XML
///
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1forcerSauvergardeConfig
  (JNIEnv *, jclass)
{
	ConfigScene::obtenirInstance()->forcerSauvegardeConfig();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1effacerFichierXml(JNIEnv *env, jclass, jstring nomDoc)
///
/// Cette fonction cause la sauvegarde du fichier Config XML
/// @param[in] Nom du document ou on va sauvegarder
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1effacerFichierXml(JNIEnv *env, jclass, jstring nomDoc)
{
	const char* cstr=env->GetStringUTFChars(nomDoc,0);
	std::string nomdocument=cstr;
	VisiteurXML* visiteur=VisiteurXML::obtenirInstance();
	visiteur->effacerFichierXml(nomdocument);
	env->ReleaseStringUTFChars(nomDoc,cstr);
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerFichierJoueur(JNIEnv *, jclass)
///
/// Cette fonction charge le fichier joueur
///
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerFichierJoueur(JNIEnv *, jclass)
{
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->chargerFichierJoueur();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerFichierTournoi(JNIEnv *, jclass)
///
/// Cette fonction charge le fichier tournoi
///
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerFichierTournoi
  (JNIEnv *, jclass)
{
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->chargerFichierTournoi();
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1enregistrerFichierJoueur(JNIEnv *, jclass)
///
/// Cette fonction enregistre le fichier Joueur
///
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1enregistrerFichierJoueur
  (JNIEnv *, jclass)
{
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->enregistrerFichierJoueur();	
}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1enregistrerFichierTournoi(JNIEnv *, jclass)
///
/// Cette fonction enregistre le fichier tournoi
///
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1enregistrerFichierTournoi
  (JNIEnv *, jclass)
{
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->enregistrerFichierTournoi();	

}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajouterJoueur(JNIEnv *env, jclass, jstring nomDoc)
///
/// Cette fonction permet d'ajouter un nouveau joueur
/// @param[in] Nom du document du nouveau joeur
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajouterJoueur(JNIEnv *env, jclass, jstring nomDoc)
{
	const char* cstr=env->GetStringUTFChars(nomDoc,0);
	std::string nomdocument=cstr;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->ajouterJoueur(nomdocument);
	env->ReleaseStringUTFChars(nomDoc,cstr);

}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajouterTournoi(JNIEnv *env, jclass, jstring nomDoc)
///
/// Cette fonction permet d'ajouter un nouveau tournoi
/// @param[in] Nom du document du nouveau tournoi
/// @return aucun
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajouterTournoi(JNIEnv *env, jclass, jstring nomDoc)
{
	const char* cstr=env->GetStringUTFChars(nomDoc,0);
	std::string nomdocument=cstr;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->ajouterTournoi(nomdocument);
	env->ReleaseStringUTFChars(nomDoc,cstr);

}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jintArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirToucheClavier
///
/// Cette fonction envoie au java les touches définies pour le controle de la balle
/// par le clavier
/// 
/// @return jintArray: Touches définies
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jintArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirToucheClavier
  (JNIEnv *env, jclass)
{
	jintArray resultat;
	resultat = env->NewIntArray(5);
	if (resultat == NULL) {
		return NULL; /* plus de mémoire */
	}
	jint fill[5];
	ConfigScene* gestionnaire=ConfigScene::obtenirInstance();

	//remplir un tableau temporaire utilisé pour peupler le tableau d'entier Java
	fill[0] = gestionnaire->obtenirToucheClavier()[0];
	fill[1] = gestionnaire->obtenirToucheClavier()[1];
	fill[2] = gestionnaire->obtenirToucheClavier()[2];
	fill[3] = gestionnaire->obtenirToucheClavier()[3];
	fill[4] = gestionnaire->obtenirToucheClavier()[4];


	//deplacer le contenu du tableau temporaire à resultat
	env->SetIntArrayRegion(resultat,0,5,fill);
	return resultat;

}


/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jintArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierToucheClavier(JNIEnv *, jclass, jint gauche, jint droit, jint haut, jint bas, jint espace)
///
/// Cette fonction permet de modifier les touches 
/// pour le controle de la balle par le clavier
/// @param[in] touche incrementer angle
/// @param[in] touche decrementer angle
/// @param[in] touche incrementer force
/// @param[in] touche decrementer force
/// @param[in] touche swing
/// @return jintArray: Touches définies
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierToucheClavier
  (JNIEnv *, jclass, jint gauche, jint droit, jint haut, jint bas, jint espace)
{
	ConfigScene* gestionnaire=ConfigScene::obtenirInstance();
	gestionnaire->modifierToucheClavier(gauche,droit,haut, bas, espace); 
}

/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jintArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierOptionClavier(JNIEnv *env, jclass, jstring nomTournoi)
///
/// Cette fonction permet d'obtenir les touches 
/// pour le controle de la balle par le clavier
/// @return resultat : Touches définies
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirOptionClavier
  (JNIEnv *env, jclass)
{
	jobjectArray resultat;
	resultat = (jobjectArray)env->NewObjectArray(5,
		env->FindClass("java/lang/String"),
		env->NewStringUTF(""));
	ConfigScene* gestionnaire=ConfigScene::obtenirInstance();


	//const char *message[5];
	//for (int i=0;i<5;++i)
	//{
	//	message[i]=gestionnaire->obtenirOptionClavier()[i].c_str();
	

	std::vector<std::string> message= gestionnaire->obtenirOptionClavier();
	for(int j=0;j<5;j++) 
	{
		env->SetObjectArrayElement(
			resultat,j,env->NewStringUTF(message[j].c_str()));
	}
	return resultat;
}



/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierOptionClavier(JNIEnv *env, jclass, jstring nomTournoi)
///
/// Cette fonction permet de modifier les touches 
/// pour le controle de la balle par le clavier
/// @param[in] touche incrementer angle
/// @param[in] touche decrementer angle
/// @param[in] touche incrementer force
/// @param[in] touche decrementer force
/// @param[in] touche swing
/// @return none
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierOptionClavier
  (JNIEnv *env, jclass, jstring gauche, jstring droit, jstring haut, jstring bas, jstring espace)
{
	ConfigScene* gestionnaire=ConfigScene::obtenirInstance();
	const char* cstr=env->GetStringUTFChars(gauche,0);
	const char* cstr1=env->GetStringUTFChars(droit,0);
	const char* cstr2=env->GetStringUTFChars(haut,0);
	const char* cstr3=env->GetStringUTFChars(bas,0);
	const char* cstr4=env->GetStringUTFChars(espace,0);
	std::string parametre0=cstr;
	std::string parametre1=cstr1;
	std::string parametre2=cstr2;
	std::string parametre3=cstr3;
	std::string parametre4=cstr4;
	gestionnaire->modifierOptionClavier(parametre0,parametre1,parametre2,parametre3,parametre4);
	env->ReleaseStringUTFChars(gauche,cstr);
	env->ReleaseStringUTFChars(droit,cstr1);
	env->ReleaseStringUTFChars(haut,cstr2);
	env->ReleaseStringUTFChars(bas,cstr3);
	env->ReleaseStringUTFChars(espace,cstr4);
}

/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsParcours(JNIEnv *env, jclass, jstring nomTournoi)
///
/// Cette fonction envoie au java les noms du parcour selon le tournoi selectionné
/// @param[in] Nom du fichier tournoi
/// @return jobjectArray: Noms des parcours
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsParcours
  (JNIEnv *env, jclass, jstring nomTournoi)
{
	jobjectArray resultat;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	const char* cstr=env->GetStringUTFChars(nomTournoi,0);
	std::string nomDuTournoi=cstr;
	env->ReleaseStringUTFChars(nomTournoi,cstr);
	int nombreParcours=gestionnaire->obtenirNombreParcours(nomDuTournoi);
	resultat = (jobjectArray)env->NewObjectArray(nombreParcours,
         env->FindClass("java/lang/String"),
         env->NewStringUTF(""));
	

	std::vector<std::string> temp=gestionnaire->obtenirNomsParcours(nomDuTournoi);
	//const char *message[9];
	//for (int i=0;i<9;++i)
	//{
	//	message[i]=[i].c_str();
	//}
	for(int j=0;j<nombreParcours;j++) 
	{
		env->SetObjectArrayElement(
			resultat,j,env->NewStringUTF(temp[j].c_str()));
	}
	return resultat;

}
/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsTournois(JNIEnv *env, jclass)
///
/// Cette fonction envoie au java les noms de tournois se trouvant dans le fichier par defaut.
/// @return jobjectArray: Noms des tournois
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsTournois
  (JNIEnv *env, jclass)
{
	jobjectArray resultat;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	int nombreTournoi=gestionnaire->obtenirNombreTournois();
	resultat = (jobjectArray)env->NewObjectArray(nombreTournoi,
         env->FindClass("java/lang/String"),
         env->NewStringUTF(""));
	

	std::vector<std::string> temp=gestionnaire->obtenirNomsTournois();
	//const char *message[9];
	//for (int i=0;i<9;++i)
	//{
	//	message[i]=[i].c_str();
	//}
	for(int j=0;j<nombreTournoi;j++) 
	{
		env->SetObjectArrayElement(
			resultat,j,env->NewStringUTF(temp[j].c_str()));
	}
	return resultat;
}
/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNombreTournois(JNIEnv *env, jclass)
///
/// Cette fonction envoie au java les nombre de tournois se trouvant dans le fichier par defaut.
/// @return jint: Nombre de tournois
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNombreTournois
  (JNIEnv *, jclass)
{
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	return gestionnaire->obtenirNombreTournois();
}

/////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFicheTournoi(JNIEnv *env, jclass, jstring nomTournoi)
///
/// Cette fonction permet de modifier la fiche de score du tournoi
/// @param[in] Nom du tournoi
/// @param[in] Parcour courrant
/// @param[in] Nom du joueur
/// @param[in] Score pour le parcour
/// @return void
///
/////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1modifierFicheTournoi
  (JNIEnv *env, jclass, jstring nomTournoi, jstring parcours, jstring nomJoueur, jint Score)
{
	const char* cstr=env->GetStringUTFChars(nomTournoi,0);
	const char* cstr1=env->GetStringUTFChars(parcours,0);
	const char* cstr2=env->GetStringUTFChars(nomJoueur,0);
	std::string nomdocument=cstr;
	std::string nomdocument1=cstr1;
	std::string nomdocument2=cstr2;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->modifierFicheTournoi(nomdocument,nomdocument1,nomdocument2,Score);
	env->ReleaseStringUTFChars(nomTournoi,cstr);
	env->ReleaseStringUTFChars(parcours,cstr1);
	env->ReleaseStringUTFChars(nomJoueur,cstr2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1changerVue(JNIEnv *, jclass)
///
/// Cette fonction change la vue
///
/// @param[in] env    : L'environnement Java.
/// @param[in] vue    : vue courante.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1changerVue(JNIEnv *, jclass, jint vue)
{
	FacadeModele::obtenirInstance()->changerVue(vue);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajouterParcoursATournoi
///  (JNIEnv *env, jclass, jstring Nomtournoi, jstring NomParcours)
///
/// Cette fonction permet d'ajouter un parcours au tournoi passe en parametre.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] Nomtournoi    : Le nom du tournoi.
/// @param[in] NomParcours    : Le nom du parcours.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajouterParcoursATournoi
  (JNIEnv *env, jclass, jstring Nomtournoi, jstring NomParcours)
{
	const char* cstr=env->GetStringUTFChars(Nomtournoi,0);
	const char* cstr1=env->GetStringUTFChars(NomParcours,0);
	std::string nomTournoi=cstr;
	std::string nomParcours=cstr1;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	gestionnaire->ajouterParcoursATournoi(nomTournoi,nomParcours);
	env->ReleaseStringUTFChars(Nomtournoi,cstr);
	env->ReleaseStringUTFChars(NomParcours,cstr1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserSon(JNIEnv *, jclass)
///
/// Cette fonction initialise le son
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserSon(JNIEnv *, jclass)
{
	Sound::obtenirInstance()->initSon();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1play(JNIEnv *, jclass)
///
/// Cette fonction part la musique
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1play(JNIEnv *, jclass)
{
	Sound::obtenirInstance()->jouerMusique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1stop(JNIEnv *, jclass)
///
/// Cette fonction arrête la musique
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1stop(JNIEnv *, jclass)
{
	Sound::obtenirInstance()->arreterMusique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajusterVolumeSon(JNIEnv *, jclass, jint volume)
///
/// Cette fonction change le volume des sons
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajusterVolumeSon(JNIEnv *, jclass, jfloat volume)
{
	Sound::obtenirInstance()->ajusterVolumeSon(volume);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajusterVolumeMusique(JNIEnv *, jclass, jint volume)
///
/// Cette fonction change le volume de la musique
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1ajusterVolumeMusique(JNIEnv *, jclass, jfloat volume)
{
	Sound::obtenirInstance()->ajusterVolumeMusique(volume);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiqueSuivante(JNIEnv *, jclass)
///
/// Cette fonction arrête la musique
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiqueSuivante(JNIEnv *, jclass)
{
	Sound::obtenirInstance()->arreterMusique();
	Sound::obtenirInstance()->setChannel(1);
	Sound::obtenirInstance()->jouerMusique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiquePrecedente(JNIEnv *, jclass)
///
/// Cette fonction arrête la musique
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiquePrecedente(JNIEnv *, jclass)
{
	Sound::obtenirInstance()->arreterMusique();
	Sound::obtenirInstance()->setChannel(0);
	Sound::obtenirInstance()->jouerMusique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiqueMenu(JNIEnv *, jclass, jint etat)
///
/// Cette fonction arrête ou repart la musique du menu
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiqueMenu(JNIEnv *, jclass, jint etat)
{
	Sound::obtenirInstance()->MusiqueMenu(etat);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1musiqueMenu(JNIEnv *, jclass, jint etat)
///
/// Cette fonction arrête ou repart le volume
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1mute(JNIEnv *, jclass)
{
	Sound::obtenirInstance()->mute();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1getTypeVue(JNIEnv*, jclass)
///
/// Cette fonction retourne le type de vue utilisee
///
/// @return Un entier representant le type de vue utilisee
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1getTypeVue(JNIEnv*, jclass)
{
	return FacadeModele::obtenirInstance()->getTypeVue(); 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deplacerLibre(JNIEnv*, jclass, jint Horizontale, jint Avant)
///
/// Cette fonction deplace la camera
///
/// @param[in] env    : L'environnement Java.
/// @param[in] Horizontale    : Le deplacement horizontale.
/// @param[in] Avant    : Le deplacement en avant et en arriere.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1deplacerLibre
  (JNIEnv*, jclass, jint Horizontale, jint Avant)
{
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerZ(Avant,true); 
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerXY(Horizontale, Horizontale); 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1tournerCamera(JNIEnv* , jclass, jdouble rotationX, jdouble rotationY)
///
/// Cette fonction tourne la camera
///
/// @param[in] env    : L'environnement Java.
/// @param[in] rotationX    : Le rotation en x.
/// @param[in] rotationY    : Le rotation en y.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1tournerCamera
(JNIEnv* , jclass, jdouble rotationX, jdouble rotationY)
{
	if(FacadeModele::obtenirInstance()->getTypeVue() == 1) //Si on est dans la vue libre
	{
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().tournerXY(rotationX, rotationY);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1orbiterCamera(JNIEnv* , jclass, jdouble rotationX, jdouble rotationY)
///
/// Cette fonction orbite la camera
///
/// @param[in] env    : L'environnement Java.
/// @param[in] rotationX    : Le rotation en x.
/// @param[in] rotationY    : Le rotation en y.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1orbiterCamera
(JNIEnv* , jclass, jdouble rotationX, jdouble rotationY)
{
	Vecteur3 position;
	position = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("balle")->obtenirPositionRelative();

	if(FacadeModele::obtenirInstance()->getTypeVue() == 2) //Si on est dans la vue orbite
	{
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(rotationX, 0);	
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().assignerPointVise(position);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirFrappes(JNIEnv* , jclass)
///
/// Cette fonction retourne le nombre de frappes
///
/// @param[in] env    : L'environnement Java.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirFrappes(JNIEnv* , jclass)
{
	return FacadeModele::obtenirInstance()->obtenirNombreCoups();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1assignerPar(JNIEnv *env, jclass, jint par)
///
/// Cette methode assigne le par du trou
///
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1assignerPar(JNIEnv *env, jclass, jint par)
{
	FacadeModele* facade=FacadeModele::obtenirInstance();
	facade->setPar(par);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomJoueur(JNIEnv* , jclass, jstring)
///
/// Cette fonction retourne le nom du joueur
///
/// @param[in] env    : L'environnement Java.
/// @param[in] jstring    : le nom du joueur
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomJoueur(JNIEnv * env, jclass, jstring nomJoueur)
{
	const char* joueurTemp = env->GetStringUTFChars(nomJoueur,0);
	std::string joueur = joueurTemp;
	FacadeModele::obtenirInstance()->assignerNomJoueur(joueur);
	env->ReleaseStringUTFChars(nomJoueur, joueurTemp);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomMap(JNIEnv * env, jclass, jstring nomMap)
///
/// Cette fonction retourne le nom du joueur
///
/// @param[in] env    : L'environnement Java.
/// @param[in] jstring    : le nom du joueur
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomMap(JNIEnv * env, jclass, jstring nomMap)
{
	const char* mapTemp = env->GetStringUTFChars(nomMap,0);
	std::string map = mapTemp;
	FacadeModele::obtenirInstance()->assignerNomMap(map);
	env->ReleaseStringUTFChars(nomMap, mapTemp);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jdoubleArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1convertirCoordonneesSouris2 (JNIEnv *, jclass, jint, jint)
///
///
/// @param[in] SourisX : coordonnée X de la souris
///	@param[in] SourisY : coordonnée Y de la souris
///
/// convertit les coordonnees de cloture de la souris en coordonnees virtuelles, version jdouble.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jdoubleArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1convertirCoordonneesSouris2(JNIEnv *env, jclass, jint sourisX, jint sourisY)

{
	Vecteur3 curseur(0,0,0);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(sourisX,sourisY,curseur);

	jdoubleArray resultat;
	resultat = env->NewDoubleArray(2);
	if (resultat == NULL) {
		return NULL; /* plus de mémoire */
	}
	int i; 
	//remplir un tableau temporaire utilisé pour peupler le tableau d'entier Java
	jdouble fill[2];
	for (i = 0; i < 2; i++) {
		fill[i] = curseur[i]; 
	}

	//deplacer le contenu du tableau temporaire à resultat#
	env->SetDoubleArrayRegion(resultat,0,2,fill);
	return resultat;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1sauvegarderMultijoueur (JNIEnv *env, jclass, jstring NomMap)
///
///
/// @param[in] NomMap : Nom de la map.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1sauvegarderMultijoueur
  (JNIEnv *env, jclass, jstring NomMap)
{
	const char* mapTemp = env->GetStringUTFChars(NomMap,0);
	std::string map = mapTemp;
	GestionJoueur::obtenirInstance()->sauvegarderMultijoueur(map);
	env->ReleaseStringUTFChars(NomMap, mapTemp);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerMultijoueur (JNIEnv *env, jclass, jstring NomJoueur)
///
///
/// @param[in] NomJoueur : Nom du Joueur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1chargerMultijoueur
  (JNIEnv *env, jclass, jstring NomJoueur)
{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	Vecteur3 temp = arbre->chercher("balle")->obtenirVitesse();
	if(temp[0]==0 && temp[1]==0)
	{
		FacadeModele::obtenirInstance()->reinitialiser();
		VisiteurXML* gestionnaire=VisiteurXML::obtenirInstance();
		gestionnaire->effacerArbreXml();
		const char* joueurTemp = env->GetStringUTFChars(NomJoueur,0);
		std::string joueur = joueurTemp;
		GestionJoueur::obtenirInstance()->chargerReplay(joueur);
		env->ReleaseStringUTFChars(NomJoueur, joueurTemp);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JJNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirPardeMap (JNIEnv *, jclass, jstring nomMap)
///
///
/// @param[in] NomJoueur : Nom du Joueur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirPardeMap
  (JNIEnv *env, jclass, jstring nomMap)
{
	const char* mapTemp = env->GetStringUTFChars(nomMap,0);
	std::string map = mapTemp;
	int par=VisiteurXML::obtenirInstance()->obtenirPardeMap(map);
	env->ReleaseStringUTFChars(nomMap, mapTemp);
	return par; 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JJNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirPardeMap (JNIEnv *, jclass, jstring nomMap)
///
///
/// @param[in] NomJoueur : Nom du Joueur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1initialiserListesAffichage(JNIEnv *env, jclass)
{

	ArbreRenduINF2990* arbre =  FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	arbre->ajouter(arbre->creerNoeud("balle"));
	arbre->ajouter(arbre->creerNoeud("baton"));
	arbre->ajouter(arbre->creerNoeud("bonus"));
	arbre->ajouter(arbre->creerNoeud("terrain"));
	arbre->ajouter(arbre->creerNoeud("sable"));
	arbre->ajouter(arbre->creerNoeud("trou"));
	arbre->ajouter(arbre->creerNoeud("eau"));
	arbre->ajouter(arbre->creerNoeud("portal"));
	arbre->ajouter(arbre->creerNoeud("fleche"));
	arbre->ajouter(arbre->creerNoeud("contour"));
	arbre->ajouter(arbre->creerNoeud("bordure"));
	arbre->vider();


}
////////////////////////////////////////////////////////////////////////
///
/// @fn JJNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNombreJoueursTableauMeilleurScore (JNIEnv *, jclass, jstring nomMap)
///
///
/// @param[in] NomJoueur : Nom du Joueur.
///
/// @return nombre de joueurs dans le fichier de meilleurs scores.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNombreJoueursTableauMeilleurScore
  (JNIEnv *env, jclass)
{
	int nbJoueurs=GestionJoueur::obtenirInstance()->obtenirNombreJoueursTableauMeilleurScore();
	return nbJoueurs;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JJNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNombreParcoursTableauMeilleurScore(JNIEnv *, jclass, jstring nomMap)
///
///
/// @param[in] NomJoueur : Nom du Joueur.
///
/// @return int du nombre de parcours presents sous le joeur dans le fichier joueurXML_ de meilleurs scores.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNombreParcoursTableauMeilleurScore
  (JNIEnv *env, jclass, jstring nomJoueur)
{
	const char* JoueurTemp = env->GetStringUTFChars(nomJoueur,0);
	std::string Joueur = JoueurTemp;
	int nbParcours=GestionJoueur::obtenirInstance()->obtenirNombreParcoursTableauMeilleurScore(Joueur);
	env->ReleaseStringUTFChars(nomJoueur, JoueurTemp);
	return nbParcours;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn JJNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsParcoursTableauMeilleurScore(JNIEnv *, jclass, jstring nomMap)
///
///
/// @param[in] NomJoueur : Nom du Joueur.
///
/// @return jobjectArray : Noms des parcours dans le fichier des meilleurs joueurs.
///
////////////////////////////////////////////////////////////////////////

JNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsParcoursTableauMeilleurScore
  (JNIEnv *env, jclass, jstring nomJoueur)
{
	const char* JoueurTemp = env->GetStringUTFChars(nomJoueur,0);
	std::string Joueur = JoueurTemp;
	GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
	int nbParcours=gestionnaire->obtenirNombreParcoursTableauMeilleurScore(Joueur);
	env->ReleaseStringUTFChars(nomJoueur, JoueurTemp);
	jobjectArray resultat;
	
	int nombreParcours=gestionnaire->obtenirNombreParcoursTableauMeilleurScore(Joueur);
	resultat = (jobjectArray)env->NewObjectArray(nombreParcours,
		env->FindClass("java/lang/String"),
		env->NewStringUTF(""));


	std::vector<std::string> temp=gestionnaire->obtenirNomsParcoursTableauMeilleurScore(Joueur);
	for(int j=0;j<nombreParcours;j++) 
	{
		env->SetObjectArrayElement(
			resultat,j,env->NewStringUTF(temp[j].c_str()));
	}
	return resultat;

}
////////////////////////////////////////////////////////////////////////
///
/// @fn JJNIEXPORT jobjectArray JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1obtenirNomsParcoursTableauMeilleurScore(JNIEnv *, jclass, jstring nomMap)
///
///

///
/// @return NILL
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_InterfaceJava_fctC_1effacerFichierJoueur
  (JNIEnv *env, jclass)
{
	GestionJoueur::obtenirInstance()->effacerFichierJoueur();
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////