///////////////////////////////////////////////////////////////////////////
/// @file HTTPRequestMethods.h
/// @date 2013-11
/// @description Int�rroge le serveur Web pour recevoir les divers objets JSON.
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _HTTPREQUESTMETHODS_H_
#define _HTTPREQUESTMETHODS_H_

/* Includes */
#include "../GameData/GameUtils.h"
#include "../NetworkInterface/NetworkInterface.h"

/* Variables */
extern NetworkInterface networkInterface;


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestGlobalConfiguration
//                      Demande au serveur la configuration globale de l'application.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* RequestGlobalConfiguration(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestLevelsSummary
//                      Demande au serveur le sommaire des tableaux possibles de t�l�charger.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
LevelsSummary** RequestLevelsSummary(HTTPRequest *httpRequest, size_t *arrLen);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestLevelDescription
//                      Demande au serveur un niveau particulier.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
LevelDescription* RequestLevelDescription(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestBitmap
//                      Demande au serveur une image Bitmap.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
void RequestBitmap(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestBitmap
//                      Demande au serveur une capsule.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
LanderDescription* RequestLanderDescription(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestLandDescription
//                      Demande au serveur la description d'un terrain de jeu selon le tableau JSON de tous les sommaires de tableaux.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant le terrain demand�.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
LandDescription* RequestLandDescription(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestBitmap
//                      Demande au serveur le score suite � l'envoie des donn�es d'une fin de partie.
// PARAMETRES:          httpRequest: contient le corps de la r�quete
//						httpRequest->payload contiendra la r�ponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant la configuration globale de l'application.
// REMARQUE:            Utilis�e par l'interface r�seau.
////////////////////////////////////////////////////////////////////////////////
double RequestScore(HTTPRequest *httpRequest);

#endif /* _HTTPREQUESTMETHODS_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
