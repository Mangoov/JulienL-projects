#include "NetworkInterface.h"
#include "../HTTP/HTTPRequestMethods.h"

// Upper 6 bytes of MAC - Digilent Ethernet OUI = 00-18-3e
#define DIGILENT_MAC_OUI0 0x00
#define DIGILENT_MAC_OUI1 0x18
#define DIGILENT_MAC_OUI2 0x3e

// Client/Server informations
#define LOCAL_MAC		{0x00, 0x18, 0x3e, 0x00, 0x00, 0x38}	// Adresse MAC du FPGA (00:18:3e:00:00:[30-3f] )
#define LOCAL_IP		{132, 207, 89, 38}						// Adresse IP du FPGA  (132.207.89.[30-39])
#define LOCAL_SUBNET	{255, 255, 255, 0}						// Masque sous-réseau du FPGA
#define LOCAL_GATEWAY	{132, 207, 89, 1}						// Adresse IP du FPGA
#define REMOTE_IP		{132, 207, 89, 2}						// Adresse IP de serveur
#define REMOTE_PORT		9010									// Port d'écoute du serveur

#define CONTENT_LEN strlen(g_psHTTPHeaderStrings[HTTP_HDR_CONTENT_LENGTH])
#define ENDLINE_LEN strlen("\r\n\r\n")

#define BUFFER_LEN 64

unsigned char mac[6]				= LOCAL_MAC;
const unsigned char ip[4]			= LOCAL_IP;
const unsigned char subnet[4]		= LOCAL_SUBNET;
const unsigned char gateway[4]		= LOCAL_GATEWAY;
const unsigned char remote_ip[4]	= REMOTE_IP;
const short int remote_port			= REMOTE_PORT;

/**/
HTTPRequest httpRequest;
NetworkInterface networkInterface;
/**/

/* Description du tableau id */
/* Description du terrain id */
/* Description de la capsule id */
char* HTTP_GetDescription_2str(char *str, char *id)
{
	char *buffer = NULL;
    size_t needed = snprintf(NULL, 0,
    		"GET /%s/%s HTTP/1.1\r\n"
    		"Host: jupiter.info.polymtl.ca:9010\r\n"
    		"Connection: Close\r\n"
    		"\r\n", str, id) + 1;
    buffer = (char *) malloc (needed);
    snprintf(buffer, needed,
        		"GET /%s/%s HTTP/1.1\r\n"
        		"Host: jupiter.info.polymtl.ca:9010\r\n"
        		"Connection: Close\r\n"
        		"\r\n", str, id);
    return buffer;
}


////////////////////////////////////////////////////////////////////////////////
char* HTTP_GetDescription_1str(char *str)
{
	char *buffer = NULL;
    size_t needed = snprintf(NULL, 0,
    		"GET /%s HTTP/1.1\r\n"
    		"Host: jupiter.info.polymtl.ca:9010\r\n"
    		"Connection: Close\r\n"
    		"\r\n", str) + 1;
    buffer = (char *) malloc (needed);
    snprintf(buffer, needed,
        		"GET /%s HTTP/1.1\r\n"
        		"Host: jupiter.info.polymtl.ca:9010\r\n"
        		"Connection: Close\r\n"
        		"\r\n", str);
    return buffer;
}


////////////////////////////////////////////////////////////////////////////////
char* HTTP_PostDescription(char *id, char *str)
{
	char *buffer = NULL;
	unsigned int length = strlen(str);
	size_t needed = snprintf(NULL, 0,
			"POST /levels/%s/gamedata HTTP/1.1\r\n"
			"Host: jupiter.info.polymtl.ca:9010\r\n"
			"Content-Type: application/json\r\n"
	    	"Content-Length: %u\r\n"
			"\r\n"
			"%s", id, length, str) + 1;
	buffer = (char *) malloc (needed);
	snprintf(buffer, needed,
			"POST /levels/%s/gamedata HTTP/1.1\r\n"
			"Host: jupiter.info.polymtl.ca:9010\r\n"
			"Content-Type: application/json\r\n"
	    	"Content-Length: %u\r\n"
			"\r\n"
			"%s", id, length, str);
	    return buffer;
}


