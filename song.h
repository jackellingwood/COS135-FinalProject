#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TAG_LENGTH 20
#define MAX_TAGS 8

typedef struct Song {
    char name[MAX_NAME_LENGTH];
    int numTags;
    char tags[MAX_TAGS][MAX_TAG_LENGTH];
} Song;

Song* createSong(char* name, int numTags, char** tags);
void printSong(Song* song);
void freeSong(Song* song);