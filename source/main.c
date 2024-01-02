#include "../include/wiicross.h"
#include "../include/libscognito.h"
#include "../include/levels.h"

s_game game;
s_option options;
s_matrix matrix;
s_time timeElapsed;
s_event event;
///
s_background splash_sco;
s_background splash_dd;
s_background bg_titlescreen;
s_background bg_titlescreen_xmas;
s_background creditscreen;
s_background bg;
s_background bg1;
s_background bg_options;
s_background bg_pause;
s_background bg_creditScreen;
s_background bg_tut1;
s_background bg_tut2;
s_background bg_tut3;
s_background bg_tut4;
s_background bg_tut5;

s_sprite fontNumber;
s_sprite font;
s_sprite tileFilled;
s_sprite tileMarked;
s_sprite errorMsg;
s_sprite squareCursor;
s_sprite gameComplete;
s_sprite levelComplete;
s_sprite preview;
s_sprite arrowL;
s_sprite arrowR;
s_sprite modeplay;
/*
s_sprite button_exit;
s_sprite button_credits;
s_sprite button_options;
s_sprite button_start;
s_sprite button_resume;
s_sprite button_titlescreen;
*/
s_sprite button_yes;
s_sprite button_no;
s_sprite button_cancel;
s_sprite needhelp;
s_sprite controllertype;
s_sprite musictype;
s_sprite themetype;
s_sprite pointer;
s_sprite opt;
s_sprite back;
s_sprite button_soce;
s_sprite eyes_ts;
s_sprite eyes_os;
s_sprite savegame;
s_sprite font_clock;
s_sprite msg_outoftime;
s_sprite button_rote;
s_sprite cursor_hand;
s_sprite minitile;
s_sprite timer;
s_sprite help;
s_sprite imageHack;
///
bool pointerVisible;
///
WPADData wpaddate[SAMP_BUFS];
WPADData *wpads[4];
///
s_song song;
///

bool lastState;
int sCursorX = 0;
int sCursorY = 0;
bool newMove;
int currentLevel;
bool backToMenu = false;
int firstState = STATE_NONE;
int currentPage = 0;
extern int ox;
extern int oy;

int ssc = 0;
char sscc[10];

int main() {
	
	initWii();
	initGfx();
	initVars();
	initStorage();
	initSound();
	initThemes();
	
	#ifndef IS_EMU
	splashScreen();
	#endif
	titleScreen();
	
	/*
	if(systemReset)
		SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
	else if(systemPowerOff)
		SYS_ResetSystem(SYS_POWEROFF, 0, 0);
	*/
	
	while(1){

		currentLevel = levelSelect();
		//currentLevel = 1;
		if(!backToMenu)
			startNewLevel(currentLevel);
		
		while(1){
			
			if(backToMenu){
				resetVars();
				titleScreen();
				currentPage = 0;
				ox = 0;
				oy = 0;
				backToMenu = false;
				break;
			}
			
			if(game.mode == MODE_NORMAL)
				game.levelFinished = checkLevelFinished(game.mode);
			
			if(game.levelFinished){
				performLevelComplete();
				showLevelComplete();
				break;
			}
			
			checkInput();
			drawScene();
			updateFrames();
			updateTime();
			
			if(options.musicType == MUSIC_CUSTOM && (song.totalSongs > 0)){
				if(StatusOgg() == OGG_STATUS_ERR){
					//breakpoint("pas ", OGG_STATUS_PAUSED);
					playOggMusic();
				}
			}
			
			#ifdef HW_RVL
			if(systemReset)
				SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
			else if(systemPowerOff)
				SYS_ResetSystem(SYS_POWEROFF, 0, 0);
			#endif
		}
		
		sleepMSeconds(60);
	}

	return 0;
}

/*
void run(){
	
	checkInput();
	drawScene();
	updateFrames();
	updateTime();
	checkLevelFinished();
}
*/
void parseLevel(int level){
	
	int i, j, z=0;
	
	for(i=0; i < ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
			//currentLevel[i][j] = leveldata[level][z];
			//drawMatrix[i][j] = 0;
			matrix.currentLevel[i][j].value = leveldata[level].data[z];
			matrix.currentLevel[i][j].state = 0;
			
			if(leveldata[level].data[z] == 1)
				matrix.tileCount++;
			
			z++;
		}
	}
	
	strncpy(matrix.name, leveldata[level].name, 8);
	strncpy(matrix.author, leveldata[level].author, 8);
	/* stampa matrice
	for(i=0; i < ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
			printf("\x1b[%d;%dH%d ", j, i*2, currentLevel[j][i]);
		}
		printf("\n");
	}
	*/
}

