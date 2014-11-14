///////////////////////////////////////////////////////////////////////////
/// @file Bitmap.c
/// @date 2013-11
/// @description Implémentation des fonctions pour le décodage bitmap
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"


///////////////////////////////////////////////////////////////////////////
void MakeBitmap2DFromBitmap1D(uint32_t Bitmap1D[], uint32_t Bitmap2D[][480], int width, int height)
{
	int ColVal, RowVal, n = 4;
	uint32_t Color, Padding, compteur;
	compteur = 0;
	for(RowVal = height - 1; RowVal >= 0; --RowVal)
	{
		for(ColVal = 0; ColVal < width; ++ColVal)
		{
			memcpy(&Color, &Bitmap1D[compteur], sizeof(uint32_t));
			fix_endian_func(&Color, sizeof(uint32_t));
			memcpy(&Bitmap2D[ColVal][RowVal], &Color, sizeof(uint32_t));
			++compteur;
		}

		/* Padding */
		Padding = compteur;
		Padding += n - 1;
		Padding &= -n;
		compteur = Padding;
	}
}


///////////////////////////////////////////////////////////////////////////
void fix_endian_func(void* data, int size) {
	int endian_test = 1;
	unsigned char* cdata;
	unsigned char* endian_test_bytes = (unsigned char *)&endian_test;
	if (endian_test_bytes[0] == '\0') {
		cdata = (unsigned char*) data;
		int i;
		for (i=0; i<size/2; i++) {
			unsigned char temp = cdata[i];
			cdata[i] = cdata[size-1 - i];
			cdata[size-1 - i] = temp;
		}
	}
}


