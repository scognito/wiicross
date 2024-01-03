#pragma once

#include "pngu.h"
#include "fontNumber_png.h"
#include "font_png.h"
#include "squarecursor_png.h"
#include "bg1_png.h"
#include "bg2_png.h"
#include "bg3_png.h"
#include "bg4_png.h"
#include "bg5_png.h"
#include "bg6_png.h"
#include "bg_xmas_png.h"
#include "filled_png.h"
#include "marked_png.h"
#include "error_png.h"
#include "levelcomplete_png.h"
#include "bg_png.h"
#include "preview_png.h"
#include "arrowL_png.h"
#include "arrowR_png.h"
#include "titlescreen_png.h"
#include "splash_sco_png.h"
#include "splash_dd_png.h"
#include "titlescreen_png.h"
#include "titlescreen_xmas_png.h"
#include "bg_tut1_png.h"
#include "bg_tut2_png.h"
#include "bg_tut3_png.h"
#include "bg_tut4_png.h"
#include "bg_tut5_png.h"
#include "modeplay_png.h"
#include "imageHack_png.h"

/*
#include "button_credits_png.h"
#include "button_exit_png.h"
#include "button_start_png.h"
#include "button_options_png.h"
#include "button_titlescreen_png.h"
#include "button_resume_png.h"
*/
#include "button_yes_png.h"
#include "button_no_png.h"
#include "button_cancel_png.h"
#include "needhelp_png.h"
#include "savegame_png.h"
#include "musictype_png.h"
#include "controllertype_png.h"
#include "bg_options_png.h"
#include "bg_pause_png.h"
#include "themetype_png.h"
#include "pencil_png.h"
#include "opt_png.h"
#include "button_back_png.h"
#include "button_soce_png.h"
#include "bg_creditscreen_png.h"
#include "eyes_ts_png.h"
#include "eyes_os_png.h"
#include "font_clock_png.h"
#include "outoftime_png.h"
#include "button_rote_png.h"
#include "cursor_hand_png.h"
#include "minitile_png.h"
#include "help_png.h"

#define SQUARECURSOR_MIN_X 300
#define	SQUARECURSOR_MIN_Y 153 // 146
#define SQUARECURSOR_MAX_X 580
#define	SQUARECURSOR_MAX_Y 426

#define TILE_UNMARKED	0
#define TILE_MARKED		1
#define TILE_DRAWN		2

#define DIR_COLOR_UP	0
#define DIR_COLOR_DOWN	1

extern s_background splash_sco;
extern s_background splash_dd;
extern s_background bg_titlescreen;
extern s_background bg_titlescreen_xmas;
extern s_background creditscreen;
extern s_background bg;
extern s_background bg1;
extern s_background bg_options;
extern s_background bg_pause;
extern s_background bg_creditScreen;
extern s_background bg_tut1;
extern s_background bg_tut2;
extern s_background bg_tut3;
extern s_background bg_tut4;
extern s_background bg_tut5;

extern s_sprite fontNumber;
extern s_sprite font;
extern s_sprite tileFilled;
extern s_sprite tileMarked;
extern s_sprite errorMsg;
extern s_sprite squareCursor;
extern s_sprite gameComplete;
extern s_sprite levelComplete;
extern s_sprite preview;
extern s_sprite arrowL;
extern s_sprite arrowR;
extern s_sprite modeplay;
/*
extern s_sprite button_exit;
extern s_sprite button_credits;
extern s_sprite button_options;
extern s_sprite button_start;
extern s_sprite button_resume;
extern s_sprite button_titlescreen;
*/
extern s_sprite button_yes;
extern s_sprite button_no;
extern s_sprite button_cancel;
extern s_sprite needhelp;
extern s_sprite controllertype;
extern s_sprite musictype;
extern s_sprite themetype;
extern s_sprite pointer;
extern s_sprite opt;
extern s_sprite back;
extern s_sprite button_soce;
extern s_sprite eyes_ts;
extern s_sprite eyes_os;
extern s_sprite savegame;
extern s_sprite font_clock;
extern s_sprite msg_outoftime;
extern s_sprite button_rote;
extern s_sprite cursor_hand;
extern s_sprite minitile;
extern s_sprite timer;
extern s_sprite help;
extern s_sprite imageHack;

extern bool pointerVisible;

void initGfx();
void drawScene();
void drawRectMarker();
void drawLevelSelectCursor(int x, int y);
void drawPreview(int x, int y);
void printText(int x, int y, char* text);
void printErrors(int x, int y);
void printTime(int x, int y);
void updateEventsGfx();
//int levelSelect();
void showLevelComplete();
void fadeIn();
void fadeOut();
bool helpNeeded(int whichLevel);
void loadTheme(char* themeName);
void splashScreen();
void initThemes();