////////////////////////////////////////////////////////////////////////////////
char* JSON_GameData()
{
	char *buffer = NULL;
	size_t needed = snprintf(NULL, 0,
			"{\n"
			"\t\"playerName\": \"%s\",\n"
			"\t\"totalTime\": %d,\n"
			"\t\"fuelLeft\": %f,\n"
			"\t\"nbPlatforms\": %u,\n"
			"\t\"totalValue\": %u\n"
			"}",
			gameData.playerName,
			gameData.totalTime,
			gameData.fuelLeft,
			gameData.nbPlatforms,
			gameData.totalValue) + 1;
	buffer = (char *) malloc (needed);
	snprintf(buffer, needed,
				"{\n"
				"\t\"playerName\": \"%s\",\n"
				"\t\"totalTime\": %d,\n"
				"\t\"fuelLeft\": %f,\n"
				"\t\"nbPlatforms\": %u,\n"
				"\t\"totalValue\": %u\n"
				"}",
				gameData.playerName,
				gameData.totalTime,
				gameData.fuelLeft,
				gameData.nbPlatforms,
				gameData.totalValue);
	return buffer;
}


////////////////////////////////////////////////////////////////////////////////
char* AppendString(char *s1, char *s2, char *s3)
{
	char *buffer = NULL;
	size_t needed = snprintf(NULL, 0, "%s/%s/%s", s1, s2, s3) + 1;
	buffer = (char *) malloc ( needed );
	snprintf(buffer, needed, "%s/%s/%s", s1, s2, s3);
	return buffer;
}

void lwip_init(void);


////////////////////////////////////////////////////////////////////////////////
err_t close_connection(struct tcp_pcb *tpcb)
{
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  return tcp_close(tpcb);
}


////////////////////////////////////////////////////////////////////////////////
err_t lwip_config(NetworkInterface *networkInterface)
{
	IP4_ADDR(&networkInterface->ipaddr, ip[0], ip[1], ip[2], ip[3]);
	IP4_ADDR(&networkInterface->netmask, subnet[0], subnet[1], subnet[2], subnet[3]);
	IP4_ADDR(&networkInterface->gw, gateway[0], gateway[1], gateway[2], gateway[3]);
	IP4_ADDR(&networkInterface->remote_ipaddr, remote_ip[0], remote_ip[1], remote_ip[2], remote_ip[3]);

	networkInterface->netif = mem_malloc(sizeof(struct netif));
	if(NULL == networkInterface->netif)
	{
		return ERR_MEM;
	}

	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(
			networkInterface->netif,
			&networkInterface->ipaddr,
			&networkInterface->netmask,
			&networkInterface->gw,
			mac,
			PLATFORM_EMAC_BASEADDR
			)
		)
	{
		return ERR_IF;
	}

	netif_set_default(networkInterface->netif);

	netif_set_up(networkInterface->netif);

	return ERR_OK;
}


////////////////////////////////////////////////////////////////////////////////
void print_err(err_t err)
{
	char dbgprint[BUFFER_LEN] = { '\0' };

	switch(err)
	{
	case ERR_OK:
		snprintf(dbgprint, BUFFER_LEN, "none\n\r");
		break;
	case ERR_MEM:
		snprintf(dbgprint, BUFFER_LEN, "pas assez de mémoire\n\r");
		break;
	case ERR_BUF:
		snprintf(dbgprint, BUFFER_LEN, "probleme de buffer\n\r");
		break;
	case ERR_ABRT:
		snprintf(dbgprint, BUFFER_LEN, "connexion abandonnee\n\r");
		break;
	case ERR_RST:
		snprintf(dbgprint, BUFFER_LEN, "connexion remise a zero\n\r");
		break;
	case ERR_CLSD:
		snprintf(dbgprint, BUFFER_LEN, "connexion fermee\n\r");
		break;
	case ERR_CONN:
		snprintf(dbgprint, BUFFER_LEN, "pas connecte\n\r");
		break;
	case ERR_VAL:
		snprintf(dbgprint, BUFFER_LEN, "valeur illegale\n\r");
		break;
	case ERR_ARG:
		snprintf(dbgprint, BUFFER_LEN, "argument illegale\n\r");
		break;
	case ERR_RTE:
		snprintf(dbgprint, BUFFER_LEN, "probleme de routine\n\r");
		break;
	case ERR_USE:
		snprintf(dbgprint, BUFFER_LEN, "addresse deja utilisee\n\r");
		break;
	case ERR_IF:
		snprintf(dbgprint, BUFFER_LEN, "probleme d'interface reseau\n\r");
		break;
	case ERR_ISCONN:
		snprintf(dbgprint, BUFFER_LEN, "deja connecte\n\r");
		break;
	default:
		snprintf(dbgprint, BUFFER_LEN, "???\n\r");
		break;
	}
	stdout_write_char_array(dbgprint, strlen(dbgprint));
}


