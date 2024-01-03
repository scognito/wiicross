#include "../include/wiicross.h"
#include "../include/graphics.h"
#include "../include/titleScreen.h"

bool exitTS;
bool modeplayVisible;
int cursorOptionX = 0;
int cursorOptionY = 0;
int frames;
int modePlayPosition;

extern s_option options;
extern s_sprite eyes_ts;

void titleScreen(){

	exitTS = false;
	frames = 0;
	modeplayVisible = false;
	modePlayPosition = 0;
	
	playTitleScreenMusic();

	
	// fade
	
	/*
	whichfb = 0;
	//VIDEO_SetNextFramebuffer(xfb[whichfb]);
	VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
	drawBackground(bg_titlescreen);
	drawSprite(button_soce);
	drawSprite(eyes_ts);
	fadeOut();
	*/
	
	while(!exitTS){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
		
		if(isChristmas())
			drawBackground(bg_titlescreen_xmas);
		else
			drawBackground(bg_titlescreen);
		
		if(frames <= 180)
			eyes_ts.frame = 0;
		else if(frames > 180 && frames <= 182)
			eyes_ts.frame = 1;
		else if(frames > 182 && frames <= 184)
			eyes_ts.frame = 2;
		else if(frames > 184 && frames <= 186)
			eyes_ts.frame = 3;
		else
			frames = 0;
		
		checkInputTS();
		
		button_soce.frame = cursorOptionX;
		drawSprite(button_soce);
		if(modeplayVisible){
			modeplay.frame = modePlayPosition;
			drawSprite(modeplay);
		}
		drawSprite(eyes_ts);
		//if(options.padType == PAD_WII)
		updateWiimote();
		#ifdef HW_RVL
		drawSprite(cursor_hand);
		#endif
		
		frames++;
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}
	
	sleepMSeconds(30);
}

void checkInputTS(){
	
	updateWiimote();
	PAD_ScanPads();
	int buttonsDown = PAD_ButtonsDown(0);
	//int buttonsHeld = PAD_ButtonsHeld(0);
	
	//POINTING
	#ifdef HW_RVL
	int px, py;
		
	//px = pointer.x + pointer.w;
	//py = pointer.y + pointer.h;
	px = cursor_hand.x;
	py = cursor_hand.y;
	
	if(!modeplayVisible){
		if(py >= 370 && py <= 450){
			if(px >= 56 && px <= 172){
				cursorOptionX = 0;
			}
			
			else if(px >=  173 && px <= 332){
				cursorOptionX = 1;
			}
			
			else if(px >= 333 && px <= 484){
				cursorOptionX = 2;
			}
			
			else if(px >= 485 && px <= 585){
				cursorOptionX = 3;
			}
		}
	}
	
	else{
		if(px >= 174 && px <= 461 && py >= 287){
			if(py >= 288 && py <= 332){
				modePlayPosition = 0;
			}
			else if(py >= 338 && py <= 380){
				modePlayPosition = 1;
			}
			else if(py >= 384 && py <= 434){
				modePlayPosition = 2;
			}
		}
	}
	
	#endif
	
	
	if(!modeplayVisible){
		if( (buttonsDown & PAD_BUTTON_RIGHT)
		#ifdef HW_RVL
		||
		((wpads[0]->btns_d & WPAD_BUTTON_DOWN))
		#endif
		){
			cursorOptionX++;
			cursorOptionX = cursorOptionX%4;
		}
		
		else if((buttonsDown & PAD_BUTTON_LEFT)
		#ifdef HW_RVL
		||
		((wpads[0]->btns_d & WPAD_BUTTON_UP))
		#endif
		){
			cursorOptionX--;
			if(cursorOptionX < 0)
				cursorOptionX = 3;
		}
	}
	else{
		if( (buttonsDown & PAD_BUTTON_DOWN)
		#ifdef HW_RVL
		||
		((wpads[0]->btns_d & WPAD_BUTTON_LEFT))
		#endif
		){
			modePlayPosition++;
			modePlayPosition = modePlayPosition%3;
		}
		
		else if((buttonsDown & PAD_BUTTON_UP)
		#ifdef HW_RVL
		||
		((wpads[0]->btns_d & WPAD_BUTTON_RIGHT))
		#endif
		){
			modePlayPosition--;
			if(modePlayPosition < 0)
				modePlayPosition = 2;
		}
	}
	
	
	if((buttonsDown & PAD_BUTTON_A || buttonsDown & PAD_BUTTON_START)
		#ifdef HW_RVL
		||
		(wpads[0]->btns_d & WPAD_BUTTON_2)
		||
		((wpads[0]->btns_d & WPAD_BUTTON_A)
		  &&
		  ((!modeplayVisible && py >= 370 && py <= 450 ) || ( modeplayVisible && px >= 174 && px <= 461 && py >= 287))
		)
		#endif
	){
		if(!modeplayVisible){
			
			playBloop();
			
			if(cursorOptionX == 0)
				modeplayVisible = true;
			else if(cursorOptionX == 1)
				optionScreen();
			else if(cursorOptionX == 2)
				creditScreen();
			else if(cursorOptionX == 3)
				exitGame();
		}
		else if(modeplayVisible){
			
			playBloop();
			
			if(modePlayPosition == 0){
				exitTS = true;
				game.mode = MODE_NORMAL;
			}
			else if(modePlayPosition == 1){
				exitTS = true;
				game.mode = MODE_FREE;
			}
			else{
				howToPlayScreen();
			}
		}
	}
	
	else if( ((buttonsDown & PAD_BUTTON_B) && modeplayVisible)
			#ifdef HW_RVL
			||
			((wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_B))
			#endif
	){
		modeplayVisible = false;
	}
	
	#ifdef HW_RVL
	if(px >= 256 && px <= 392 && py >= 72 && py <= 148 && (wpads[0]->btns_d & WPAD_BUTTON_A)){
		frames = 181; // make the eyes close when you click on them
	}
	#endif
	
	if(buttonsDown & PAD_TRIGGER_L){
		sprintf(sscc, "ss-%d.png", ssc);
		ssc++;
		IMGCTX pngContext;
		if ( (pngContext = PNGU_SelectImageFromDevice (sscc)) ){
			PNGU_EncodeFromYCbYCr (pngContext, 640, 480, xfb[whichfb], 0);
			PNGU_ReleaseImageContext (pngContext);
		}
	}
}
