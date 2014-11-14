#include "video.h"


extern GlobalConfiguration *globalConfiguration;

int initialTop,initialLeft;

void Draw(
		uint32_t image[][480],
		size_t width,
		size_t height,
		size_t offsetCol,
		size_t offsetRow
		)
{
	int ColVal, RowVal;
	for(ColVal = 0; ColVal < width; ++ColVal)
	{
		for(RowVal = 0; RowVal < height; ++RowVal)
		{
			if(image[ColVal][RowVal] != 0x00ff00ff)
				XTft_SetPixel(&TftInstance, offsetCol + ColVal, offsetRow + RowVal, image[ColVal][RowVal]);
		}
	}
}

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}

void XTft_ColorPlatform (int x1, int x2, int y)
{
	int i;
	for(i = x1; i < x2; i++)
	{
		XTft_SetPixel(&TftInstance, i, y, 0x00FF00);
	}

}

void XTft_DrawBoundaries()
{
	int x1,x2,y1,y2,x,y;
	double a,b;
	int compteurX;
	int i;
	int p=0;
	for(i = 0 ; i < app.landDescription->arr_boundaries_len - 1; i ++)
	{
		x1 = app.landDescription->boundaries[i]->horizon; y1 = app.landDescription->boundaries[i]->vertical;
		x2 = app.landDescription->boundaries[i+1]->horizon; y2 = app.landDescription->boundaries[i+1]->vertical;

		compteurX= x1;
		a = (double)(y2-y1)/(x2-x1);
		b = y1 - a*x1;

		int j;
		int incrementp = 0;
		for(j = x1 ; j < x2 ; j++)
		{
			y = (a*j)+b;
			if(y2-y1 == 0 && i==app.landDescription->platforms[p]->ptIndexLeft)
			{
				XTft_SetPixel(&TftInstance, j, y, 0xFF0000);
				incrementp = 1;
			}
			else
				XTft_SetPixel(&TftInstance, j, y, 0xFFFFFF);
		}
		if(incrementp==1)
		{
			p++;
		}
		int k;
		/*Si pente positive*/
		if(y2-y1<0)
		{
			compteurX= x1;
			for(k = y2 ; k < y1 ; k++)
			{
				x = (k-b) / a;
				XTft_SetPixel(&TftInstance, x, k, 0xFFFFFF);
			}
		}
		/*Si pente negative*/
		else
		{
			compteurX= x1;
			for(k = y1 ; k < y2 ; k++)
			{
				x = (k-b) / a;
				XTft_SetPixel(&TftInstance, x, k, 0xFFFFFF);
			}
		}
	}

}

void XTft_HideBoundaries()
{
	int x1,x2,y1,y2,x,y;
	double a,b;

	int i;

	for(i = 0 ; i < app.landDescription->arr_boundaries_len - 1; i ++)
	{
		x1 = app.landDescription->boundaries[i]->horizon; y1 = app.landDescription->boundaries[i]->vertical;
		x2 = app.landDescription->boundaries[i+1]->horizon; y2 = app.landDescription->boundaries[i+1]->vertical;

		a = (double)(y2-y1)/(x2-x1);
		b = y1 - a*x1;

		int j;
		for(j = x1 ; j < x2 ; j++)
		{
			y = (a*j)+b;
			XTft_SetPixel(&TftInstance, j, y, LandBMP.Image[j][y]);
		}

		int k;
		/*Si pente positive*/
		if(y2-y1<0)
		{
			for(k = y2 ; k < y1 ; k++)
			{
				x = (k-b) / a;
				XTft_SetPixel(&TftInstance, x, k, LandBMP.Image[x][k]);
			}
		}
		/*Si pente negative*/
		else
		{
			for(k = y1 ; k < y2 ; k++)
			{
				x = (k-b) / a;
				XTft_SetPixel(&TftInstance, x, k, LandBMP.Image[x][k]);
			}
		}
	}
}

void XTft_ShowCapsule(
		uint32_t image[][480],
		size_t width,
		size_t height
		)
{
	int ColVal, RowVal;
	for(ColVal = 0; ColVal < width; ++ColVal)
	{
		for(RowVal = 0; RowVal < height; ++RowVal)
		{
			if(image[ColVal][RowVal] != 0x00ff00ff)
				XTft_SetPixel(&TftInstance, initialLeft + ColVal, initialTop + RowVal, LanderBMP.Image[ColVal][RowVal]);
			//else
				//XTft_SetPixel(&TftInstance, initialLeft + ColVal, initialTop + RowVal, LandBMP.Image[initialLeft + ColVal][initialTop + RowVal]);

		}
	}
}

