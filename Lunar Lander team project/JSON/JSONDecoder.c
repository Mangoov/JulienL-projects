///////////////////////////////////////////////////////////////////////////
/// @file GameStructures.h
/// @date 2013-11
/// @description Sérialisation des structures de données du jeu à partir du serveur Web.
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#include "JSONDecoder.h"

/* Defines */
#define ANONYME "anonyme"
#define ANONYME_LEN strlen("anonyme")

////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LoadJSON
//						À Partir d'un châine de caractère contenant un objet JSON, initialise un pointeur vers un arbre json_t.
// PARAMETRES: 			text: Corps de la requête HTTP qui contient l'objet JSON qui décrit un tableau.
// VALEUR DE RETOUR:    NULL en cas d'erreur, sinon un pointeur sur la structure représentant l'arbre json_t.
// REMARQUE:            Appelé lors de la sérialisation de l'objet à partir d'un objet JSON représentant un tableau.
//						Le buffer text sera désalloué à la fin de la fonction.
////////////////////////////////////////////////////////////////////////////////
static json_t* LoadJSON(char *text)
{
	json_error_t error;
	json_t *root = json_loads(text, 0, &error);

	if(!root)
	{
		fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
		return NULL;
	}

	if(!json_is_object(root))
	{
		fprintf(stderr, "error: root is not an object\n");
		json_decref(root);
		return NULL;
	}

	return root;
}


///////////////////////////////////////////////////////////////////////////
char* Author(json_t *author)
{
	char *pchAuthor;
	if(!author)
	{
		pchAuthor = (char*) malloc(ANONYME_LEN);
		strcpy(pchAuthor, ANONYME);
	}
	else
	{
		pchAuthor = (char*) malloc( strlen( (char* )json_string_value(author) ) );
		strcpy(pchAuthor, (char* )json_string_value(author));
	}
	return pchAuthor;
}


///////////////////////////////////////////////////////////////////////////
int TimeLimit(json_t *timeLimit)
{
	int iTimeLimit;
	if(!timeLimit)
	{
		iTimeLimit = 0;
	}
	else
	{
		iTimeLimit = json_integer_value(timeLimit);
	}
	return iTimeLimit;
}


///////////////////////////////////////////////////////////////////////////
void _InitializeBoundaries(json_t *boundaries, Boundaries **ppBoundaries)
{
	size_t i = 0, j = 0;
	json_t *data, *element, *horizon, *vertical;
	int point[2];
	int iHorizon, iVertical;
	json_array_foreach(boundaries, i, data)
	{
		json_array_foreach(data, j, element)
		{
			point[j] = json_integer_value(element);
		}
		ppBoundaries[i]->horizon = point[0];
		ppBoundaries[i]->vertical = point[1];
	}
}


///////////////////////////////////////////////////////////////////////////
void _InitializePlatforms(json_t *platforms, Platforms **ppPlatforms)
{
	size_t i = 0;
	json_t *data, *ptIndexLeft, *valeur;
	int iPtIndexLeft, iValue;
	json_array_foreach(platforms, i, data)
	{
		ptIndexLeft = json_object_get(data, "ptIndexLeft");
		valeur = json_object_get(data, "value");
		iPtIndexLeft = json_integer_value(ptIndexLeft);
		iValue= json_integer_value(valeur);
		ppPlatforms[i]->ptIndexLeft = iPtIndexLeft;
		ppPlatforms[i]->value = iValue;
	}
}


///////////////////////////////////////////////////////////////////////////
LevelDescription* GetLevelDescription(char *text)
{
	json_t *root, *data;
	json_t *name, *author, *landId, *landerId, *landerInitPos, *landerInitSpeed, *landerInitFuel, *timeLimit;
	LevelDescription *levelDescription = NULL;

	char *pchName, *pchAuthor, *pchLandId, *pchLanderId;
	LanderPosition stlanderInitPos;
	LanderSpeed stlanderInitSpeed;
	float x, y, flLanderInitFuel;
	int top, left, iTimeLimit;

	root = LoadJSON(text);
	free(text);

	if(root)
	{
		name = json_object_get(root, "name");
		author = json_object_get(root, "author");
		landId = json_object_get(root, "landId");
		landerId = json_object_get(root, "landerId");
		landerInitPos = json_object_get(root, "landerInitPos");
		landerInitSpeed = json_object_get(root, "landerInitSpeed");
		landerInitFuel = json_object_get(root, "landerInitFuel");
		timeLimit = json_object_get(root, "timeLimit");

		pchName = (char* ) malloc ( strlen ( (char* )json_string_value(name) ) );
		pchLandId = (char* ) malloc ( strlen ( (char* )json_string_value(landId) ) );
		pchLanderId = (char* ) malloc ( strlen ( (char* )json_string_value(landerId) ) );
		strcpy(pchName, (char* )json_string_value(name));
		strcpy(pchLandId, (char* )json_string_value(landId));
		strcpy(pchLanderId, (char* )json_string_value(landerId));
		pchAuthor = Author(author);
		flLanderInitFuel = json_number_value(landerInitFuel);
		iTimeLimit = TimeLimit(timeLimit);

		data = json_object_get(landerInitPos, "left");
		left = json_integer_value(data);
		data = json_object_get(landerInitPos, "top");
		top = json_integer_value(data);

		data = json_object_get(landerInitSpeed, "x");
		x = json_real_value(data);
		data = json_object_get(landerInitSpeed, "y");
		y = json_real_value(data);

		stlanderInitPos.left = left;
		stlanderInitPos.top = top;
		stlanderInitSpeed.x = x;
		stlanderInitSpeed.y = y;

		json_decref(root);

		levelDescription = LevelDescription_new(
				pchName,
				pchAuthor,
				pchLandId,
				pchLanderId,
				stlanderInitPos,
				stlanderInitSpeed,
				flLanderInitFuel,
				iTimeLimit
			);
	}

	return levelDescription;
}


