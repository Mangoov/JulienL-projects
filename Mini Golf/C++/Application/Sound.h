///////////////////////////////////////////////////////////////////////////////
/// @file Sound.h
/// @author Etienne Vallée
/// @date 2011-11-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// Musique : Gros fichiers
/// Son : Petits fichiers
///////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_SOUND_H__
#define __APPLICATION_SOUND_H__

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include "VisiteurXML.h"
///////////////////////////////////////////////////////////////////////////
/// @class GestionSon
/// @brief Classe qui va gerer l'Ensemble des sons
///////////////////////////////////////////////////////////////////////////


class Sound
{
	public:
		static Sound* obtenirInstance();
		static void libererInstance();

		void initSon();

		//void Xml();

		//Joueur Sons
		void jouerBaton();
		void arreterBaton();
		void jouerEau();
		void arreterEau();
		void jouerSable();
		void arreterSable();
		void jouerBonus();
		void arreterBonus();
		void jouerTrou();
		void arreterTrou();
		void jouerCollision();
		void arreterCollision();
		void jouerPortal();
		void arreterPortal();
		void jouerFeuArtifices();
		void arreterFeuArtifices();
		void jouerHoleInOne();
		
		//Joueur Musiques
		void jouerMusique();
		void arreterMusique();
		void MusiqueMenu(int etat);
		void jouerMusique1();
		void arreterMusique1();
		void jouerMusique2();
		void arreterMusique2();
		void jouerMusique3();
		void arreterMusique3();
		void jouerMusique4();
		void arreterMusique4();
		void jouerMusiqueMenu();
		void arreterMusiqueMenu();

		//Autres
		bool isPlaying();
		
		float volumeSon_;
		float volumeMusique_;
		float volumeMute_;

		void ajusterVolumeSon(float);
		void ajusterVolumeMusique(float);
		void mute();

		void setChannel(int);

		void ERRCHECK(FMOD_RESULT result);
		
		std::string musiqueCourante_;
	private:
		Sound();
		~Sound();
		int choixMusique_;
		bool isPlaying_;
		bool isMute_;
		TiXmlDocument  * ConfigSon_;
		std::vector<std::string> temp1,temp2;

		int channelEnCours_;

		FMOD::System *system;
		FMOD_RESULT result;

		//patron visiteur
		Sound(const Sound&);
		static Sound* instance_;

		//Son
		FMOD::Sound *sonBaton_;
		FMOD::Sound *sonEau_;
		FMOD::Sound *sonSable_;
		FMOD::Sound *sonBonus_;
		FMOD::Sound *sonTrou_;
		FMOD::Sound *sonCollision_;
		FMOD::Sound *sonPortal_;
		FMOD::Sound *sonFeuArtifice_;
		FMOD::Sound *sonHoleInOne_;

		//Musique
		FMOD::Sound *musiqueMenu_;
		FMOD::Sound *musique1_;
		FMOD::Sound *musique2_;
		FMOD::Sound *musique3_;
		FMOD::Sound *musique4_;

		//Canaux pour sons
	    FMOD::Channel *channel1_;
		FMOD::Channel *channel2_;
		FMOD::Channel *channel3_;
		FMOD::Channel *channel4_;
		FMOD::Channel *channel5_;
		FMOD::Channel *channel6_;
		FMOD::Channel *channel7_;
		FMOD::Channel *channel8_;
		FMOD::Channel *channel9_;

		//Canaux pour musique
		FMOD::Channel *channel01_;
		FMOD::Channel *channel02_;
		FMOD::Channel *channel03_;
		FMOD::Channel *channel04_;
		FMOD::Channel *channelMenu_;
		
		int               key;
		unsigned int      version;
};

#endif // __APPLICATION_SOUND_H__