void initVars(){

	int i, j, k;

	for(k=0; k<2; k++){
		for(i=0; i< ROWLEN; i++){
			for(j=0; j < 8; j++){
				if(k==0){
					matrix.row[i][j] = -1;
				}
				else{
					matrix.col[i][j] = -1;
				}
			}
		}
	}
	
	game.frames = 0;
	game.errors = 0;
	
	matrix.tileCount = 0;
	game.tileCount = 0;
	game.heldFrames = 0;
	
	newMove = true;
	
	#ifdef HW_RVL
	options.padType = PAD_WII;
	#else
	options.padType = PAD_NGC;
	#endif
	
	options.musicType = MUSIC_ON;
	sprintf(options.theme, "default");
	theme.currentTheme = 0;
	
	lastState = false;
	pointerVisible = false;
	
	//game.mode = MODE_NORMAL;
	game.mode = MODE_FREE;
	game.levelFinished = false;
	
	//christmas
	//levelComplete.frame = isChristmas();
	needhelp.frame = isChristmas();
	eyes_ts.hidden = isChristmas();
}

void resetVars(){

	int i, j, k;

	for(k=0; k<2; k++){
		for(i=0; i< ROWLEN; i++){
			for(j=0; j < 8; j++){
				if(k==0){
					matrix.row[i][j] = -1;
				}
				else{
					matrix.col[i][j] = -1;
				}
			}
		}
	}
	
	game.frames = 0;
	game.errors = 0;
	game.heldFrames = 0;
	errorMsg.frame = 0;
	
	matrix.tileCount = 0;
	game.tileCount = 0;
	
	newMove = true;
	
	/*
	if(strcasecmp(options.theme, "default") != 0)
		timer.hidden = false;
	else
		timer.hidden = true;
	*/
	
	pointerVisible = false;
	lastState = false;
	
	squareCursor.x = SQUARECURSOR_MIN_X;
	squareCursor.y = SQUARECURSOR_MIN_Y;
	sCursorX = 0;
	sCursorY = 0;
	
	game.levelFinished = false;
}

void startNewLevel(int level){
	
	resetVars();
	parseLevel(level);
	fillRowsColumns();
	
	if(options.musicType == MUSIC_ON)
		playDefaultLevelMusic();
	else if(options.musicType == MUSIC_CUSTOM)
		playOggMusic();
	else
		SND_StopVoice(0);
		
	#ifndef IS_EMU
		helpNeeded(level);
	#endif
	
	timeElapsed.timeOld = time(NULL);
	timeElapsed.timeNew = time(NULL);
	timeElapsed.minutes = 0;
	timeElapsed.seconds = 0;
}

void printInitMatrix(){
	
	int i, j, k;

	for(k=1; k<2; k++){
		for(i=0; i< ROWLEN; i++){
			for(j=0; j < 8; j++){
				if(k==0){
					if(matrix.row[i][j] != -1)
						printf("\x1b[%d;%dH%d ", 15+i, j*2+18, matrix.row[i][j]);
					else
						printf("\x1b[%d;%dH- ", 15+i, j*2+18);
				}
				else{
					if(matrix.col[i][j] != -1)
						printf("\x1b[%d;%dH%d ", 15+i, j*2+18, matrix.col[i][j]);
					else
						printf("\x1b[%d;%dH- ", 15+i, j*2+18);
				}
			}
		}
	}
}

void fillRowsColumns(){

	int i,j;
	int tempCounter = 0;
	int idx = 0;
	
	for(j=0; j<ROWLEN; j++){
		for(i=0; i<ROWLEN; i++){
			if(matrix.currentLevel[j][i].value == 1)
				tempCounter++;
			else{
				if(tempCounter != 0){
					matrix.row[j][idx] = tempCounter;
					idx++;
					tempCounter = 0;
				}
			}
			//if(currentLevel[j][i] == 1 && i==ROWLEN-1)
			//if(i==ROWLEN-1 && idx==0)
			//	matrix.row[j][idx] = tempCounter;
			if(i==ROWLEN-1){
				if(matrix.currentLevel[j][i].value == 1)
					matrix.row[j][idx] = tempCounter;
				else if(idx ==0)
					matrix.row[j][idx] = 0;
			}
		}
		idx = 0;
		tempCounter = 0;
	}
	
	// cols
	tempCounter = 0;
	idx = 0;

	for(j=0; j<ROWLEN; j++){
		for(i=0; i<ROWLEN; i++){
			if(matrix.currentLevel[i][j].value == 1)
				tempCounter++;
			else{
				if(tempCounter != 0){
					matrix.col[j][idx] = tempCounter;
					idx++;
					tempCounter = 0;
				}
			}
			//if(currentLevel[i][j] == 1 && i==ROWLEN-1)
			if(i==ROWLEN-1){
				if(matrix.currentLevel[i][j].value == 1)
					matrix.col[j][idx] = tempCounter;
				else if(idx ==0)
					matrix.col[j][idx] = 0;
			}
		}
		idx = 0;
		tempCounter = 0;
	}

}

