#include "../include/wiicross.h"
#include "../include/graphics.h"
#include "../include/howToPlay.h"

bool exitHTP;
int currentScene;

void howToPlayScreen(){

	sleepMSeconds(30);
	
	exitHTP = false;
	currentScene = 1;
	
	arrowR.y = 380;
	arrowL.y = 380;
	
	
	while(!exitHTP){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer(vmode, xfb[whichfb], COLOR_BLACK);
		
		checkInput_HTP();
		
		switch(currentScene){
			case 1:
				drawBackground(bg_tut1);
				break;
			case 2:
				drawBackground(bg_tut2);
				break;
			case 3:
				drawBackground(bg_tut3);
				break;
			case 4:
				drawBackground(bg_tut4);
				break;
			default:
				drawBackground(bg_tut5);
				break;
		}
		
		drawSprite(arrowR);
		if(currentScene != 1)
			drawSprite(arrowL);
		
		//drawSprite(back);
		#ifdef MAKE_WII
		drawSprite(cursor_hand);
		#endif
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}

	arrowR.y = 208;
	arrowL.y = 208;
	
	sleepMSeconds(30);
}

void checkInput_HTP(){

	updateWiimote();
		
	PAD_ScanPads();
	int buttonsDown = PAD_ButtonsDown(0);
	
	//POINTING
	#ifdef MAKE_WII
	int px, py;
	
	px = cursor_hand.x;
	py = cursor_hand.y;
	
	if(py >= arrowR.y && py <= arrowR.y + arrowR.h && px >= arrowR.x && px <= arrowR.x + arrowR.w){
		arrowR.frame = 1;
	}
	else if(py >= arrowL.y && py <= arrowL.y + arrowL.h && px >= arrowL.x && px <= arrowL.x + arrowL.w){
		arrowL.frame = 1;
	}
	else{
		arrowL.frame = 0;
		arrowR.frame = 0;
	}
	#endif
	
	if((buttonsDown & PAD_BUTTON_RIGHT) || (buttonsDown & PAD_BUTTON_A)
		#ifdef MAKE_WII
		||
		((wpads[0]->btns_d & WPAD_BUTTON_RIGHT) || (wpads[0]->btns_d & WPAD_BUTTON_DOWN))
		#endif
	  ){
		
		if(currentScene < 5)
			currentScene++;
		else
			exitHTP = true;
		playBloop();
	}
	
	if((buttonsDown & PAD_BUTTON_LEFT) || (buttonsDown & PAD_BUTTON_B)
		#ifdef MAKE_WII
		||
		((wpads[0]->btns_d & WPAD_BUTTON_LEFT) || (wpads[0]->btns_d & WPAD_BUTTON_UP))
		#endif
	  ){
		
		if(currentScene > 1){
			currentScene--;
			playBloop();
		}
	}
	
	#ifdef MAKE_WII	
	if(wpads[0]->btns_d & WPAD_BUTTON_A){
		if(py >= arrowR.y && py <= arrowR.y + arrowR.h && px >= arrowR.x && px <= arrowR.x + arrowR.w){
			if(currentScene < 5)
				currentScene++;
			else
				exitHTP = true;
			playBloop();
		}
		else if(py >= arrowL.y && py <= arrowL.y + arrowL.h && px >= arrowL.x && px <= arrowL.x + arrowL.w){
			if(currentScene > 1){
				currentScene--;
				playBloop();
			}		
		}
	}
	#endif
}