////////////////////////////////////////////////////////////////////////////////
void client_err(void* arg, err_t err)
{
	char dbgprint[BUFFER_LEN] = { '\0' };
	snprintf(dbgprint, BUFFER_LEN, "???\n\r");
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	print_err(err);
}


////////////////////////////////////////////////////////////////////////////////
void ResetHTTPRequest(HTTPRequest *httpRequest, RequestType requestType)
{
	httpRequest->payload 		= NULL;
	httpRequest->response 		= NONE;
	httpRequest->initialize 	= false;
	httpRequest->requestState 	= RECEIVING;
	httpRequest->requestType 	= requestType;
	httpRequest->buffer_len 	= 0;
	httpRequest->content_len 	= 0;
}


////////////////////////////////////////////////////////////////////////////////
void CheckHTTPResponseHeader(HTTPRequest *httpRequest, char *pheader)
{
	char *phttp200, *phttp400, *phttp404, *phttp405, *phttp500, *phttp501;

	phttp200 = strstr(pheader, g_psHTTPHeaderStrings[HTTP_HDR_OK]);
	phttp400 = strstr(pheader, g_psHTTPHeaderStrings[HTTP_HDR_BAD_REQUEST]);
	phttp404 = strstr(pheader, g_psHTTPHeaderStrings[HTTP_HDR_NOT_FOUND]);
	phttp405 = strstr(pheader, g_psHTTPHeaderStrings[HTTP_HDR_NOT_ALLOW]);
	phttp500 = strstr(pheader, g_psHTTPHeaderStrings[HTTP_HDR_INTERNAL_ERROR]);
	phttp501 = strstr(pheader, g_psHTTPHeaderStrings[HTTP_HDR_NOT_IMPL]);

	if(phttp200)
	{
		httpRequest->response = HTTP_200_OK;
	}
	else if(phttp400)
	{
		httpRequest->response = HTTP_400_BAD_REQUEST;
	}
	else if(phttp404)
	{
		httpRequest->response = HTTP_404_FILE_NOT_FOUND;
	}
	else if(phttp405)
	{
		httpRequest->response = HTTP_405_METHOD_NOT_ALLOW;
	}
	else if(phttp500)
	{
		httpRequest->response = HTTP_500_INTERNAL_SERVER_ERROR;
	}
	else if(phttp501)
	{
		httpRequest->response = HTTP_501_NOT_IMPLEMENTED;
	}
}


////////////////////////////////////////////////////////////////////////////////
err_t client_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *pbuf, err_t err)
{
	err_t ret_code = err;
	HTTPRequest *httpRequest = (HTTPRequest *)arg;
	void *pdata;
	char *payload, *pcontentlength;

	if(err == ERR_OK && pbuf != NULL)
	{
		payload = ( char * ) malloc ( pbuf->tot_len + 1 );
		memcpy( payload, ( char * )pbuf->payload, pbuf->tot_len );
		payload[ pbuf->tot_len ] = '\0';

		/* enregistre auprès de LwIP le nombre de données reçues. */
		tcp_recved(pcb, pbuf->tot_len);

		if(!httpRequest->initialize)
		{
			/* Check is the request produce a valid response */
			CheckHTTPResponseHeader(httpRequest, payload);

			if(httpRequest->response == HTTP_200_OK)
			{
				/* Update status variables */
				httpRequest->initialize = true;
			}
			else { /* Error */
				httpRequest->requestState = COMPLETE;
				ret_code = close_connection(pcb);
			}
		}
		else if(httpRequest->content_len == 0){ /* Pas encore reçu content length*/
			/* will point to start of 'Content-Length' header */
			pcontentlength = strstr((char*)pbuf->payload, g_psHTTPHeaderStrings[HTTP_HDR_CONTENT_LENGTH]);

			if(pcontentlength)
			{
				pcontentlength += CONTENT_LEN;

				/* get the length of the data */
				httpRequest->content_len = atoi(pcontentlength);

				/* Initialize a buffer to hold the payload (+1 for the NULL char to be able to parse JSON strings) */
				httpRequest->payload = ( void* ) malloc ( httpRequest->content_len + 1 );

				/* will point to start of data */
				pdata = strstr(payload, "\r\n\r\n");

				if(pdata)
				{
					pdata += ENDLINE_LEN;

					/* Copy data */
					httpRequest->buffer_len = ((size_t) payload + pbuf->tot_len - (size_t) pdata);
					memcpy(httpRequest->payload, (void *)pdata, httpRequest->buffer_len);
				}
			}
		}
		else { /* Append data*/
			memcpy(httpRequest->payload + httpRequest->buffer_len, pbuf->payload, pbuf->tot_len);
			httpRequest->buffer_len += pbuf->tot_len;
		}

		/* libère le paquet reçu. */
		free (payload);
		pbuf_free(pbuf);
	}
	else { /* LAST_ACK */
		httpRequest->requestState = COMPLETE;
		ret_code = close_connection(pcb);
	}

	return ret_code;
}


