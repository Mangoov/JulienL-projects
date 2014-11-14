////////////////////////////////////////////////
/// @file   Sound.cpp
/// @author Etienne Vallée
/// @date   2011-11-11
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "Sound.h"

Sound* Sound::instance_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn Sound* Sound::obtenirInstance()
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
Sound* Sound::obtenirInstance()
{
	if (instance_ == 0)
		instance_ = new Sound;

	return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::libererInstance()
///
/// Libere l'instance de la classe
///
/// @return Sound*
///
////////////////////////////////////////////////////////////////////////
void Sound::libererInstance()
{
	delete instance_;
	instance_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::Sound()
///
/// Constructeur de la classe
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
Sound::Sound()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::~Sound()
///
/// Detruit tous les sons
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
Sound::~Sound()
{
	//FMOD_Sound_Release(sound1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::ERRCHECK(FMOD_RESULT result)
///
/// vérifie s'il y a une erreur avec FMOD
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::initSon()
///
/// initialise le son (pour une meilleure performance, effectuer lors du splashScreen)
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::initSon()
{
	ConfigSon_ = new TiXmlDocument();
	ConfigSon_->LoadFile("configurationSon.xml");

	TiXmlHandle docHandle(ConfigSon_);
	TiXmlElement* fils = docHandle.FirstChild().FirstChild().ToElement();
	std::string name ,estAffiche,estSelectionnable,estSelectionne;
	
	if(fils != NULL)
	{
		for(fils; fils; fils = fils->NextSiblingElement())
		{
			const char* shit = fils->Attribute("Nom");
			temp1.push_back(shit);
			temp2.push_back(fils->Attribute("Fichier"));//A verifier qu'il ne faut pas utiliser le constructeur de string
		}
	}
		
	//Create a System object and initialize.
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->getVersion(&version);
	ERRCHECK(result);

	result = system->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	/////////////////////
	//Creation des sons//
	/////////////////////

	result = system->createSound(temp2[0].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonBaton_);
	ERRCHECK(result);

	result = system->createSound(temp2[1].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonEau_);
	ERRCHECK(result);

	result = system->createSound(temp2[2].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonSable_);
	ERRCHECK(result);

	result = system->createSound(temp2[3].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonBonus_);
	ERRCHECK(result);

	result = system->createSound(temp2[4].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonTrou_);
	ERRCHECK(result);

	result = system->createSound(temp2[5].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonCollision_);
	ERRCHECK(result);

	result = system->createSound(temp2[6].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonPortal_);
	ERRCHECK(result);

	result = system->createSound(temp2[7].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonFeuArtifice_);
	ERRCHECK(result);

	result = system->createSound(temp2[8].c_str(), FMOD_DEFAULT | FMOD_2D, 0, &sonHoleInOne_);

	/////////////////////////
	//Creation des musiques//
	/////////////////////////

	result = system->createStream(temp2[9].c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &musique1_);
	ERRCHECK(result);

	result = system->createStream(temp2[10].c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &musique2_);
	ERRCHECK(result);

	result = system->createStream(temp2[11].c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &musique3_);
	ERRCHECK(result);

	result = system->createStream(temp2[12].c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &musique4_);
	ERRCHECK(result);

	result = system->createStream(temp2[13].c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &musiqueMenu_);
	ERRCHECK(result);

	channelEnCours_ = 1;
	volumeMusique_ = 0.3;
	volumeSon_ = 0.5;
	isMute_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::setChannel(int pos)
///
/// Dit quel poste sera le prochain ou quel poste est le précédent
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::setChannel(int pos)
{
	if(pos == 1)
	{
		if(channelEnCours_ <=3)
		{
			channelEnCours_ = channelEnCours_ + 1;	
		}
		else
		{
			channelEnCours_ = 1;
		}
	}
	else
	{
		if(channelEnCours_ >=2)
		{
			channelEnCours_ = channelEnCours_ - 1;	
		}
		else
		{
			channelEnCours_ = 4;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::ajusterVolumeSon(int volume)
///
/// Augmente ou baisse le volume des sons
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::ajusterVolumeSon(float volume)
{
	if(volume==2.0) //Baisser volume
	{
		if(volumeSon_ > 0.0)
		{
			volumeSon_ = volumeSon_ - 0.1;
		}
	}
	else if(volume == 3.0) //Monter volume
	{
		if(volumeSon_ < 1.0)
		{
			volumeSon_ = volumeSon_ + 0.1;
		}
	}
	else
	{
		volumeSon_ = volume;
	}
	system->update();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::ajusterVolumeMusique()
///
/// Augmente ou baisse le volume de la musique
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::ajusterVolumeMusique(float volume)
{

	if(volume==2.0) //Baisser volume
	{
		if(volumeMusique_ > 0.0)
		{
			volumeMusique_ = volumeMusique_ - 0.1;
		}
	}
	else if(volume == 3.0) //Monter volume
	{
		if(volumeMusique_ < 1.0)
		{
			volumeMusique_ = volumeMusique_ + 0.1;
		}
	}
	else
	{
		volumeMusique_ = volume;
	}

	switch(channelEnCours_)
	{
	case 1:
		channel01_->setVolume(volumeMusique_);
		system->update();
		break;
	case 2:
		channel02_->setVolume(volumeMusique_);
		system->update();
		break;
	case 3:
		channel03_->setVolume(volumeMusique_);
		system->update();
		break;
	case 4:
		channel04_->setVolume(volumeMusique_);
		system->update();
		break;
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerMusique()
///
/// Joue la musique en cours
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerMusique()
{
	switch(channelEnCours_)
	{
	case 1:
		jouerMusique1();
		musiqueCourante_ = temp1[9];
		break;
	case 2:
		jouerMusique2();
		musiqueCourante_ = temp1[10];
		break;
	case 3:
		jouerMusique3();
		musiqueCourante_ = temp1[11];
		break;
	case 4:
		jouerMusique4();
		musiqueCourante_ = temp1[12];
		break;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusique()
///
/// Joue la musique en cours
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterMusique()
{
	switch(channelEnCours_)
	{
	case 1:
		arreterMusique1();
		break;
	case 2:
		arreterMusique2();
		break;
	case 3:
		arreterMusique3();
		break;
	case 4:
		arreterMusique4();
		break;
	}
	musiqueCourante_ = " ";
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerBaton()
///
/// Joue le son du baton
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerBaton()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonBaton_, false, &channel1_);
	ERRCHECK(result);
	channel1_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterBaton()
///
/// Arrete le son du baton
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterBaton()
{ 
	result = channel1_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerEau()
///
/// Joue le son de l'eau
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerEau()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonEau_, false, &channel2_);
	ERRCHECK(result);
	channel2_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterEau()
///
/// Arrete le son de l'eau
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterEau()
{ 
	result = channel2_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerSable()
///
/// Joue le son du sable
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerSable()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonSable_, false, &channel3_);
	ERRCHECK(result);
	channel3_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterSable()
///
/// Arrete le son du sable
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterSable()
{ 
	result = channel3_->stop();
	ERRCHECK(result);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerBonus()
///
/// Joue le son du bonus
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerBonus()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonBonus_, false, &channel4_);
	ERRCHECK(result);
	channel4_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterBonus()
///
/// Arrete le son du bonus
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterBonus()
{ 
	result = channel4_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerTrou()
///
/// Joue le son du Trou
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerTrou()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonTrou_, false, &channel5_);
	ERRCHECK(result);
	channel5_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterTrou()
///
/// Arrete le son du trou
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterTrou()
{ 
	result = channel5_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerCollision()
///
/// Joue le son de la Collision
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerCollision()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonCollision_, false, &channel6_);
	ERRCHECK(result);
	channel6_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterCollision()
///
/// Arrete le son de la Collision
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterCollision()
{ 
	result = channel6_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerPortal()
///
/// Joue le son du Portal
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerPortal()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonPortal_, false, &channel7_);
	ERRCHECK(result);
	channel7_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterPortal()
///
/// Arrete le son du Portal
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterPortal()
{ 
	result = channel7_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerFeuArtifices()
///
/// Joue le son du Portal
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerFeuArtifices()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonFeuArtifice_, false, &channel8_);
	ERRCHECK(result);
	channel8_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void arreterFeuArtifices()
///
/// Arrete le son du Portal
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterFeuArtifices()
{ 
	result = channel8_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerMusique1()
///
/// Joue la musique 1
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerMusique1()
{
	channelEnCours_ = 1;
	result = system->playSound(FMOD_CHANNEL_REUSE, musique1_, false, &channel01_);
	channel01_->setVolume(volumeMusique_);
	system->update();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusique1()
///
/// Arrete la musique 1
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterMusique1()
{ 
	result = channel01_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerMusique2()
///
/// Joue la musique 2
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerMusique2()
{
	channelEnCours_ = 2;
	result = system->playSound(FMOD_CHANNEL_REUSE, musique2_, false, &channel02_);
	channel02_->setVolume(volumeMusique_);
	system->update();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusique2()
///
/// Arrete la musique 2
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterMusique2()
{ 
	result = channel02_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerMusique3()
///
/// Joue la musique 3
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerMusique3()
{
	channelEnCours_ = 3;
	result = system->playSound(FMOD_CHANNEL_REUSE, musique3_, false, &channel03_);
	channel03_->setVolume(volumeMusique_);
	system->update();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusique3()
///
/// Arrete la musique 3
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterMusique3()
{ 
	result = channel03_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerMusique4()
///
/// Joue la musique 4
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerMusique4()
{
	channelEnCours_ = 4;
	result = system->playSound(FMOD_CHANNEL_REUSE, musique4_, false, &channel04_);
	channel04_->setVolume(volumeMusique_);
	system->update();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusique4()
///
/// Arrete la musique 4
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterMusique4()
{ 
	result = channel04_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerMusiqueMenu()
///
/// Joue la musique du menu
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerMusiqueMenu()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, musiqueMenu_, false, &channelMenu_);
	channelMenu_->setVolume(volumeMusique_);
	system->update();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusiqueMenu()
///
/// Arrete la musique du menu
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::arreterMusiqueMenu()
{ 
	result = channelMenu_->stop();
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::arreterMusiqueMenu()
///
/// Arrete la musique du menu
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::MusiqueMenu(int etat)
{ 
	if(etat == 1)
	{
		jouerMusiqueMenu();
	}
	else
	{
		arreterMusiqueMenu();
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::jouerHoleInOne();
///
/// Joue le son qui va avec un trou d'un coup
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::jouerHoleInOne()
{
	result = system->playSound(FMOD_CHANNEL_REUSE, sonHoleInOne_, false, &channel9_);
	ERRCHECK(result);
	channel9_->setVolume(volumeSon_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sound::mute()
///
/// Joue le son qui va avec un trou d'un coup
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Sound::mute()
{

	if(isMute_ == false)
	{
		volumeMute_ = volumeSon_;
		volumeSon_ = 0.0;
	}
	else
	{
		volumeSon_ = volumeMute_;
	}

	switch(channelEnCours_)
	{
	case 1:
		if(isMute_ == false)
		{
			channel01_->setMute(true);
			isMute_ = true;
		}
		else
		{
			channel01_->setMute(false);
			isMute_ = false;
		}
			system->update();
		break;

	case 2:
		if(isMute_ == false)
		{
			channel02_->setMute(true);
			isMute_ = true;
		}
		else
		{
			channel02_->setMute(false);
			isMute_ = false;
		}
		system->update();
		break;

	case 3:
		if(isMute_ == false)
		{
			channel03_->setMute(true);
			isMute_ = true;
		}
		else
		{
			channel03_->setMute(false);
			isMute_ = false;
		}
		system->update();
		break;

	case 4:
		if(isMute_ == false)
		{
			channel04_->setMute(true);
			isMute_ = true;
		}
		else
		{
			channel04_->setMute(false);
			isMute_ = false;
		}
		system->update();
		break;
	}
}