void printFormattedValues(){
	
	int coorX = 16;
	int coorY = 16;
	
	int i, j;
	
	//i=3;
	//rows
	
	for(i=0; i< ROWLEN; i++){
		for(j=7; j >= 0; j--){
		//for(j=0; j < 8; j++){
			if(matrix.row[i][j] != -1){
				printf("\x1b[%d;%dH%d",15 + i, coorX, matrix.row[i][j]);
				coorX -= 2;
				//coorY += 2;
			}
		}
		coorX = 16;
	}
	
	coorX = 32;
	i = 0;
	//columns
	for(i=0; i< ROWLEN; i++){
		for(j=7; j >= 0; j--){
			if(matrix.col[i][j] != -1){
				printf("\x1b[%d;%dH%d", coorY, coorX + (i * 2),  matrix.col[i][j]);
				coorY -= 2;
				//coorY += 2;
			}
		}
		coorY = 16;
	}
}

void checkInput(){
	
	updateWiimote();
	PAD_ScanPads();
	
	int buttonsDown = PAD_ButtonsDown(0);
	int buttonsHeld = PAD_ButtonsHeld(0);
	int buttonsUp = PAD_ButtonsUp(0);
	int px, py;
	bool firstMove = false;
	
	px = pointer.x + pointer.w;
	py = pointer.y + pointer.h;
	
	if( ((((buttonsDown & PAD_BUTTON_RIGHT) || (buttonsHeld & PAD_BUTTON_RIGHT && game.heldFrames >= HELD_FRAMES_MAX))&& options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		(((wpads[0]->btns_d & WPAD_BUTTON_DOWN) || (wpads[0]->btns_h & WPAD_BUTTON_DOWN && game.heldFrames >= HELD_FRAMES_MAX)) && options.padType == PAD_WII_S)
		#endif
		)&& squareCursor.x < SQUARECURSOR_MAX_X
	){
		squareCursor.x += 20;
		sCursorX++;
		newMove = true;
	}
	else if(((((buttonsDown & PAD_BUTTON_LEFT) || (buttonsHeld & PAD_BUTTON_LEFT && game.heldFrames >= HELD_FRAMES_MAX)) && options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		(((wpads[0]->btns_d & WPAD_BUTTON_UP) || (wpads[0]->btns_h & WPAD_BUTTON_UP && game.heldFrames >= HELD_FRAMES_MAX))  && options.padType == PAD_WII_S)
		#endif
		)&& squareCursor.x > SQUARECURSOR_MIN_X
	){
		squareCursor.x -= 20;
		sCursorX--;
		newMove = true;
	}
	else if(((((buttonsDown & PAD_BUTTON_UP) || (buttonsHeld & PAD_BUTTON_UP && game.heldFrames >= HELD_FRAMES_MAX)) && options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		(((wpads[0]->btns_d & WPAD_BUTTON_RIGHT) || (wpads[0]->btns_h & WPAD_BUTTON_RIGHT && game.heldFrames >= HELD_FRAMES_MAX))  && options.padType == PAD_WII_S)
		#endif
		)&& squareCursor.y > SQUARECURSOR_MIN_Y
	){
		squareCursor.y -= 20;
		sCursorY--;
		newMove = true;
	}
	else if(((((buttonsDown & PAD_BUTTON_DOWN) || (buttonsHeld & PAD_BUTTON_DOWN && game.heldFrames >= HELD_FRAMES_MAX)) && options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		(((wpads[0]->btns_d & WPAD_BUTTON_LEFT)  || (wpads[0]->btns_h & WPAD_BUTTON_LEFT && game.heldFrames >= HELD_FRAMES_MAX)) && options.padType == PAD_WII_S)
		#endif
		)&& squareCursor.y < SQUARECURSOR_MAX_Y
	){
		squareCursor.y += 20;
		sCursorY++;
		newMove = true;
	}
		
	else if((buttonsDown & PAD_BUTTON_START)
		#ifdef HW_RVL
		|| (wpads[0]->btns_d & WPAD_BUTTON_HOME)
		#endif
	){
		pauseScreen();
	}
	
	else if( ( ((buttonsDown & PAD_BUTTON_A)||(buttonsHeld & PAD_BUTTON_A)) && options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		(( ((wpads[0]->btns_d & WPAD_BUTTON_B) && wpads[0]->ir.valid) || ((wpads[0]->btns_h & WPAD_BUTTON_B) && wpads[0]->ir.valid) || (wpads[0]->btns_d & WPAD_BUTTON_2) || (wpads[0]->btns_h & WPAD_BUTTON_2) )&& options.padType != PAD_NGC)
		#endif
	){
		//NEW
		//if(firstState = STATE_NONE){
		//if(firstMove = false){
		//	firstMove = true;
		//}
		//ENDNEW
		
		if(newMove){
			checkTile(sCursorX, sCursorY, ACTION_DRAW);
			newMove = false;
		}
	}
	
	else if( ((buttonsHeld & PAD_BUTTON_B) && options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		(((wpads[0]->btns_h & WPAD_BUTTON_1) || (wpads[0]->btns_h & WPAD_BUTTON_A)) && options.padType != PAD_NGC)
		#endif
	){
		if(newMove){
			checkTile(sCursorX, sCursorY, ACTION_MARK);
			newMove = false;
		}
	}
	
	else if( !(buttonsDown & PAD_BUTTON_A) && !(buttonsDown & PAD_BUTTON_B) && options.padType == PAD_NGC){
		newMove = true;
		firstState = STATE_NONE;
		firstMove = false;
	}
	
	#ifdef HW_RVL
	else if( !(wpads[0]->btns_d & WPAD_BUTTON_A) && !(wpads[0]->btns_d & WPAD_BUTTON_B) && options.padType != PAD_NGC){
		newMove = true;
		firstState = STATE_NONE;
		firstMove = false;
	}
	#endif
	
	if( ((buttonsDown & PAD_TRIGGER_L) && options.padType == PAD_NGC)
		#ifdef HW_RVL
		||
		((wpads[0]->btns_d & WPAD_BUTTON_MINUS) && options.padType != PAD_NGC)
		#endif
	){
		//breakpoint("sux", 123);
		if(game.mode == MODE_FREE){
			if(checkLevelFinishedModeFree())
				game.levelFinished = true;
			else
				updateErrors(302 + 20*sCursorX, 134 + 20*sCursorY);
		}
	}
	/*
	// DEBUG
	else if((buttonsDown & PAD_BUTTON_X) || (wpads[0]->btns_d & WPAD_BUTTON_PLUS))
		exit(0);
		
	else if(buttonsDown & PAD_BUTTON_Y)
		completePuzzle();
	// END DEBUG
	*/
	
	if(options.padType == PAD_NGC){
		if(buttonsHeld & (PAD_BUTTON_UP | PAD_BUTTON_DOWN | PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)){
			game.heldFrames++;
		}
		else if(buttonsUp){
			game.heldFrames = 0;
		}
	}
	#ifdef HW_RVL
	else if(options.padType == PAD_WII_S){
		if(wpads[0]->btns_h & (WPAD_BUTTON_UP | WPAD_BUTTON_DOWN | WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT)){
			game.heldFrames++;
		}
		else if(wpads[0]->btns_u){
			game.heldFrames = 0;
		}
	}
	#endif
	
	if(newMove){
		if(game.heldFrames > HELD_FRAMES_MAX)
			game.heldFrames -= HELD_FRAMES_STEP;
	}	
	
	//POINTING
	if(options.padType == PAD_WII){
		if( px >= 303 && px < 600 && py >= 149 && py < 446 ){
		
			int sCursorXtemp = sCursorX;
			int sCursorYtemp = sCursorY;
			
			squareCursor.x = SQUARECURSOR_MIN_X + (20* ((px - SQUARECURSOR_MIN_X) / 20));
			squareCursor.y = SQUARECURSOR_MIN_Y + (20* ((py - SQUARECURSOR_MIN_Y) / 20));
			
			sCursorX = (px - SQUARECURSOR_MIN_X) / 20;
			sCursorY = (py - SQUARECURSOR_MIN_Y) / 20;
			
			if((sCursorXtemp != sCursorX)||(sCursorYtemp != sCursorY)){
				newMove = true;
			}
		}
	}
	
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

void checkTile(int x, int y, int action){

	if(firstState == STATE_NONE){
	
		if(action == ACTION_MARK){
			if(matrix.currentLevel[y][x].state == TILE_UNMARKED)
				firstState = STATE_MARK;
			else if(matrix.currentLevel[y][x].state == TILE_MARKED)
				firstState = STATE_UNMARK;
			else if((matrix.currentLevel[y][x].state == TILE_MARKED) && (matrix.currentLevel[y][x].state == TILE_DRAWN))
				firstState = STATE_UNMARK;
		}
		else{ // DRAW
			if(matrix.currentLevel[y][x].state == TILE_MARKED){
				firstState = STATE_UNMARK;
				//breakpoint("unmark", 0);
			}
			else if(matrix.currentLevel[y][x].state == TILE_DRAWN  || matrix.currentLevel[y][x].state == TILE_UNMARKED){
				firstState = STATE_DRAW;
				//breakpoint("draw", 0);
			}
		}
	}
	
	if(action == ACTION_MARK){ // X
	
		//breakpoint("iiii", 123);
	
		if(matrix.currentLevel[y][x].state == TILE_UNMARKED && firstState == STATE_MARK){
			matrix.currentLevel[y][x].state = TILE_MARKED;
			playClick();
		}
		else if(matrix.currentLevel[y][x].state == TILE_MARKED && firstState == STATE_UNMARK){
			matrix.currentLevel[y][x].state = TILE_UNMARKED;
			playClick();
		}
		else if(game.mode == MODE_FREE && matrix.currentLevel[y][x].state == TILE_DRAWN){
			matrix.currentLevel[y][x].state = TILE_UNMARKED;
			playClick();
		}
	}
	
	else if(action == ACTION_DRAW){ // []
	
		if(matrix.currentLevel[y][x].state == TILE_MARKED){
			matrix.currentLevel[y][x].state = TILE_UNMARKED;
			playClick();
			return;
		}
		
		if(game.mode == MODE_NORMAL){
			
			if(matrix.currentLevel[y][x].state == TILE_DRAWN ) // rimetto none?
				return;
			
			else if(matrix.currentLevel[y][x].value == 1 && matrix.currentLevel[y][x].state == TILE_UNMARKED && firstState == STATE_DRAW){
				matrix.currentLevel[y][x].state = TILE_DRAWN;
				playClick();
				game.tileCount++;
			}
			
			/*
			else if(matrix.currentLevel[y][x].state == TILE_UNMARKED){
				matrix.currentLevel[y][x].state = TILE_MARKED;
			}
			*/
			
			else if(matrix.currentLevel[y][x].state == TILE_UNMARKED && matrix.currentLevel[y][x].value == 0 && firstState == STATE_DRAW){
				matrix.currentLevel[y][x].state = TILE_MARKED;
				updateErrors(302 + 20*x, 134 + 20*y);
			}
		}
		
		else{ // MODE_FREE
		
			//breakpoint("state 1: ", matrix.currentLevel[y][x].state);
			if(matrix.currentLevel[y][x].state == TILE_UNMARKED && firstState == STATE_DRAW){
				matrix.currentLevel[y][x].state = TILE_DRAWN;
				//breakpoint("sss", 456);
			}
			else if(matrix.currentLevel[y][x].state == TILE_DRAWN){
				//breakpoint("jjj", 123);
				matrix.currentLevel[y][x].state = TILE_UNMARKED;
			}
			//breakpoint("state 2: ", matrix.currentLevel[y][x].state);
		}
	}
}

void updateFrames(){
	// every 10 seconds reset
	game.frames++;
	if(game.frames == 590)
		game.frames = 0;
}

void completePuzzle(){

	int i,j;
	
	for(i=0; i < ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
			if(matrix.currentLevel[j][i].value == 1)
				matrix.currentLevel[j][i].state = TILE_DRAWN;
		}
	}
	
	game.tileCount = matrix.tileCount;
}

void updateTime(){

	timeElapsed.timeNew = time(NULL);
	
	if(timeElapsed.timeNew != timeElapsed.timeOld){
		
		timeElapsed.timeOld = timeElapsed.timeNew;
		timeElapsed.seconds++;
		
		if(timeElapsed.seconds == 60){
			
			timeElapsed.minutes++;
			timeElapsed.seconds = 0;
			
			if(timeElapsed.minutes >= 99){
				timeElapsed.minutes = 99;
				timeElapsed.seconds = 59;
			}
		}
	}
}

void updateErrors(int x, int y){
	
	if(game.errors <= 4)
		errorMsg.frame = game.errors;
	
	if(timeElapsed.minutes >= 99)
		errorMsg.frame = 5;
	
	if(game.errors < 99)
		game.errors++;
		
	switch(game.errors){
		case 1:
			timeElapsed.minutes++;
			break;
		case 2:
			timeElapsed.minutes += 2;
			break;
		case 3:
			timeElapsed.minutes += 4;
			break;
		case 4:
			timeElapsed.minutes += 8;
			break;
		default:
			timeElapsed.minutes += 10;
	}
	
	errorMsg.x = x - 40 - errorMsg.w/2;
	errorMsg.y = y;
	errorMsg.hidden = false;
	event.errorImgDistance = 60;
	
	playError();
}


bool checkLevelFinished(int mode){

	if(mode == MODE_NORMAL){
		if(game.tileCount == matrix.tileCount){
			return true;
		}
	}
	return false;
}

bool checkLevelFinishedModeFree(){

	int i, j;
	
	for(i=0; i < ROWLEN; i++){
		for(j=0; j < ROWLEN; j++){
			if((matrix.currentLevel[j][i].value == 1) && (matrix.currentLevel[j][i].state != TILE_DRAWN))
				return false;
			else if((matrix.currentLevel[j][i].value == 0) && (matrix.currentLevel[j][i].state == TILE_DRAWN))
				return false;
		}
	}
	
	return true;
}

void performLevelComplete(){
	
	if(options.musicType == MUSIC_ON)
		SND_StopVoice(0);
	else if(options.musicType == MUSIC_CUSTOM)
		StopOgg();
	
	if(leveldata[currentLevel].played == false){
	
		leveldata[currentLevel].played = true;
		
		if(timeElapsed.minutes > 99)
			leveldata[currentLevel].min = 99;
		else
			leveldata[currentLevel].min = timeElapsed.minutes;
		
		if(timeElapsed.seconds > 99)
			leveldata[currentLevel].sec = 99;
		else
			leveldata[currentLevel].sec = timeElapsed.seconds;
	}
	
	else{
		// update the time only if the current time is better than old one
		if((timeElapsed.minutes < leveldata[currentLevel].min) || ((timeElapsed.minutes == leveldata[currentLevel].min) && (timeElapsed.seconds < leveldata[currentLevel].sec)) ) {
			leveldata[currentLevel].min = timeElapsed.minutes;
			leveldata[currentLevel].sec = timeElapsed.seconds;
		}
	}
	
	writeSD(FILE_LEVELS);
}

void updateWiimote(){
	
#ifndef HW_DOL
	
	WPAD_ReadPending(WPAD_CHAN_0, NULL);
	wpads[0] = WPAD_Data(WPAD_CHAN_0);
	
	int res;
    u32 type;
	
	res = WPAD_Probe(0, &type);
	if(res == WPAD_ERR_NO_CONTROLLER){
		pointerVisible = false;
		
	}
	else{
		pointerVisible = true;
	}
	
	if(lastState == false && pointerVisible == true){ // wiimote reconnected
		WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
		pointerVisible = true;
	}
	
	pointer.x = wpads[0]->ir.x;
	pointer.y = wpads[0]->ir.y;
	
	if(pointer.x <= 0)
		pointer.x = 0;
	else if(pointer.x > 640 - pointer.w - 3)
		pointer.x = 640 - pointer.w - 3;
	
	if(pointer.y <= 0)
		pointer.y = 0;
	else if(pointer.y > 480 - pointer.h - 3)
		pointer.y = 480 - pointer.h - 3;
		
	cursor_hand.x = pointer.x;
	cursor_hand.y = pointer.y;
	
	
	/*
	if(!wpads[0]->ir.valid){
		pointer.hidden = true;
		cursor_hand.hidden = true;
	}
	else{
		pointer.hidden = false;
		cursor_hand.hidden = false;
	}
	*/
		
	lastState = pointerVisible;
	#else
	pointerVisible = false;
	#endif
}

bool isChristmas(){
	
	time_t now;
	struct tm  *ts;
   
	now = time(NULL);
	ts = localtime(&now);

	if((ts->tm_mon == 11 && ts->tm_mday  >=15) || (ts->tm_mon == 0 && ts->tm_mday  <=31)){
		return true;
    }
	
	return false;
}

