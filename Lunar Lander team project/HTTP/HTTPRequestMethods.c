///////////////////////////////////////////////////////////////////////////
/// @file HTTPRequestMethods.c
/// @date 2013-11
/// @description Implémentation des divers requêtes HTTP + le traitement JSON si nécéssaire
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////


/* Includes */
#include "../HTTP/HTTPRequestMethods.h"


///////////////////////////////////////////////////////////////////////////////
GlobalConfiguration* RequestGlobalConfiguration(HTTPRequest *httpRequest)
{
	char *pJSON = NULL;
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
	pJSON = ( char* ) httpRequest->payload;
	pJSON[httpRequest->buffer_len] = '\0';
	return GetGlobalConfiguration(pJSON);
}


///////////////////////////////////////////////////////////////////////////////
LevelsSummary** RequestLevelsSummary(HTTPRequest *httpRequest, size_t *arrLen)
{
	char *pJSON = NULL;
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
	pJSON = ( char* ) httpRequest->payload;
	pJSON[httpRequest->buffer_len] = '\0';
	return GetLevelsSummary(pJSON, arrLen);
}


///////////////////////////////////////////////////////////////////////////////
LevelDescription* RequestLevelDescription(HTTPRequest *httpRequest)
{
	char *pJSON = NULL;
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
	pJSON = ( char* ) httpRequest->payload;
	pJSON[httpRequest->buffer_len] = '\0';
	return GetLevelDescription(pJSON);
}


///////////////////////////////////////////////////////////////////////////////
void RequestBitmap(HTTPRequest *httpRequest)
{
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
}


///////////////////////////////////////////////////////////////////////////////
LandDescription* RequestLandDescription(HTTPRequest *httpRequest)
{
	char *pJSON = NULL;
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
	pJSON = ( char* ) httpRequest->payload;
	pJSON[httpRequest->buffer_len] = '\0';
	return GetLandDescription(pJSON);
}


///////////////////////////////////////////////////////////////////////////////
LanderDescription* RequestLanderDescription(HTTPRequest *httpRequest)
{
	char *pJSON = NULL;
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
	pJSON = ( char* ) httpRequest->payload;
	pJSON[httpRequest->buffer_len] = '\0';
	return GetLanderDescription(pJSON);
}

///////////////////////////////////////////////////////////////////////////////
double RequestScore(HTTPRequest *httpRequest)
{
	char *pJSON = NULL;
	err_t ret_code = client_init(httpRequest);
	while(httpRequest->requestState != COMPLETE) xemacif_input(networkInterface.netif);
	pJSON = ( char* ) httpRequest->payload;
	pJSON[httpRequest->buffer_len] = '\0';
	return GetScore(pJSON);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////