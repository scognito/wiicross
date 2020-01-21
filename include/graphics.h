#ifndef _WIICROSSGFX_
#define _WIICROSSGFX_

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

bool pointerVisible;

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
#endif
