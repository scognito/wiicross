#include "../include/wiicross.h"
#include "../include/graphics.h"
#include "../include/optionScreen.h"

bool exitOS;

int cursorX;
int cursorY;
int cursorOption;
int oldMusicType, oldPadType;
char oldTheme[255];

extern s_option options;
extern bool exitTS;
s_theme theme;

void optionScreen(){

	cursorX = 56;
	cursorY = 124;
	cursorOption = 0;
	
	exitOS = false;
	controllertype.frame = options.padType;
	musictype.frame = options.musicType;
	
	oldMusicType = options.musicType; 
	oldPadType = options.padType;
	sprintf(oldTheme, "%s", theme.themesArray[theme.currentTheme]);
	//oldTheme = options.;
	
	//theme.totalThemes = readThemesDir();
	//breakpoint(oldTheme, 123);
	
	while(!exitOS){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer(vmode, xfb[whichfb], COLOR_BLACK);
		
		drawBackground(bg_options);
		
		checkInput_OS();
		
		if(cursorOption == 3)
			back.frame = 1;
		else
			back.frame = 0;
		
		if(theme.currentTheme <= 5)
			themetype.frame = theme.currentTheme;
		else
			themetype.frame = 6;
		
		musictype.frame = options.musicType;
		
		opt.frame = cursorOption;
		eyes_os.frame = cursorOption;
		
		drawSprite(opt);
		drawSprite(controllertype);
		drawSprite(musictype);
		#ifndef MAKE_WII
		drawSprite(imageHack);
		#endif
		drawSprite(themetype);
		drawSprite(eyes_os);
		drawSprite(back);
		
		if(theme.currentTheme != 0)
			drawSprite(theme.titleArray[theme.currentTheme]);
		
		#ifdef MAKE_WII
			drawSprite(cursor_hand);
		#endif
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	}
	
	applyChanges();
	sleepMSeconds(20);
}

