///////////////////////////////////////////////////////////////////////////
/// @file TAR.h
/// @date 2013-11
/// @description Définition des fontions pour le décodage d'une archive TAR.
/// @version 1.0
///	@date 2013-12
/// @description Décodage WAVE déficient besoins de plus d'informations pour jouer les Sample + fonctions utilitaire pour jouer le son.
///	@version 1.1
/// Ajout des fonctions: InitCurrentSound, decodeTarOctal, getFileSize, IsEndOfTarFile, DecodeWave, ProcessSound, LoadSound, PlaySound.
///	Ajout des structures: SoundState, TARFileHeader, wav_hdr, WAV_FILE_TYPE, Sound, WaveFile, TARArchive.
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef TAR_H_
#define TAR_H_

/* INCLUDES */
#include "../Configuration/platform.h"
#include "../src/typedef.h"
#include <xbasic_types.h>
#include <xtft.h>
#include <xio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* DEFINES */
#define ASCII_TO_NUMBER(num) ((num)-48)
#define TAR_OFFSET_NAME  124
#define TAR_OFFSET_SIZE  0
#define TAR_HEADER  512
#define XPAR_EMC_0_MENO_BASEADDR 0X8C000000
#define TAILLE_ECHANTILLON 300000
#define NUM_WAV_FILES 12

/* Définitions de types usagers */

/* Pour connaître l'état de la structure de son */
typedef enum SoundState_t
{
	IDLE = 0,
	PLAYING
} SoundState;

typedef struct WAV_HEADER
{
	char        RIFF[4];        // RIFF Header      Magic header
	uint32_t 	ChunkSize;      // RIFF Chunk Size
    char 		WAVE[4];        // WAVE Header
    char        fmt[4];         // FMT header
    uint32_t    Subchunk1Size;  // Size of the fmt chunk
    uint16_t    AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t    NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t    SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t    bytesPerSec;    // bytes per second
    uint16_t    blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t    bitsPerSample;  // Number of bits per sample
    char        Subchunk2ID[4]; // "data"  string
    uint32_t 	Subchunk2Size;  // Sampled data length
} wav_hdr;

typedef struct TARFileHeader_t
{
    char filename[100]; //NUL-terminated
    char mode[8];
    char uid[8];
    char gid[8];
    char fileSize[12];
    char lastModification[12];
    char checksum[8];
    char typeFlag; //Also called link indicator for none-UStar format
    char linkedFileName[100];
    //USTar-specific fields -- NUL-filled in non-USTAR version
    char ustarIndicator[6]; //"ustar" -- 6th character might be NUL but results show it doesn't have to
    char ustarVersion[2]; //00
    char ownerUserName[32];
    char ownerGroupName[32];
    char deviceMajorNumber[8];
    char deviceMinorNumber[8];
    char filenamePrefix[155];
    char padding[12]; //Nothing of interest, but relevant for checksum
} TARFileHeader;

/* Servira à identifier le type de son à être joué */
typedef enum WAV_FILE_TYPE_T
{
	CRASH = 0,
	FAIL,
	HURRYUP,
	JET,
	LAND,
	MENUERROR,
	MENUIN,
	MENUOUT,
	MENUSELECT,
	PAUSE,
	START,
	WIN,
	NO_SOUND
} WAV_FILE_TYPE;

typedef struct Sound_t
{
	uint32_t *Sample;
	uint32_t FileSize;
	uint32_t CurrentIndex;
	SoundState CurrentState;
	WAV_FILE_TYPE SoundType;
} Sound;

/* Abstraction d'un fichier WAVE */
typedef struct WaveFile_t
{
	uint8_t *Data;
	uint8_t *RawSample;
	uint32_t *Sample;
	size_t FileSize;
	size_t SampleSize;
} WaveFile;

/* Abstraction d'une archive TAR */
typedef struct TARArchive_t
{
	TARFileHeader TARFileHeaders[NUM_WAV_FILES];
	WaveFile WaveFiles[NUM_WAV_FILES];
	wav_hdr WaveFileHeader[NUM_WAV_FILES];
} TARArchive;