////////////////////////////////////////////////////////////////////////////////
err_t client_connected(void *arg, struct tcp_pcb *pcb, err_t err)
{
	struct pbuf *pbuf = NULL;
	err_t ret_code = ERR_OK;
	HTTPRequest *httpRequest = (HTTPRequest *)arg;
	unsigned int bufferlength = 0;

	if(ERR_OK == err)
	{
		bufferlength = strlen(httpRequest->request);
		pbuf = pbuf_alloc(PBUF_TRANSPORT, bufferlength, PBUF_RAM);
		if(pbuf != NULL)
		{
			/*puts(httpRequest->request);*/
			strcpy((char*)pbuf->payload, httpRequest->request);
			(void) tcp_write(pcb, pbuf->payload, pbuf->len, 1);
			pbuf_free(pbuf);
		}
	}
	else
	{
		ret_code = err;
	}

	return ret_code;
}


////////////////////////////////////////////////////////////////////////////////
int client_init(void *arg)
{
	char dbgprint[BUFFER_LEN] = { '\0' };

	err_t ret_code = ERR_OK;

	networkInterface.pcb = tcp_new();
	if(NULL == networkInterface.pcb) {
		snprintf(dbgprint, BUFFER_LEN, "tcp_new(): echec.\n\r");
		stdout_write_char_array(dbgprint, strlen(dbgprint));
		return -1;
	}

	tcp_arg(networkInterface.pcb, arg);

	/* Enregistrement des callbacks */
	tcp_err(networkInterface.pcb, client_err);
	tcp_recv(networkInterface.pcb, client_recv);
	tcp_sent(networkInterface.pcb, client_sent);

	ret_code = tcp_connect(networkInterface.pcb, &networkInterface.remote_ipaddr, remote_port, client_connected);

	if(ERR_OK != ret_code)
	{
		return -1;
	}

	return 0;
}

err_t client_sent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
	/*NET_PRINT("Donnees emises par le client : 0x%X\n", len);*/
	return ERR_OK;
}


////////////////////////////////////////////////////////////////////////////////
void PrintPossibleMap()
{
	char msg[32];
	HTTPRequest httpRequest;
	size_t i = 0;

	ResetHTTPRequest(&httpRequest, JSON);
	httpRequest.request = g_psHTTPGETLevels;
	summary.arrLevelsSummary = RequestLevelsSummary(&httpRequest, &summary.levelSummaryArrayLen);

	snprintf(msg, BUFFER_LEN, "\nListe des tableaux possibles:\n");
	stdout_write_char_array(msg, strlen(msg));
	for(i = 0; i < summary.levelSummaryArrayLen; i++)
	{
		snprintf(msg, BUFFER_LEN, "\t@%s\n", summary.arrLevelsSummary[i]->id);
		stdout_write_char_array(msg, strlen(msg));
	}
}