void checkInput_OS(){

	#ifdef MAKE_WII	
	
	updateWiimote();
	
	int px = cursor_hand.x;
	int py = cursor_hand.y;
	
	if(wpads[0]->ir.valid){
		if(py >= 90 && py <= 107){
			cursorOption = 0;
		}
		
		else if(py >= 160 && py <= 220){
			cursorOption = 1;
		}
		
		else if(py >= 270 && py <= 300){
			cursorOption = 2;
		}
		
		else if(py >= 370 && py <= 430 && px >= 444 && px <= 600){
			cursorOption = 3;
		}
	}
	#endif
	
	PAD_ScanPads();
	int buttonsDown = PAD_ButtonsDown(0);
	
	if((buttonsDown & PAD_BUTTON_DOWN)
		#ifdef MAKE_WII
		||
		(wpads[0]->btns_d & WPAD_BUTTON_LEFT)
		#endif
	  ){
		cursorOption++;
		cursorOption = cursorOption % 4;
	}
	
	else if((buttonsDown & PAD_BUTTON_UP)
		#ifdef MAKE_WII
		||
		(wpads[0]->btns_d & WPAD_BUTTON_RIGHT)
		#endif
	  ){
		cursorOption--;
		if(cursorOption < 0)
			cursorOption = 3;
	}
	
	else if((buttonsDown & PAD_BUTTON_RIGHT)
		#ifdef MAKE_WII
		||
		(wpads[0]->btns_d & WPAD_BUTTON_DOWN)
		#endif
	  ){
		
		if(cursorOption == 0){ // controller, can't be changed in gc
			#ifdef MAKE_WII
			controllertype.frame++;
			controllertype.frame = controllertype.frame % 3;
			playBloop();
			#endif
		}
		
		else if (cursorOption == 1){ // audio
			options.musicType++;
			#ifdef MAKE_WII
			options.musicType = options.musicType % 3;
			#else
			options.musicType = options.musicType % 2;
			#endif
			playBloop();
		}
		
		else if (cursorOption == 2){ // theme
			if(theme.totalThemes > 1){
				if(theme.currentTheme < theme.totalThemes-1){
					theme.currentTheme++;
				}
				else{
					theme.currentTheme=0;
				}
				playBloop();
			}
		}
	}
	
	else if((buttonsDown & PAD_BUTTON_LEFT)
		#ifdef MAKE_WII
		||
		(wpads[0]->btns_d & WPAD_BUTTON_UP)
		#endif
	  ){
		
		if(cursorOption == 0){ // controller
			#ifdef MAKE_WII
			if(controllertype.frame > 0)
				controllertype.frame--;
			else
				controllertype.frame = 2;
			playBloop();
			#endif
		}
		
		else if (cursorOption == 1){
			
			options.musicType--;
			if(options.musicType < 0)
				#ifdef MAKE_WII
				options.musicType = 2;
				#else
				options.musicType = 1;
				#endif
			playBloop();
		}
		
		else if (cursorOption == 2){
			if(theme.totalThemes > 1){
				if(theme.currentTheme > 0){
					theme.currentTheme--;
				}
				else{
					theme.currentTheme = theme.totalThemes-1;
				}
				playBloop();
			}
		}
	}
	
	else if((buttonsDown & PAD_BUTTON_A)
		#ifdef MAKE_WII
		||
		((wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_2))
		#endif
	){
		
		if(cursorOption == 0){ // controller
			#ifdef MAKE_WII
			controllertype.frame++;
			controllertype.frame = controllertype.frame % 3;
			playBloop();
			#endif
		}
		
		else if (cursorOption == 1){ // audio
			options.musicType++;
			#ifdef MAKE_WII
			options.musicType = options.musicType % 3;
			#else
			options.musicType = options.musicType % 2;
			#endif
			playBloop();
		}
		
		else if (cursorOption == 2){ // theme
			if(theme.totalThemes > 1){
				if(theme.currentTheme < theme.totalThemes-1){
					theme.currentTheme++;
				}
				else{
					theme.currentTheme=0;
				}
				playBloop();
			}
		}
		
		else if(cursorOption == 3){
			exitOS = true;
			playBloop();
		}
	}
	
	#ifdef MAKE_WII
	else if(wpads[0]->btns_d & WPAD_BUTTON_A){
	
		switch(cursorOption){
			case 0:
				controllertype.frame++;
				controllertype.frame = controllertype.frame % 3;
				playBloop();
				break;
			case 1:
				if(px >= 286 && px <= 358)
					options.musicType = MUSIC_ON;
				else if(px >= 287 && px <= 437)
					options.musicType = MUSIC_OFF;
				else if(px >= 438 && px <= 580)
					options.musicType = MUSIC_CUSTOM;
				else{
					options.musicType++;
					options.musicType = options.musicType % 3;
				}
				playBloop();
				break;
			case 2:
				if(theme.totalThemes > 1){
					if(theme.currentTheme < theme.totalThemes-1){
						theme.currentTheme++;
					}
					else{
						theme.currentTheme=0;
					}
					playBloop();
				}
				break;
			case 3:
				playBloop();
				exitOS = true;
				break;
		}
	}
	#endif
	
	if(buttonsDown & PAD_TRIGGER_R){
		sprintf(sscc, "ss-%d.png", ssc);
		ssc++;
		IMGCTX pngContext;
		if ( (pngContext = PNGU_SelectImageFromDevice (sscc)) ){
			PNGU_EncodeFromYCbYCr (pngContext, 640, 480, xfb[whichfb], 0);
			PNGU_ReleaseImageContext (pngContext);
		}
	}
}

void applyChanges(){

	//theme
	sprintf(options.theme, "%s", theme.themesArray[theme.currentTheme]);
	
	//breakpoint(options.theme, 456);
	
	//is theme changed?
	if(strcasecmp(options.theme, oldTheme) != 0){
		//breakpoint("theme changed", 1);
		if(theme.currentTheme != 0){
			//breakpoint(theme.themesArray[theme.currentTheme], 2);
			loadTheme(theme.themesArray[theme.currentTheme]);
		}
		else{ // default theme, hardcoded
			//("default", 3);
			loadTheme("default");
		}
	}

	//controller
	options.padType = controllertype.frame;
	
	//audio
	options.musicType = musictype.frame;
	
	if(exitTS){
		if(options.musicType != oldMusicType){
			if(options.musicType == MUSIC_OFF)
				SND_StopVoice(0);
			else if(options.musicType == MUSIC_ON && oldMusicType != MUSIC_ON)
				playDefaultLevelMusic();
			else if(options.musicType == MUSIC_CUSTOM && oldMusicType != MUSIC_CUSTOM)
				playOggMusic();
		}
	}
	
	#ifndef IS_EMU
	if((options.musicType != oldMusicType) || (options.padType != oldPadType) || (strcasecmp(options.theme, oldTheme) != 0)){
		//breakpoint("save ",123);
		writeSD(FILE_OPTIONS);
	}
	#endif
}