void XTft_CapsuleMove(
		uint32_t image[][480],
		size_t width,
		size_t height,
		GamePhysics *phys)
{
	int ColVal, RowVal;
	for(ColVal = 0; ColVal < width; ++ColVal)
	{
		for(RowVal = 0; RowVal < height; ++RowVal)
		{
			if(initialLeft + ColVal > 0 &&
					initialLeft + ColVal < 640 &&
					initialTop + RowVal > 0 &&
					initialTop + RowVal < 480)
			{
				XTft_SetPixel(&TftInstance,
						initialLeft + ColVal,
						initialTop + RowVal,
						LandBMP.Image[initialLeft + ColVal][initialTop + RowVal]);
			}
		}
	}
	// dessiner new
	initialTop = phys->currentXPos * globalConfiguration->landResolution;
	initialLeft = phys->currentYPos * globalConfiguration->landResolution;
	if(initialLeft > 0 && initialLeft < 640 && initialTop > 0 && initialTop < 480)
	{
		XTft_ShowCapsule(LanderBMP.Image, LanderBMP.Width, LanderBMP.Height);
	}
}

void XTft_Background(
		uint32_t image[][480],
		size_t width,
		size_t height
		)
{
	int ColVal, RowVal;
	for(ColVal = 0; ColVal < width; ++ColVal)
	{
		for(RowVal = 0; RowVal < height; ++RowVal)
		{
			if(image[ColVal][RowVal] != 0x00ff00ff)
				XTft_SetPixel(&TftInstance, ColVal,RowVal, image[ColVal][RowVal]);
		}
	}
}

void XTft_Preview(
		uint32_t image[][480],
		size_t width,
		size_t height,
		int i,
		int j
		)
{
	int ColVal, RowVal,x,y;
	x = i;
	y = j;
	for(ColVal = 0; ColVal < width; ++ColVal)
	{
		for(RowVal = 0; RowVal < height; ++RowVal)
		{
				XTft_SetPixel(&TftInstance, x,y, image[ColVal][RowVal]);
				y++;
		}
		y=j;
		x++;
	}
}

int TftWriteString(const u8 *CharValue)
{
	/*
	 * Writes a character from the string to the screen
	 * until it reaches null or end of the string.
	 */
	while (*CharValue != 0) {
		XTft_Write(&TftInstance, *CharValue);
		CharValue++;
	}

	return XST_SUCCESS;
}
int XTft_Init(u32 TftDeviceId)
{
	int Status;
	XTft_Config *TftConfigPtr;

	int row = 0, col = 0, compteur = 0;

	TftConfigPtr = XTft_LookupConfig(TftDeviceId);
	if (TftConfigPtr == (XTft_Config *)NULL) {
		return XST_FAILURE;
	}

	XTft_CfgInitialize(&TftInstance, TftConfigPtr,
				 	TftConfigPtr->BaseAddress);
	while (XTft_GetVsyncStatus(&TftInstance) !=
					XTFT_IESR_VADDRLATCH_STATUS_MASK);
	XTft_SetFrameBaseAddr(&TftInstance, TFT_FB_ADDR);
	XTft_ClearScreen(&TftInstance);
}

void XTft_DrawLines(int a1,int a2, int b1, int b2,u32 color)
{
	int x1,x2,y1,y2,x,y;
	double a,b;
	int compteurX;
	x1 = a1; y1 = a2;
	x2 = b1; y2 = b2;

	compteurX= x1;
	a = (double)(y2-y1)/(x2-x1);
	b = y1 - a*x1;

	int j;

	for(j = x1 ; j < x2 ; j++)
	{
		y = (a*j)+b;
		XTft_SetPixel(&TftInstance, j, y, color);
	}
	int k;
	/*Si pente positive*/
	if (x1 == x2)
	{
		for(y1; y1<y2;y1++)
			XTft_SetPixel(&TftInstance, x1, y1, color);
	}
	if(y2-y1<0)
	{
		compteurX= x1;
		for(k = y2 ; k < y1 ; k++)
		{
			x = (k-b) / a;
			XTft_SetPixel(&TftInstance, x, k, color);
		}
	}
	/*Si pente negative*/
	else
	{
		compteurX= x1;
		for(k = y1 ; k < y2 ; k++)
		{
			x = (k-b) / a;
			XTft_SetPixel(&TftInstance, x, k, color);
		}
	}

}

void XTft_WriteTextExt(const u8 *CharValue,int x, int y, u32 fgColor, u32 bgColor)
{
	XTft_SetColor(&TftInstance,fgColor,bgColor);
	XTft_SetPos(&TftInstance,x,y);
	while (*CharValue != 0) {
			XTft_Write(&TftInstance, *CharValue);
			CharValue++;
		}
}

void XTft_WriteTextExt2(const inputBuf buf,int x, int y, u32 fgColor, u32 bgColor)
{
	XTft_SetColor(&TftInstance,fgColor,bgColor);
	XTft_SetPos(&TftInstance,x,y);
	int i;
	for (i = 0; i < buf.bufSize; ++i){
			XTft_Write(&TftInstance, buf.buf[i]);
		}
}

void XTft_ClearZone(int a1, int a2, int b1, int b2, u32 bgColor)
{
	int ColVal, RowVal;
	for(ColVal = a1; ColVal < b1; ++ColVal)
	{
		for(RowVal = a2; RowVal < b2; ++RowVal)
		{
			XTft_SetPixel(&TftInstance, ColVal,RowVal, bgColor);
		}
	}

}
