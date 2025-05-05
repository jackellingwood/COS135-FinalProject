#pragma once

#include "helpers.h"
#include "song.h"

#include <ctype.h>

#define INIT_LIBRARY_MAX_SIZE 2

typedef struct Library {
    Song** songs;
    int size;
    int maxSize;
} Library;

Library* readFromFile(char* path);
Library* copyLibrary(Library* c);
Library* containsTags(Library* library, char* tags[], int numTags);
Library* anyTags(Library* library, char* tags[], int numTags);
void addSong(Library* library, Song* song);
int editSong(Library* library, char* name, char* newName, int numNewTags, char** newTags);
int removeSong(Library* library, char* name);
void sortLibrary(Library* library);
void saveToFile(Library* library, char* path);
void printLibrary(Library* library);
void freeLibrary(Library* library);