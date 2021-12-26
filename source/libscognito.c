#include "../include/libscognito.h"

GXRModeObj *vmode;
u32 *xfb[2] = { NULL, NULL };
int whichfb = 0;
bool systemReset = false;
bool systemPowerOff = false;

u32 FLIP32 (u32 value){
  
  u32 b;

  b = (value & 0xff) << 24;
  b |= (value & 0xff00) << 8;
  b |= (value & 0xff0000) >> 8;
  b |= (value & 0xff000000) >> 24;

  return b;
}


u16 FLIP16 (u16 value){

  return ((value & 0xff) << 8) | ((value & 0xff00) >> 8);
}


u32 CvtRGB (u8 r1, u8 g1, u8 b1, u8 r2, u8 g2, u8 b2){

  int y1, cb1, cr1, y2, cb2, cr2, cb, cr;

  y1 = (299 * r1 + 587 * g1 + 114 * b1) / 1000;
  cb1 = (-16874 * r1 - 33126 * g1 + 50000 * b1 + 12800000) / 100000;
  cr1 = (50000 * r1 - 41869 * g1 - 8131 * b1 + 12800000) / 100000;

  y2 = (299 * r2 + 587 * g2 + 114 * b2) / 1000;
  cb2 = (-16874 * r2 - 33126 * g2 + 50000 * b2 + 12800000) / 100000;
  cr2 = (50000 * r2 - 41869 * g2 - 8131 * b2 + 12800000) / 100000;

  cb = (cb1 + cb2) >> 1;
  cr = (cr1 + cr2) >> 1;

  return (y1 << 24) | (cb << 16) | (y2 << 8) | cr;
}


int getRandomNum(int min, int max){

	int diff = max - min + 1;
	int res = (rand() % diff)+min;
	
	return res;
}

void sleepSeconds(int seconds){

	long i = 0;
	
	#ifdef IS_EMU
	for(i=0; i<seconds*60; i++){
		VIDEO_WaitVSync();
	}
	#else
	for(i=0; i<seconds*90; i++){
		VIDEO_WaitVSync();
	}
	#endif
}

void sleepMSeconds(int frames){

	long i = 0;
	
	for(i=0; i<frames; i++){
		VIDEO_WaitVSync();
	}
}

void initWii() {

	VIDEO_Init();
	PAD_Init();
	#ifdef HW_RVL
	WPAD_Init();
	#endif
	
	vmode = VIDEO_GetPreferredMode(NULL);

	xfb[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(vmode));
	xfb[1] = MEM_K0_TO_K1 (SYS_AllocateFramebuffer (vmode));
	
	console_init(xfb[0],20,20, vmode->fbWidth, vmode->xfbHeight, vmode->fbWidth*VI_DISPLAY_PIX_SZ);
	
	VIDEO_ClearFrameBuffer (vmode, xfb[0], COLOR_BLACK);
	VIDEO_ClearFrameBuffer (vmode, xfb[1], COLOR_BLACK);
	
	VIDEO_Configure(vmode);
	VIDEO_SetNextFramebuffer (xfb[0]);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	
	if(vmode->viTVMode&VI_NON_INTERLACE)
		VIDEO_WaitVSync();
	
	#ifdef HW_RVL
	WPAD_SetVRes(WPAD_CHAN_0, vmode->fbWidth, vmode->xfbHeight);
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetIdleTimeout(60);
	#endif
	
	// random stuff
	srand(time(NULL));
}


