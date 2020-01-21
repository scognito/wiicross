#ifndef _OPTIONSCREEN_
#define _OPTIONSCREEN_

#include <errno.h>

extern s_background bg_options;
extern s_sprite controllertype;
extern s_sprite musictype;

void optionScreen();
void checkInput_OS();
void applyChanges();
#endif
