#ifndef __APPLICATION_HUD_H__
#define __APPLICATION_HUD_H__

#include "FacadeModele.h"
#include "NoeudAbstrait.h"
#include "AideCollision.h"
#include "ArbreRenduINF2990.h"
#include "Vue.h"
#include "AideGL.h"
#include <string.h>
#include <cstring>

class HUD
{
public:
	
	// Instance du HUD
	static HUD *getInstance()
	{
		if (singleton_ == NULL)
		{
			singleton_ =  new HUD;
		}
		return singleton_;
	}
	static void libererInstance();

	// Updater le HUD
	void updateHUD();
	// imprimer le texte dans le HUD
	GLvoid glPrint(const char *fmt,...);
	// build le font
	GLvoid buildFont(int tailleFont);
	
	// dessiner radio
	void dessinerRadio();
	// dessiner radio dans le HUD
	void dessinerHUD(int frappes, double distance, char * typeVue, std::string nomJoueur,std::string nomMap);


private:
	// Constructeur HUD
	HUD();
	//Destructeur HUD
	~HUD();
	static HUD *singleton_;
	GLuint base, radio;


};

#endif // __APPLICATION_HUD_H__