u32 createBackground(s_background *bg, const u8 *bmpfile, char* path, s32 x, s32 y, u8 type, bool useDevice){

	u32 width, height, tmp;

	if (type == FMT_BMP){
		WINBITMAP* bmpTemp = (WINBITMAP *) bmpfile;
		
		if (memcmp (&bmpTemp->bfMagic, "BM", 2)) return -1;
		if (FLIP16 (bmpTemp->biPlanes) != 1) return -2;
		if (FLIP32 (bmpTemp->biCompression) != 0) return -3;
		if (FLIP16 (bmpTemp->biBitsPerPixel) != 24) return -4;

		width = FLIP32 (bmpTemp->biWidth);
		height = FLIP32 (bmpTemp->biHeight);
		
		bg->w = width;
		bg->h = height;

		//bg->frameHeight = vmode -> xfbHeight;

		if ((width > 640) || (height > vmode->xfbHeight)) return -5;
		
		bg->rgbImg = (u8 *) bmpfile + FLIP32 (bmpTemp->bfOffset);
		
		// image loaded, let's convert from RGB to YCBYCR
		int rows, cols;
		int z = 0;
		
		bg->ycbImg = malloc(sizeof(u32)*(width>>1)*height);
		
		for (rows = bg->h; rows > 0; rows--) {
			for (cols = 0; cols < (bg->w >> 1); cols++) {
				bg->ycbImg[(rows-1) * (bg->w >> 1) + z] = CvtRGB (bg->rgbImg[2], bg->rgbImg[1], bg->rgbImg[0], bg->rgbImg[5], bg->rgbImg[4], bg->rgbImg[3]);
				bg->rgbImg += 6;
				z++;
			}
			z=0;
		}
	}
	
	else if (type == FMT_PNG){
	
		PNGUPROP imgProp;
		IMGCTX ctx;
	
		if(!useDevice){
			if ( !(ctx = PNGU_SelectImageFromBuffer (bmpfile)) )
				return -1;
		}
		else{
			if ( !(ctx = PNGU_SelectImageFromDevice(path) ))
				return -1;
		}

		if (PNGU_GetImageProperties(ctx, &imgProp) != PNGU_OK)
			return -2;
	
		width = imgProp.imgWidth;
		height = imgProp.imgHeight;
		
		if ((width > 640) || (height > vmode->xfbHeight)) return -5;
		
		bg->w = width;
		bg->h = height;
		
		bg->ycbImg = malloc(sizeof(u32)*(width>>1)*height);
			
		tmp = PNGU_DecodeToYCbYCr(ctx, width, height, bg->ycbImg, 0);
		
		if (tmp != PNGU_OK)
			return -3;

		PNGU_ReleaseImageContext(ctx);
	}
	
	bg->x = x;
	bg->y = y;
	bg->wrap = false;
	
	return 1;
}


void drawBackground(s_background bg){

	u32 fboffset;
	int cols, rows;
	int xtemp = 0;
	int ytemp = 0;//, xoffset, yoffset;
	
	if(bg.x>640)
		bg.x -= 640;
	
	if(bg.y>480)
		bg.y -= 480;
	
	fboffset = (bg.x) >> 1;
	fboffset += (bg.y * 320);
	
	if(bg.x==0 && bg.y==0)
		memcpy(&xfb[whichfb][fboffset], &bg.ycbImg[0], (bg.w<<1)*bg.h);
	
	else{
		
		xtemp = bg.x;
		ytemp = bg.y;
		
		if(xtemp%2 != 0)
		 xtemp++;
		 
		for(rows=0; rows<(480-ytemp); rows++){
			for(cols = 0; cols<(320-(bg.x>>1)); cols++){
				xfb[whichfb][fboffset + cols] = bg.ycbImg[rows*(320-(xtemp>>1))+cols];//CvtRGB(255, 0, 0, 255, 0, 0);
			}
			fboffset += 320;
		}
	
		//if wrap
		fboffset = 0;
		for(rows=0; rows<ytemp; rows++){
			for(cols = 0; cols<320; cols++){
				xfb[whichfb][fboffset + cols] = bg.ycbImg[(480-ytemp+rows)*(320-(xtemp>>1))+cols];//CvtRGB(0, 0, 255, 0, 0, 255);
			}
			fboffset += 320;
		}
		//endwrap
		
		//printf("480-bg.y: \n", (480-bg.y));
	}
	
	/*
	console_setpos(0, 320);
	printf("ytemp: %d\n", ytemp);
	printf("(320-(xtemp>>1)): %d\n", (320-(xtemp>>1)));
	*/
	
	
	/*
	int rows, cols;
	//u32 fboffset = 320 * vmode->xfbHeight;
	u32 fboffset;
	fboffset = (bg.x) >> 1;
	fboffset += (bg.y * 320);
	fboffset += (bg.frameHeight * 320);
	
	u32 z = 0;
	cols = 0;

	for (rows = 0; rows < bg.frameHeight; rows++) {
		
		memcpy(&xfb[whichfb][fboffset], &bg.ycbImg[z], 640+(bg.frameWidth));
		z+=(bg.frameWidth >> 1);			
		fboffset -= 320;
	}
	*/
}