///////////////////////////////////////////////////////////////////////////
LandDescription* GetLandDescription(char *text)
{
	size_t arr_boundaries_len = 0, arr_platforms_len = 0;
	json_t *root, *name, *author, *imgId, *gravity, *boundaries, *platforms;
	LandDescription *landDescription = NULL;

	char *pchName, *pchAuthor, *pchImgId;
	float flGravity;
	Boundaries **ppBoundaries = NULL;
	Platforms **ppPlatforms = NULL;

	root = LoadJSON(text);
	free(text);

	if(root)
	{
		name = json_object_get(root, "name");
		author = json_object_get(root, "author");
		imgId = json_object_get(root, "imgId");
		gravity = json_object_get(root, "gravity");
		boundaries = json_object_get(root, "boundaries");
		platforms = json_object_get(root, "platforms");

		/**/
		arr_boundaries_len 	= json_array_size(boundaries);
		arr_platforms_len 	= json_array_size(platforms);

		ppBoundaries = CreateBoundries(arr_boundaries_len);
		ppPlatforms = CreatePlatforms(arr_platforms_len);

		pchName = (char* ) malloc ( strlen ( (char* )json_string_value(name) ) );
		pchImgId = (char* ) malloc ( strlen ( (char* )json_string_value(imgId) ) );
		strcpy(pchName, (char* )json_string_value(name));
		strcpy(pchImgId, (char* )json_string_value(imgId));
		pchAuthor = Author(author);
		flGravity = json_number_value(gravity);

		_InitializeBoundaries(boundaries, ppBoundaries);
		_InitializePlatforms(platforms, ppPlatforms);
		/**/

		json_decref(root);

		landDescription = LandDescription_new(
				pchName,
				pchAuthor,
				pchImgId,
				flGravity,
				ppBoundaries,
				ppPlatforms,
				arr_boundaries_len,
				arr_platforms_len
				);
		}

		return landDescription;
}


///////////////////////////////////////////////////////////////////////////
LanderDescription* GetLanderDescription(char *text)
{
	json_t *root, *data;
	json_t *name, *author, *netMass, *dimensions, *exhaustSpeed, *fuelExpense, *breakdownSpeed;
	LanderDescription *landerDescription = NULL;

	char *pchName, *pchAuthor;
	Dimensions structDimensions;
	int width, height, iNetMass, iExhaustSpeed, iFuelExpense;
	float flBreakdownSpeed;

	root = LoadJSON(text);
	free(text);

	if(root)
	{
		name = json_object_get(root, "name");
		author = json_object_get(root, "author");
		netMass = json_object_get(root, "netMass");
		dimensions = json_object_get(root, "dimensions");
		exhaustSpeed = json_object_get(root, "exhaustSpeed");
		fuelExpense = json_object_get(root, "fuelExpense");
		breakdownSpeed = json_object_get(root, "breakdownSpeed");

		/**/
		pchName = (char*) malloc ( strlen ( (char* )json_string_value(name) ) );
		strcpy(pchName, (char*)json_string_value(name) );
		pchAuthor = Author(author);
		iNetMass = json_integer_value(netMass);

		data = json_object_get(dimensions, "width");
		width = json_integer_value(data);
		data = json_object_get(dimensions, "height");
		height = json_integer_value(data);
		structDimensions.width = width;
		structDimensions.height = height;

		iExhaustSpeed = json_integer_value(exhaustSpeed);
		iFuelExpense = json_integer_value(fuelExpense);
		flBreakdownSpeed = json_number_value(breakdownSpeed);
		/**/

		json_decref(root);

		landerDescription = LanderDescription_new(
				pchName,
				pchAuthor,
				iNetMass,
				structDimensions,
				iExhaustSpeed,
				iFuelExpense,
				flBreakdownSpeed
				);
	}

	return landerDescription;
}


