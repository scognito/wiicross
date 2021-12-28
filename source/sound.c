#include "../include/wiicross.h"
#include "sound.h"
#include <asndlib.h>
#include <aesndlib.h>

extern s_option options;

void initSound(){

	#ifdef IS_EMU
	return;
	#endif

	SND_Init(INIT_RATE_48000);
	//MODPlay_Init(&mod_track);
	
	song.totalSongs = loadCustomSongs();
	shuffle(song.totalSongs);
}

void playDefaultLevelMusic(){

	#ifdef IS_EMU
	return;
	#endif
	SND_Pause(0); // the sound loop is running now

	int rand;
	rand = getRandomNum(0, 1);
	
	if(rand == 0){
		if(MODPlay_SetMOD(&mod_track, snd_bg0_mod ) < 0 ){
			MODPlay_Unload(&mod_track);
		}
		else{
			MODPlay_SetVolume(&mod_track, 64,64);
			MODPlay_Start(&mod_track); // Play the MOD
		}
	}
	else{
		if(MODPlay_SetMOD(&mod_track, snd_bg1_mod ) < 0 ){
			MODPlay_Unload(&mod_track);
		}
		else{
			MODPlay_SetVolume(&mod_track, 64,64);
			MODPlay_Start(&mod_track); // Play the MOD
		}
	}
}

void playTitleScreenMusic(){

	#ifdef IS_EMU
	return;
	#endif
	
	if(options.musicType == MUSIC_CUSTOM){
		StopOgg();
	}
	
	SND_Pause(0); // the sound loop is running now

	if(MODPlay_SetMOD(&mod_track, snd_titlescreen_mod ) < 0 ){
		MODPlay_Unload(&mod_track);
	}
	else{
		MODPlay_SetVolume(&mod_track, 64,64);
		MODPlay_Start(&mod_track);
	}
}

void playLevelCleared(){

	#ifdef IS_EMU
	return;
	#endif
	
	PlayOgg(mem_open((char*)snd_levelcleared_ogg, snd_levelcleared_ogg_size), 0, OGG_ONE_TIME);
	SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 8000, 0, (char*)snd_levelcleared_raw, snd_click_raw_size, 255, 255, NULL);
}

void playOggMusic(){

	#ifdef IS_EMU
	return;
	#endif
	
	#ifndef HW_RVL
	return;
	#endif
	
	if(song.totalSongs == 0)
		return;
	
	char sng[200];	
	int fd;
	
	sprintf(sng, DIR_ROOT "res/music/%s", song.songsArray[getRandomNum(0, song.totalSongs-1)]);
	
	fd = open(sng,O_RDONLY, 0);
	if(fd < 0){
		//breakpoint(strerror(errno), errno);
		//breakpoint(sng, 123);
		return;
	}

	PlayOgg(fd, 0, OGG_ONE_TIME);
}

int loadCustomSongs(){
/*
	struct stat st;
	char filename[MAXNAMLEN];
	
	DIR_ITER* dir;
	dir = diropen (DIR_ROOT "res/music");
	
	int i = 0;
	
	if(dir == NULL){
		return -1;
	}
	
	while(dirnext(dir, filename, &st) == 0){
	
		if((strlen(filename) > 2) && (st.st_mode == 33206)){
			if(checkOggExt(filename)){
				strcpy(song.songsArray[i], filename);
				i++;
			}
		}
	}
	
	dirclose(dir);
	
	return i;*/
	return 0;
}

void playClick(){
	SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 8000, 0, (char*)snd_click_raw, snd_click_raw_size, 255, 255, NULL);
}

void playError(){
	SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 8000, 0, (char*)snd_error_raw, snd_click_raw_size, 255, 255, NULL);
}

void playBloop(){
	SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 8000, 0, (char*)snd_error_raw, snd_click_raw_size, 255, 255, NULL);
	SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 8000, 0, (char*)snd_bloop_raw, snd_bloop_raw_size, 255, 255, NULL);
}

bool checkOggExt(char* s1){
    
    if((s1[0] != 'o' && s1[0] != 'O') || (s1[1] != 'g' && s1[1] != 'G') || (s1[2] != 'g' && s1[2] != 'G'))
      return true;
    
    return false;
}

void shuffle(int len){
	
	int i;
	
	for(i=0; i<len; i++){
		int a = getRandomNum(0, len-1);
        int b = getRandomNum(0, len-1);
		swap(a, b);
	}
}

void swap(int a, int b){

	char temp[256];
	
	sprintf(temp, song.songsArray[a]);
	sprintf(song.songsArray[a], song.songsArray[b]);
	sprintf(song.songsArray[b], temp);
}
