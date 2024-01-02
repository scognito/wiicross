#ifndef _SCOSOUND_H_
#define _SCOSOUND_H_

#include "oggplayer.h"
#include <fcntl.h>
#include "snd_titlescreen_mod.h"
#include "snd_bg0_mod.h"
#include "snd_bg1_mod.h"
#include "snd_levelcleared_ogg.h"
#include "snd_levelcleared_raw.h"
#include "snd_click_raw.h"
#include "snd_error_raw.h"
#include "snd_bloop_raw.h"

extern MODPlay mod_track;

void initSound();
void playDefaultLevelMusic();
void playTitleScreenMusic();
void playLevelCleared();
void playOggMusic();
void playClick();
void playError();
void playBloop();
int loadCustomSongs();
bool checkOggExt(char* s1);
void shuffle(int len);
void swap(int a, int b);

#endif