///////////////////////////////////////////////////////////////////////////
GlobalConfiguration* GetGlobalConfiguration(char *text)
{
	json_t *root, *landResolution;
	float flLandResolution;
	GlobalConfiguration *globalConfiguration = NULL;

	root = LoadJSON(text);
	free(text); text = NULL;

	if(root)
	{
		landResolution = json_object_get(root, "landResolution");
		flLandResolution = json_number_value(landResolution);

		json_decref(root);

		globalConfiguration = GlobalConfiguration_new(flLandResolution);
	}

	return globalConfiguration;
}


///////////////////////////////////////////////////////////////////////////
SummaryDescription* GetSummaryDescription(char *text)
{
	json_t *root, *id, *name, *author, *landerInitFuel, *timeLimit, *topScore;
	SummaryDescription *summaryDescription = NULL;

	char *pchId, *pchName, *pchAuthor;
	float flLanderInitFuel;
	int iTimeLimit, iTopScore;

	root = LoadJSON(text);
	free(text); text = NULL;

	if(root)
	{
		id = json_object_get(root, "id");
		name = json_object_get(root, "name");
		author = json_object_get(root, "author");
		landerInitFuel = json_object_get(root, "landerInitFuel");
		timeLimit = json_object_get(root, "timeLimit");
		topScore = json_object_get(root, "topScore");

		pchId = (char* ) malloc ( strlen ( (char* )json_string_value(id) ) );
		pchName = (char* ) malloc ( strlen ( (char* )json_string_value(name) ) );
		strcpy(pchId, (char* )json_string_value(id));
		strcpy(pchName, (char* )json_string_value(name));
		pchAuthor = Author(author);
		flLanderInitFuel = json_number_value(landerInitFuel);
		iTimeLimit = json_integer_value(timeLimit);
		iTopScore = json_integer_value(topScore);

		json_decref(root);

		summaryDescription = SummaryDescription_new(
				pchId,
				pchName,
				pchAuthor,
				flLanderInitFuel,
				iTimeLimit,
				iTopScore
				);
		}

	return summaryDescription;
}


////////////////////////////////////////////////////////////////////////////////
const char* PackGameData(GameData *gameData)
{
	json_t *root = json_pack("{s:s, s:i, s:f, s:i, s:i}",
			"playerName", gameData->playerName,
			"totalTime", gameData->totalTime,
			"fuelLeft", gameData->fuelLeft,
			"nbPlatforms", gameData->nbPlatforms,
			"totalValue", gameData->totalValue
			);

	return json_string_value(root);;
}


////////////////////////////////////////////////////////////////////////////////
LevelsSummary** GetLevelsSummary(char *text, size_t *arrLen)
{
	size_t i = 0;
	json_error_t error;
	json_t *root, *data, *id, *name, *author, *landerInitFuel, *timeLimit, *topScore;
	LevelsSummary **levelsSummary = NULL;

	char *pchId, *pchName, *pchAuthor;
	int iTimeLimit;
	float flLanderInitFuel;

	root = json_loads(text, 0, &error);
	free(text);

	if(!json_is_array(root))
	{
		fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
		return 0;
	}
	else
	{
		*arrLen = json_array_size(root);
		levelsSummary = CreateLevelSummaryArray(*arrLen);
		json_array_foreach(root, i, data)
		{
			id = json_object_get(data, "id");
			name = json_object_get(data, "name");
			author = json_object_get(data, "author");
			landerInitFuel = json_object_get(data, "landerInitFuel");
			timeLimit = json_object_get(data, "timeLimit");
			topScore = json_object_get(data, "topScore");

			pchId = (char* ) malloc ( strlen ( (char* )json_string_value(id) ) );
			pchName = (char* ) malloc ( strlen ( (char* )json_string_value(name) ) );
			strcpy(pchId, (char* )json_string_value(id) );
			strcpy(pchName, (char* )json_string_value(name) );
			pchAuthor = Author(author);
			flLanderInitFuel = json_number_value(landerInitFuel);
			iTimeLimit = json_integer_value(timeLimit);
			if(topScore)
			{
				topScore = json_integer_value("topScore");
			}
			else
			{
				topScore = 0;
			}

			levelsSummary[i] = LevelsSummary_new(
					pchId,
					pchName,
					pchAuthor,
					flLanderInitFuel,
					iTimeLimit,
					topScore
					);
		}

		json_decref(root);

		return levelsSummary;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
double GetScore(char *text)
{
	json_t *root, *data;

	double score;

	root = LoadJSON(text);
	free(text);

	if(root)
	{
		data = json_object_get(root, "score");
		score = json_number_value(data);
		json_decref(root);

	}
	return score;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
