///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

@li <a href="../Javadoc/index.html">Documentation Javadoc de la partie Java.</a>
*/
#include "FacadeModele.h"
#include <windows.h>
#include <cassert>
#include "FreeImage.h"
#include "HUD.h"
#include "VueOrtho.h"
#include "VuePerspective.h"
#include "Camera.h"
#include "Projection.h"
#include "Utilitaire.h"
#include "AideCollision.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include "Sound.h"
#include "GestionJoueur.h"

#include "ConfigScene.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml.h"

#include "CompteurAffichage.h"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_ = 0;

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION = "configuration.xml";

//Aller chercher l'instance du son
Sound* sound_ = Sound::obtenirInstance();

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == 0)
		instance_ = new FacadeModele;

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::FacadeModele()
///
/// Ce constructeur par défaut ne fait qu'initialiser toutes les
/// variables à une valeur nulle.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::FacadeModele()
	: hGLRC_(0), hDC_(0), hWnd_(0), vue_(0), arbre_(0), isBalle_(false), isTrou_(false), angle_ (0), force_ (0), flecheKeyboard_(false), frappes_(0), modeJeu_(false), tomber_(true), test_(false), compteur_(0),estModeReplay_(false)
{
	positionSoleil[0] = 0;
	positionSoleil[1] = 0;
	positionSoleil[2] = 100;
	positionSoleil[3] = 0;
	angleSoleil_ = 0;

	ValeurAmbiante[0] = 0;
	ValeurAmbiante[1] = 0;
	ValeurAmbiante[2] = 0;
	ValeurAmbiante[3] = 0;

	positionLune[0]= 0;
	positionLune[1] = 0;
	positionLune[2] = 0;
	positionLune[3] = 0;
	alphaBlend_ = 1;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	noeudsSelectiones_.clear();
	delete arbre_;
	delete vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur 3DS) et assigne des paramètres
