///////////////////////////////////////////////////////////////////////////////
/// @file ChargementModele.cpp
/// @author Jean-Luc et Aiman
/// @date 2010-12-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
//Le code des textures provient de NEHE

#include "HUD.h"
#include "NoeudAbstrait.h"
#include "ArbreRenduINF2990.h"
#include "Sound.h"
#include <time.h>
#include "stdarg.h"
#include "Aidecollision.h"
#include "Vecteur.h"
#include "Projection.h"


HUD* HUD::singleton_ = NULL;

////////////////////////////////////////////////////////////////////////
///
/// @fn void HUD::libererInstance()
///
/// instance de HUD
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void HUD::libererInstance()
{
	delete singleton_;
	singleton_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn HUD::HUD()
///
/// Constructeur par defaut, charge les images
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
HUD::HUD()
{
	glEnable(GL_TEXTURE_2D);	
	glEnable(GL_DEPTH_TEST);	
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	aidegl::glLoadTexture("media/radio.png",radio);
	
	base = glGenLists(96);
	buildFont(-15);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn HUD::~HUD()
///
/// Destructeur
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
HUD::~HUD()
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLvoid HUD::glPrint(const char *fmt,...)
///
/// afficher le texte dans le HUD
///
/// @param[in] fmt 
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
GLvoid HUD::glPrint(const char *fmt,...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)
	{
		return;		
	}

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GLvoid HUD::buildFont(int tailleFont)
///
/// Font de l'ecriture
///
/// @param[in] tailleFont : la taille du texte du font
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
GLvoid HUD::buildFont(int tailleFont)
{
	HDC			hDC=FacadeModele::obtenirInstance()->obtenirContexte();
	HFONT font;
	HFONT oldfont;
	font = CreateFont(tailleFont,0,0,0,1000,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,FF_DONTCARE | DEFAULT_PITCH,(LPCTSTR)"Courier New");
	oldfont = (HFONT)SelectObject(hDC, font);
	wglUseFontBitmaps(hDC, 32, 96, base);
	SelectObject(hDC, oldfont);
	DeleteObject(font);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void HUD::dessinerRadio()
///
/// Creer la zone de radio et lui appliquer la texture
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void HUD::dessinerRadio()
{
	// On active les textures.
    glEnable(GL_TEXTURE_2D);

	//radio
	glBindTexture(GL_TEXTURE_2D, radio);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex2f( 0.0f, 0.88f);
	glTexCoord2f(1.0, 0.0);	glVertex2f( 0.26f, 0.88f);
	glTexCoord2f(1.0, 1.0);	glVertex2f( 0.26f, 1.0f);
	glTexCoord2f(0.0, 1.0);	glVertex2f( 0.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void HUD::dessinerHUD(int frappes, double distance)
///
/// Dessine les Head-Up-Display
/// @param[in]  frappes : nombre de coups joués
/// @param[in]  distance: distance entre la balle et le trou
/// @param[in]  typeVue : type de la vue
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void HUD::dessinerHUD(int frappes, double distance, char * typeVue, std::string nomJoueur,std::string nomMap)
{
	glPushAttrib(GL_CURRENT_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable( GL_CULL_FACE );
	glDisable(GL_LIGHTING); 
	dessinerRadio();

	//HUD de la musique courante
	glColor4f(0.0f,0.7f,1.0f,1.0f);
	glRasterPos2d(0.07,0.925);
	glPrint(Sound::obtenirInstance()->musiqueCourante_.c_str()); // rajouter le fichier de la musique en cours
	
	//HUD du nombre de coups et de la distance entre la balle et le trou
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glRasterPos2d(0.73,0.02);
	glPrint("COUPS : %i DISTANCE : %4.2f",frappes,distance);

	//HUD du nom de joueur
	glColor4f(1.0f,0.8f,0.2f,1.0f);
	glRasterPos2d(0.01,0.06);
	glPrint(nomJoueur.c_str());

	//HUD du nom de la map
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glRasterPos2d(0.01,0.02);
	glPrint(nomMap.c_str());

	//HUD du type de la vue
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glRasterPos2d(0.82,0.95);
	glPrint(typeVue);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable( GL_CULL_FACE );
	glEnable(GL_LIGHTING);

	glMatrixMode( GL_PROJECTION );
	glPopMatrix(); 
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glPopAttrib();
}




