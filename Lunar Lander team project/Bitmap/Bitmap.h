///////////////////////////////////////////////////////////////////////////
/// @file Bitmap.h
/// @date 2013-11
/// @description Définition des fonctions pour le décodage des images bitmaps
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _BITMAP_H_
#define _BITMAP_H_

/* Includes */
#include "Order32.h"
#define O32_HOST_ORDER (o32_host_order.value)
#include <string.h>
#include "../GameData/GameUtils.h"
#include <stdio.h>
#include <stdlib.h>

/* Defines */
#define BITMAP_FILEHEADER_SIZE 14
#define BITMAP_HEADER_SIZE 40

/* Déclaration de type usager*/

/* Entete Bitmap */
typedef struct bmpfile_header_t {
	unsigned char magic[2];
	uint32_t filesz;
	uint16_t creator1;
	uint16_t creator2;
	uint32_t bmp_offset;
} bmpfile_header;

/* Information Bitmap */
typedef struct BITMAPINFOHEADER{
	uint32_t header_sz;
	int32_t width;
	int32_t height;
	uint16_t nplanes;
	uint16_t bitspp;
	uint32_t compress_type;
	uint32_t bmp_bytesz;
	int32_t hres;
	int32_t vres;
	uint32_t ncolors;
	uint32_t nimpcolors;
} bmpfile_info_header;

/* Pour représenter une image Bitmap */
typedef struct Bitmap_t
{
	int Width;
	int Height;
	bmpfile_header header;
	bmpfile_info_header info_header;
	uint32_t arr1D[640 * 480];
	uint32_t Image[640][480];
	uint32_t ColorTable[1024];
} Bitmap;


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		MakeBitmap2DFromBitmap1D
//						Le buffer Bitmap est initialement un tableau 1D avec des valeurs de padding.
//						Sert à enlever le padding et pour faciliter la représentation de l'image,
//						on convertit le buffer 1D en buffer 2D avec des indices qui coincident avec l'affichage du tft.
// PARAMETRES: 			uint32_t *Bitmap1D: Tableau de données bitmap raw.
//						uint32_t Bitmap2D[][480]: Tableau sur lequel le résultat de la conversion sera affectée.
//						int width, int height: dimension de l'image.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Est appelée par DecodeBitmap.
////////////////////////////////////////////////////////////////////////////////
void MakeBitmap2DFromBitmap1D(uint32_t *Bitmap1D, uint32_t Bitmap2D[][480], int width, int height);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		fix_endian_func
//						Conversion de little-endian à big-endian
// PARAMETRES: 			void* data: Pointeur vers le tableau d'octet à inverser
//						int size: Nombre d'octets à inverser
// VALEUR DE RETOUR:    Un tableau avec le BitmapData.
// REMARQUE:            Aucune.
////////////////////////////////////////////////////////////////////////////////
void fix_endian_func(void* data, int size);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		ParseBitmap
//						1) Analyse le header bitmap
//						2) Extrait la tablea de couleur
//						3) Assigne à chaque pixel une valeur de la table de couleur
// PARAMETRES: 			buffer(in): Raw Data reçu du seveur qui contient l'entête bitmap, la table de couleur et les index dans la table
//						header(out): entête bitmap (offset et taille de l'image)
//						info_header(out): informations sur l'image
//						width (out): nombre de colonnes
//						height(out): nombre de lignes
// VALEUR DE RETOUR:    Un tableau avec le BitmapData.
// REMARQUE:            Est appelée par DecodeBitmap.
////////////////////////////////////////////////////////////////////////////////
void ParseBitmap(void *buffer, Bitmap *bmp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		DecodeBitmap
//						Sert à allouer un tableau contenant le BitmapData d'après buffer.
// PARAMETRES: 			buffer(in): Raw Data reçu du seveur qui contient l'entête bitmap, la table de couleur et les index dans la table
//						lander_width (out): longeur de l'image
//						lander_height(out): largeur de l'image
// VALEUR DE RETOUR:    Un tableau avec le BitmapData.
// REMARQUE:            Le buffer sera désalloué après l'appel à cette fonction.
////////////////////////////////////////////////////////////////////////////////
void DecodeBitmap(void *buffer, Bitmap *bmp);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		AllocBimapStrucutures
//						Alloue un tableau d'images Bitmap.
// PARAMETRES: 			size_t arr_bmp_len: Nombre d'image bitmap à allouer.
// VALEUR DE RETOUR:    Un tableau d'image Bitmap à initialiser.
// REMARQUE:            Aucune
////////////////////////////////////////////////////////////////////////////////
Bitmap** AllocBimapStrucutures(size_t arr_bmp_len);

#endif /* BITMAP_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