/* Déclaré dans le main */
extern Sound sound;
extern TARArchive archive;


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		InitCurrentSound
//						Initialise une structure de son en tant que "son en cours".
// PARAMETRES: 			WAV_FILE_TYPE SoundType: Le type de son à être entendu.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé dans l'ISR du ac97.
////////////////////////////////////////////////////////////////////////////////
void InitCurrentSound(WAV_FILE_TYPE SoundType);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		decodeTarOctal
//						Rapport un représentation octal en représentation décimale
// PARAMETRES: 			char* data: Pointeur vers la chaîne de caractère à décoder.
// 						size_t size; Taille de la chaîne.
// VALEUR DE RETOUR:	La valeur décimal du champ octal.
// REMARQUE:            Pour le décodage de l'archive TAR.
////////////////////////////////////////////////////////////////////////////////
uint64_t decodeTarOctal(char* data, size_t size);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		getFileSize
//						Retourne la taille d'un fichier dans une archive TAR
// PARAMETRES: 			TARFileHeader *currentFileHeader: L'entête du fichier dont on veut connaître la taille.
// VALEUR DE RETOUR:    La taille du fichier en question.
// REMARQUE:            Pour le décodage de l'archive TAR.
////////////////////////////////////////////////////////////////////////////////
size_t getFileSize(TARFileHeader *currentFileHeader);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		IsEndOfTarFile
//						Permet de trouver la fin d'une archive TAR en comparant un bloc rempli de zéros à l'entête courante.
// PARAMETRES: 			TARFileHeader *currentFileHeader: entête à comparer.
// VALEUR DE RETOUR:    true, si l'entête courante ne contient que des zéros, false autrement.
// REMARQUE:            Par définition, le fin d'une archive TAR est padder d'un bloc de 512 char mis à '0'.
////////////////////////////////////////////////////////////////////////////////
bool IsEndOfTarFile(TARFileHeader *currentFileHeader);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		DecodeWave
//						À partir du RAW data de l'Archive TAR on lit l'entête WAVE du fichier et on le décode
// PARAMETRES: 			TARArchive* archive: archive TAR ne contenant que des fichiers WAVE
// VALEUR DE RETOUR:    Aucune
// REMARQUE:            Après l'appel de cette fonction on se retrouve avec des fichiers WAVE décodés et leur RawData.
////////////////////////////////////////////////////////////////////////////////
void DecodeWave();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		DecodeTar
//						Lit les entêtes TAR d'une archive une par une, décode leur contenue, et les sauvent en mémoire pour utilisation ultérieur.
// PARAMETRES: 			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Après l'appel à cette fonction tout les fichies sont décodés et sérialisé dans la structure TARArchive archive.
//						Reste à décoder le contenu des fichiers.
////////////////////////////////////////////////////////////////////////////////
void DecodeTar();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		ProcessSound
//						Effectue un traitement sur les échantillons de sons RAW de notre archive TAR.
// PARAMETRES: 			TARArchive* archive: archive TAR contenant les fichiers WAVE sur lesquelles il faut effectuer les traitement.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Après l'appel à cette fonction, les échantillons sont près à être jouer par le ac97.
////////////////////////////////////////////////////////////////////////////////
void ProcessSound();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		LoadSound
//						Décode l'archives TAR contenant les échantillons WAVE et décode les fichiers WAVE pour obtenir leur RAW data
// PARAMETRES: 			TARArchive* archive: Archive TAR sur laquelle il faut lancer le traitement
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            La structure TARArchive archive contiendra les fichiers WAVE et leur RAW Data
//						Fait appel à DecodeTar et DecodeWave(TARArchive*)
////////////////////////////////////////////////////////////////////////////////
void LoadSound();

void PlaySound(ac97_core *CfgAC97, WAV_FILE_TYPE soundType);

typedef struct  {

	char echantillon_tar[100];

} tarFichierHeader;


typedef struct  {

	Xuint8 taille_tar[12];

} tarFichierTaille;

typedef struct  {

	Xuint8 sampleRate_wave[4];
	Xuint8 sampleTmp_wave[4];

} waveSampleRate, wavesampleTmp ;

typedef struct  {

	Xuint8 subchunk2Size_wave[4];
	Xuint8 subchunTmp_wave[4];

} waveSubchunk2Size, waveSubchunTmp;

typedef struct  {

	Xuint8 data_wave[300000];

} waveData;

//Fonctions

tarFichierHeader gettarFichierHeader(u32 address);

tarFichierTaille gettarFichierTaille(u32 address);

waveSampleRate getwaveSampleRate(u32 address);

waveSubchunk2Size getwaveSubchunk2Size(u32 address);

waveData getwaveData(u32 address, u32 taille);

void decrompresserFileTar(Xuint32 baseAdress);

#endif /* TAR_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
