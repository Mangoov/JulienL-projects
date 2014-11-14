///////////////////////////////////////////////////////////////////////////
/// @file NetworkInterface.h
/// @date 2013-11
/// @description Pr�sente une interface uniforme pour acc�der au serveur Web.
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

/* D�finitions de types */

/* Type de la requ�te vers le serveur */
typedef enum RequestType_t
{
	JSON = 0,
	BMP
} RequestType;

/* �tat de la requ�te */
typedef enum RequestState_t
{
	RECEIVING = 0,
	COMPLETE
} RequestState;

/* Structure de donn�es d�finissant la connexion au serveur */
typedef struct NetworkInterface_t
{
	struct ip_addr ipaddr;
	struct ip_addr netmask;
	struct ip_addr gw;
	struct ip_addr remote_ipaddr;
	struct netif *netif;
	struct tcp_pcb *pcb;
} NetworkInterface;

/* Structure contenant la requ�te/r�ponse HTTP */
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

/* Structures de donn�es pour le jeu */
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

/* Sert � s�rialiser les donn�es � envoyer au serveur */
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
//                      Configure l'interface r�seau de lwIP.
// PARAMETRES:          Aucun.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure repr�sentant notre interface r�seau.
// REMARQUE:            Utilis�e dans le main.
////////////////////////////////////////////////////////////////////////////////
err_t lwip_config(NetworkInterface *networkInterface);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_init
//                      Initialise notre client.
// PARAMETRES:          remote_ip[4]:	adresse du serveur sur lequel se connecter.
//						remote_port:	num�ro de port du serveur sur lequel se connecter
// VALEUR DE RETOUR:    -1 en cas d'erreur, 0 sinon.
// REMARQUE:            Utilis�e dans le main.
////////////////////////////////////////////////////////////////////////////////
int client_init(void *arg);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         print_err
//                      Affiche sur stdin, de mani�re lisible, une erreur.
// PARAMETRES:          err: erreur � afficher.

