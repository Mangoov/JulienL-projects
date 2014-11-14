#ifndef VIDEO_H_
#define VIDEO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbasic_types.h>
#include <xtft.h>
#include <xparameters.h>
#include <xio.h>
#include "../NetworkInterface/NetworkInterface.h"
#include "physics.h"

// adresse absolue choisie pour la page vidéo en RAM DDR2
#define TFT_FB_ADDR (XPAR_MPMC_0_MPMC_HIGHADDR - 0x001fffff)
#define TFT_DEVICE_ID	XPAR_TFT_0_DEVICE_ID
/**
 * Color Values.
 */
#define FGCOLOR_VALUE		0x0000FF00	/**< Foreground Color - Green */
#define BGCOLOR_VALUE		0x0		/**< Background Color - Black */
#define WHITECOLOR_VALUE 	0x00FFFFFF	/**< Color - White */

/*typedef struct {
   int x;
   int y;
} Points;*/

void Draw(
		uint32_t image[][480],
		size_t width,
		size_t height,
		size_t offsetCol,
		size_t offsetRow
		);

XTft TftInstance;
extern Application app;
u32 bg[640][480];

int TftWriteString(const u8 *CharValue);
void XTft_DrawBoundaries();
void XTft_CapsuleMove(uint32_t image[][480],size_t width,size_t height,GamePhysics *phys);
void XTft_HideBoundaries();
void XTft_PauseGame();
void XTft_ShowCapsule(uint32_t image[][480],size_t width,size_t height);
void XTft_Background(uint32_t image[][480],size_t width,size_t height);
void XTft_Preview(uint32_t image[][480],size_t width,size_t height,int i,int j);
int XTft_Init(u32 TftDeviceId);
void XTft_Background2();
void XTft_ColorPlatform (int x1, int x2, int y);
void XTft_WriteTextExt(const u8 *CharValue,int x, int y, u32 fgColor, u32 bgColor);
void XTft_DrawLines(int a1,int a2, int b1, int b2,u32 color);
void XTft_ClearZone(int a1, int a2, int b1, int b2, u32 bgColor);
#endif /* VIDEO_H_ */