////////////////////////////////////////////////////////////////////////////////
void PrintNetworkParameters()
{
	char dbgprint[BUFFER_LEN] = { '\0' };

	/* Paramètres de l'interface réseau */
	snprintf(dbgprint, BUFFER_LEN, "\t@ MAC   : %x:%x:%x:%x:%x:%x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	stdout_write_char_array(dbgprint, strlen(dbgprint));

	snprintf(dbgprint, BUFFER_LEN, "\t@ IP    : %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
	stdout_write_char_array(dbgprint, strlen(dbgprint));

	snprintf(dbgprint, BUFFER_LEN, "\tNetmask : %d.%d.%d.%d\n", subnet[0], subnet[1], subnet[2], subnet[3]);
	stdout_write_char_array(dbgprint, strlen(dbgprint));

	snprintf(dbgprint, BUFFER_LEN, "\tGateway : %d.%d.%d.%d\n", gateway[0], gateway[1], gateway[2], gateway[3]);
	stdout_write_char_array(dbgprint, strlen(dbgprint));

	snprintf(dbgprint, BUFFER_LEN, "\t@ IP distante : %d.%d.%d.%d\n", remote_ip[0], remote_ip[1], remote_ip[2], remote_ip[3]);
	stdout_write_char_array(dbgprint, strlen(dbgprint));

	snprintf(dbgprint, BUFFER_LEN, "\tPort distant  : %d\n\n", remote_port);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
}


////////////////////////////////////////////////////////////////////////////////
err_t InitNetworkInterface()
{
	char dbgprint[BUFFER_LEN] = { '\0' };
	err_t ret_code;

	ret_code = lwip_config(&networkInterface);
	if(ret_code != ERR_OK)
	{
		snprintf(dbgprint, BUFFER_LEN, "Configuration de lwIP : FAIL\n");
		stdout_write_char_array(dbgprint, strlen(dbgprint));
	}
	else
	{
		snprintf(dbgprint, BUFFER_LEN, "Configuration de lwIP : OK\n");
		stdout_write_char_array(dbgprint, strlen(dbgprint));
		PrintNetworkParameters();
	}


	return ret_code;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadGlobalConfiguration()
{
	char dbgprint[BUFFER_LEN] = { '\0' };; snprintf(dbgprint, 128, "\t@ global configuration\n");
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, JSON);
	httpRequest.request = g_psHTTPGETGlobalConfig;
	globalConfiguration = RequestGlobalConfiguration(&httpRequest);
}


////////////////////////////////////////////////////////////////////////////////
void DownloadLevel(const unsigned char *id, Application *pApp)
{
	char *pHTTPGETString = NULL;
	char dbgprint[BUFFER_LEN] = { '\0' };; snprintf(dbgprint, 128, "\t@ levels %s\n", id);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, JSON);
	pHTTPGETString = HTTP_GetDescription_2str("levels", id);
	httpRequest.request = pHTTPGETString;
	pApp->levelDescription = RequestLevelDescription(&httpRequest);
	free(pHTTPGETString); pHTTPGETString = NULL;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadLevelPreview(const unsigned char *id, Bitmap *pPreviewBMP)
{
	char *pHTTPGETString = NULL, *pPathStr = NULL;
	char dbgprint[BUFFER_LEN] = { '\0' };; snprintf(dbgprint, 128, "\t@ levels %s preview\n", id);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, BMP);
	pPathStr = AppendString("levels", id, "preview");
	pHTTPGETString = HTTP_GetDescription_1str(pPathStr);
	httpRequest.request = pHTTPGETString;
	RequestBitmap(&httpRequest);
	if(httpRequest.response == HTTP_200_OK)
	{
		DecodeBitmap(httpRequest.payload, pPreviewBMP);
	}
	free(pPathStr); pPathStr = NULL;
	free(pHTTPGETString); pHTTPGETString = NULL;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadLand(Application *pApp)
{
	char *pHTTPGETString = NULL;
	char dbgprint[BUFFER_LEN] = { '\0' };; snprintf(dbgprint, 128, "\t@ land %s bitmap image\n", pApp->levelDescription->landId);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, JSON);
	pHTTPGETString = HTTP_GetDescription_2str("lands", pApp->levelDescription->landId);
	httpRequest.request = pHTTPGETString;
	pApp->landDescription = RequestLandDescription(&httpRequest);
	free(pHTTPGETString); pHTTPGETString = NULL;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadLandBackground(Application *pApp, Bitmap *pLandBMP)
{
	char *pHTTPGETString = NULL, *pPathStr = NULL;
	char dbgprint[BUFFER_LEN] = { '\0' };; snprintf(dbgprint, 128, "\t@ levels %s bitmap image\n", pApp->landDescription->imgId);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, BMP);
	pPathStr = AppendString("lands", "bg", pApp->landDescription->imgId);
	pHTTPGETString = HTTP_GetDescription_1str(pPathStr);
	httpRequest.request = pHTTPGETString;
	RequestBitmap(&httpRequest);
	if(httpRequest.response == HTTP_200_OK)
	{
		DecodeBitmap(httpRequest.payload, pLandBMP);
	}
	free(pPathStr); pPathStr = NULL;
	free(pHTTPGETString); pHTTPGETString = NULL;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadLander(Application *pApp)
{
	char *pHTTPGETString = NULL;
	char dbgprint[BUFFER_LEN] = { '\0' }; snprintf(dbgprint, 128, "\t@ lander %s\n", pApp->levelDescription->landerId);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, JSON);
	pHTTPGETString = HTTP_GetDescription_2str("landers", pApp->levelDescription->landerId);
	httpRequest.request = pHTTPGETString;
	pApp->landerDescription = RequestLanderDescription(&httpRequest);
	free(pHTTPGETString); pHTTPGETString = NULL;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadLanderImage(Application *pApp, Bitmap *pLanderBMP)
{
	char *pHTTPGETString = NULL, *pPathStr = NULL;
	char dbgprint[BUFFER_LEN] = { '\0' }; snprintf(dbgprint, 128, "\t@ lander %s bitmap image\n", pApp->levelDescription->landerId);
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, BMP);
	pPathStr = AppendString("landers", pApp->levelDescription->landerId, "img");
	pHTTPGETString = HTTP_GetDescription_1str(pPathStr);
	httpRequest.request = pHTTPGETString;
	RequestBitmap(&httpRequest);
	if(httpRequest.response == HTTP_200_OK)
	{
		DecodeBitmap(httpRequest.payload, pLanderBMP);
	}
	free(pPathStr); pPathStr = NULL;
	free(pHTTPGETString); pHTTPGETString = NULL;
}


////////////////////////////////////////////////////////////////////////////////
void DownloadApplicationData()
{
	char dbgprint[BUFFER_LEN] = { '\0' }; snprintf(dbgprint, BUFFER_LEN, "Downlading application data: IN PROGRESS\n");
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	/**/
	size_t i = 0;
	DownloadGlobalConfiguration();
	for(i = 0; i < summary.levelSummaryArrayLen; ++i)
	{
		DownloadLevel(summary.arrLevelsSummary[i]->id, ppApp[i]);
		DownloadLevelPreview(summary.arrLevelsSummary[i]->id, ppPreviewBMP[i]);
		DownloadLand(ppApp[i]);
		DownloadLandBackground(ppApp[i], ppLandBMP[i]);
		DownloadLander(ppApp[i]);
		DownloadLanderImage(ppApp[i], ppLanderBMP[i]);
	}
	/**/
	snprintf(dbgprint, BUFFER_LEN, "Downlading application data: COMPLETE\n");
	stdout_write_char_array(dbgprint, strlen(dbgprint));
}


////////////////////////////////////////////////////////////////////////////////
double SendGameData(char* id)
{
	char dbgprint[BUFFER_LEN] = { '\0' }; snprintf(dbgprint, BUFFER_LEN, "Sending game data: IN PROGRESS\n");
	double score;
	char *jsonstr;
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	ResetHTTPRequest(&httpRequest, JSON);
	jsonstr = JSON_GameData();
	httpRequest.request = HTTP_PostDescription(id, jsonstr);
	/**/
	score = RequestScore(&httpRequest);
	/**/
	free(jsonstr); jsonstr = NULL;
	free(httpRequest.request); httpRequest.request = NULL;
	snprintf(dbgprint, BUFFER_LEN, "Sending game data: COMPLETE\n");
	stdout_write_char_array(dbgprint, strlen(dbgprint));
	return score;
}


////////////////////////////////////////////////////////////////////////////////
Application** AllocApplication(size_t arr_app_len)
{
	Application **appli;
	unsigned int i = 0;

	/* arr_boundaries_len is the number of rows */
	appli = ( Application** ) malloc ( arr_app_len * sizeof( Application* ));
	if ( appli == NULL )
	{ /* error */ }
	for ( i = 0; i < arr_app_len; ++i )
	{
		appli[i] = ( Application* )malloc( sizeof(Application) );
		if(appli[i] == NULL )
		{ /* error */ }
	}

	return appli;
}


////////////////////////////////////////////////////////////////////////////////
int LevelIdToInt(unsigned char *id)
{
	size_t i = 0;
	for(i = 0; i < summary.levelSummaryArrayLen; ++i)
	{
		if(strcmp((char*)id, summary.arrLevelsSummary[i]->id) == 0)
		{
			return i;
		}
	}
	return -1;
}
