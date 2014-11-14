///////////////////////////////////////////////////////////////////////////
/// @file NetworkInterface.h
/// @date 2013-11
/// @description Présente une interface uniforme pour accéder au serveur Web.
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////


#ifndef _NETWORK_INTERFACE_H
#define _NETWORK_INTERFACE_H

/* Includes */
#include "lwip/sys.h"   // sys_init()
#include "lwip/mem.h"   // mem_init()
#include "lwip/memp.h"  // memp_init()
#include "lwip/pbuf.h"  // pbuf_init()
#include "lwip/netif.h" // struct netif, netif_init()
#include "lwip/tcp.h"   // tcp_init(), tcp_new(), tcp_connect(), tcp_tmr()
#include "lwip/err.h" 	// err_t

#include "xparameters.h"

#include "netif/xadapter.h"

#include "../Configuration/platform.h"
#include "../Configuration/platform_config.h"
#include "../HTTP/HTTPDefinitions.h"
#include "../JSON/JSONDecoder.h"
#include "../Bitmap/Bitmap.h"
#include "../src/typedef.h"

#include "string.h"

#include "../src/log.h"

/* Définitions de types */

/* Type de la requête vers le serveur */
typedef enum RequestType_t
{
	JSON = 0,
	BMP
} RequestType;

/* État de la requête */
typedef enum RequestState_t
{
	RECEIVING = 0,
	COMPLETE
} RequestState;

/* Structure de données définissant la connexion au serveur */
typedef struct NetworkInterface_t
{
	struct ip_addr ipaddr;
	struct ip_addr netmask;
	struct ip_addr gw;
	struct ip_addr remote_ipaddr;
	struct netif *netif;
	struct tcp_pcb *pcb;
} NetworkInterface;

/* Structure contenant la requête/réponse HTTP */
typedef struct HTTPRequest_t
{
	char *request;
	HTTPResponse response;
	void *payload;
	RequestState requestState;
	RequestType requestType;
	bool initialize;
	size_t buffer_len, content_len;
} HTTPRequest;

/* Structures de données pour le jeu */
typedef struct Application_t
{
	LevelDescription *levelDescription;
	LandDescription *landDescription;
	LanderDescription *landerDescription;
} Application;

typedef struct Summary_t
{
	LevelsSummary **arrLevelsSummary;
	size_t levelSummaryArrayLen;
} Summary;

/* Sert à sérialiser les données à envoyer au serveur */
GameData gameData;

 /**/
extern Bitmap **ppLandBMP, **ppLanderBMP, **ppPreviewBMP;
extern Bitmap LandBMP, LanderBMP, PreviewBMP;
extern GlobalConfiguration *globalConfiguration;
extern Application **ppApp;
extern Summary summary;
/**/

////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         lwip_config
//                      Configure l'interface réseau de lwIP.
// PARAMETRES:          Aucun.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant notre interface réseau.
// REMARQUE:            Utilisée dans le main.
////////////////////////////////////////////////////////////////////////////////
err_t lwip_config(NetworkInterface *networkInterface);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_init
//                      Initialise notre client.
// PARAMETRES:          remote_ip[4]:	adresse du serveur sur lequel se connecter.
//						remote_port:	numéro de port du serveur sur lequel se connecter
// VALEUR DE RETOUR:    -1 en cas d'erreur, 0 sinon.
// REMARQUE:            Utilisée dans le main.
////////////////////////////////////////////////////////////////////////////////
int client_init(void *arg);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         print_err
//                      Affiche sur stdin, de manière lisible, une erreur.
// PARAMETRES:          err: erreur à afficher.

