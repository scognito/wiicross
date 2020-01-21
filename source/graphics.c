#include "../include/wiicross.h"
#include "../include/graphics.h"

extern s_matrix matrix;
extern s_time timeElapsed;
extern s_event event;
extern s_level leveldata[NUMLEVELS];
extern s_option options;
//extern s_theme theme;

s_marker markerH; // horizontal marker
s_marker markerV; // vertical marker

int px, py;

extern bool newMove;

void initGfx(){

	int spriteError = 0;
	int bgError = 0;
	
	// sprites
	spriteError = createSprite(&fontNumber, fontNumber_png, "", 0, 0, 16, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&font, font_png, "", 0, 0, 60, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&squareCursor, squarecursor_png, "", SQUARECURSOR_MIN_X, SQUARECURSOR_MIN_Y, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&tileFilled, filled_png, "", 0, 0, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&tileMarked, marked_png, "", 0, 0, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&errorMsg, error_png, "", 0, 0, 6, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&levelComplete, levelcomplete_png, "", 0, 178, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&preview, preview_png, "", 0, 0, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&arrowL, arrowL_png, "", 48, 208, 2, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&arrowR, arrowR_png, "", 558, 208, 2, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&button_yes, button_yes_png, "", 138, 388, 2, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&button_no, button_no_png, "", 320, 388, 2, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);

	spriteError = createSprite(&button_cancel, button_cancel_png, "", 228, 308, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&needhelp, needhelp_png, "", 138, 268, 2, FMT_PNG, false); //308
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);

	spriteError = createSprite(&savegame, savegame_png, "", 138, 308, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&controllertype, controllertype_png, "", 292, 28, 3, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&musictype, musictype_png, "", 292, 176, 3, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&themetype, themetype_png, "", 354, 248, 7, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&pointer, pencil_png, "", 50, 50, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&opt, opt_png, "", 58, 82, 4, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);

	spriteError = createSprite(&back, button_back_png, "", 446, 379, 2, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&button_soce, button_soce_png, "", 56, 380, 4, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&eyes_ts, eyes_ts_png, "", 246, 18, 4, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);

	spriteError = createSprite(&eyes_os, eyes_os_png, "", 78, 370, 4, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);

	spriteError = createSprite(&font_clock, font_clock_png, "", 144, 53, 10, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&msg_outoftime, outoftime_png, "", 120, 58, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&button_rote, button_rote_png, "", 82, 329, 4, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	spriteError = createSprite(&cursor_hand, cursor_hand_png, "", 58, 64, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&minitile, minitile_png, "", 0, 0, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&help, help_png, "", 0, 0, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&modeplay, modeplay_png, "", 174, 268, 3, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
	
	spriteError = createSprite(&imageHack, imageHack_png, "", 442, 178, 1, FMT_PNG, false);
	if( spriteError != 1)
		breakpoint("cannot load resource", spriteError);
		
	//spriteError = createSprite(&timer, timer_png, "", 30, 30, 1, FMT_PNG, false);
	//if( spriteError != 1)
	//	breakpoint("cannot load resource", spriteError);
	
	// backgrounds
	if(isChristmas())
		bgError = createBackground(&bg1, bg_xmas_png, "", 0, 0, FMT_PNG, false);
	else
		bgError = createBackground(&bg1, bg1_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource", bgError);	
	
	bgError = createBackground(&bg, bg_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource bg", bgError);	
	
	bgError = createBackground(&bg_titlescreen, titlescreen_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource titlescreen", bgError);
	
	bgError = createBackground(&bg_titlescreen_xmas, titlescreen_xmas_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource titlescreen", bgError);
	
	bgError = createBackground(&bg_options, bg_options_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource optionscreen", bgError);
		
	bgError = createBackground(&bg_pause, bg_pause_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource optionscreen", bgError);
	
	bgError = createBackground(&bg_creditScreen, bg_creditscreen_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource optionscreen", bgError);
	
	bgError = createBackground(&splash_sco, splash_sco_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource sco", bgError);
	
	bgError = createBackground(&splash_dd, splash_dd_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource sco", bgError);
	
	bgError = createBackground(&bg_tut1, bg_tut1_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource bg", bgError);	
	
	bgError = createBackground(&bg_tut2, bg_tut2_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource bg", bgError);	
	
	bgError = createBackground(&bg_tut3, bg_tut3_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource bg", bgError);	
		
	bgError = createBackground(&bg_tut4, bg_tut4_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource bg", bgError);	

	bgError = createBackground(&bg_tut5, bg_tut5_png, "", 0, 0, FMT_PNG, false);
	if( bgError != 1)
		breakpoint("cannot load resource bg", bgError);	
	
	markerH.x = SQUARECURSOR_MIN_X - 136;
	markerH.y = SQUARECURSOR_MIN_Y + 4;
	markerH.w = 136;
	markerH.h = 18;
	markerH.r = 255;
	markerH.g = 255;
	markerH.b = 255;
	markerH.dirColor = DIR_COLOR_DOWN;
	
	markerV.x = SQUARECURSOR_MIN_X - 132;
	markerV.y = 2;
	markerV.w = 18;
	markerV.h = 150; //144
	markerV.r = 255;
	markerV.g = 255;
	markerV.b = 0;
	markerV.dirColor = DIR_COLOR_DOWN;
}


void drawScene(){

	int i, j;

	whichfb ^= 1;
	VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
	
	int coorX = 280;
	int coorY = 159; //152
	
	drawBackground(bg1);
	drawRectMarker();
		
	//rows
	for(i=0; i< ROWLEN; i++){
		for(j=7; j >= 0; j--){
			if(matrix.row[i][j] != -1){
				fontNumber.x = coorX;
				fontNumber.y = coorY;
				fontNumber.frame = matrix.row[i][j];
				drawSprite(fontNumber);
				coorX -= 16;
			}
		}
		coorX = 280;
		coorY += 20;
	}
	
	coorX = 306;
	coorY = 138; //126
	
	//columns
	for(i=0; i< ROWLEN; i++){
		for(j=7; j >= 0; j--){
			if(matrix.col[i][j] != -1){
				fontNumber.x = coorX;
				fontNumber.y = coorY;
				fontNumber.frame = matrix.col[i][j];
				drawSprite(fontNumber);
				coorY -= 16;
			}
		}
		coorY = 138; //126
		coorX += 20;
	}
	
	for(i=0; i < ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
				tileFilled.x = SQUARECURSOR_MIN_X + 4 + i*20;
				tileFilled.y = SQUARECURSOR_MIN_Y + 4 + j*20;
				tileMarked.x = SQUARECURSOR_MIN_X + 4 + i*20;
				tileMarked.y = SQUARECURSOR_MIN_Y + 4 + j*20;
			if(matrix.currentLevel[j][i].state == TILE_MARKED)
				drawSprite(tileMarked);
			else if(matrix.currentLevel[j][i].state == TILE_DRAWN)
				drawSprite(tileFilled);
		}
	}
	
	//printErrors(30, 100);
	drawSprite(timer);
	printTime(30, 70);
	drawPreview(38, 348);
	drawSprite(squareCursor);
	updateEventsGfx();
	
	if(timeElapsed.minutes >= 99)
		drawSprite(msg_outoftime);
	
	//px = pointer.x + pointer.w;
	//py = pointer.y + pointer.h;
	
	/*
	char a[100];
	sprintf(a, "%d", wpads[0]->ir.valid);
	printText(70, 170, a);
	
	sprintf(a, "%d", wpads[0]->ir.state);
	printText(70, 190, a);
	*/
	//sprintf(succa, "%d", game.tileCount);
	//printText(20, 20, succa);
	
	//if(pointerVisible)
	#ifdef MAKE_WII
	if(options.padType == PAD_WII)
		drawSprite(pointer);
	#endif
	
	drawSprite(errorMsg);
	/*
	//drawFilledRect(100, 100, 200, 100, 255, 0, 0);
	
	*/
	VIDEO_SetNextFramebuffer(xfb[whichfb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
}

void drawPreview(int x, int y){
	
	int i,j;
	
	for(i=0; i < ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
			if(matrix.currentLevel[j][i].state == TILE_DRAWN){
				drawFilledRect(x + i*6, y + j*6, 6, 6, 40, 60, 120);
				//minitile.x = x + i*6;
				//minitile.y = y + j*6;
				//drawSprite(minitile);
			}
		}
	}
}

void drawRectMarker(){
	
	markerV.x = squareCursor.x + 4;
	markerH.y = squareCursor.y + 4;
	
	if(game.frames % 5 == 0){
		if(markerH.dirColor == DIR_COLOR_DOWN){
			markerH.r -= 10;
			markerH.g -= 10;
			
			if(markerH.r < 200)
				markerH.dirColor = DIR_COLOR_UP;
		}
		else{
			markerH.r += 10;
			markerH.g += 10;
			
			if(markerH.r >= 255)
				markerH.dirColor = DIR_COLOR_DOWN;
		}
		
	}
	
	drawFilledRect(markerV.x, markerV.y, markerV.w, markerV.h, markerH.r, markerH.g, markerH.b);
	drawFilledRect(markerH.x, markerH.y, markerH.w, markerH.h, markerH.r, markerH.g, markerH.b);
}

void drawLevelSelectCursor(int x, int y){
	
	if(game.frames % 5 == 0){
		if(markerH.dirColor == DIR_COLOR_DOWN){
			markerH.r -= 20;
			markerH.g -= 20;
			markerH.b -= 20;
			
			if(markerH.r < 41)
				markerH.dirColor = DIR_COLOR_UP;
		}
		else{
			markerH.r += 20;
			markerH.g += 20;
			markerH.b += 20;
			
			if(markerH.r >= 255)
				markerH.dirColor = DIR_COLOR_DOWN;
		}
	}
	
	drawFilledRect(x, y, 122, 10, markerH.r, markerH.g, markerH.b); // -
	drawFilledRect(x, y, 10, 122, markerH.r, markerH.g, markerH.b); // |
	drawFilledRect(x, y+112, 122, 10, markerH.r, markerH.g, markerH.b); // _
	drawFilledRect(x+112, y, 10, 122, markerH.r, markerH.g, markerH.b);
	
	/*
	char a[100];
	sprintf(a, "%d", game.frames);
	printText(10, 10, a);
	*/
}

void printText(int x, int y, char* text){
	
	font.x = x;
	font.y = y;
	
	while(*text != '\0'){
			
		if( (*text < 32) || (*text > 90 && *text <97) || (*text >=123))
			font.frame = 0; // unknown
		else if(*text >= 97 && *text <= 122)
			font.frame =  -63 + *text; // a -> A
		else
			font.frame = -31 + *text;
			
		drawSprite(font);
		font.x += font.w;
		++text;
	}
}

void printTime(int x, int y){

	//char timeStr[12];
	
	/*
	if(timeElapsed.minutes >= 99){
		printText(x, y, "TIME OVER!");
	}
	else
	*/
	
	if(timeElapsed.minutes < 99)
	{
	
		font_clock.x = 144;
		if(timeElapsed.minutes > 9){
			font_clock.frame = timeElapsed.minutes/10;
		}
		else{
			font_clock.frame = 0;
		}
		drawSprite(font_clock);
		
		font_clock.x += font_clock.w;
		font_clock.frame = timeElapsed.minutes%10;
		drawSprite(font_clock);
	
		font_clock.x = 200;
		if(timeElapsed.seconds > 9){
			font_clock.frame = timeElapsed.seconds/10;
		}
		else{
			font_clock.frame = 0;
		}
		drawSprite(font_clock);
		
		font_clock.x += font_clock.w;
		font_clock.frame = timeElapsed.seconds%10;
		drawSprite(font_clock);
	
		//sprintf(timeStr, "TIME:%02d:%02d", timeElapsed.minutes, timeElapsed.seconds);
		//printText(x, y, timeStr);
	}
}

void printErrors(int x, int y){

	char errorStr[11];
	
	sprintf(errorStr, "ERRORS:%02d", game.errors);
	printText(x, y, errorStr);
}

void updateEventsGfx(){
	
	int speed = 2;
	
	if(event.errorImgDistance > 0){
		event.errorImgDistance -= speed;
		errorMsg.y -= speed;
	}
	else
		errorMsg.hidden = true;
}

void fadeIn(){

	int x = 0;
	int y = 0;
	int i = 0;
	int step = 10;
	
	u32 *tempXfb = malloc(sizeof(u32)*(640>>1)*480);
	//screenshot
	memcpy(&tempXfb, &xfb[whichfb][0], (640<<1)*480);

	for(i=0; i<11; i++){
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);	
		memcpy(&xfb[whichfb][0], &tempXfb, (640<<1)*480);
		
		for(y=0; y < 48; y++){
			for(x=0; x < 64; x++){
				drawFilledRect(x * step, y*step, i, i, 0, 0, 0);
			}
		}
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
		sleepMSeconds(20);
	}
	
	free(tempXfb);
}

void fadeOut(){

	int x = 0;
	int y = 0;
	int i = 0;
	int step = 10;
	
	whichfb = 1;
	VIDEO_SetNextFramebuffer(xfb[whichfb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	u32 *tempXfb = malloc(sizeof(u32)*(640>>1)*480);
	//screenshot
	memcpy(&tempXfb, &xfb[whichfb][0], (640<<1)*480);
	memcpy(&xfb[whichfb][0], &tempXfb, (640<<1)*480);
	
	VIDEO_Flush();
	VIDEO_WaitVSync();
	
	for(i=10; i>0; i--){
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);	
		memcpy(&xfb[whichfb][0], &tempXfb, (640<<1)*480);
		
		for(y=0; y < 48; y++){
			for(x=0; x < 64; x++){
				drawFilledRect(x * step, y*step, i, i, 255, 0, 0);
			}
		}
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
		//sleepSeconds(1);
		sleepMSeconds(20);
	}
	
	//breakpoint("pre free", 0);
	//free(&tempXfb);
}

void showLevelComplete(){	
	
	playLevelCleared();
	sleepMSeconds(30);
	levelComplete.x = 320 - levelComplete.w / 2;
	levelComplete.y = 240 - levelComplete.h / 2;
	drawSprite(levelComplete);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	sleepSeconds(3);
}

bool helpNeeded(int whichLevel){

	int i,j,k;
	int phase = 0; //7
	bool wantHelp = false;
	int buttonsDown;
	bool exit = false;
	int zCountX = 0;
	int zCountY = 0;
	
	// mark all columns and rows with only 0 values
	for(i=0; i< ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
			if(matrix.currentLevel[i][j].value == 1){
				zCountX++;
			}
			
			if(matrix.currentLevel[j][i].value == 1){
				zCountY++;
			}
		}
		
		if(zCountX == 0){
			for(k=0; k<15; k++)
				matrix.currentLevel[i][k].state = TILE_MARKED;
		}
		if(zCountY == 0){
			for(k=0; k<15; k++)
				matrix.currentLevel[k][i].state = TILE_MARKED;
		}
		zCountY = 0;
		zCountX = 0;
	}
	
	needhelp.hidden = false;
	button_yes.hidden = false;
	button_no.hidden = false;
	
	
	button_yes.x = 138;
	button_yes.y = 388;//408;//388
	button_no.x = 320;
	button_no.y = 388;//408;//388
		

	while(!exit){
	
		int coorX = 280;
		int coorY = 159; //152
		int speed = 8;
	
		whichfb ^= 1;
		VIDEO_ClearFrameBuffer(vmode, xfb[whichfb], COLOR_BLACK);

		drawBackground(bg1);
			
		//rows
		for(i=0; i< ROWLEN; i++){
			for(j=7; j >= 0; j--){
				if(matrix.row[i][j] != -1){
					fontNumber.x = coorX;
					fontNumber.y = coorY;
					fontNumber.frame = matrix.row[i][j];
					drawSprite(fontNumber);
					coorX -= 16;
				}
			}
			coorX = 280;
			coorY += 20;
		}
		
		coorX = 306;
		coorY = 138; //126
		
		//columns
		for(i=0; i< ROWLEN; i++){
			for(j=7; j >= 0; j--){
				if(matrix.col[i][j] != -1){
					fontNumber.x = coorX;
					fontNumber.y = coorY;
					fontNumber.frame = matrix.col[i][j];
					drawSprite(fontNumber);
					coorY -= 16;
				}
			}
			coorY = 138; //126
			coorX += 20;
		}
		
		/*
		 *
		 * ANIMATION
		 *
		 */
		/*
		needhelp.hidden = false;
		button_yes.hidden = false;
		button_no.hidden = false;
		
		
		button_yes.x = 138;
		button_yes.y = 388;
		button_no.x = 320;
		button_no.y = 388;
		*/
		
		if(phase == 0){
			if(needhelp.y > 80){
				needhelp.y -= speed;
				button_yes.y -= speed;
				button_no.y -= speed;
			}
			else{
				phase = 1;
			}
		}
		
		else if(phase == 1){
		
			if(button_no.y < 300){
				button_no.y += speed;
				button_yes.y += speed;
			}
			else{
				phase = 2;
				}
		}
		
		else if(phase == 2){
		
			if(button_yes.x > 80){
				button_yes.x -= speed;
				button_no.x += speed;
			}
			else{
				phase = 3;
			}
		}
		
		else if(phase == 3){
			
			//px = pointer.x + pointer.w;
			//py = pointer.y + pointer.h;
			px = cursor_hand.x;
			py = cursor_hand.y;
			
			//updateWiimote();
			PAD_ScanPads();
			buttonsDown = PAD_ButtonsDown(0);
			
			if( ((buttonsDown & PAD_BUTTON_A || buttonsDown & PAD_BUTTON_START))
				#ifdef MAKE_WII
				||
				((wpads[0]->btns_d & WPAD_BUTTON_A) || (wpads[0]->btns_d & WPAD_BUTTON_1) || (wpads[0]->btns_d & WPAD_BUTTON_2))
				#endif
			){
				//exit = true;
				playBloop();
				phase = 4;
			}
			
			else if( (((buttonsDown & PAD_BUTTON_RIGHT))
				#ifdef MAKE_WII
				||
				((wpads[0]->btns_d & WPAD_BUTTON_DOWN))
				#endif
				) && wantHelp
			){
				wantHelp = false;
			}
			
			else if( (((buttonsDown & PAD_BUTTON_LEFT))
				#ifdef MAKE_WII
				||
				((wpads[0]->btns_d & WPAD_BUTTON_UP))
				#endif
				) && !wantHelp
			){
				wantHelp = true;
			}
			
			/*
			else if(buttonsDown & PAD_TRIGGER_L){
			IMGCTX pngContext;
			if ( (pngContext = PNGU_SelectImageFromDevice ("/scrnsht1.png")) ){
			PNGU_EncodeFromYCbYCr (pngContext, 640, 480, xfb[whichfb], 0);
			PNGU_ReleaseImageContext (pngContext);
			}
			}
			*/
			
			//
			// DEBUG
			//
			
			if(buttonsDown & PAD_BUTTON_X ){
				exit = true;
			}
			
			//POINTER
			if(px > button_yes.x && px < button_yes.x + button_yes.w && py > button_yes.y && py < button_yes.y + button_yes.h){
				wantHelp = true;
				//button_yes.frame = 1;
				//button_no.frame = 0;
			}
			else if(px > button_no.x && px < button_no.x + button_no.w && py > button_no.y && py < button_no.y + button_no.h){
				wantHelp = false;
				//button_yes.frame = 0;
				//button_no.frame = 1;
			}
			
			//drawFilledRect( cursorX, button_no.y + 64, 182, 4, 255, 0, 0);
		}
		
		else if(phase == 4){
			if(button_yes.x < 136){
				button_yes.x += speed;
				button_no.x -= speed;
			}
			else{
				phase = 5;
			}
		}
		
		else if(phase == 5){
			if(button_yes.y > needhelp.y + 120){
				button_yes.y -= speed;
				button_no.y -= speed;
			}
			else{
				phase = 6;
			}
		}
		
		else if(phase == 6){
			if(needhelp.y + needhelp.h < 460 ){
				needhelp.y += speed*2;
				button_yes.hidden = true;
				button_no.hidden = true;
				//button_yes.y = needhelp.y;
				//button_no.y = needhelp.y;
			}
			else{
				phase = 7;
			}
		}
		
		else if(phase == 7){
			exit = true;
			needhelp.hidden = true;
			button_yes.hidden = true;
			button_no.hidden = true;
		}
		
		if(wantHelp){
			button_yes.frame = 1;
			button_no.frame = 0;
		}
		else{
			button_yes.frame = 0;
			button_no.frame = 1;
		}
		
		drawSprite(timer);
		drawSprite(button_yes);
		drawSprite(button_no);
		drawSprite(needhelp);
		updateWiimote();
		#ifdef MAKE_WII
		drawSprite(cursor_hand);
		#endif
		
		VIDEO_SetNextFramebuffer(xfb[whichfb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
	};
	
	sleepMSeconds(30);
	
	if(wantHelp){
		
		// fill a random row and col
		
		int randomRow = getRandomNum(0, ROWLEN-1);
		int randomCol = getRandomNum(0, ROWLEN-1);
		
		zCountX = 0;
		zCountY = 0;
		
		bool exitX = false;
		bool exitY = false;
		
		// if the random col or row is empty or full
		// that's not help so move to another line
		
		while(!exitX || !exitY){
			
			for(i=0; i<ROWLEN; i++){
				
				if(!exitX){
					if(matrix.currentLevel[i][randomCol].value == 1){
						zCountX++;
					}
				}
				
				if(!exitY){
					if(matrix.currentLevel[randomRow][i].value == 1){
						zCountY++;
					}
				}
			}
			
			if(zCountX == 0 || zCountX == 15){
				randomCol++;
				randomCol = randomCol%ROWLEN;
				zCountX = 0;
			}
			else
				exitX = true;
			
			if(zCountY == 0 || zCountY == 15){
				randomRow++;
				randomRow = randomRow%ROWLEN;
				zCountY = 0;
			}
			else
				exitY = true;
		}

		for(i=0; i<ROWLEN; i++){
		
			if(matrix.currentLevel[i][randomCol].value == 1){
				matrix.currentLevel[i][randomCol].state = TILE_DRAWN;
			}
			else
				matrix.currentLevel[i][randomCol].state = TILE_MARKED;
				
			if(matrix.currentLevel[randomRow][i].value == 1){
				matrix.currentLevel[randomRow][i].state = TILE_DRAWN;
			}
			else
				matrix.currentLevel[randomRow][i].state = TILE_MARKED;
		}
		
		//count the ones drawn and update the level tile counter
		for(i=0; i < ROWLEN; i++){
			for(j=0; j < ROWLEN; j++){
				if(matrix.currentLevel[j][i].state == TILE_DRAWN)
				game.tileCount++;
			}
		}
	}
	
	leveldata[whichLevel].help = wantHelp;
	
	return wantHelp;
}

void loadTheme(char* themeName){

	int spriteError, bgError;
	bool bgCustom = false;
	
	deleteBackground(&bg1);
	deleteSprite(&tileFilled);
	deleteSprite(&tileMarked);
	deleteSprite(&levelComplete);

	if(strcasecmp("default", themeName) == 0){
		if(isChristmas())
			bgError = createBackground(&bg1, bg_xmas_png, "", 0, 0, FMT_PNG, false);
		else
			bgError = createBackground(&bg1, bg1_png, "", 0, 0, FMT_PNG, false);
	}
	else if(strcasecmp("woods", themeName) == 0)
		bgError = createBackground(&bg1, bg2_png, "", 0, 0, FMT_PNG, false);
	else if(strcasecmp("space", themeName) == 0)
		bgError = createBackground(&bg1, bg3_png, "", 0, 0, FMT_PNG, false);
	else if(strcasecmp("candy", themeName) == 0)
		bgError = createBackground(&bg1, bg4_png, "", 0, 0, FMT_PNG, false);
	else if(strcasecmp("spooky", themeName) == 0)
		bgError = createBackground(&bg1, bg5_png, "", 0, 0, FMT_PNG, false);
	else if(strcasecmp("blue", themeName) == 0)
		bgError = createBackground(&bg1, bg6_png, "", 0, 0, FMT_PNG, false);
		
	else{
	
		bgCustom = true;
		char temp[500];
		
		sprintf(temp, DIR_ROOT "res/themes/%s/bg.png", options.theme);
		bgError = createBackground(&bg1, NULL, temp, 0, 0, FMT_PNG, true);
		if( bgError != 1)
			breakpoint(temp, bgError);
		
		sprintf(temp, DIR_ROOT "res/themes/%s/filled.png", options.theme);
		spriteError = createSprite(&tileFilled, NULL, temp, 0, 0, 1, FMT_PNG, true);
		if( spriteError != 1)
			breakpoint("cannot load resource filled ", spriteError);
		
		sprintf(temp, DIR_ROOT "res/themes/%s/marked.png", options.theme);	
		spriteError = createSprite(&tileMarked, NULL, temp, 0, 0, 1, FMT_PNG, true);
		if( spriteError != 1)
			breakpoint("cannot load resource marked ", spriteError);
		
		sprintf(temp, DIR_ROOT "res/themes/%s/levelcomplete.png", options.theme);
		spriteError = createSprite(&levelComplete, NULL, temp, 0, 178, 1, FMT_PNG, true);
		if( spriteError != 1)
			breakpoint("cannot load resource level complete", spriteError);
	}
	
	if(!bgCustom){
	
		if( bgError != 1)
			breakpoint("cannot load resource", bgError);
		
		spriteError = createSprite(&tileFilled, filled_png, "", 0, 0, 1, FMT_PNG, false);
		if( spriteError != 1)
			breakpoint("cannot load resource", spriteError);
			
		spriteError = createSprite(&tileMarked, marked_png, "", 0, 0, 1, FMT_PNG, false);
		if( spriteError != 1)
			breakpoint("cannot load resource", spriteError);
		
		spriteError = createSprite(&levelComplete, levelcomplete_png, "", 0, 178, 1, FMT_PNG, false);
		if( spriteError != 1)
			breakpoint("cannot load resource", spriteError);
	}
}

void splashScreen(){

	int i, j, l;
	
	while(1){
		
		for(l = 0; l<2; l++){
			for(j = 20; j>0; j--){
			
				whichfb ^= 1;
				VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
			
				if(l==0)
					drawBackground(splash_sco);
				else
					drawBackground(splash_dd);
				for(i=0; i<32; i++){
					drawFilledRect(i*20, 0, j, 480, 0, 0, 0);
				}
				
				VIDEO_SetNextFramebuffer(xfb[whichfb]);
				VIDEO_Flush();
				VIDEO_WaitVSync();
			}
			
			sleepSeconds(2);
			
			for(j=0; j<=20; j++){
				
				whichfb ^= 1;
				VIDEO_ClearFrameBuffer (vmode, xfb[whichfb], COLOR_BLACK);
			
				if(l==0)
					drawBackground(splash_sco);
				else
					drawBackground(splash_dd);
			
				for(i=0; i<32; i++){
					drawFilledRect(i*20, 0, j, 480, 0, 0, 0);
				}
				
				VIDEO_SetNextFramebuffer(xfb[whichfb]);
				VIDEO_Flush();
				VIDEO_WaitVSync();
			}
		}
		break;
	}
		
	deleteBackground(&splash_sco);
	deleteBackground(&splash_dd);	
}

void initThemes(){

	int i = 0;

	theme.totalThemes = readThemesDir();

	//if(strcasecmp(options.theme, "default") != 0){
		for(i = 0; i<theme.totalThemes; i++){
			if(strcasecmp(options.theme, theme.themesArray[i]) == 0){
				theme.currentTheme = i;
				break;
			}
		}
	//}
	
	sprintf(options.theme, "%s", theme.themesArray[theme.currentTheme]);
	loadTheme(options.theme);
}
