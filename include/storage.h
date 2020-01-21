#ifndef _SCOSTORAGE_
#define _SCOSTORAGE_

#include <unistd.h>
#include <sys/dir.h>

void initStorage();
int readSD(int file);
int writeSD(int file);
void saveCurrentLevel();
int readThemesDir();

#endif
