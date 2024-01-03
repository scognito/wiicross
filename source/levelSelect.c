#include "levelSelect.h"

#ifdef HW_DOL
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

extern s_level leveldata[NUMLEVELS];
extern s_marker markerH;
extern s_time timeElapsed;
extern s_option options;
//extern s_sprite pointer;
extern bool backToMenu;
extern s_sprite arrowR;
extern s_sprite arrowL;
extern unsigned int currentPage;

extern int px, py;
char timeStr[20];
char pageStr[10];

//int currentPage = 0;
int ox = 0;
int oy = 0;

int questionMark[225] = {

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

int levelSelect(){

	int i, j, k, l, m, z;
	bool exit = false;
	int startX = 92;
	int startY = 30;
	int xDistance = 62;
	int yDistance = 32;
	int buttonsDown;
	
	int puzzlesInPage = 0;
	//int currentPage = 0;
	int posX = ox;
	int posY = oy;
	int level = 0;
	bool isOT = false; // is the pointer over a level thumbnail?
	int frames = 0;
	
	//int numPages = NUMLEVELS / 9;
	markerH.r = 255;
	markerH.g = 255;
	markerH.b = 255;
	markerH.dirColor = DIR_COLOR_DOWN;
	
	unsigned int numPages = 0;
	
	if (NUMLEVELS > 9)
		numPages = NUMLEVELS / 9;
	
	#ifndef IS_EMU
	if(SND_StatusVoice(0) == SND_UNUSED) 
		playTitleScreenMusic();
	#endif
	
	while(!exit){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
	
		drawBackground(bg);
		
		//px = pointer.x + pointer.w;
		//py = pointer.y + pointer.h;
		px = cursor_hand.x;
		py = cursor_hand.y;
		
		z = 9 * currentPage;
		puzzlesInPage = 0;
		
		drawLevelSelectCursor(startX -6 + (preview.w + xDistance)*posX, startY -6 + (preview.h + yDistance)*posY);
		
		for(i=0; i<3; i++){
			preview.y = startY + (preview.h + yDistance)*i;
			for(j=0; j<3; j++){
			
				preview.x = startX + (preview.w + xDistance)*j;
				drawSprite(preview);
				
				if(z < NUMLEVELS){
					// draw the puzzle image if the puzzle was clear otherwise draw a question mark
					m=0;
					for(k=0; k<ROWLEN; k++){
						for(l=0; l<ROWLEN; l++){
							if(leveldata[z].played){
								if(leveldata[z].data[m] == 1){
									//minitile.x = preview.x + 10 + l*6;
									//minitile.y = preview.y + k*6 + 10;
									//drawSprite(minitile);
									drawFilledRect(preview.x + 10 + l*6, preview.y + k*6 + 10, 6, 6, 40, 60, 120);
									//printText((preview.x + preview.w/2 - strlen(leveldata[z].name) * font.w / 2), preview.y + preview.h + 8, leveldata[z].name);
								}
							}
							else{
								if(questionMark[m] == 1)
									drawFilledRect(preview.x + 10 + l*6, preview.y + k*6 + 10, 6, 6, 0, 0, 0);
							}
							m++;
						}
					}
					
					if(leveldata[z].played){
						
						if(leveldata[z].help){
							help.x = preview.x + preview.w - help.w;
							help.y = preview.y + preview.h - help.h;
							drawSprite(help);
						}
						
						if(frames<120)
							printText((preview.x + preview.w/2 - strlen(leveldata[z].name) * font.w / 2), preview.y + preview.h + 8, leveldata[z].name);
						else{
							sprintf(timeStr, "TIME %02d:%02d", leveldata[z].min, leveldata[z].sec);
							printText((preview.x + preview.w/2 - strlen(timeStr) * font.w / 2), preview.y + preview.h + 8, timeStr);
						}
					}
					
					z++;
					puzzlesInPage++;
				}
			}
			preview.x = startX;
		}
		
		if(currentPage > 0){
			if(px >= arrowL.x && px <= arrowL.x + arrowL.w && py >= arrowL.y && py <= arrowL.y + arrowL.h && currentPage > 0)
				arrowL.frame = 1;
			else
				arrowL.frame = 0;
			drawSprite(arrowL);
			
			sprintf(pageStr, "%d/%d", currentPage, numPages+1);
			printText(42, 186, pageStr);
		}
		
		if(numPages > 0 && currentPage < numPages){
			if(px >= arrowR.x && px <= arrowR.x + arrowR.w && py >= arrowR.y && py <= arrowR.y + arrowR.h && currentPage < numPages)
				arrowR.frame = 1;
			else
				arrowR.frame = 0;
			drawSprite(arrowR);
			
			sprintf(pageStr, "%d/%d", currentPage+2, numPages+1);
			printText(556, 186, pageStr);
		}
			
			//556 42
		// input
		updateWiimote();
		isOT = moveCursorPointer(&posX, &posY);
		PAD_ScanPads();
		buttonsDown = PAD_ButtonsDown(0);
		
		if(((buttonsDown & PAD_TRIGGER_R)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_PLUS)
		#endif
		)&& currentPage < numPages
		){
			playBloop();
			currentPage++;
			posX = 0;
			posY = 0;
		}
		
		if(buttonsDown & PAD_BUTTON_X){
			sprintf(sscc, "ss-%d.png", ssc);
			ssc++;
			IMGCTX pngContext;
			if ( (pngContext = PNGU_SelectImageFromDevice (sscc)) ){
				PNGU_EncodeFromYCbYCr (pngContext, 640, 480, xfb[whichfb], 0);
				PNGU_ReleaseImageContext (pngContext);
			}
		}
		
	/*
					else if(buttonsDown & PAD_TRIGGER_L){
			IMGCTX pngContext;
			if ( (pngContext = PNGU_SelectImageFromDevice ("/scrnsht2.png")) ){
			PNGU_EncodeFromYCbYCr (pngContext, 640, 480, xfb[whichfb], 0);
			PNGU_ReleaseImageContext (pngContext);
			}
			}
			*/
		
		if(((buttonsDown & PAD_TRIGGER_L)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_MINUS)
		#endif
		)&& currentPage > 0
		){
			playBloop();
			currentPage--;
			posX = 0;
			posY = 0;
		}
		
		else if((buttonsDown & PAD_BUTTON_RIGHT)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_DOWN)
		#endif
		){
			posX++;
			posX = posX%3;
		}
		
		else if((buttonsDown & PAD_BUTTON_LEFT)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_UP)
		#endif
		){
			if(posX == 0)
				posX = 2;
			else
				posX--;
		}
		
		else if((buttonsDown & PAD_BUTTON_DOWN)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_LEFT)
		#endif
	    ){
			posY++;
			posY = posY%3;
		}
		
		else if((buttonsDown & PAD_BUTTON_UP)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_RIGHT)
		#endif
		){
			if(posY == 0)
				posY = 2;
			else
				posY--;
		}
		
		else if( (buttonsDown & PAD_BUTTON_A)
		#ifdef HW_RVL
		|| ((wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_2))
		#endif
		){
			level = (9*currentPage) + (posY * 3 + posX);
			if(level < NUMLEVELS){
				//playBloop();
				break;
			}
		}
		
		else if((buttonsDown & PAD_BUTTON_START)
		#ifdef HW_RVL
		|| (wpads[0]->btns_d & WPAD_BUTTON_HOME)
		#endif
		){
			pauseScreen();
		}
		
		#ifdef HW_RVL
		else if(wpads[0]->btns_d & WPAD_BUTTON_A){
		
			if((px > 545 || px < 92) && !isOT){
			
				if(px >= arrowL.x && px <= arrowL.x + arrowL.w && py >= arrowL.y && py <= arrowL.y + arrowL.h && currentPage > 0){
					currentPage--;
					posX = 0;
					posY = 0;
					//playBloop();
					//breakpoint("dx", 0);
				}
				
				else if(px >= arrowR.x && px <= arrowR.x + arrowR.w && py >= arrowR.y && py <= arrowR.y + arrowR.h && currentPage < numPages){
					currentPage++;
					posX = 0;
					posY = 0;
					//playBloop();
					//breakpoint("sx", 1);
				}
			}
			
			if((posY * 3 + posX < puzzlesInPage) && isOT){
				level = (9*currentPage) + (posY * 3 + posX);
				//playBloop();
				break;
			}
		}
		
		//# else
		//isOT = true;
		#endif
		// end input
		
		//
		// DEBUG
		//
		/*
		#ifdef HW_RVL
		if(wpads[0]->btns_d & WPAD_BUTTON_HOME)
			exit=true;
		if(buttonsDown & PAD_BUTTON_X)
			break;		
		#endif
		*/
		
		// NEW
		
		if(backToMenu){
			//backToMenu = false;
			//breakpoint("ssss", 123);
			level = -1;
			break;
		}
		
		
		updateFrames();
		
		if(frames < 240)
			frames++;
		else
			frames = 0;
		
		//drawLevelSelectCursor(startX -2 + (preview.w + xDistance)*posX, startY -2 + (preview.h + yDistance)*posY);
		#ifdef HW_RVL
		drawSprite(cursor_hand);
		#endif
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}
	
	//fade(0);
	
	//SND_Pause(1);
	
	playBloop();
	sleepMSeconds(10);
	
	timeElapsed.minutes = 0;
	timeElapsed.seconds = 0;
	
	markerH.r = 255;
	markerH.g = 255;
	markerH.b = 0;
	
	oy = posY;
	ox = posX;
	
	return level;
}

bool moveCursorPointer(int* posX, int* posY){

	#ifndef HW_RVL
		return false;
	#endif
	
	if(!wpads[0]->ir.valid)
		return false;
	
	bool isOTx = false;
	bool isOTy = false;
	
	int tmpX = -1;
	int tmpY = -1;
	
	if(px > 100 && px < 200){
		//*posX = 0;
		tmpX = 0;
		isOTy = true;
	}
	else if(px > 264 && px < 372){
		//*posX = 1;
		tmpX = 1;
		isOTy = true;
	}
	else if(px > 436 && px < 540){
		//*posX = 2;
		tmpX = 2;
		isOTy = true;
	}
		
	if(py > 30 && py < 140){
		tmpY = 0;
		//*posY = 0;
		isOTx = true;
	}
	else if(py > 172 && py < 281){
		//*posY = 1;
		tmpY = 1;
		isOTx = true;
	}
	else if(py > 314 && py < 424){
		//*posY = 2;
		tmpY = 2;
		isOTx = true;
	}
	
	if(isOTx && isOTy){
		*posX = tmpX;
		*posY = tmpY;
	}
	
	return (isOTx && isOTy);
}
#ifdef HW_DOL
#pragma GCC diagnostic pop
#endif