// VALEUR DE RETOUR:    Aucune
// REMARQUE:            Utilis�e par client_err.
////////////////////////////////////////////////////////////////////////////////
void print_err(err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_err
//                      Fonction appel�e lors d'une erreur.
// PARAMETRES:          arg: pointeur sur nos donn�es personnelles.
// 						err: erreur qui s'est produite.
// VALEUR DE RETOUR:    -1 en cas d'erreur, 0 sinon.
// REMARQUE:            Utilis�e dans le main.
////////////////////////////////////////////////////////////////////////////////
void client_err(void* arg, err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_recv
//                      Fonction appel�e lors de la r�ception de donn�es.
//						Affiche le nombre de donn�es re�ues.
//						Enregistre aupr�s de LwIP le nombre de donn�es re�ues.
//						Lib�re le paquet re�u.
// PARAMETRES:
// VALEUR DE RETOUR:    ERR_OK en cas de succ�s, sinon le code d'erreur.
// REMARQUE:            Utilis�e dans le client_connected.
////////////////////////////////////////////////////////////////////////////////
err_t client_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *pbuf, err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_connected
//                      Fonction appel�e lorsqu'une connexion � �t� �tablie.
//						Enregistre aupr�s de lwIP le callback client_recv() qui sera appel� � chaque fois que le client recevra des donn�es.
// PARAMETRES:
// VALEUR DE RETOUR:    ERR_OK en cas de succ�s, sinon le code d'erreur.
// REMARQUE:            Utilis�e par client_init.
////////////////////////////////////////////////////////////////////////////////
err_t client_connected(void *arg, struct tcp_pcb *pcb, err_t err);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         client_sent
//                      Fonction appel�e lors de l'acquittement des donn�es �mises.
// PARAMETRES:			arg: pointeur sur nos donn�es.
//						pcb: pointeur sur le PCB de la connexion.
// 						len: taille des donn�es �mises correctement.
// VALEUR DE RETOUR:    ERR_OK en cas de succ�s, sinon le code d'erreur.
// REMARQUE:            Utilis�e dans le client_connected.
////////////////////////////////////////////////////////////////////////////////
err_t client_sent(void *arg, struct tcp_pcb *pcb, u16_t len);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         PrintPossibleMap
//                      Imprime les identifiants de tableau possible
// PARAMETRES:			HTTPRequest *httpRequest: Pour la requ�te au serveur
//						NetworkInterface *networkInterface: Interface sur laquelle on achemine la requ�te
// VALEUR DE RETOUR:    Aucun.
// REMARQUE:            LWIP doit �tre initialis� et l'interface doit �tre valide.
////////////////////////////////////////////////////////////////////////////////
void PrintPossibleMap();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         InitNetworkInterface
//                      Initialise l'interface r�seau
// PARAMETRES:			Aucun.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Doit �tre appel� avant la communication avec le seveur
////////////////////////////////////////////////////////////////////////////////
err_t InitNetworkInterface();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadApplicationData
//						configure l'interface r�seau de lwIP.
//						initialise notre serveur et/ou notre client.
//						lance la fonction principale : program().
// PARAMETRES:			char *id: id du tableau s�lectionn� pour lequel nous allons t�l�charger les donn�es
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            PrintPossibleMap doit avoir �t� appel� et un choix valide avoir �t� fait.
//						La structure app sera rempli apr�s l'appel � cette fonction.
//						Fait appel �: 
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
//						T�l�charger la configuration globale pour l'affichage.
// PARAMETRES:			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre globalCOnfiguration d�clar�e externe contiendra les informations (d�clar�e dans le main).
////////////////////////////////////////////////////////////////////////////////
void DownloadGlobalConfiguration();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLevel
//						T�l�charger les informations d'un niveau.
// PARAMETRES:			const unsigned char *id: Nom unique du niveau.
//						Application *pApp: Structure � remplir par les informations t�l�charg�es.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pApp[index du niveau] d�clar�e externe contiendra les informations (d�clar�e dans le main).
//						Doit �tre appel� apr�s DownloadLevel
////////////////////////////////////////////////////////////////////////////////
void DownloadLevel(const unsigned char *id, Application *pApp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLevelPreview
//						T�l�charge le preview Bitmap d'un niveau.
// PARAMETRES:			const unsigned char *id: Nom unique du niveau.
//						Bitmap *pPreviewBMP: Structure bitmap � remplir par les informations t�l�charg�es.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pPreviewBMP[index du niveau] d�clar�e externe contiendra le preview bitmap (d�clar�e dans le main).
////////////////////////////////////////////////////////////////////////////////
void DownloadLevelPreview(const unsigned char *id, Bitmap *pPreviewBMP);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLand
//						T�l�charge le terrain associ� � un niveau particulier.
// PARAMETRES:			const unsigned char *id: Nom unique du niveau.
//						Bitmap *pPreviewBMP: Structure bitmap � remplir par les informations t�l�charg�es.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pPreviewBMP[index du niveau] d�clar�e externe contiendra le preview bitmap (d�clar�e dans le main).
//						Doit �tre appel� apr�s DownloadLevel
////////////////////////////////////////////////////////////////////////////////
void DownloadLand(Application *pApp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLandBackground
//						T�l�charge l'image bitmap du terrain associ� � un niveau particulier.
// PARAMETRES:			Application *pApp: Sert � identifi� le terrain � partir pour lequel on veut l'image background 
//						Bitmap *pLandBMP: Structure bitmap � remplir par les informations t�l�charg�es.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pApp[index du niveau] d�clar�e externe contiendra les informations (d�clar�e dans le main).
//						Doit �tre appel� apr�s DownloadLand
////////////////////////////////////////////////////////////////////////////////
void DownloadLandBackground(Application *pApp, Bitmap *pLandBMP);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLander
//						T�l�charge la description d'une capsule.
// PARAMETRES:			Application *pApp: Sert � identifi� la capsule pour un niveau particulier.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pApp[index du niveau] d�clar�e externe contiendra le preview bitmap (d�clar�e dans le main).
//						Doit �tre appel� apr�s DownloadLevel.
////////////////////////////////////////////////////////////////////////////////
void DownloadLander(Application *pApp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         DownloadLanderImage
//						T�l�charge l'image bitmap d'une capsue associ� � un niveau particulier.
// PARAMETRES:			Application *pApp: Sert � identifi� le terrain � partir pour lequel on veut l'image de la capsule.
//						Bitmap *pLandBMP: Structure bitmap � remplir par les informations t�l�charg�es.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La strucutre pLanderBMP[index du niveau] d�clar�e externe contiendra le preview bitmap (d�clar�e dans le main).
//						Doit �tre appel� apr�s DownloadLevel
////////////////////////////////////////////////////////////////////////////////
void DownloadLanderImage(Application *appli, Bitmap *pLanderBMP);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         SendGameData
//						Envoie les donn�es d'une partie r�ussi au serveur pour la comptabilisation du score.
// PARAMETRES:			char* nameid: identificateur unique du tableau
// VALEUR DE RETOUR:    Le score renvoy� par le serveur.
// REMARQUE:            La structure gameData doit �tre valide avant d'appeler cette fonction.
////////////////////////////////////////////////////////////////////////////////
double SendGameData(char* nameid);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:         AllocApplication
//						Sert � allou� un bloc de m�moire pour contenir les informations de plusieurs types de parties.
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
