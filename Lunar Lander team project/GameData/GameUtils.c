///////////////////////////////////////////////////////////////////////////
/// @file GameUtils.c
/// @date 2013-11
/// @description Fonctions utilitaires pour gérer les structures de données du jeu
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

/* Includes */
#include "GameUtils.h"

///////////////////////////////////////////////////////////////////////////
LevelDescription* LevelDescription_new
(
		char *name,
		char *author,
		char *landId,
		char *landerId,
		LanderPosition landerInitPos,
		LanderSpeed landerInitSpeed,
		float landerInitFuel,
		int timeLimit
)
{
	LevelDescription *levelDescription = (LevelDescription *) malloc (sizeof(LevelDescription));

	if(levelDescription)
	{
		levelDescription->name = name;
		levelDescription->author = author;
		levelDescription->landId = landId;
		levelDescription->landerId = landerId;
		levelDescription->landerInitPos.left = landerInitPos.left;
		levelDescription->landerInitPos.top = landerInitPos.top;
		levelDescription->landerInitSpeed.x = landerInitSpeed.x;
		levelDescription->landerInitSpeed.y = landerInitSpeed.y;
		levelDescription->landerInitFuel = landerInitFuel;
		levelDescription->timeLimit = timeLimit;
		return levelDescription;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void LevelDescription_free(LevelDescription* levelDescription)
{
	free (levelDescription->name); levelDescription->name = NULL;
	free (levelDescription->author); levelDescription->author = NULL;
	free (levelDescription->landId); levelDescription->landId = NULL;
	free (levelDescription->landerId); levelDescription->landerId = NULL;
	free (levelDescription);
	levelDescription = NULL;
}


///////////////////////////////////////////////////////////////////////////
LandDescription* LandDescription_new
(
		char *name,
		char *author,
		char *imgId,
		float gravity,
		Boundaries **boundaries,
		Platforms **platforms,
		unsigned int arr_boundaries_len,
		unsigned int arr_platforms_len
)
{
	LandDescription *landDescription = (LandDescription*) malloc (sizeof(LandDescription));

	if(landDescription)
	{
		landDescription->name = name;
		landDescription->author = author;
		landDescription->imgId = imgId;
		landDescription->gravity = gravity;
		landDescription->boundaries = boundaries;
		landDescription->platforms = platforms;
		landDescription->arr_boundaries_len = arr_boundaries_len;
		landDescription->arr_platforms_len = arr_platforms_len;
		return landDescription;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void LandDescription_free(LandDescription* landDescription)
{
	unsigned int i = 0;

	/* Boundaries */
	for(i = 0; i < landDescription->arr_boundaries_len; ++i)
	{
		free(landDescription->boundaries[i]);
	}

	free(landDescription->boundaries);

	/* Platforms */
	for(i = 0; i < landDescription->arr_platforms_len; ++i)
	{
		free(landDescription->platforms[i]);
	}
	free(landDescription->platforms);

	free (landDescription->name); landDescription->name = NULL;
	free (landDescription->author); landDescription->author = NULL;
	free (landDescription->imgId); landDescription->imgId = NULL;

	free(landDescription);
}


///////////////////////////////////////////////////////////////////////////
Boundaries** CreateBoundries(unsigned int arr_boundaries_len)
{
	Boundaries **boundaries;
	unsigned int i = 0;

		/* arr_boundaries_len is the number of rows */
	boundaries = ( Boundaries** ) malloc ( arr_boundaries_len * sizeof( Boundaries* ));
		if ( boundaries == NULL )
		{ /* error */ }
		for ( i = 0; i < arr_boundaries_len; ++i )
		{
		  /* x_i here is the size of given row, no need to
		   * multiply by sizeof( char ), it's always 1
		   */
			boundaries[i] = ( Boundaries* )malloc( sizeof(Boundaries) );
			if(boundaries[i] == NULL )
			{ /* error */ }
		}

		return boundaries;
}


///////////////////////////////////////////////////////////////////////////
Platforms** CreatePlatforms(unsigned int arr_platforms_len)
{
	Platforms **platforms;
	unsigned int i = 0;

	/* arr_boundaries_len is the number of rows */
	platforms = ( Platforms** ) malloc ( arr_platforms_len * sizeof( Platforms* ));
	if ( platforms == NULL )
	{ /* error */ }
	for ( i = 0; i < arr_platforms_len; ++i )
	{
	  /* x_i here is the size of given row, no need to
	   * multiply by sizeof( char ), it's always 1
	   */
		platforms[i] = ( Platforms* )malloc( sizeof(Platforms) );
		if(platforms[i] == NULL )
		{ /* error */ }
	}
	return platforms;
}


///////////////////////////////////////////////////////////////////////////
LanderDescription* LanderDescription_new
(
		char *name,
		char *author,
		int netMass,
		Dimensions dimensions,
		int exhaustSpeed,
		int fuelExpense,
		float breakdownSpeed
)
{
	LanderDescription* landerDescription = (LanderDescription*) malloc (sizeof(LanderDescription));

	if(landerDescription)
	{
		landerDescription->name = name;
		landerDescription->author = author;
		landerDescription->netMass = netMass;
		landerDescription->dimensions.height = dimensions.height;
		landerDescription->dimensions.width = dimensions.width;
		landerDescription->exhaustSpeed = exhaustSpeed;
		landerDescription->fuelExpense = fuelExpense;
		landerDescription->breakdownSpeed = breakdownSpeed;
		return landerDescription;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void landerDescription_free(LanderDescription *landerDescription)
{
	free (landerDescription->name); landerDescription->name = NULL;
	free (landerDescription->author); landerDescription->author = NULL;
	landerDescription = NULL;
}

///////////////////////////////////////////////////////////////////////////
GlobalConfiguration* GlobalConfiguration_new(float landResolution)
{
	GlobalConfiguration*  globalConfiguration = (GlobalConfiguration*) malloc (sizeof(GlobalConfiguration));

	if(globalConfiguration)
	{
		globalConfiguration->landResolution = landResolution;
		return globalConfiguration;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void GlobalConfiguration_free(GlobalConfiguration *globalConfiguration)
{
	free (globalConfiguration);
	globalConfiguration = NULL;
}


///////////////////////////////////////////////////////////////////////////
SummaryDescription* SummaryDescription_new
(
		char *id,
		char *name,
		char *author,
		float landerInitFuel,
		int timeLimit,
		int topScore
)
{
	SummaryDescription* summaryDescription = (SummaryDescription*) malloc (sizeof(SummaryDescription));

	if(summaryDescription)
	{
		summaryDescription->id 	= id;
		summaryDescription->name = name;
		summaryDescription->author = author;
		summaryDescription->landerInitFuel = landerInitFuel;
		summaryDescription->timeLimit = timeLimit;
		summaryDescription->topScore = topScore;
		return summaryDescription;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void SummaryDescription_free(SummaryDescription* summaryDescription)
{
	free (summaryDescription->id); summaryDescription->id = NULL;
	free (summaryDescription->name); summaryDescription->name = NULL;
	free (summaryDescription->author); summaryDescription->author = NULL;
	free (summaryDescription);
	summaryDescription = NULL;
}


///////////////////////////////////////////////////////////////////////////
GameData* GameData_new(
		char *playerName,
		int totalTime,
		float fuelLeft,
		int nbPlatforms,
		int totalValue
)
{
	GameData* gameData = (GameData*) malloc (sizeof(GameData));

	if(gameData)
	{
		gameData->playerName = playerName;
		gameData->totalTime = totalTime;
		gameData->fuelLeft = fuelLeft;
		gameData->nbPlatforms = nbPlatforms;
		gameData->totalValue = totalValue;
		return gameData;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void GameData_free(GameData* gameData)
{
	free (gameData->playerName);
	free (gameData);
	gameData = NULL;
}


///////////////////////////////////////////////////////////////////////////
LevelsSummary* LevelsSummary_new
(
		char *id,
		char *name,
		char *author,
		float landerInitFuel,
		int timeLimit,
		int score
)
{

	LevelsSummary* levelsSummary = (LevelsSummary*) malloc (sizeof(LevelsSummary));

	if(levelsSummary)
	{
		levelsSummary->id = id;
		levelsSummary->name = name;
		levelsSummary->author = author;
		levelsSummary->landerInitFuel = landerInitFuel;
		levelsSummary->timeLimit = timeLimit;
		levelsSummary->score = score;
		return levelsSummary;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////////
void LevelsSummary_free(LevelsSummary *levelsSummary)
{
	free (levelsSummary->id);		levelsSummary->id = NULL;
	free (levelsSummary->name);		levelsSummary->name = NULL;
	free (levelsSummary->author);	levelsSummary->author = NULL;
}


///////////////////////////////////////////////////////////////////////////
LevelsSummary** CreateLevelSummaryArray(unsigned int array_len)
{
	LevelsSummary** arrlevelsSummary;
	unsigned int i = 0;

	/* arr_boundaries_len is the number of rows */
	arrlevelsSummary = ( LevelsSummary** ) malloc ( array_len * sizeof( LevelsSummary* ));
	if ( arrlevelsSummary == NULL )
	{ /* error */ }
	for ( i = 0; i < array_len; ++i )
	{
		/* x_i here is the size of given row, no need to
		 * multiply by sizeof( char ), it's always 1
		 */
		arrlevelsSummary[i] = ( LevelsSummary* )malloc( sizeof(LevelsSummary) );
		if(arrlevelsSummary[i] == NULL )
		{ /* error */ }
	}

	return arrlevelsSummary;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
