#include <gccore.h>
#include <ogcsys.h>
#include <gcmodplay.h>
#include <ogc/ipc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>
#include <bte/bte.h>
#include "pngu.h"

#ifndef _LIBSCOGNITO_
#define _LIBSCOGNITO_

#define COLOR_MAGENTA 1775528426
#define SOGLIA 		     3000000 //5000000
#define FMT_BMP	0
#define FMT_PNG 1

//#define IS_EMU
//#define HW_RVL

extern GXRModeObj *vmode;
extern u32 *xfb[2];
extern int whichfb;
bool systemReset;
bool systemPowerOff;

typedef struct{

	u16 bfMagic;			/*** Always BM ***/
	u32 bfSize;				/*** Size of file ***/
	u32 bfReserved;			/*** Always 0 ***/
	u32 bfOffset;			/*** Offset to pixel data ***/
	u32 biImageHdrSize;		/*** Size of Image info header ***/
	u32 biWidth;			/*** Width of bitmap ***/
	u32 biHeight;			/*** Height of bitmap ***/
	u16 biPlanes;			/*** Number of planes ***/
	u16 biBitsPerPixel;		/*** Bits per pixel ***/
	u32 biCompression;		/*** Is this compressed? ***/
	
} __attribute__ ((__packed__)) WINBITMAP;

typedef struct{

	s32 x;
	s32 y;
	u32 w;
	u32 h;
	
	u8 *rgbImg;
	u32 *ycbImg;
	
	bool wrap;
	
} s_background;

typedef struct{

	s32 x;
	s32 y;
	u32 w;
	u32 h;
	
	u8 *rgbImg;
	u32 *ycbImg;
	
	u32 frameHeight;
	u32 numFrames;
	u32 frame;
	
	bool wrap;
	bool hidden;
} s_sprite;

//
// FUNCTIONS
//

u32 FLIP32 (u32 value);
u16 FLIP16 (u16 value);
u32 CvtRGB (u8 r1, u8 g1, u8 b1, u8 r2, u8 g2, u8 b2);
int getRandomNum(int min, int max);
void sleepSeconds(int seconds);
void sleepMSeconds(int frames);
void initWii();
u32 createBackground(s_background *bg, const u8 *bmpfile, char* path, s32 x, s32 y, u8 type, bool useDevice);
void drawBackground(s_background bg);
void deleteBackground(s_background *bg);
u32 createSprite(s_sprite *sp, const u8 *bmpfile, char* path,  s32 x, s32 y, u32 numframes, u8 type, bool useDevice);
void drawSprite(s_sprite sp);
void deleteSprite(s_sprite *sp);
void cloneSprite(s_sprite *spDest, s_sprite *spOrig);
void drawFilledRect(u32 x, u32 y, u32 w, u32 h, u8 r, u8 g, u8 b);
void breakpoint(char* msg, int value);
void stopDvdMotor();
void poweroffSystem();
void resetSystem();
void exitGame();
#endif
