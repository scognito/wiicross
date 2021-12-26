#ifndef _WIICROSS_
#define _WIICROSS_

#include <gccore.h>
#include <ogcsys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <mp3player.h>
#include <asndlib.h>
#include <fat.h>

#include "libscognito.h"
#include "titleScreen.h"
#include "graphics.h"
#include "levelSelect.h"
#include "optionScreen.h"
#include "pauseScreen.h"
#include "creditScreen.h"
#include "howToPlay.h"
#include "storage.h"
#include "sound.h"

#include <wiiuse/wpad.h>
#include <bte/bte.h>

#define MAX_WIIMOTES		4
#define SAMP_BUFS			100

#define ROWLEN 15
#define NUMLEVELS 59

#define HELD_FRAMES_MAX 20
#define HELD_FRAMES_STEP 6//10

#ifdef MAKE_WII
#define DIR_ROOT   ""
#else
#define DIR_ROOT   "/"
#endif

enum {
	
	PAD_WII = 0, // IR
	PAD_WII_S,   // Side
	PAD_NGC,
	PAD_AUTO
};

enum {
	MUSIC_ON = 0,
	MUSIC_OFF,
	MUSIC_CUSTOM
};

enum {
	FILE_OPTIONS = 0,
	FILE_LEVELS,
	FILE_RESUME
};

enum {
	ACTION_MARK = 0,
	ACTION_DRAW
};

enum {
	STATE_NONE = 0,
	STATE_DRAW,
	STATE_MARK,
	STATE_UNMARK
};

enum {
	MODE_NORMAL = 0,
	MODE_FREE
};

typedef struct{
	
	int frames;
	int errors;
	int tileCount;
	int heldFrames;
	int mode;
	bool levelFinished;
} s_game;

typedef struct{

	int value;
	int state;
} s_tile;

typedef struct{

	s_tile currentLevel[ROWLEN][ROWLEN];

	int row[ROWLEN][8];
	int col[ROWLEN][8];

	char name[9];
	char author[9];
	
	int tileCount;
	bool played;
	
} s_matrix;

typedef struct{

	int data[ROWLEN * ROWLEN];
	char name[9];
	char author[9];
	bool played;
	int min;
	int sec;
	bool help;
	
} s_level;

typedef struct{
	
	int x;
	int y;
	int w;
	int h;
	int r,g,b;
	int dirColor;
	
} s_marker;

typedef struct{

	time_t timeOld;
	time_t timeNew;
	
	//int value;
	int minutes;
	int seconds;
} s_time;

typedef struct{

	int padType;
	int musicType;
	char theme[256];
} s_option;

typedef struct{
	int errorImgDistance;
} s_event;

typedef struct{
	char themesArray[256][256];
	int totalThemes;
	int currentTheme;
	s_sprite titleArray[256];
} s_theme;

typedef struct{
	char songsArray[256][128];
	int totalSongs;
	int currentSong;
} s_song;

WPADData wpaddata[SAMP_BUFS];
WPADData *wpads[4];

extern s_background splash_sco;
extern s_background splash_kenney;
extern s_background titlescreen;
extern s_background creditscreen;

extern s_sprite gamecomplete;
extern s_sprite levelcomplete;

extern bool pointerVisible;
extern bool lastState;
extern MODPlay mod_track;

extern s_game game;
extern s_theme theme;
s_song song;

extern char sscc[10];
extern int ssc;

void run();
void initVars();
void resetVars();
void startNewLevel(int level);
void fillRowsColumns();
void printInitMatrix();
void parseLevel(int level);
void checkInput();
void printFormattedValues();
void checkTile(int x, int y, int action);
void updateFrames();
void completePuzzle();
void updateErrors(int x, int y);
void updateTime();
bool checkLevelFinished(int gameMode);
bool checkLevelFinishedModeFree();
void performLevelComplete();
void updateWiimote();
bool isChristmas();
#endif
