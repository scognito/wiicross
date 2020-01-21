#include "../include/wiicross.h"
#include "../include/graphics.h"
#include "../include/pauseScreen.h"

bool exitPS;
int cOptionX;
int cOptionY;

extern bool backToMenu;
extern s_option options;

void pauseScreen(){

	button_soce.frame = 0;
	
	exitPS = false;
	
	cOptionX = 0;
	cOptionY = 0;

	sleepMSeconds(10);
	
	while(!exitPS){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
		
		drawBackground(bg_pause);
		
		checkInputPS();
		
		drawSprite(button_rote);
		
		updateWiimote();
		#ifdef MAKE_WII
			drawSprite(cursor_hand);
		#endif
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}
}



void checkInputPS(){
	
	updateWiimote();
	PAD_ScanPads();
	int buttonsDown = PAD_ButtonsDown(0);
	
	#ifdef MAKE_WII
	//POINTING
	int px, py;

	px = cursor_hand.x;
	py = cursor_hand.y;
	
	if(px >= 390 && px <= 545 && py >= 329 && py <= 383){
	   
		cOptionX = 1;
		cOptionY = 0;
	}
	
	else if(px >= 85 && px <= 344 && py >= 329 && py <= 383){
	   
		cOptionX = 0;
		cOptionY = 0;
	}
	
	else if(px >= 81 && px <= 298 && py >= 392 && py <= 445){
	   
		cOptionX = 0;
		cOptionY = 1;
	}
	
	else if(px >= 420 && px <= 514 && py >= 392 && py <= 445){
	   
		cOptionX = 1;
		cOptionY = 1;
	}
	#endif
	
	if((buttonsDown & PAD_BUTTON_DOWN)
	#ifdef MAKE_WII
	||
	(wpads[0]->btns_d & WPAD_BUTTON_LEFT)
	#endif
	){
		cOptionY ^= 1;
	}
	
	else if((buttonsDown & PAD_BUTTON_UP)
	#ifdef MAKE_WII
	||
	(wpads[0]->btns_d & WPAD_BUTTON_RIGHT)
	#endif
	){
		cOptionY ^= 1;
	}
	
	else if( ((buttonsDown & PAD_BUTTON_RIGHT))
	#ifdef MAKE_WII
	||
	(wpads[0]->btns_d & WPAD_BUTTON_DOWN)
	#endif
	){
		cOptionX ^= 1;
	}
	
	else if((buttonsDown & PAD_BUTTON_LEFT)
	#ifdef MAKE_WII
	||
	(wpads[0]->btns_d & WPAD_BUTTON_UP)
	#endif
	){
		cOptionX ^= 1;
	}
	
	else if((buttonsDown & PAD_BUTTON_START) // metti R per test
	#ifdef MAKE_WII
	|| (wpads[0]->btns_d & WPAD_BUTTON_HOME)
	#endif
	){
		exitPS = true;
	}
	
	else if((buttonsDown & PAD_BUTTON_A)
	#ifdef MAKE_WII
	||
	((wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_2) 
	  || ((wpads[0]->btns_d & WPAD_BUTTON_A) && ( px >= 80 && py >= 335 && px <= 548 && py <= 442)))
	#endif
	){
		button_rote.frame = 2 * cOptionY + cOptionX;
		playBloop();
		
		if(cOptionX == 0 && cOptionY ==0){
			exitPS = true;
			sleepMSeconds(30);
		}
		else if(cOptionX == 1 && cOptionY ==0){
			sleepMSeconds(30);
			optionScreen();
		}
		else if(cOptionX == 1 && cOptionY == 1){
			exitGame();
		}
		else if(cOptionX == 0 && cOptionY ==1){
			backToMenu = true;
			exitPS = true;
			if(options.musicType == MUSIC_CUSTOM){
				StopOgg();
			}
			sleepMSeconds(30);
		}
	}
	
	button_rote.frame = 2 * cOptionY + cOptionX;
}






