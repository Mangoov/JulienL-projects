///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTerrain.cpp
/// @author Jean-Luc Dubeau
/// @date 2011-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "FacadeModele.h"
#include "NoeudTerrain.h"
#include "Utilitaire.h"
#include "GestionListeAffichages.h"

#include <windows.h>
#include <aidegl.h>
#include <cmath>

Modele3D* NoeudTerrain::modele_ = nullptr;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTerrain::NoeudTerrain(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTerrain::NoeudTerrain(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud) , liste_(0xffffffff) 
{
	assignerEstSelectionnable(false);
	
   coefFriction_ = 1;
   aidegl::glLoadTexture("media/gazon.png",textureTerrain_,true);
   glBindTexture(GL_TEXTURE_2D, textureTerrain_);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   // Création d'une liste d'affichage pour toutes les instances du noeud Terrain
    if( !GestionListeAffichages::obtenirInstance()->estListeCompiler(LISTE_TERRAIN) )
	{
		modele_ = new Modele3D();
		modele_->charger("media/gazon2.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_TERRAIN);

		modele_->dessiner();		
		glEndList();

		modele_->charger("media/lamp.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_LAMP);

		modele_->dessiner();		
		glEndList(); 

		modele_->charger("media/statue.obj");
		modele_->assignerFacteurAgrandissement(1);
		GestionListeAffichages::obtenirInstance()->creeListeAffichage(LISTE_STATUE);
		modele_->dessiner();
		glEndList();
	}

	

	
	
	liste_ = glGenLists(1);
	glNewList(liste_,GL_COMPILE);
	//glDisable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);

	glBegin(GL_QUADS);
	glNormal3f( 0.0f,  0.0f, 1.0 );
	glTexCoord2f( 0.0, 0.0 );glVertex3f(-195.0f, -195.0f, 0.0 );
	glTexCoord2f( 5.0, 0.0 );glVertex3f( 195.0f, -195.0f, 0.0 );
	glTexCoord2f( 5.0, 5.0 );glVertex3f( 195.0f,  195.0f, 0.0 );
	glTexCoord2f( 0.0, 5.0 );glVertex3f(-195.0f, 195.0f, 0.0 );
	glEnd();
	//glEnable(GL_TEXTURE_2D);
	

	glEndList();
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTerrain::~NoeudTerrain()
///
/// Ce destructeur désallouee la liste d'affichage du terrain
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTerrain::~NoeudTerrain()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTerrain::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax);
///
/// Appel a le calcul de la boite de l'objet
///
/// @param coinMin : le coin min de la boite
/// @param coinMax : le coin max de la boite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTerrain::calculerBoite(Vecteur3& coinMin, Vecteur3& coinMax)
{
	modele_->calculerBoiteEnglobante(coinMin, coinMax);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTerrain::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTerrain::afficherConcret() const
{
   // Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();



	glPushMatrix();
	EtatOpenGL etatTest = EtatOpenGL();
	glTranslatef(0,0,-0.5);
	glScalef(factEchelle_,factEchelle_,factEchelle_);
	if(etatTest.obtenirChaineGlRenderMode() == "GL_SELECT")
	{
		GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_TERRAIN);
	}
	else
	{
		//definition des materiaux
		GLfloat mat_ambiant_model[]  = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_diffuse_model[]  = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_specular_model[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess_model[] = { 100.0 };

		if(FacadeModele::obtenirInstance()->soleilLeve == false)
		{
			glUseProgram(FacadeModele::obtenirInstance()->progPhong_);

			//application de la texture
			glEnable(GL_TEXTURE_2D);		
			int texture_location = glGetUniformLocation(FacadeModele::obtenirInstance()->progPhong_, "texture_color");
			glUniform1i(texture_location, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureTerrain_);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiant_model );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_model );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_model );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess_model );
		}
		else
		{
			glUseProgram(0);


			//application de la texture
			glEnable(GL_TEXTURE_2D);		
			glBindTexture(GL_TEXTURE_2D, textureTerrain_);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiant_model );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_model );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_model );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess_model );
		}


		//terrain
		glCallList(liste_);


	}
	glPopMatrix();

	glActiveTexture(GL_TEXTURE0);  
	glBindTexture(GL_TEXTURE_2D, 0);  
	glDisable(GL_TEXTURE_2D);  
	
	//lampe
	glUseProgram(0);

	glPushMatrix();
	glScalef(1,1,1.4);
	glTranslatef( -180, 180, 0 );
	glRotatef( 90, 1, 0,0 );
	glRotatef( 45, 0, 1,0 );
	GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_LAMP);
	glPopMatrix();
	

	glPushMatrix();
	glTranslatef( 180, -180, 0 );
	glRotatef( 35, 0, 0,1 );
	GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_STATUE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef( -180, -180, 0 );
	glRotatef( -60, 0, 0,1 );
	GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_STATUE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 180, 180, 0 );
	glRotatef( 120, 0, 0,1 );
	GestionListeAffichages::obtenirInstance()->appelListeAffichage(LISTE_STATUE);
	glPopMatrix();

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////