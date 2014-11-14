///////////////////////////////////////////////////////////////////////////
/// @file HTTPDefinitions.h
/// @date 2013-11
/// @description Définitions de structures et de chaînes de caractères pour l'envoie de requête HTTP au serveur.
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _HTTPDEFINITIONS_H_
#define _HTTPDEFINITIONS_H_

/* Includes */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* snprintf */

/* Type définit par l'usager */

/* Index dans le tableau g_psHTTPHeaderStrings */
#define HTTP_HDR_HTML           0 /* text/html */
#define HTTP_HDR_BMP            1 /* image/bmp */
#define HTTP_HDR_OK          	2 /* 200 OK */
#define HTTP_HDR_BAD_REQUEST 	3 /* 400 Bad request */
#define HTTP_HDR_NOT_FOUND	   	4 /* 404 File not found */
#define HTTP_HDR_NOT_ALLOW 		5 /* 405 Method Not Allowed */
#define HTTP_HDR_INTERNAL_ERROR	6 /* 500 Internal Server Error */
#define HTTP_HDR_NOT_IMPL       7 /* 501 Not Implemented */
#define HTTP_HDR_CONTENT_LENGTH 8 /* Content-Length: (HTTP 1.1)*/
#define HTTP_HDR_CONN_CLOSE     9 /* Connection: Close (HTTP 1.1) */

/* Type de réponse HTTP possible */
typedef enum HTTPResponse_t
{
	NONE = 0,
	HTTP_200_OK,
	HTTP_400_BAD_REQUEST,
	HTTP_404_FILE_NOT_FOUND,
	HTTP_405_METHOD_NOT_ALLOW,
	HTTP_500_INTERNAL_SERVER_ERROR,
	HTTP_501_NOT_IMPLEMENTED
} HTTPResponse;

/* Liste de chaîne de caractères possible dans une entête HTTP */
static const char * const g_psHTTPHeaderStrings[] =
{
		"text/html\r\n\r\n",
		"image/bmp\r\n\r\n",
		"HTTP/1.0 200 OK\r\n",
		"HTTP/1.0 400 Bad Request\r\n",
		"HTTP/1.0 404 File not found\r\n",
		"HTTP/1.0 405 Method Not Allowed\r\n",
		"HTTP/1.0 500 Internal Server Error\r\n",
		"HTTP/1.0 501 Not Implemented\r\n",
		"Content-Length: ",
		"Connection: Close\r\n",
};

/* Requête pour le projet */
typedef enum API_HTTP_T { /* Requêtes HTTP possibles*/
	CONFIG = 0,
	LEVELS,
	LEVELS_ID,
	LEVEL_ID_PREVIEW,
	LEVELS_ID_GAMEDATA,
	LANDS_ID,
	LANDS_BG_ID,
	LANDER_ID,
	LANDER_ID_IMG
} API_HTTP;

/* Configuration globale (objet JSON à ne télécharger qu’une seule fois lors du lancement de l’application */
static const char const g_psHTTPGETGlobalConfig[] =
{
		"GET /config HTTP/1.1\r\n"
		"Host: jupiter.info.polymtl.ca:9010\r\n"
		"Connection: close\r\n"
		"\r\n"
};

/* Tableau JSON de tous les sommaires de tableaux (à télécharger pour présenter la liste des tableaux afin que l’utilisateur en choisisse un pour lancer une partie) */
static const char const g_psHTTPGETLevels[] =
{
		"GET /levels/ HTTP/1.1\r\n"
		"Host: jupiter.info.polymtl.ca:9010\r\n"
		"Connection: Close\r\n"
		"\r\n"
};

#endif /* _HTTPDEFINITIONS_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