/// du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes = aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_);
	assert(succes);


	// Initialisation de la configuration
	chargerConfiguration();


	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();
	
	glewInit();

	// compiler et linker les nuanceurs
	initialiserNuanceurs();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumières
	glEnable( GL_LIGHTING );
	glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
	glEnable( GL_COLOR_MATERIAL );

	//Lumiere ambiante
	glEnable(GL_LIGHT0);
	GLfloat ambient[4] ={0.25f,0.25f,0.25f,0};
	GLfloat difuse[4] = {0.05f,0.05f,0.05f,0};
	GLfloat speculaire[4] = {0,0,0,0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ValeurAmbiante);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, speculaire);
	glLightf ( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
	glLightf ( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.09f );
	glLightf ( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0 );

	//lumiere soleil
	glEnable(GL_LIGHT1);
	glLightf ( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
	glLightf ( GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.009f );
	glLightf ( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0 );
	GLfloat lumAmbient1 [] = {0,0,0,1};
	GLfloat lumDiffuse1 [] = {0.5,0.5,0.5,1};
	GLfloat lumSpecular1 [] = {0,0,0,1};
	glLightfv( GL_LIGHT1, GL_AMBIENT, lumAmbient1 );
	glLightfv( GL_LIGHT1, GL_DIFFUSE, lumDiffuse1 );
	glLightfv( GL_LIGHT1, GL_SPECULAR, lumSpecular1 );

	//Lumiere lune
	glEnable(GL_LIGHT2);
	GLfloat lumAmbient2 [] = {0,0,0,1};
	GLfloat lumDiffuse2 [] = {0.1f,0.1f,0.3f,1.0f};
	GLfloat lumSpecular2 [] = {0,0,0,1};
	glLightfv( GL_LIGHT2, GL_AMBIENT, lumAmbient2 );
	glLightfv( GL_LIGHT2, GL_DIFFUSE, lumDiffuse2 );
	glLightfv( GL_LIGHT2, GL_SPECULAR, lumSpecular2 );
	glLightf ( GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);
	glLightf ( GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.05f );
	glLightf ( GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0 );

	glEnable(GL_LIGHT3);
	GLfloat position3[4] = { 0, 0, 100, 0 };

	GLfloat angle = 4;
	GLint lum3_spotExponent = 15;
	GLfloat lum3_spotDirection[] = { 0, 0, -1 };

	glLightfv( GL_LIGHT3, GL_SPOT_CUTOFF, &angle );
	glLightfv( GL_LIGHT3, GL_SPOT_DIRECTION, lum3_spotDirection );
	glLightiv( GL_LIGHT3, GL_SPOT_EXPONENT, &lum3_spotExponent );
	glLightf ( GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0);
	glLightf ( GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.009f );
	glLightf ( GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0 );

	glEnable(GL_LIGHT4);
	GLfloat ambient4[4] = {0,0,0,0};
	GLfloat difuse4[4] = {1,1,1,0};
	GLfloat speculaire4[4] = {0,0,0,0};
	
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambient4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, difuse4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, speculaire4);
	/*glLightf ( GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0);
	glLightf ( GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.05f );
	glLightf ( GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0 );*/

		//Spotlight
	GLfloat lumAmbient3 [] = {0.25f,0.25f,0.25f,1};
	GLfloat lumDiffuse3 [] = {0.7f,0.7f,0.7f,0.7f};
	GLfloat lumSpecular3 [] = {0,0,0,1};
	glLightfv( GL_LIGHT3, GL_AMBIENT, lumAmbient3 );
	glLightfv( GL_LIGHT3, GL_DIFFUSE, lumDiffuse3 );
	glLightfv( GL_LIGHT3, GL_SPECULAR, lumSpecular3 );

	GLfloat lumAmbient5 [] = {0,0,0,1};
	GLfloat lumDiffuse5 [] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat lumSpecular5 [] = {1,1,1,1};
	glEnable(GL_LIGHT5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, lumAmbient5);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, lumDiffuse5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, lumSpecular5);
	glLightf ( GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0);
	glLightf ( GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.009f );
	glLightf ( GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0 );

	//glEnable(GL_LIGHT6);
	//glLightfv(GL_LIGHT6, GL_AMBIENT, lumAmbient3);
	//glLightfv(GL_LIGHT6, GL_DIFFUSE, lumDiffuse3);
	//glLightfv(GL_LIGHT6, GL_SPECULAR, lumSpecular3);
	//glLightf ( GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0);
	//glLightf ( GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.009f );
	//glLightf ( GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0 );

	//glEnable(GL_LIGHT7);
	//glLightfv(GL_LIGHT7, GL_AMBIENT, lumAmbient3);
	//glLightfv(GL_LIGHT7, GL_DIFFUSE, lumDiffuse3);
	//glLightfv(GL_LIGHT7, GL_SPECULAR, lumSpecular3);
	//glLightf ( GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0);
	//glLightf ( GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.009f );
	//glLightf ( GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0 );

	glEnable( GL_VERTEX_PROGRAM_TWO_SIDE ); // two-side mode en GLSL
	// Qualité
	glShadeModel( GL_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

	// Profondeur
	glEnable( GL_DEPTH_TEST );

	// Le cull face
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	//skybox
	skybox();

	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();
	
	vueOrtho_ = new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 200), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, 500, 0, 500,
		1, 1000, 1, 10000, 1.25,
		-100, 100, -100, 100
		);

	vueLibre_ = new vue::VueLibre(
		vue::Camera(Vecteur3(0, -400, 150), Vecteur3(0, 0, 100),
		Vecteur3(0, 0, 1)  , Vecteur3(0, 0, 1)),
		0, 500, 0, 500,
		1, 1000, 1, 10000, 1.25,
		-100, 100, -100, 100
		);

	vueCiel_ = new vue::VueCiel(
		vue::Camera(Vecteur3(0, -350, 600), Vecteur3(0, 0, 0),
		Vecteur3(0, 0, 1)  , Vecteur3(0, 0, 1)),
		0, 500, 0, 500,
		1, 1000, 1, 10000, 1.25,
		-100, 100, -100, 100
		);

	vueOrbite_ = new vue::VueOrbite(
		vue::Camera(Vecteur3(0, -350, 200), Vecteur3(0, 0, 0),
		Vecteur3(0, 0, 1)  , Vecteur3(0, 0, 1)),
		0, 500, 0, 500,
		1, 1000, 1, 10000, 1.25,
		-100, 100, -100, 100
		);

	vue_ = vueLibre_;
	typeVue_ = "Vue : Libre";

	// Initialisation.
	reinitialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if ( !utilitaire::fichierExiste(FICHIER_CONFIGURATION) ) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {

		// On lit les différentes configurations.
		try 
		{
			if(ConfigScene::obtenirInstance()->chargerFichierConfig(FacadeModele::FICHIER_CONFIGURATION.c_str())==false)
				throw "Echec de chargement de variables du fichier de configuration";
		}
		catch( char * str ) 
		{
			std::cout << "Exception raised: " << str << '\n';
		}

	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	/*TiXmlElement* positionFenetre = new TiXmlElement("fenetre");
	positionFenetre->SetAttribute("position", FacadeModele::obtenirInstance()->);
	document.LinkEndChild(positionFenetre);*/

	// On enregistre les différentes configurations.

	ConfigScene::obtenirInstance()->Xmlvide(FacadeModele::FICHIER_CONFIGURATION);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();


	bool succes = aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_);
	assert(succes);

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	
	// Efface l'ancien rendu
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	
	GLfloat angle = 15;
	GLint lum3_spotExponent = 15;
	GLfloat lum3_spotDirection[] = { 0.3, -0.3, -1 };

	glLightfv( GL_LIGHT3, GL_SPOT_CUTOFF, &angle );
	glLightfv( GL_LIGHT3, GL_SPOT_DIRECTION, lum3_spotDirection );
	glLightiv( GL_LIGHT3, GL_SPOT_EXPONENT, &lum3_spotExponent );

    GLfloat lum3_position[] = {-130, 130, 400, 1.0 };
	glLightfv( GL_LIGHT3, GL_POSITION, lum3_position);



	Vecteur3 posTrou;
	GLfloat angleLumTrou = 1.8f;
	if(arbre_->chercher("trou") != nullptr)
		posTrou = arbre_->chercher("trou")->obtenirPositionRelative();
	else
	{
		posTrou[0] = 0;
		posTrou[1] = 0;
	}
    GLfloat lum5_position[] = {posTrou[0], posTrou[1], 400, 1.0 };
	GLfloat lum5_spotDirection[] = { 0.0, 0.0, -1 };
	glLightfv( GL_LIGHT5, GL_POSITION, lum5_position);		
	glLightfv( GL_LIGHT5, GL_SPOT_CUTOFF, &angleLumTrou );
	glLightfv( GL_LIGHT5, GL_SPOT_DIRECTION, lum5_spotDirection );
	glLightiv( GL_LIGHT5, GL_SPOT_EXPONENT, &lum3_spotExponent );

	//glLightfv( GL_LIGHT6, GL_SPOT_CUTOFF, &angleLumTrou );
	//glLightfv( GL_LIGHT6, GL_SPOT_DIRECTION, lum5_spotDirection );
	//glLightiv( GL_LIGHT6, GL_SPOT_EXPONENT, &lum3_spotExponent );

   /* GLfloat lum6_position[] = {130, -130, 400, 1.0 };
	glLightfv( GL_LIGHT6, GL_POSITION, lum6_position);

	glLightfv( GL_LIGHT7, GL_SPOT_CUTOFF, &angle );
	glLightfv( GL_LIGHT7, GL_SPOT_DIRECTION, lum3_spotDirection );
	glLightiv( GL_LIGHT7, GL_SPOT_EXPONENT, &lum3_spotExponent );

    GLfloat lum7_position[] = {-130, -130, 400, 1.0 };
	glLightfv( GL_LIGHT7, GL_POSITION, lum7_position);*/

	GLfloat position[4] = { 0, 0, 100, 0 };
	
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT4, GL_POSITION, position);

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	

	// Positionne la caméra
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	vue_->appliquerCamera();
	
	//skybox
	//if(skyboxTex_ == 1)
	//{
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
		glColor4f(1.0f,1.0f,1.0f,alphaBlend_);         // Full Brightness, 50% Alpha ( NEW )
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);    
        glEnable(GL_BLEND);     // Turn Blending On
        glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
		glDisable(GL_TEXTURE_2D);
		skybox_->afficher(Vecteur3(vue_->obtenirCamera().obtenirPosition()),250);
        glDisable(GL_BLEND);        // Turn Blending Off
        glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
		glPopAttrib();


	// Afficher la scène
	afficherBase();

	

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers( hDC_ );
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	if(modeJeu_ == true)
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glEnable(GL_LIGHT5);
	}
	else
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		glEnable(GL_LIGHT5);
	}
	
	

	// Positionner la lumière.
	// Lumière ambiante
	


	//Lumière Soleil
	//GLfloat LumPosition1 [] =	{0,0,100,1};
	glLightfv( GL_LIGHT1, GL_POSITION, positionSoleil );

	//Lumière Lune
	glLightfv( GL_LIGHT2, GL_POSITION, positionLune );



	// Afficher la scène. 
	arbre_->afficher();
	//HUD
	if(modeJeu_ == true)
		HUD::getInstance()->dessinerHUD(frappes_,obtenirDistanceBalleTrou(), typeVue_,nomJoueur_,nomMap_);
		

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rafraichirFenetre() const
///
/// Cette fonction rafraîchit le contenu de la fenêtre, c'est-à-dire
/// qu'elle indique à Windows que la fenêtre doit être repeinte.  Un
/// événement sera donc généré puis traité plus tard, ce qui évite de
/// faire plusieurs affichages sans raison.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::rafraichirFenetre() const
{
	// Indique à Windows que la fenêtre doit être rafraîchie.
	//::InvalidateRect(hWnd_, 0, FALSE);

	// Finalement, on choisit de simplement appeler afficher() pour éviter
	// que le fond ne soit redessiné par Windows ou Java.

	// Or, comme il y a en permanence une boucle qui réaffiche, on ne fait
	// rien.

	//afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	isBalle_ = false;
	isTrou_ = false;
	frappes_ = 0;
	noeudsSelectiones_.empty();
	// Réinitialisation de la scène.
	arbre_->initialiser();
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
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
void FacadeModele::animer(float temps)
{
	//Mise à jour du soleil
	angleSoleil_+= 0.00005f;
	if(angleSoleil_>=360)
	{
		angleSoleil_ = 0;
	}
	ValeurAmbiante[0] = 0.45f * sin(angleSoleil_) + 0.01f;
	ValeurAmbiante[1] = ValeurAmbiante[0];
	ValeurAmbiante[2] = ValeurAmbiante[0];

	positionSoleil[0] = 100 * cos(angleSoleil_* 180 / 3.14159265f);
	positionSoleil[2] = 100 * sin(angleSoleil_* 180 / 3.14159265f);
	positionLune[0] = 100 * cos((angleSoleil_-180.0f)* 180 / 3.14159265f);
	positionLune[2] = 100 * sin((angleSoleil_-180.0f)* 180 / 3.14159265f);
	if(sin(angleSoleil_* 180 / 3.14159265)<-0.5&& modeJeu_ == true)
	{
		glDisable(GL_LIGHT1);
		soleilLeve = false;
	}
	else
	{
		glEnable(GL_LIGHT1);
		soleilLeve = true;
	}

	if(modeJeu_ == true)
		alphaBlend_ = cos((angleSoleil_-180)* 180 / 3.14159265f)+0.5f ;

	if(alphaBlend_<0.2 && modeJeu_ == true)
	{
		alphaBlend_ = 0.2f;
	}
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer( temps );

	if(modeJeu_ == true)
	{
		if(vue_ == vueOrtho_ )//!vue_->obtenirProjection().estPerspective())
		{  
			//vue_->obtenirCamera().assignerPointVise(arbre_->chercher("balle")->obtenirPositionRelative());
			Vecteur3 position = arbre_->chercher("balle")->obtenirPositionRelative();
			position[2] = 200;
			vue_->obtenirCamera().assignerPosition(position);
			position[2] = 0;
			vue_->obtenirCamera().assignerPointVise(position);
			vue_->obtenirCamera().positionner();
		}
		//else if(vue_ == vuePerspective_)
		//{
		//	vue_->obtenirCamera().assignerPointVise(arbre_->chercher("balle")->obtenirPositionRelative());
		//	vue_->obtenirCamera().positionner();
		//}
	}

}


////////////*********************Controle?! bon emplacement?*********************

///////////////////////////////////////////////////////////////////////////////
///
/// @}fn Vecteur3 FacadeModele::pos3Dvirtuelle(int sourisX, int sourisY)
///
/// Fonction transforme les coordonnes X, Y de la souris recu en paramentre
/// En coordonnes Virtuelle X,Y,Z
///
/// @param[in] sourisX : coordonnée X (clôture) du pointeur de la souris
///	@param[in] sourisY : coordonnée Y (clôture) du pointeur de la souris
///
/// @return Vecteur3
///	
///////////////////////////////////////////////////////////////////////////////
Vecteur3 FacadeModele::pos3Dvirtuelle(int sourisX, int sourisY)
{
	Vecteur3 position(0,0,0);
	/*vue_->convertirClotureAVirtuelle(sourisX, sourisY, position);
	return position;*/

	  GLfloat winX, winY, winZ;
	  // Lire la matrice de modélisation et de visualisation.
	  GLdouble matriceModelisation[16];
	  glGetDoublev ( GL_MODELVIEW_MATRIX, matriceModelisation );

	  // Lire la matrice de projection.
	  GLdouble matriceProjection[16];
	  glGetDoublev ( GL_PROJECTION_MATRIX, matriceProjection );

	  // Lire la clôture.
	  GLint cloture[4];
	  glGetIntegerv ( GL_VIEWPORT, cloture );

	  winX = (float)sourisX;
	  winY = (float)cloture[3] - (float)sourisY;
	  glReadPixels( sourisX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	  gluUnProject( winX, winY, winZ, matriceModelisation, matriceProjection, cloture, &position[0], &position[1], &position[2]);

	  return position;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @}fn void FacadeModele::selectionClick(int sourisX, int sourisY, int modeSelection)
///
/// Selectionne un objet base sur les paremetres x et y 
/// En coordonnees virtuelles X,Y,Z
///
/// @param[in] sourisX : coordonnée X (clôture) du pointeur de la souris
///	@param[in] sourisY : coordonnée X (clôture) du pointeur de la souris
///	
///@param[in] modeSelection : 0 selection simple
///							  1 selection multiple
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void  FacadeModele::selectionClick(int sourisX, int sourisY, int modeSelection)
{


	GLint viewport[4];
	GLuint tampon[BUFSIZ];
	GLint nombre_touche;
	glSelectBuffer(BUFSIZ, tampon );
	glGetIntegerv(GL_VIEWPORT, viewport);

	glRenderMode(GL_SELECT); //mode selection
	glInitNames(); //initialisation de la pile de noms
	glPushName(-1);//on push au moin un nom

	glMatrixMode(GL_PROJECTION);//on passe à la matrice de projection

	glPushMatrix();	//on push la matrice de projection
	glLoadIdentity(); // on réinitialise la matrice	
	gluPickMatrix( sourisX, viewport[3]-sourisY, 0.1, 0.1, viewport); //Mat_selection X Mat_projection pour restreindre la zone de selection.
	vue_->obtenirProjection().appliquer();
	glMatrixMode(GL_MODELVIEW);	//on passe à la matrice model_view
	arbre_->afficher(); //on affiche les objets pour déposer leurs noms dans le tampon de selection
	nombre_touche = glRenderMode(GL_RENDER); //on trouve le nombre d'objets selectionnés
	glMatrixMode(GL_PROJECTION); //on passe à la matrice de projection
	glPopMatrix(); //on pop la matrice de projection

	glMatrixMode(GL_MODELVIEW); //on remet la matrice model_view


	//déselectionner tous les noeuds et vider la liste de selection (mode simple)
	if(modeSelection == 0){
		arbre_->deselectionnerTout();
		noeudsSelectiones_.clear();
	}

	//Analyse du tampon pour déterminer les objets selectionnés
	unsigned int min = tampon[1],j = 0;
	for(int i = 1; i < nombre_touche; i++) 
	{
		if(tampon[i*4+1] <= min) 
		{
			min = tampon[i*4+1];
			j = i;
		}

		if(i+1 == nombre_touche)
		{
			if(arbre_->chercher(tampon[j*4+3])->estSelectionnable())
			{
				if(modeJeu_ == true && arbre_->chercher(tampon[j*4+3])->obtenirType() == "balle")
				{
					arbre_->chercher(tampon[j*4+3])->assignerSelection(true);
					noeudsSelectiones_.push_back(arbre_->chercher(tampon[j*4+3]));
				}
				if(modeJeu_ == false)
				{
					arbre_->chercher(tampon[j*4+3])->assignerSelection(true);
					noeudsSelectiones_.push_back(arbre_->chercher(tampon[j*4+3]));
				}
			}
		}
	}		



}


///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::selectionRectangle(int startX, int startY, int endX, int endY)
///
///	Selectionne un objet base sur les paremetres x et y du debut et de fin
/// En coordonnes Virtuelle X,Y,Z
///
/// @param[in] startX : coordonnée X (clôture) de début pointeur de la souris
///	@param[in] startY : coordonnée Y (clôture) de début pointeur de la souris
///	@param[in] endX   : coordonnée X (clôture) de fin pointeur de la souris
///	@param[in] endY   : coordonnée Y (clôture) de fin pointeur de la souris
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void  FacadeModele::selectionRectangle(int startX, int startY, int endX, int endY)
{

	Vecteur3 coordDebut, coordFin;
	coordDebut = pos3Dvirtuelle(startX, startY);
	coordFin = pos3Dvirtuelle(endX, endY);
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	arbre->deselectionnerTout();
	noeudsSelectiones_.clear();

	//Selection rectangle de coin haut droite vers coin bas gauche
	if(coordDebut[0] > coordFin[0])
	{
		Vecteur3 temp;
		temp = coordDebut;
		coordDebut[0] = coordFin[0];
		coordFin[0] = temp[0];
	}

	///		Algorithme recherche dans l'arbre et verifier le hitbox
	for( unsigned int i = 0; i < (arbre->obtenirNombreEnfants()); i++)
	{
		if(arbre->chercher(i) != NULL)
		{
			Vecteur3 positionRelative =  arbre->chercher(i)->obtenirPositionRelative();

			//Notre objet est dans le hitbox?
			if( positionRelative[0] >= coordDebut[0] && 
				positionRelative[0] <= coordFin[0] &&
				positionRelative[1] <= coordDebut[1] &&
				positionRelative[1] >= coordFin[1])
			{

				if(arbre->chercher(i)->estSelectionnable())
				{
					arbre->chercher(i)->assignerSelection(true);
					noeudsSelectiones_.push_back(arbre->chercher(i));
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::rotationSelection(float angle)
///
///	Permet de faire une rotation sur un objet 
/// NOTE: L'objet incremente de 5 degree a chaque appel de cette fonction
///
/// @param[in] angle: angle de rotation.
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void  FacadeModele::rotationSelection(float angle)
{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::list<NoeudAbstrait*>::iterator iter;

	for ( iter=noeudsSelectiones_.begin(); iter != noeudsSelectiones_.end(); ++iter )
	{
		float angleInit = (*iter)->obtenirRot();
		(*iter)->assignerRot(angle); 
		if((*iter)->obtenirType() == "bordure")
		{
			(*iter)->distanceP1P2_ = (*iter)->distanceP1P2_.tourner((utilitaire::DEG_TO_RAD(angle - angleInit)),Vecteur3(0,0,1));
			(*iter)->assignerCoinBordure((*iter)->obtenirCoinBordureMin(),0);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::FacteurSelection(float facteur)
///
///	Assigne un facteur d'agrandissement reçu en paramètre aux noeuds sélectionnés
///
/// @param[in] facteur: facteur d'agrandissement.
///
/// @return Aucune.
/// 
///////////////////////////////////////////////////////////////////////////////
void  FacadeModele::facteurSelection(float facteur)
{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::list<NoeudAbstrait*>::iterator iter;

	for ( iter=noeudsSelectiones_.begin(); iter != noeudsSelectiones_.end(); ++iter )
	{
		if((*iter)->obtenirType() == "bordure")
		{
			(*iter)->distanceP1P2_ *= facteur;
			(*iter)->assignerCoinBordure((*iter)->obtenirPositionRelative(),0);
			float x = (float)abs((*iter)->obtenirCoinBordureMin()[0] - (*iter)->obtenirCoinBordureMax()[0]);
			float y = (float)abs((*iter)->obtenirCoinBordureMin()[1] - (*iter)->obtenirCoinBordureMax()[1]);

			float hyp = sqrtf(x*x+y*y);
			Vecteur3 coinMin, coinMax;
			//modele_->calculerBoiteEnglobante(coinMin, coinMax);
			(*iter)->calculerBoite(coinMin,coinMax);
			float objLength = (float)abs(coinMax[0] - coinMin[0]);
			(*iter)->assignerFacteurAgrandissement(hyp / objLength);
		}
		else
			(*iter)->assignerFacteurAgrandissement(facteur);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::creationObjet(int objet, int sourisX, int sourisY, int souris2X, int souris2Y)
///
///	Permet de creer les objets et les ajouter à l'arbre lorsqu'on est dans le mode d'edition
/// 
/// @param[in] objet   : entier indiquant le type d'objet à créer
/// @param[in] sourisX : coordonnée X de la souris (premier point)
///	@param[in] sourisY : coordonnée Y de la souris (premier point)
///	@param[in] souris2X: coordonnée X de la souris (second point)
///	@param[in] souris2Y: coordonnée Y de la souris (second point)
///
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FacadeModele::creationObjet(int objet, double sourisX, double sourisY, double souris2X, double souris2Y)
{
	//On deselectionne tout
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	arbre->deselectionnerTout();
	noeudsSelectiones_.clear();
	Vecteur3 position;
	bool estCree = false;
	//Vecteur3 position = pos3Dvirtuelle(sourisX,sourisY);
	if(objet == 6 || objet == 5)
		position = Vecteur3(sourisX,sourisY,0);
	else
	{
		vue_->convertirClotureAVirtuelle((int)sourisX,(int)sourisY,position);
	}
	
   
	NoeudAbstrait* noeud;
	//position[2] = 0;
	unsigned int compteurContour = 0, compteurContourBordure1 = 0, compteurContourBordure2 = 0;
	Vecteur3 coinContourMin, coinContourMax;
	Vecteur3 positionXmax(position[0] + 500,position[1],position[2]);
	//Algorithme pour vérifier si l'objet est dans la bordure
	if(objet != 6)
	{
		for(unsigned int i = 0; i < arbre_->obtenirNombreEnfants(); i++)
		{
			if(arbre_->chercher(i)->obtenirType() == "contour")
			{
				
				coinContourMin = arbre_->chercher(i)->obtenirCoinBordureMin();
				coinContourMax = arbre_->chercher(i)->obtenirCoinBordureMax();
				////si contour a droite e l'objet
				//if(position[0] < coinContourMax[0] || position[0] < coinContourMin[0])
				//{
				//	//si contour inversé
				//	if(coinContourMin[1] > coinContourMax[1])
				//	{
				//		double temp = coinContourMax[1];
				//		coinContourMax[1] = coinContourMin[1];
				//		coinContourMin[1] = temp;
				//	}
				//
				//	if(position[1] <= coinContourMax[1] && position[1] >= coinContourMin[1])
				//	{
				//		compteurContour++;
				//	}
				//}
				if(objet != 5)
				{
					if(checkCollision2Segments(position, positionXmax,coinContourMin,coinContourMax) == true)
					{
						compteurContour++;
					}
				}
				else
				{
					Vecteur3 position2(souris2X,souris2Y,0);
					Vecteur3 positionXmax2(position2[0]+500,position2[1],position2[2]);

					if(checkCollision2Segments(position,positionXmax,coinContourMin,coinContourMax) == true)
					{
						compteurContourBordure1++;
					}
					if(checkCollision2Segments(position2,positionXmax2,coinContourMin,coinContourMax) == true)
					{
						compteurContourBordure2++;
					}
						
				}


			}
		}
	}


	if(position[0]<195 && position[0]>-195 && position[1]<195 && position[1]>-195)
	{
		//si nombre de contours a droite de l'objet est impair...
		if((compteurContour % 2 != 0 && objet != 6 ) || (compteurContourBordure1 %2 != 0 && compteurContourBordure2 %2 != 0 && objet == 5) )
		{
			if(objet==0)
			{
				if(isBalle_ == false)		//Creation s'il ny a pas de balle
				{
					noeud = arbre->creerNoeud("balle");
					noeud->assignerPositionRelative(position);
					noeud->assignerPositionInitiale(position);
					noeud->assignerSelection(true);
					arbre->ajouter(noeud);
					estCree = true;
					isBalle_ = true;
				}
				
			}

			if(objet==4)
			{
				noeud = arbre->creerNoeud("bonus");
				noeud->assignerSelection(true);
				noeud->assignerPositionRelative(position);
				noeud->assignerPositionInitiale(position);
				arbre->ajouter(noeud);
				estCree = true;
			}
			if(objet==3)
			{
				noeud = arbre->creerNoeud("sable");
				noeud->assignerSelection(true);
				noeud->assignerPositionRelative(position);
				noeud->assignerPositionInitiale(position);
				arbre->ajouter(noeud);
				estCree = true;

			}
			if(objet==2)
			{
				noeud = arbre->creerNoeud("eau");
				noeud->assignerSelection(true);
				noeud->assignerPositionRelative(position);
				noeud->assignerPositionInitiale(position);
				arbre->ajouter(noeud);
				estCree = true;
			}
			if(objet==1)
			{
				if(isTrou_ == false && calculerCollisionTrouObstacles(position) == false)		//Creation s'il ny a pas de trou
				{
					noeud = arbre->creerNoeud("trou");
					noeud->assignerSelection(true);
					noeud->assignerPositionRelative(position);
					noeud->assignerPositionInitiale(position);
					arbre->ajouter(noeud);
					isTrou_ = true;
					estCree = true;
				}
				
			}


			if(objet==5)
			{
				//Vecteur3 position2 = pos3Dvirtuelle(souris2X,souris2Y);
				Vecteur3 position2(souris2X,souris2Y,0);
				if(position2[0]<195 && position2[0]>-195 && position2[1]<195 && position2[1]>-195)
				{
					noeud = arbre->creerNoeud("bordure");
					noeud->assignerSelection(true);
					noeud->AssignerDonnes(position, position2);
					arbre->ajouter(noeud);
					estCree = true;
				}
				
			}
			if(objet==7)
			{
				bool linkFound = false;
				for(unsigned int i = 0; i < arbre_->obtenirNombreEnfants(); i++)
				{
					if(arbre_->chercher(i)->obtenirType() == "portal" && arbre_->chercher(i)->obtenirPortalLinked() == false)
					{

						noeud = arbre->creerNoeud("portal");
						noeud->assignerPortalType(false);
						noeud->assignerPortalLinked(true);
						noeud->linkPortal(arbre_->chercher(i)->obtenirPositionRelative());
						arbre_->chercher(i)->assignerPortalLinked(true);
						noeud->assignerPositionRelative(position);
						noeud->assignerPositionInitiale(position);
						arbre_->chercher(i)->linkPortal(noeud->obtenirPositionRelative());
						arbre->ajouter(noeud);
						linkFound = true;
						estCree = true;
					}
				}
				if(linkFound == false)
				{
					noeud = arbre->creerNoeud("portal");
					noeud->assignerPositionRelative(position);
					noeud->assignerPositionInitiale(position);
					noeud->assignerPortalType(true);
					noeud->linkPortal(position);
					arbre->ajouter(noeud);
					estCree = true;
				}
				
			}

		}
		if(objet == 6)
		{
			//Vecteur3 position2 = pos3Dvirtuelle(souris2X,souris2Y);
			Vecteur3 position2(souris2X,souris2Y,0);
			bool croisement = false;
			for(unsigned int i = 0; i < arbre_->obtenirNombreEnfants(); i++)
			{
				if(arbre_->chercher(i)->obtenirType() == "contour")
				{

					coinContourMin = arbre_->chercher(i)->obtenirCoinBordureMin();
					coinContourMax = arbre_->chercher(i)->obtenirCoinBordureMax();
					if(checkCollision2Segments(position,position2,coinContourMin,coinContourMax))
					{
						if(!(position2 == coinContourMax))
							croisement = true;
					}
				}
			}
			//vue_->convertirClotureAVirtuelle(souris2X,souris2Y,position2);
			if(position2[0]<195 && position2[0]>-195 && position2[1]<195 && position2[1]>-195 && croisement == false)
			{
				noeud = arbre->creerNoeud("contour");
				noeud->assignerSelection(false);
				noeud->assignerEstSelectionnable(false);
				noeud->AssignerDonnes(position, position2);
				arbre->ajouter(noeud);
				estCree = true;
			}
			
		}
	}
	
	noeudsSelectiones_.push_back(noeud);

	return estCree;
}
///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::deleteSelection()
///
///	Supprime les objets selectionnés.
/// 
///
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::deleteSelection()
{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::list<NoeudAbstrait*>::iterator iter;
	int nbEnfant;
	NoeudAbstrait* parentDeSelection;
	NoeudAbstrait* enfantDeSelection;
	for ( iter=noeudsSelectiones_.begin(); iter != noeudsSelectiones_.end(); ++iter )
	{
		if(*iter!=NULL)
		{
			parentDeSelection = (*iter)->obtenirParent();
			if(nbEnfant = (*iter)->obtenirNombreEnfants() > 0)				//Placer nombre d'enfant dans nbEnfant
			{

				(*iter)->effacerSelection();								//On commence par effacer les enfants selectionnes
				for(int i = 0; i<nbEnfant; i++)
				{
					if((*iter)->obtenirType() == "balle")
						isBalle_ = false;
					if((*iter)->obtenirType() == "trou")
						isTrou_ = false;
					
					enfantDeSelection =((*iter)->chercher(i));					//On assigne le parent du neoud a delete comme parent des 
					parentDeSelection->ajouter(enfantDeSelection);			//Enfant du noeud a delete
					enfantDeSelection->assignerParent(parentDeSelection);	
				}
				parentDeSelection->effacer(*iter);
			}
			else
			{
				if((*iter)->obtenirType() == "portal")
					{

						NoeudAbstrait* root = (*iter);
						do
						{
							root = root->obtenirParent();
						}while(root->obtenirType() != "racine");

						Vecteur3 postemp = (*iter)->obtenirPosLinkingPortal();

						for(unsigned int i = 0; i<root->obtenirNombreEnfants(); i++)
						{
							if(root->chercher(i)->obtenirPositionRelative() == postemp)
							{
								if(root->chercher(i)!= (*iter) &&root->chercher(i)->estSelectionne() == false)
								{
									root->chercher(i)->obtenirParent()->effacer(root->chercher(i));
								}//noeudsSelectiones_.push_back(root->chercher(i));
							}
							

						}
					}
				if((*iter)->obtenirType() == "balle")
					isBalle_ = false;
				if((*iter)->obtenirType() == "trou")
					isTrou_ = false;
				parentDeSelection->effacer(*iter);
			}
		}
	}

	noeudsSelectiones_.clear();
}

///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::deplacementSelection(int startX, int startY, int currentX, int currentY)
///
///	Deplace les objets selectionnes en se servant le la position actuelle de
/// la souris
///
/// @param[in] startX     : coordonnée X (clôture) de début pointeur de la souris
///	@param[in] startY     : coordonnée Y (clôture) de début pointeur de la souris
///	@param[in] currentX   : coordonnée X (clôture) de fin pointeur de la souris
///	@param[in] currentY   : coordonnée Y (clôture) de fin pointeur de la souris
///
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacementSelection(int startX, int startY, int currentX, int currentY)
{

	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::list<NoeudAbstrait*>::iterator iter;
	Vecteur3 posStart, posCurrent, posRelative, posDepart;
	posStart =  pos3Dvirtuelle(startX, startY);
	vue_->convertirClotureAVirtuelle(currentX,currentY,posCurrent);
	posStart[2] = 0.0;


	//Premierement on parcour les objets selectionnes pour voir si le mouse a click un des objets

	if(noeudsSelectiones_.size()> 0)
	{
		Vecteur3 min, max, posRelativeSelectionne;
		std::list<NoeudAbstrait*>::iterator iter2;
		float facteur;
		//Algorithme recherche dans l'arbre et verifier le hitbox
		for( iter2 = noeudsSelectiones_.begin(); iter2 != noeudsSelectiones_.end(); iter2++)
		{
			if((*iter2) != NULL)
			{

				posRelativeSelectionne = (*iter2)->obtenirPositionRelative();
				(*iter2)->calculerBoite(min, max);
				facteur = (*iter2)->obtenirFacteurAgrandissment();
				min[0] = min[0]*facteur+posRelativeSelectionne[0];
				max[0] = max[0]*facteur+posRelativeSelectionne[0];
				min[1] = min[1]*facteur+posRelativeSelectionne[1];
				max[1] = max[1]*facteur+posRelativeSelectionne[1];

				if( posCurrent[0] >= min[0] && 
					posCurrent[0] <= max[0] &&
					posCurrent[1] >= min[1] &&
					posCurrent[1] <= max[1])
				{
					//l'objet selectionne surlequel on a clické pour effectuer le déplacement devient le premier (on évite le "snap")
					noeudsSelectiones_.splice(noeudsSelectiones_.begin(),noeudsSelectiones_,iter2);
					break;
				}
			}
		}
		//maintenant on assigne les positions
		iter = noeudsSelectiones_.begin();
		posRelative = (*iter)->obtenirPositionRelative();
		Vecteur3 posRel2;

		if((*iter)->horsContour() == false)
		{
			(*iter)->assignerPositionRelative(posCurrent);
			if((*iter)->obtenirType() == "bordure")
			{
				(*iter)->assignerCoinBordure(posCurrent,0);
			}

			if((*iter)->obtenirType() == "portal")
			{
				for(unsigned int i = 0; i < arbre_->obtenirNombreEnfants(); i++)
				{			
					if( arbre_->chercher(i)->obtenirType() == "portal" && arbre_->chercher(i)->obtenirPosLinkingPortal() == posRelative)
					{
						arbre_->chercher(i)->linkPortal(posCurrent);
					}
				}
			}

			iter++;
		}
		else
		{
			(*iter)->assignerPositionRelative((*iter)->obtenirPositionInitiale());
			if((*iter)->obtenirType() == "bordure")
			{
				(*iter)->assignerCoinBordure((*iter)->obtenirPositionInitiale(),0);
			}
			(*iter)->assignerSelection(false);
			iter = noeudsSelectiones_.erase(iter);
		}

		for ( iter; iter != noeudsSelectiones_.end() && noeudsSelectiones_.size() > 1; ++iter )
		{
			if(*iter!=NULL) 
			{
				Vecteur3 postemp = (*iter)->obtenirPositionRelative();
				if((*iter)->horsContour() == false)
				{

					posRel2 = (*iter)->obtenirPositionRelative();
					posRel2[0] = -(posRelative[0] - posRel2[0]) + posCurrent[0];
					posRel2[1] = -(posRelative[1] - posRel2[1]) + posCurrent[1];
					posRel2[2] = 0;
					(*iter)->assignerPositionRelative(posRel2);
					if((*iter)->obtenirType() == "bordure")
					{
						(*iter)->assignerCoinBordure(posRel2,0);
					}
					if((*iter)->obtenirType() == "portal")
					{
						for(unsigned int i = 0; i < arbre_->obtenirNombreEnfants(); i++)
						{			
							if( arbre_->chercher(i)->obtenirType() == "portal" && arbre_->chercher(i)->obtenirPosLinkingPortal() == postemp)
							{
								arbre_->chercher(i)->linkPortal((*iter)->obtenirPositionRelative());
							}
						}
					}

				}
				else
				{
					(*iter)->assignerPositionRelative((*iter)->obtenirPositionInitiale());
					if((*iter)->obtenirType() == "bordure")
					{
						(*iter)->assignerCoinBordure((*iter)->obtenirPositionInitiale(),0);
					}
					(*iter)->assignerSelection(false);					
					iter = noeudsSelectiones_.erase(iter);

					if(noeudsSelectiones_.size() > 1)
						iter--;
					else
						break;
				}

			}

		}
	}

}

///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::viderArbre();
///
///	vide l'arbre de ses noeuds
/// 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::viderArbre()
{
	//ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	//arbre->initialiser();
	//noeudsSelectiones_.empty();
	//isBalle_ = false;
	//isTrou_ = false;
}

///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::duplicationSelection();
///
///	Copie les elements selectionnes
/// 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::duplicationSelection()
{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::list<NoeudAbstrait*>::iterator iter;
	Vecteur3 pos;
	std::string objet;

	for ( iter=noeudsSelectiones_.begin(); iter != noeudsSelectiones_.end(); ++iter )
	{
		if(*iter!=NULL)
		{
			NoeudAbstrait* noeud;
			objet = (*iter)->obtenirType();
			noeud = arbre->creerNoeud(objet);
			arbre->ajouter(noeud);
			//On assigne les memes valeurs que le noeuds que nous dupliquons
			pos = (*iter)->obtenirPositionRelative();
			//On deplace la position d'un peu pour voir que nous avons dupliquer
			pos[0] += 10;
			pos[1] += 10;

			noeud->assignerPositionRelative(pos);
			noeud->assignerParent((*iter)->obtenirParent());
			noeud->assignerFacteurAgrandissement((*iter)->obtenirFacteurAgrandissment());
			noeud->assignerRot((*iter)->obtenirRot());
		}
	}


	/*
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::vector<NoeudAbstrait*>::iterator iter;
	NoeudAbstrait* NoeudDupliquer;
	NoeudAbstrait* parentDeSelection;
	Vecteur3 pos;
	for ( iter=noeudsSelectiones_.begin(); iter != noeudsSelectiones_.end(); ++iter )
	{
	if(*iter!=NULL)
	{
	parentDeSelection = (*iter)->obtenirParent();
	//NoeudAbstrait* bla = (*iter);
	NoeudAbstrait* bla = new NoeudAbstrait(**iter);

	//pos = bla->obtenirPositionRelative();
	pos = (0, 0, 0);
	bla->assignerPositionRelative(pos);
	bla->assignerParent(parentDeSelection);
	bla->assignerSelection(false);
	//NoeudDupliquer = arbre->creerNoeud((*iter)->obtenirType());
	//Noeuddupliquer((*iter));
	arbre->ajouter(bla);

	}
	}*/
}


///////////////////////////////////////////////////////////////////////////////
/// @}fn void FacadeModele::manipulerObjet(int X, int Y, int Z, int rotation, int facteur)
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
void  FacadeModele::manipulerObjet(int X, int Y, int Z, int rotation, int facteur)
{
	std::list<NoeudAbstrait*>::iterator iter;
	iter = iter=noeudsSelectiones_.begin();
	Vecteur3 pos;
	pos[0] = X;
	pos[1] = Y;
	pos[2] = Z;
	(*iter)->assignerPositionRelative(pos);
	(*iter)->assignerFacteurAgrandissement((float)facteur);
	(*iter)->assignerRot((float)rotation);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerXml(std::string nomfichier)
///
/// Cette methode permet d'enregistrer une carte dans un fichier .xml
///
///	@param[in]	nomfichier : nom du fichier xml
///				
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::enregistrerXml(std::string nomfichier, int Nbpar ) const
{
	if(isBalle_ == true && isTrou_ == true/*arbre_->chercher("balle") != 0  && arbre_->chercher("trou") != 0 */)
	{
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		//noeudsSelectiones_.clear();
		arbre->deselectionnerTout();
		VisiteurXML* visiteur=VisiteurXML::obtenirInstance();
		visiteur->assignerPar(Nbpar);
		visiteur->ecrireFichier(arbre_,nomfichier);
		return true;
	}
	return false;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerXml(std::string nomfichier)
///
/// Cette methode permet de charger une carte sauvegardée dans un fichier .xml
///
///	@param[in]	nomfichier : nom du fichier xml
///				
/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerXml(std::string nomfichier)
{
	VisiteurXML* visiteur=VisiteurXML::obtenirInstance();
	visiteur->lireFichierXML(arbre_,nomfichier);
	unsigned int nbBalle = 0, nbTrou = 0;
	for( unsigned int i = 0; i < arbre_->obtenirNombreEnfants(); i++)
	{
		if(arbre_->chercher(i)->obtenirType() == "balle")
		{
			nbBalle++;
		}
		if(arbre_->chercher(i)->obtenirType() == "trou")
		{
			nbTrou++;
		}
	}
	if(nbBalle == 1)
	{
		isBalle_ = true;
	}
	if(nbTrou == 1)
	{
		isTrou_ = true;
	}
	//afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::clickBalle(int x, int y)
///
/// Cette methode permet de verifier si la balle a ete cliquer
///
///	@param[in]	x : position x du click
///	@param[in]	y : position y du click		
/// @return bool si l'utilisateur a clicker sur la balle
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::clickBalle(int x, int y)
{


	selectionClick(x,y,0);
	if(noeudsSelectiones_.size() == 1)
	{
		std::list<NoeudAbstrait*>::iterator iter;
		iter = noeudsSelectiones_.begin();
		if((*iter)->obtenirType() == "balle")
		{
			(*iter)->assignerSelection(false);
			Vecteur3 vitese = (*iter)->obtenirVitesse();
			if(vitese[0] == 0 && vitese[1] == 0)
			{
				ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
				NoeudAbstrait* noeud;
				noeud = arbre->chercher("baton");
				arbre->effacer(noeud);
				return true;
			}
		}

	}
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerFleche()
///
/// Cette methode ajoute une fleche a l'arbre de rendu

/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void  FacadeModele::creerFleche()
{
	angle_ =0;
	force_ =0;
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	NoeudAbstrait* noeud;
	noeud = arbre->creerNoeud("fleche");
	fleche_ = noeud;
	arbre->ajouter(noeud);
	noeud->assignerPositionRelative(arbre_->chercher("balle")->obtenirPositionRelative());
	noeud = arbre->creerNoeud("baton");
	arbre->ajouter(noeud);
	noeud->assignerPositionRelative(arbre_->chercher("balle")->obtenirPositionRelative());
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::effacerFleche()
///
/// Cette methode efface une fleche a l'arbre de rendu

/// @return aucune.
///
////////////////////////////////////////////////////////////////////////
void  FacadeModele::effacerFleche()
{	
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	float force = 4000*fleche_->obtenirFacteurAgrandissment();
	float vitesse = force / 5.0f * 0.02f ; //v = 0 + a*t  et a = F/m : 5 = masse, 0.02 = dt
	float angle = 180+fleche_->obtenirRot();
	
	if(fleche_->obtenirFacteurAgrandissment() != 1)
		arbre_->chercher("balle")->initialiserVitesse(angle, vitesse);

	
	sound_->jouerBaton();
	arbre_->effacer(fleche_);
	fleche_ = NULL;
	NoeudAbstrait* noeud;
	noeud = arbre->chercher("baton");
	noeud->assignerBatonPret();
	fleche_ = NULL;
	if(obtenirModeReplay() == false)
		frappes_++;	
	
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierFleche(int x, int y)
///
/// Cette methode permet de mettre les bons parametres a la fleche
///
///	@param[in]	x : position x du click
///	@param[in]	y : position y du click		
/// @return void
///
////////////////////////////////////////////////////////////////////////
void  FacadeModele::modifierFleche(int x, int y)
{
	
	if(fleche_ != NULL)
	{
		Vecteur3 pos1 = fleche_->obtenirPositionRelative();
		Vecteur3 pos2;
		vue_->convertirClotureAVirtuelle(x,y,pos2);
		fleche_->AssignerDonnes(pos1, pos2);
		arbre_->chercher("baton")->assignerRot(fleche_->obtenirRot());
		arbre_->chercher("baton")->assignerFacteurAgrandissement(fleche_->obtenirFacteurAgrandissment());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierFlecheTouche(int x)
///
/// Cette methode controle les parametres de la fleche avec les touches du clavier
///
///	@param[in]	x : désigne le bouton pesé
///
/// @return void
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::modifierFlecheTouche(int x)
{
	if(arbre_->chercher("balle")->obtenirVitesse()[0] == 0 && arbre_->chercher("balle")->obtenirVitesse()[1] == 0)
	{
		if(flecheKeyboard_ == false)
		{

			angle_ =0;
			force_ =0;
			ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
			NoeudAbstrait* noeud;
			noeud = arbre->chercher("baton");
			arbre->effacer(noeud);
			noeud = arbre->creerNoeud("fleche");
			fleche_ = noeud;
			arbre->ajouter(noeud);
			noeud->assignerPositionRelative(arbre_->chercher("balle")->obtenirPositionRelative());
			noeud = arbre->creerNoeud("baton");
			arbre->ajouter(noeud);
			noeud->assignerPositionRelative(arbre_->chercher("balle")->obtenirPositionRelative());
			flecheKeyboard_ = true;

	}
	if(x == 0 )		//Case release
	{
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		arbre_->effacer(fleche_);
		fleche_ = NULL;
		float force = 4000*force_;
		float vitesse = force / 5.0f * 0.02f ; //v = 0 + a*t  et a = F/m : 5 = masse, 0.02 = dt
		float angle = 180+angle_;
		}
		if(x == 0 )		//Case release
		{
			ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
			arbre_->effacer(fleche_);
			fleche_ = NULL;
			float force = 4000*force_;
			float vitesse = force / 5.0f * 0.02f ; //v = 0 + a*t  et a = F/m : 5 = masse, 0.02 = dt
			float angle = 180+angle_;

			if(force_ != 0)
				arbre_->chercher("balle")->initialiserVitesse(angle, vitesse);

			NoeudAbstrait* noeud;
			noeud = arbre->chercher("baton");
			noeud->assignerBatonPret();
			flecheKeyboard_ = false;
			frappes_++;

		}
		if(x == 1)	    //Case Incementer angle
		{

			angle_-=5;
			fleche_->assignerRot(angle_);
			arbre_->chercher("baton")->assignerRot(angle_);
		}
		if(x == 2)		//Case Decrementer angle
		{
			angle_+=5;
			fleche_->assignerRot(angle_);
			arbre_->chercher("baton")->assignerRot(angle_);
		}
		if(x == 3)		//Case incrementer force
		{
			force_+=0.5;
			if(force_>10)
			{
				force_ = 10;
			}
			fleche_->assignerFacteurAgrandissement(force_);
			arbre_->chercher("baton")->assignerFacteurAgrandissement(force_);
		}
		if(x == 4)		//Case decrementer force
		{
			force_-=0.5;
			if(force_<0)
			{
				force_ = 0;
			}
			fleche_->assignerFacteurAgrandissement(force_);
			arbre_->chercher("baton")->assignerFacteurAgrandissement(force_);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::verifierVictoire()
///
/// Cette methode permet de vérifier la victoire du joueur
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::verifierVictoire()
{
	if(modeJeu_ == 1)
	{
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		if(arbre_->obtenirType() == "racine")
		{
			NoeudAbstrait* noeud = arbre_->chercher("balle");
			if(noeud != nullptr)
			{
			bool victoire = noeud->verifierEstDansTrou();
			noeud->setEstDansTrou(false);
			if(victoire==true)
			{
				GestionJoueur* gestionnaire=GestionJoueur::obtenirInstance();
				gestionnaire->modifierFicheJoueur(obtenirJoueurCourant(),obtenirMapCourante(),obtenirNombreCoups());
			}
			return victoire;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void modifierMode(bool modeJeu)
///
/// Cette methode permet de modifier le mode du jeu
///
///	@param[in]	modeJeu : booléen indiquant le mode du jeu
/// @return void
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::modifierMode(bool modeJeu)
{
	modeJeu_ = modeJeu;
	if(modeJeu_ == true)
	{
		alphaBlend_ = 1.0f;
		//arbre_->chercher("balle")->lacher();
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::changerVue()
///
/// Cette fonction change la vue
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changerVue(int vue)
{
	Vecteur3 position;
	if(modeJeu_ && arbre_->chercher("balle") != nullptr)
		position = arbre_->chercher("balle")->obtenirPositionRelative();

	switch(vue)
	{
	case 1:
		if(vue_ != vueOrtho_ )
		{
			vueLibre_->obtenirCamera().assignerPosition(vue_->obtenirCamera().obtenirPosition());
			if(vue_ != vueOrbite_)
				vueLibre_->obtenirCamera().assignerPointVise(vue_->obtenirCamera().obtenirPointVise());
		}
		vue_ = vueLibre_;
		typeVue_ = "Vue : Libre";
		break;
	case 2:
		vueOrbite_->obtenirCamera().assignerPosition(vue_->obtenirCamera().obtenirPosition());
		vueOrbite_->obtenirCamera().assignerPointVise(position);

		vue_ = vueOrbite_;
		typeVue_ = "Vue : Orbite";
		break;
	case 3:
		vue_ = vueCiel_;
		typeVue_ = "Vue : Ciel";
		break;
	case 4:
		vueOrtho_ = new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 200), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, 500, 0, 500,
		1, 1000, 1, 10000, 1.25,
		-100, 100, -100, 100
		);
		vue_ = vueOrtho_;
		typeVue_ = "Vue : Ortho";
		break;
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool checkCollision2Segments(Vecteur3 segment1Point1, Vecteur3 segment1Point2,Vecteur3 segment2Point1, Vecteur3 segment2Point2)
///
/// Cette methode permet de detecter une collision entre deux segments
///
///	@param[in]	segments : booléen indiquant si la collision existe
/// @return bool.
///
////////////////////////////////////////////////////////////////////////

bool FacadeModele::checkCollision2Segments(const Vecteur3& segment1Point1, const Vecteur3& segment1Point2,const Vecteur3& segment2Point1, const Vecteur3& segment2Point2)
{
	double ud, ua, ub;
	ua = 0;

	ud = (segment2Point2[1] - segment2Point1[1]) * (segment1Point2[0] - segment1Point1[0]) - (segment2Point2[0] - segment2Point1[0]) * (segment1Point2[1] - segment1Point1[1]);
	if(ud != 0) 
	{
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
/// @fn HDC FacadeModele::obtenirContexte()
///
/// Cette methode permet de retourner le handle vers le device context
///
///
/// @return HDC.
///
////////////////////////////////////////////////////////////////////////

HDC FacadeModele::obtenirContexte()
{
	return hDC_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLdouble obtenirDistanceBalleTrou() const
///
/// Cette methode permet de retourner la distance entre la balle et le trou
///
///
/// @return GLdouble distance.
///
////////////////////////////////////////////////////////////////////////

GLdouble FacadeModele::obtenirDistanceBalleTrou() const
{
	GLdouble distance = 0;
	Vecteur3 posTrou(0,0,0), posBalle(0,0,0), vecteurDistance(0,0,0);

	unsigned int nbEnfant = arbre_->obtenirNombreEnfants();

	for( unsigned int i = 0; i < nbEnfant; i++)
	{
		if(arbre_->chercher(i)->obtenirType() == "balle")
		{
			posBalle = arbre_->chercher(i)->obtenirPositionRelative();
		}
		if(arbre_->chercher(i)->obtenirType() == "trou")
		{
			posTrou = arbre_->chercher(i)->obtenirPositionRelative();
		}
	}

	vecteurDistance[0] = posTrou[0] - posBalle[0];
	vecteurDistance[1] = posTrou[1] - posBalle[1];
	vecteurDistance[2] = 0;

	distance = vecteurDistance.norme();

	return distance;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLdouble calculerCollisionTrouObstacles()
///
/// Cette methode permet de calculer la collision du trou avec l'eau ou le sable
///
///
/// @return true si collision, false sinon.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::calculerCollisionTrouObstacles(Vecteur3 positionTrou)
{

	unsigned int compteurObstacle = 0;
	Vecteur3  min, max, posRelativeSable;
	Vecteur3 positionXmax(positionTrou[0] + 500,positionTrou[1],positionTrou[2]);

	for(unsigned int i = 0; i<arbre_->obtenirNombreEnfants(); i++)
	{
		if(arbre_->chercher(i)->obtenirType() == "sable" || arbre_->chercher(i)->obtenirType() == "eau" )
		{
			arbre_->chercher(i)->calculerBoite(min, max);
			posRelativeSable = arbre_->chercher(i)->obtenirPositionRelative();
			//coin haut gauche
			Vecteur3 hautGauche(posRelativeSable[0] - utilitaire::ABS( (float)min[0]),posRelativeSable[1] + utilitaire::ABS( (float)max[1]),0);
			//coin bas droit
			Vecteur3 basDroit(posRelativeSable[0] + utilitaire::ABS( (float)max[0]),posRelativeSable[1] - utilitaire::ABS( (float)(min[1])),0);
			//coin bas gauche
			Vecteur3 basGauche(posRelativeSable[0] - utilitaire::ABS( (float)min[0]),posRelativeSable[1] - utilitaire::ABS( (float)min[1]),0);
			//coin haut droit
			Vecteur3 hautDroit(posRelativeSable[0] + utilitaire::ABS( (float)max[0]),posRelativeSable[1] + utilitaire::ABS( (float)max[1]),0);

			/*			if(aidecollision::calculerCollisionSegment(basGauche,hautGauche,positionTrou,6,true).type!= 0
			||aidecollision::calculerCollisionSegment(basGauche,basDroit,positionTrou,6,true).type!= 0
			||aidecollision::calculerCollisionSegment(hautGauche,hautDroit,positionTrou,6,true).type!= 0
			||aidecollision::calculerCollisionSegment(hautDroit,basDroit,positionTrou,6,true).type!= 0)
			{
			return true;
			}*/	
			if(checkCollision2Segments(positionTrou, positionXmax,hautGauche,hautDroit) == true)
			{
				compteurObstacle++;
			}
			if(checkCollision2Segments(positionTrou, positionXmax,hautGauche,basGauche) == true)
			{
				compteurObstacle++;
			}
			if(checkCollision2Segments(positionTrou, positionXmax,basGauche,basDroit) == true)
			{
				compteurObstacle++;
			}
			if(checkCollision2Segments(positionTrou, positionXmax,basDroit,hautDroit) == true)
			{
				compteurObstacle++;
			}

			if(compteurObstacle % 2 != 0)
				return true;
			else
				compteurObstacle = 0;
		}
		else if(arbre_->chercher(i)->obtenirType() == "bordure" || arbre_->chercher(i)->obtenirType() == "contour")
		{

			double rotationBordure;
			Vecteur3 posRelativeBordure,posRelativeTrou,posRelativeBonus,posRelativeEau,coinBordureMin,coinBordureMax,basGauche,hautGauche,basDroit,hautDroit;
			posRelativeBordure = arbre_->chercher(i)->obtenirPositionRelative();
			rotationBordure = (double) arbre_->chercher(i)->obtenirRot();
			arbre_->chercher(i)->calculerCoinsBordure(coinBordureMin,coinBordureMax);


			if( 0.0 <= rotationBordure && rotationBordure <= 90.0)
			{
				basGauche[0] = coinBordureMin[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[1] = coinBordureMin[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));			
				basDroit[0] = coinBordureMax[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				basDroit[1] = coinBordureMax[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[0] = coinBordureMin[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[1] = coinBordureMin[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[0] = coinBordureMax[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[1] = coinBordureMax[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure));
			}

			if(90.0 < rotationBordure && rotationBordure <= 180.0)
			{
				hautGauche[0] = coinBordureMin[0] - 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[1] = coinBordureMin[1] - 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));			
				hautDroit[0]  = coinBordureMax[0] - 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[1]  = coinBordureMax[1] - 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[0]  = coinBordureMin[0] + 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[1]  = coinBordureMin[1] + 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));			
				basDroit[0]   = coinBordureMax[0] + 2.5*sin(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));
				basDroit[1]   = coinBordureMax[1] + 2.5*cos(utilitaire::PI - utilitaire::DEG_TO_RAD(rotationBordure));

			}

			if(-180 < rotationBordure && rotationBordure <= -90)
			{
				hautGauche[0] = coinBordureMin[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				hautGauche[1] = coinBordureMin[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);			
				hautDroit[0]  = coinBordureMax[0] + 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				hautDroit[1]  = coinBordureMax[1] - 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				basGauche[0]  = coinBordureMin[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				basGauche[1]  = coinBordureMin[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);			
				basDroit[0]   = coinBordureMax[0] - 2.5*sin(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);
				basDroit[1]   = coinBordureMax[1] + 2.5*cos(utilitaire::DEG_TO_RAD(rotationBordure) + utilitaire::PI);

			}

			if(-90 < rotationBordure && rotationBordure < 0)
			{
				basGauche[0] = coinBordureMin[0] - 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				basGauche[1] = coinBordureMin[1] - 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));			
				basDroit[0] = coinBordureMax[0] - 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				basDroit[1] = coinBordureMax[1] - 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[0] = coinBordureMin[0] + 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautGauche[1] = coinBordureMin[1] + 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[0] = coinBordureMax[0] + 2.5*sin(-utilitaire::DEG_TO_RAD(rotationBordure));
				hautDroit[1] = coinBordureMax[1] + 2.5*cos(-utilitaire::DEG_TO_RAD(rotationBordure));
			}
			 
			if(aidecollision::calculerCollisionSegment(basGauche,basDroit,positionTrou,6,true).type != 0)
			{					
				return true;
			}
			 
			if(aidecollision::calculerCollisionSegment(hautGauche,hautDroit,positionTrou,6,true).type!= 0)
			{					
				return true;
			}
			
			if(aidecollision::calculerCollisionSegment(basGauche,hautGauche,positionTrou,6,true).type != 0)
			{					
				return true;
			}
			
			if(aidecollision::calculerCollisionSegment(basDroit,hautDroit,positionTrou,6,true).type != 0)
			{					
				return true;
			}
		}

	}
	return false;
}




void FacadeModele::skybox()
{
	skybox_ =  new utilitaire::BoiteEnvironnement("media/Xpos.bmp","media/Xneg.bmp","media/Ypos.bmp","media/Yneg.bmp","media/Zpos.bmp","media/Zneg.bmp");
	//utilitaire::BoiteEnvironnement::afficher(temp, 100);
	//utilitaire::BoiteEnvironnement::afficher(temp, patate);
	//test.afficher(temp, patate);
}

int FacadeModele::getTypeVue()
{
	if (vue_ == vueLibre_)
		return 1;	
	if (vue_ == vueOrbite_)
		return 2;
	if (vue_ == vueCiel_)
		return 3;
	if (vue_ == vueOrtho_)
		return 4;

	//defaut
	return 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLuint  FacadeModele::obtenirNombreCoups() const
///
/// Cette methode permet de retourner le nombre de coups
///
///
/// @return GLdouble frappes.
///
////////////////////////////////////////////////////////////////////////

GLuint FacadeModele::obtenirNombreCoups() const
{
	return frappes_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn char * FacadeModele::textFileRead( const char *fn )
///
///
///
/// @return char* contenu texte.
///
////////////////////////////////////////////////////////////////////////
char * FacadeModele::textFileRead( const char *fn )
{
   char *content = NULL;

   if ( fn != NULL )
   {
      FILE *fp;
	  fopen_s(&fp,fn,"r");
      if ( fp != NULL )
      {
         fseek( fp, 0, SEEK_END );
         int count = ftell(fp);
         rewind(fp);

         if ( count > 0 )
         {
            content = (char *) malloc(sizeof(char) * (count+1) );
            count = (int)fread( content, sizeof(char), count, fp );
            content[count] = '\0';
         }
         fclose(fp);
      }
   }
   return content;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  FacadeModele::initialiserNuanceurs() const
///
/// Cette methode permet d'initialiser les shaders.
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserNuanceurs()
{
   // déclaration des chaînes qui devront recevoir le code des nuanceurs
   // lire les fichiers de nuanceurs de sommets et de fragments
   const char *ns = textFileRead( "nuanceurs/nuanceurSommetsMULT.glsl" );
   const char *nf = textFileRead( "nuanceurs/nuanceurFragmentsMULT.glsl" );

   // créer le programme
   progPhong_ = glCreateProgram();
   // créer les nuanceurs de sommets et de fragments
   GLuint nuanceurSommets = glCreateShader( GL_VERTEX_SHADER );
   GLuint nuanceurFragments = glCreateShader( GL_FRAGMENT_SHADER );

   // associer le fichier de sommets au nuanceur de sommets
   glShaderSource( nuanceurSommets, 1, &ns, NULL );
   glCompileShader( nuanceurSommets );
   glAttachShader( progPhong_, nuanceurSommets );


   // associer le fichier de fragments au nuanceur de fragments
   glShaderSource( nuanceurFragments, 1, &nf, NULL );
   glCompileShader( nuanceurFragments );
   glAttachShader( progPhong_, nuanceurFragments );



   // linker le programme
   glLinkProgram( progPhong_ );
}

void FacadeModele::setPar(int par)
{
	arbre_->chercher("terrain")->assignerPar(par);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerNomJoueur(const char* nomJoueur)
///
/// Cette methode permet d'assigner le nom du joueur
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::assignerNomJoueur(std::string nomJoueur)
{
	nomJoueur_ = nomJoueur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerNomMap(std::string nomMap)
///
/// Cette methode permet d'assigner le nom du joueur
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::assignerNomMap(std::string nomMap)
{
	nomMap_ = nomMap;
}

bool FacadeModele::getMode()
{
	return modeJeu_;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
