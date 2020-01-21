#include "../include/wiicross.h"
#include "../include/graphics.h"
#include "../include/creditScreen.h"

bool exitCS;

void creditScreen(){

	sleepMSeconds(30);
	
	exitCS = false;
	back.frame = 1;
	
	while(!exitCS){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer(vmode, xfb[whichfb], COLOR_BLACK);
		
		checkInput_CS();
		
		drawBackground(bg_creditScreen);
		drawSprite(back);
		#ifdef MAKE_WII
		drawSprite(cursor_hand);
		#endif
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}

	sleepMSeconds(30);
}

void checkInput_CS(){

	updateWiimote();
		
	PAD_ScanPads();
	int buttonsDown = PAD_ButtonsDown(0);
	
	if((buttonsDown & PAD_BUTTON_A)
		#ifdef MAKE_WII
		||
		((wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_2) || (wpads[0]->btns_d & WPAD_BUTTON_A) || (wpads[0]->btns_d & WPAD_BUTTON_B))
		#endif
	  ){
		exitCS = true;
		playBloop();
	}
}
