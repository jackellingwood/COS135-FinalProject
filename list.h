#pragma once

#include "song.h"

#include <ctype.h>

#define INIT_LIST_MAX_SIZE 2

typedef struct List {
    Song** songs;
    int size;
    int maxSize;
} List;

List* readFromFile(char* path);
void addSong(List* list, Song* song);
int editSong(List* list, Song* song);
int removeSong(List* list, Song* song);
void printList(List* list);
void freeList(List* list);