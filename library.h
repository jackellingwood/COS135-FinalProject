#pragma once

#include "song.h"

#include <ctype.h>

#define INIT_LIBRARY_MAX_SIZE 2

typedef struct Library {
    Song** songs;
    int size;
    int maxSize;
} Library;

Library* readFromFile(char* path);
void addSong(Library* library, Song* song);
int editSong(Library* library, char* name);
int removeSong(Library* library, char* name);
void printLibrary(Library* library);
void freeLibrary(Library* library);