void deleteBackground(s_background *bg){
	
	free(bg->ycbImg);
	bg = NULL;
}

u32 createSprite(s_sprite *sp, const u8 *bmpfile, char* path, s32 x, s32 y, u32 numFrames, u8 type, bool useDevice){
	
	u32 width, height, tmp;
	
	if (type == FMT_BMP){
	
		WINBITMAP* bmpTemp = (WINBITMAP *) bmpfile;
		//u32 width, height;
		
		if (memcmp (&bmpTemp->bfMagic, "BM", 2)) return -1;
		if (FLIP16 (bmpTemp->biPlanes) != 1) return -2;
		if (FLIP32 (bmpTemp->biCompression) != 0) return -3;
		if (FLIP16 (bmpTemp->biBitsPerPixel) != 24) return -4;

		width = FLIP32 (bmpTemp->biWidth);
		height = FLIP32 (bmpTemp->biHeight);
		
		sp->w = width;
		sp->h = height / numFrames;
//		sp->x = x;
//		sp->y = y;
		
/*
		sp->frameHeight = height / numFrames;
		sp->frame = 0;
		sp->numFrames = numFrames;
		
		sp->wrap = false;
		sp->hidden = false;
*/

		//if ((width > 640) || (height > vmode->xfbHeight)) return -5;
		
		sp->rgbImg = (u8 *) bmpfile + FLIP32 (bmpTemp->bfOffset);
		
		// ADDED	
		// image loaded, let's convert from RGB to YCBYCR
		int rows, cols;
		int z = 0;
		
		sp->ycbImg = malloc(sizeof(u32)*(width >> 1)*height);
		// magenta? 16711935
		// Bitmap image is stored from left to right, *bottom to up*
		// Let's store in human way
		// So già che rileggendo sto for fra 2 giorni non ricorderò nulla :)
		for (rows = sp->h * numFrames; rows > 0; rows--) {
			for (cols = 0; cols < (sp->w >> 1); cols++) {
				sp->ycbImg[(rows-1) * (sp->w >> 1) + z] = CvtRGB (sp->rgbImg[2], sp->rgbImg[1], sp->rgbImg[0], sp->rgbImg[5], sp->rgbImg[4], sp->rgbImg[3]);
				sp->rgbImg += 6;
				z++;
			}
			z=0;
		}
	}
	
	else if (type == FMT_PNG){
	
		PNGUPROP imgProp;
		IMGCTX ctx;
		
		if(!useDevice){
			if ( !(ctx = PNGU_SelectImageFromBuffer(bmpfile)) )
				return -1;
		}
		else{
			if ( !(ctx = PNGU_SelectImageFromDevice(path) ))
				return -1;
		}
			
		if (PNGU_GetImageProperties (ctx, &imgProp) != PNGU_OK)
			return -2;
	
		width = imgProp.imgWidth;
		height = imgProp.imgHeight;
		
		//if ((width > 640) || (height > vmode->xfbHeight)) return -5;
		
		sp->w = width;
		sp->h = height / numFrames;
		
		sp->ycbImg = malloc(sizeof(u32)*(width>>1)*height);
			
		tmp = PNGU_DecodeToYCbYCr(ctx, width, height, sp->ycbImg, 0);
		
		if (tmp != PNGU_OK)
			return -3;
			
		PNGU_ReleaseImageContext(ctx);
	}
	
	sp->x = x;
	sp->y = y;

	sp->frameHeight = height / numFrames;
	sp->frame = 0;
	sp->numFrames = numFrames;
	
	sp->wrap = false;
	sp->hidden = false;
	//breakPointInt(xaa);
	return 1;
}