// VALEUR DE RETOUR:    Aucune
// REMARQUE:            Utilisée par client_err.
////////////////////////////////////////////////////////////////////////////////
void print_err(err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_err
//                      Fonction appelée lors d'une erreur.
// PARAMETRES:          arg: pointeur sur nos données personnelles.
// 						err: erreur qui s'est produite.
// VALEUR DE RETOUR:    -1 en cas d'erreur, 0 sinon.
// REMARQUE:            Utilisée dans le main.
////////////////////////////////////////////////////////////////////////////////
void client_err(void* arg, err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_recv
//                      Fonction appelée lors de la réception de données.
//						Affiche le nombre de données reçues.
//						Enregistre auprès de LwIP le nombre de données reçues.
//						Libère le paquet reçu.
// PARAMETRES:
// VALEUR DE RETOUR:    ERR_OK en cas de succès, sinon le code d'erreur.
// REMARQUE:            Utilisée dans le client_connected.
////////////////////////////////////////////////////////////////////////////////
err_t client_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *pbuf, err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_connected
//                      Fonction appelée lorsqu'une connexion à été établie.
//						Enregistre auprès de lwIP le callback client_recv() qui sera appelé à chaque fois que le client recevra des données.
// PARAMETRES:
// VALEUR DE RETOUR:    ERR_OK en cas de succès, sinon le code d'erreur.
// REMARQUE:            Utilisée par client_init.
////////////////////////////////////////////////////////////////////////////////
err_t client_connected(void *arg, struct tcp_pcb *pcb, err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_sent
//                      Fonction appelée lors de l'acquittement des données émises.
// PARAMETRES:			arg: pointeur sur nos données.
//						pcb: pointeur sur le PCB de la connexion.
// 						len: taille des données émises correctement.
// VALEUR DE RETOUR:    ERR_OK en cas de succès, sinon le code d'erreur.
// REMARQUE:            Utilisée dans le client_connected.
////////////////////////////////////////////////////////////////////////////////
err_t client_sent(void *arg, struct tcp_pcb *pcb, u16_t len);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         PrintPossibleMap
//                      Imprime les identifiants de tableau possible
// PARAMETRES:			HTTPRequest *httpRequest: Pour la requête au serveur
//						NetworkInterface *networkInterface: Interface sur laquelle on achemine la requête
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            LWIP doit être initialisé et l'interface doit être valide.
////////////////////////////////////////////////////////////////////////////////
void PrintPossibleMap();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         InitNetworkInterface
//                      Initialise l'interface réseau
// PARAMETRES:			Aucun.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Doit être appelé avant la communication avec le seveur
////////////////////////////////////////////////////////////////////////////////
err_t InitNetworkInterface();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadApplicationData
//						configure l'interface réseau de lwIP.
//						initialise notre serveur et/ou notre client.
//						lance la fonction principale : program().
// PARAMETRES:			char *id: id du tableau sélectionné pour lequel nous allons télécharger les données
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            PrintPossibleMap doit avoir été appelé et un choix valide avoir été fait.
//						La structure app sera rempli après l'appel à cette fonction.
//						Fait appel à: 
// 						DownloadGlobalConfiguration,
// 						DownloadLevel,
// 						DownloadLevelPreview,
// 						DownloadLand,	
// 						DownloadLandBackground,
// 						DownloadLander,	
// 						DownloadLanderImage,
////////////////////////////////////////////////////////////////////////////////
void DownloadApplicationData();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadGlobalConfiguration
//						Télécharger la configuration globale pour l'affichage.
// PARAMETRES:			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre globalCOnfiguration déclarée externe contiendra les informations (déclarée dans le main).
////////////////////////////////////////////////////////////////////////////////
void DownloadGlobalConfiguration();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLevel
//						Télécharger les informations d'un niveau.
// PARAMETRES:			const unsigned char *id: Nom unique du niveau.
//						Application *pApp: Structure à remplir par les informations téléchargées.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pApp[index du niveau] déclarée externe contiendra les informations (déclarée dans le main).
//						Doit être appelé après DownloadLevel
////////////////////////////////////////////////////////////////////////////////
void DownloadLevel(const unsigned char *id, Application *pApp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLevelPreview
//						Télécharge le preview Bitmap d'un niveau.
// PARAMETRES:			const unsigned char *id: Nom unique du niveau.
//						Bitmap *pPreviewBMP: Structure bitmap à remplir par les informations téléchargées.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pPreviewBMP[index du niveau] déclarée externe contiendra le preview bitmap (déclarée dans le main).
////////////////////////////////////////////////////////////////////////////////
void DownloadLevelPreview(const unsigned char *id, Bitmap *pPreviewBMP);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLand
//						Télécharge le terrain associé à un niveau particulier.
// PARAMETRES:			const unsigned char *id: Nom unique du niveau.
//						Bitmap *pPreviewBMP: Structure bitmap à remplir par les informations téléchargées.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pPreviewBMP[index du niveau] déclarée externe contiendra le preview bitmap (déclarée dans le main).
//						Doit être appelé après DownloadLevel
////////////////////////////////////////////////////////////////////////////////
void DownloadLand(Application *pApp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLandBackground
//						Télécharge l'image bitmap du terrain associé à un niveau particulier.
// PARAMETRES:			Application *pApp: Sert à identifié le terrain à partir pour lequel on veut l'image background 
//						Bitmap *pLandBMP: Structure bitmap à remplir par les informations téléchargées.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pApp[index du niveau] déclarée externe contiendra les informations (déclarée dans le main).
//						Doit être appelé après DownloadLand
////////////////////////////////////////////////////////////////////////////////
void DownloadLandBackground(Application *pApp, Bitmap *pLandBMP);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLander
//						Télécharge la description d'une capsule.
// PARAMETRES:			Application *pApp: Sert à identifié la capsule pour un niveau particulier.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pApp[index du niveau] déclarée externe contiendra le preview bitmap (déclarée dans le main).
//						Doit être appelé après DownloadLevel.
////////////////////////////////////////////////////////////////////////////////
void DownloadLander(Application *pApp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLanderImage
//						Télécharge l'image bitmap d'une capsue associé à un niveau particulier.
// PARAMETRES:			Application *pApp: Sert à identifié le terrain à partir pour lequel on veut l'image de la capsule.
//						Bitmap *pLandBMP: Structure bitmap à remplir par les informations téléchargées.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pLanderBMP[index du niveau] déclarée externe contiendra le preview bitmap (déclarée dans le main).
//						Doit être appelé après DownloadLevel
////////////////////////////////////////////////////////////////////////////////
void DownloadLanderImage(Application *appli, Bitmap *pLanderBMP);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         SendGameData
//						Envoie les données d'une partie réussi au serveur pour la comptabilisation du score.
// PARAMETRES:			char* nameid: identificateur unique du tableau
// VALEUR DE RETOUR:    Le score renvoyé par le serveur.
// REMARQUE:            La structure gameData doit être valide avant d'appeler cette fonction.
////////////////////////////////////////////////////////////////////////////////
double SendGameData(char* nameid);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         AllocApplication
//						Sert à alloué un bloc de mémoire pour contenir les informations de plusieurs types de parties.
// PARAMETRES:			size_t arr_app_len: Nombres de types de parties possibles.
// VALEUR DE RETOUR:    Application**: Un pointeur vers le tableau.
// REMARQUE:            Aucune.
////////////////////////////////////////////////////////////////////////////////
Application** AllocApplication(size_t arr_app_len);

int LevelIdToInt(unsigned char *id);

#endif /* _NETWORK_INTERFACE_H */


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