///////////////////////////////////////////////////////////////////////////
size_t InitBMPHeaders(void *buffer, Bitmap *bmp)
{
	size_t offset = 0;

	/* HEADER */
	memcpy((uint8_t*)&bmp->header.magic, 		buffer + offset, sizeof(2)); 		offset += 2;
	memcpy((uint8_t*)&bmp->header.filesz, 		buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	memcpy((uint8_t*)&bmp->header.creator1, 	buffer + offset, sizeof(uint16_t)); offset += sizeof(uint16_t);
	memcpy((uint8_t*)&bmp->header.creator2, 	buffer + offset, sizeof(uint16_t)); offset += sizeof(uint16_t);
	memcpy((uint8_t*)&bmp->header.bmp_offset, 	buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	/* HEADER */

	/* INFO_HEADER */
	memcpy((uint8_t*)&bmp->info_header.header_sz, 		buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	memcpy((uint8_t*)&bmp->info_header.width, 			buffer + offset, sizeof(int32_t)); 	offset += sizeof(int32_t);
	memcpy((uint8_t*)&bmp->info_header.height, 			buffer + offset, sizeof(int32_t)); 	offset += sizeof(int32_t);
	memcpy((uint8_t*)&bmp->info_header.nplanes, 		buffer + offset, sizeof(uint16_t)); offset += sizeof(uint16_t);
	memcpy((uint8_t*)&bmp->info_header.bitspp, 			buffer + offset, sizeof(uint16_t)); offset += sizeof(uint16_t);
	memcpy((uint8_t*)&bmp->info_header.compress_type, 	buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	memcpy((uint8_t*)&bmp->info_header.bmp_bytesz, 		buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	memcpy((uint8_t*)&bmp->info_header.hres, 			buffer + offset, sizeof(int32_t)); 	offset += sizeof(int32_t);
	memcpy((uint8_t*)&bmp->info_header.vres, 			buffer + offset, sizeof(int32_t)); 	offset += sizeof(int32_t);
	memcpy((uint8_t*)&bmp->info_header.ncolors, 		buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	memcpy((uint8_t*)&bmp->info_header.nimpcolors, 		buffer + offset, sizeof(uint32_t)); offset += sizeof(uint32_t);
	/* INFO_HEADER */

	fix_endian_func(&bmp->header.magic, 				sizeof(2));
	fix_endian_func(&bmp->header.filesz, 				sizeof(uint32_t));
	fix_endian_func(&bmp->header.creator1, 				sizeof(uint16_t));
	fix_endian_func(&bmp->header.creator2, 				sizeof(uint16_t));
	fix_endian_func(&bmp->header.bmp_offset, 			sizeof(uint32_t));

	fix_endian_func(&bmp->info_header.header_sz, 		sizeof(uint32_t));
	fix_endian_func(&bmp->info_header.width, 			sizeof(int32_t));
	fix_endian_func(&bmp->info_header.height, 			sizeof(int32_t));
	fix_endian_func(&bmp->info_header.nplanes, 			sizeof(uint16_t));
	fix_endian_func(&bmp->info_header.bitspp, 			sizeof(uint16_t));
	fix_endian_func(&bmp->info_header.compress_type, 	sizeof(uint32_t));
	fix_endian_func(&bmp->info_header.bmp_bytesz, 		sizeof(uint32_t));
	fix_endian_func(&bmp->info_header.hres, 			sizeof(int32_t));
	fix_endian_func(&bmp->info_header.vres, 			sizeof(int32_t));
	fix_endian_func(&bmp->info_header.ncolors, 			sizeof(uint32_t));
	fix_endian_func(&bmp->info_header.nimpcolors, 		sizeof(uint32_t));

	return offset;
}


///////////////////////////////////////////////////////////////////////////
void ParseBitmap(void *buffer, Bitmap *bmp)
{
	uint8_t col;
	size_t i = 0;
	size_t offset = 0;
	uint32_t Color;

	uint8_t *buf;
	uint32_t *colortable;

	offset = InitBMPHeaders(buffer, bmp);

	buf = (uint8_t *)(buffer + bmp->header.bmp_offset);

	if(bmp->info_header.ncolors)
	{
		colortable = (uint32_t*)(buffer + offset);
		memcpy(&bmp->ColorTable[0], colortable, bmp->info_header.ncolors * sizeof( uint32_t ) );
		offset += bmp->info_header.ncolors * sizeof( uint32_t );

		for (i = 0; i < bmp->info_header.bmp_bytesz; i++)
		{
			/* Extract color */
			memcpy(&col, buf, sizeof(uint8_t)); offset += sizeof(uint8_t);

			/* Search in color table */
			Color = bmp->ColorTable[col];

			memcpy(&bmp->arr1D[i], &Color, sizeof(uint32_t));

			buf++;
		}
	}
	else
	{
		memset(bmp->arr1D, 0, 640 * 480);
		for(i = 0; i < bmp->info_header.bmp_bytesz / 3; i++)
		{
			memcpy(&bmp->arr1D[i], buf, 3);
			buf += 3;
		}
	}

	bmp->Width 	= bmp->info_header.width;
	bmp->Height = bmp->info_header.height;
}


///////////////////////////////////////////////////////////////////////////
void DecodeBitmap(void *buffer, Bitmap *bmp)
{
	ParseBitmap(buffer, bmp);
	MakeBitmap2DFromBitmap1D(bmp->arr1D, bmp->Image, bmp->Width, bmp->Height);
	free (buffer); buffer = NULL;
}


///////////////////////////////////////////////////////////////////////////
Bitmap** AllocBimapStrucutures(size_t arr_bmp_len)
{
	Bitmap **bmp;
	unsigned int i = 0;

	/* arr_boundaries_len is the number of rows */
	bmp = ( Bitmap** ) malloc ( arr_bmp_len * sizeof( Bitmap* ));
	if ( bmp == NULL )
	{ /* error */ }
	for ( i = 0; i < arr_bmp_len; ++i )
	{
		bmp[i] = ( Bitmap* )malloc( sizeof(Bitmap) );
		if(bmp[i] == NULL )
		{ /* error */ }
	}

	return bmp;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
