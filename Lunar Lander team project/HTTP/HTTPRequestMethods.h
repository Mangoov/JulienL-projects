///////////////////////////////////////////////////////////////////////////
/// @file HTTPRequestMethods.h
/// @date 2013-11
/// @description Intérroge le serveur Web pour recevoir les divers objets JSON.
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
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* RequestGlobalConfiguration(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestLevelsSummary
//                      Demande au serveur le sommaire des tableaux possibles de télécharger.
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
LevelsSummary** RequestLevelsSummary(HTTPRequest *httpRequest, size_t *arrLen);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestLevelDescription
//                      Demande au serveur un niveau particulier.
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
LevelDescription* RequestLevelDescription(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestBitmap
//                      Demande au serveur une image Bitmap.
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
void RequestBitmap(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestBitmap
//                      Demande au serveur une capsule.
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
LanderDescription* RequestLanderDescription(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestLandDescription
//                      Demande au serveur la description d'un terrain de jeu selon le tableau JSON de tous les sommaires de tableaux.
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant le terrain demandé.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
LandDescription* RequestLandDescription(HTTPRequest *httpRequest);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         RequestBitmap
//                      Demande au serveur le score suite à l'envoie des données d'une fin de partie.
// PARAMETRES:          httpRequest: contient le corps de la rêquete
//						httpRequest->payload contiendra la réponse du serveur
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant la configuration globale de l'application.
// REMARQUE:            Utilisée par l'interface réseau.
////////////////////////////////////////////////////////////////////////////////
double RequestScore(HTTPRequest *httpRequest);

#endif /* _HTTPREQUESTMETHODS_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
