///////////////////////////////////////////////////////////////////////////////
/// @file NoeudEau.cpp
/// @author Julien Lapointe
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudEau.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"
#include "AideGl.h"
#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define GL_CLAMP_TO_EDGE 0x812F
Modele3D* NoeudEau::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudEau::NoeudEau(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudEau::NoeudEau(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
	factEchelle_ = 1;
   coefFriction_ = 1;

   // Création d'une liste d'affichage pour toutes les instances du noeud Eau
    if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_EAU) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/eau.obj");
		modele_->assignerFacteurAgrandissement(factEchelle_);

		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_EAU);
		
		modele_->dessiner();		
		glEndList(); 
	}
	//liste_ = glGenLists(1);

	
	//aidegl::glLoadTexture("media/Frame_01.png",frame_[0]);
	//aidegl::glLoadTexture("media/Frame_02.png",frame_[1]);
	//aidegl::glLoadTexture("media/Frame_03.png",frame_[2]);
	//aidegl::glLoadTexture("media/Frame_04.png",frame_[3]);
	//aidegl::glLoadTexture("media/Frame_05.png",frame_[4]);
	//aidegl::glLoadTexture("media/Frame_06.png",frame_[5]);
	//aidegl::glLoadTexture("media/Frame_07.png",frame_[6]);
	//aidegl::glLoadTexture("media/Frame_08.png",frame_[7]);
	//Vecteur3 point, point2;
	//modele_->calculerBoiteEnglobante(point, point2);
	//glNewList(liste_, GL_COMPILE);  
	//	glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
	//	//glBindTexture(GL_TEXTURE_2D,frame_[0]);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	//	glDisable(GL_DEPTH_TEST);
	//	glDepthMask(GL_FALSE);
	//	glEnable(GL_TEXTURE_2D);
	//	glBegin(GL_QUADS);
	//	glTexCoord2i(0, 0);
	//	glVertex3d(point[0]*factEchelle_,point[1]*factEchelle_, 0.0);	
	//	glTexCoord2i(0, 1);
	//	glVertex3d(point[0]*factEchelle_, point2[1]*factEchelle_, 0.0);			
	//	glTexCoord2i(1, 1);
	//	glVertex3d(point2[0]*factEchelle_,point2[1]*factEchelle_, 0.0);		
	//	glTexCoord2i(1, 0);
	//	glVertex3d(point2[0]*factEchelle_,point[1]*factEchelle_, 0.0);
	//	glEnd();
	//	glPopAttrib();
	//glEndList();
	//nextFrame_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudEau::~NoeudEau()
///
/// Ce destructeur désallouee la liste d'affichage de l'eau.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudEau::~NoeudEau()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudEau::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudEau::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudEau::assignerFacteurAgrandissement( float facteur)
///
/// Cette fonction permet d'assigner le facteur d'agrandissement
///
/// @param facteur : Le facteur d'agrandissement
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void NoeudEau::assignerFacteurAgrandissement( float facteur)
{
	factEchelle_ = facteur;
	modele_->assignerFacteurAgrandissement(factEchelle_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudEau::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudEau::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
   NoeudComposite::afficherConcret();
   // Sauvegarde de la matrice.													
   glPushMatrix();

    if(this->estSelectionne())
	{
		glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
		glDepthMask(false);                               //Disable du buffer depthmask

		glEnable(GL_STENCIL_TEST);                        //Enable Stencil test
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDepthMask(true);
		glScalef(factEchelle_, factEchelle_, factEchelle_);
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_EAU); 

	    glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);


		Vecteur3 point, point2;
	    modele_->calculerBoiteEnglobante(point, point2);
		glEnable(GL_BLEND);
		glColor4f(1,0,0,0.5);
	    glBegin(GL_QUADS);						
		glVertex3d(point[0]*factEchelle_*2, point2[1]*factEchelle_, 2.0);		
		glVertex3d(point[0]*factEchelle_*2,point[1]*factEchelle_, 2.0);		
		glVertex3d(point2[0]*factEchelle_*2,point[1]*factEchelle_, 2.0);
		glVertex3d(point2[0]*factEchelle_*2,point2[1]*factEchelle_, 2.0);
	    glEnd();
		glDisable(GL_STENCIL_TEST);

	}
	else
	{
		glRotatef(rotationObjet_, 0.0, 0.0, 1.0);
		glScalef(factEchelle_, factEchelle_, factEchelle_);
		// Affichage du modèle.
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_EAU);
		//test animation			
		/*glBindTexture(GL_TEXTURE_2D,frame_[(int)nextFrame_]);
		glCallList(liste_);	*/	
		//FIN TEST ANIMATION
	}
	
   glPopMatrix();
}

void NoeudEau::animer(float dt)
{
	//nextFrame_ += 0.2;
	//if(nextFrame_ > 8)
	//	nextFrame_ = 0;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////