void drawSprite(s_sprite sp){

	if(sp.hidden)
		return;
	
	int rows, cols;
	u32 fboffset;

	fboffset = sp.x  >> 1;
	fboffset += (sp.y * 320);
	//fboffset += (sp.frameHeight * 320);
	
	u32 z = ((sp.w>>1) * sp.frameHeight * sp.frame);
	//u32 z = (((sp.w>>2) * sp.offsetY0>>2) + (sp.offsetX0 >> 1));
	
	//u32 z = (sp.frameWidth >> 1) * sp.offsetY0;
	for (rows = 0; rows<sp.frameHeight; rows++){
		for (cols=0; cols<(sp.w >> 1); cols++){
			if ((sp.ycbImg[z] > COLOR_MAGENTA + SOGLIA) || (sp.ycbImg[z] < COLOR_MAGENTA - SOGLIA))
				xfb[whichfb][cols + fboffset] = sp.ycbImg[z];
			z++;
		}
		fboffset += 320;
	}
}

void deleteSprite(s_sprite *sp){
	
	free(sp->ycbImg);
	sp = NULL;
}

void cloneSprite(s_sprite *spDest, s_sprite *spOrig){
	
	memcpy(spDest, spOrig, sizeof(s_sprite));
	spDest->x = 0;
	spDest->y = 0;
}

void drawFilledRect(u32 x, u32 y, u32 w, u32 h, u8 r, u8 g, u8 b){
	
	
	int rows, cols;
	u32 fboffset;
	u32 color;
	
	fboffset = x  >> 1;
	fboffset += y * 320;
	color = CvtRGB(r, g, b, r, g, b);
	
	for(rows = 0; rows < h; rows++){
		for (cols=0; cols<(w >> 1); cols++){
			xfb[whichfb][cols + fboffset] = color;
		}
		fboffset += 320;
	}
	
}

void breakpoint(char* msg, int value){
	
	int buttonsDown;
	int i = 0;
	
	while(1){
		
		whichfb ^= 1;
		
		//console_setpos(0, 0);
		//printf("Breakpoint!\n");
		iprintf ("\x1b[3;0Hbreakpoint\n");
		printf("  %s: %d                                             \n", msg, value);
		printf("Press Start to continue\n");
		
		PAD_ScanPads();
		buttonsDown = PAD_ButtonsDown(0);
		
		if(buttonsDown & PAD_BUTTON_START) {
			break;
		} 
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}
	
	while(i<10){
		VIDEO_WaitVSync();
		i++;
	}
}

void stopDvdMotor(){
	   
	s32 di_fd;
    s32 buf[3];
    buf[0] = 0xE3000000;
    buf[1] = 0; //unknown/unused at this point
    buf[2] = 0; //unknown/unused at this point
            
    /* Open DVD interface for writing */
	//static char _di_fs[] ATTRIBUTE_ALIGN(32) = "/dev/di"; // by shagkur
	//2) for the buf var applies the same, have it aligned on a 32byte boundery. 
	//either by declaring a static array or by using memalign(32,0x20) for instance
    
	di_fd = IOS_Open("/dev/di", 2);
    
    //IOS_Ioctl( di_fd, buf[0], buf, 0x20, buf, 0x20);
	IOS_IoctlAsync( di_fd, buf[0], buf, 0x20, buf, 0x20, NULL, NULL);
}

void poweroffSystem(){
	
	systemPowerOff = true;
}

void resetSystem(){

	systemReset = true;
}

void exitGame(){

	#ifdef HW_RVL
		exit(0);
	#else
		void (*PSOreload)() = (void(*)())0x80001800;
		PSOreload();
	#endif
}