int askSaveGame(){

	int phase = 0;
	int buttonsDown;
	bool exit = false;
	int cursorX = 0;
	int cursorY = 0;
	int px, py;
	int selection = 0;
	
	button_yes.x = 138;
	button_yes.y = savegame.y;
	
	button_no.x = 320;
	button_no.y = savegame.y;
	 
	button_cancel.x = 228;
	button_cancel.y = savegame.y;
	
	while(!exit){
	
		int speed = 8;
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer(vmode, xfb[whichfb], COLOR_BLACK);

		drawBackground(bg_pause);
		
		savegame.hidden = false;
		button_yes.hidden = false;
		button_no.hidden = false;
		button_cancel.hidden = false;
		
		if(phase == 0){
			if(savegame.y > 140){
				savegame.y -= speed;
				button_yes.y -= speed;
				button_no.y -= speed;
				button_cancel.y -= speed;
			}
			else{
				phase = 1;
			}
		}
		
		else if(phase == 1){
		
			if(button_no.y < 250){
				button_no.y += speed;
				button_yes.y += speed;
				button_cancel.y += speed + 2;
			}
			else
				phase = 2;
		}
		
		else if(phase == 2){
		
			if(button_yes.x > 80){
				button_yes.x -= speed;
				button_no.x += speed;
				button_cancel.y += speed;
			}
			else
				phase = 3;
		}
		
		else if(phase == 3){
			
			px = cursor_hand.x;
			py = cursor_hand.y;
			
			PAD_ScanPads();
			buttonsDown = PAD_ButtonsDown(0);
			
			if( ((buttonsDown & PAD_BUTTON_A || buttonsDown & PAD_BUTTON_START))
				#ifdef MAKE_WII
				||
				((wpads[0]->btns_d & WPAD_BUTTON_A) || (wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_2))
				#endif
			){
				phase = 4;
			}
			
			else if( (((buttonsDown & PAD_BUTTON_RIGHT))
				#ifdef MAKE_WII
				||
				((wpads[0]->btns_d & WPAD_BUTTON_DOWN))
				#endif
				)
			){
				selection++;
				selection = selection % 3;
			}
			
			else if( (((buttonsDown & PAD_BUTTON_LEFT))
				#ifdef MAKE_WII
				||
				((wpads[0]->btns_d & WPAD_BUTTON_UP))
				#endif
				)
			){
				selection--;
				if(selection < 0)
					selection = 2;
			}

			#ifdef MAKE_WII
			//POINTER
			if(px > button_yes.x && px < button_yes.x + button_yes.w && py > button_yes.y && py < button_yes.y + button_yes.h){
				cursorX = button_yes.x;
			}
			else if(px > button_no.x && px < button_no.x + button_no.w && py > button_no.y && py < button_no.y + button_no.h){
				cursorX = button_no.x;
			}
			#endif
			
			switch(selection){
				case 0:
					cursorX = button_yes.x;
					cursorY = button_yes.y + button_yes.h;
					break;
				case 1:
					cursorX = button_cancel.x;
					cursorY = button_cancel.y + button_cancel.h;
					break;
				case 2:
					cursorX = button_no.x;
					cursorY = button_no.y + button_no.h;
					break;
			}
		}
		
		else if(phase == 4){
			if(button_yes.x < 140){
				button_yes.x += speed;
				button_no.x -= speed;
				button_cancel.y -= speed-2;
			}
			else{
				phase = 5;
			}
		}
		
		else if(phase == 5){
			if(button_yes.y > savegame.y){
				button_yes.y -= speed;
				button_no.y -= speed;
				button_cancel.y -= speed;
			}
			else
				phase = 6;
		}
		
		else if(phase == 6){
			if(savegame.y < 400 ){
				savegame.y += speed*2;
				button_yes.y = savegame.y;
				button_no.y = savegame.y;
				button_cancel.y = savegame.y;
			}
			else
				phase = 7;
		}
		
		else if(phase == 7){
			exit = true;
			savegame.hidden = true;
			button_yes.hidden = true;
			button_no.hidden = true;
			button_cancel.hidden = true;
		}

		drawSprite(button_rote);
		
		drawSprite(button_yes);
		drawSprite(button_no);
		drawSprite(button_cancel);
		drawSprite(savegame);
		
		drawFilledRect(cursorX, cursorY, button_no.w, 5, 255, 0, 0);
		
		updateWiimote();
		drawSprite(cursor_hand);
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}
	
	return selection;
}
