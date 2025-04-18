#include "song.h"

Song* createSong(char* name, int numTags, char** tags) {
    Song* n = malloc(sizeof(Song));

    strcpy(n->name, name);

    n->numTags = numTags;

    for (int i = 0; i < n->numTags; i++) {
        strcpy(n->tags[i], tags[i + 2]);
    }

    return n;
}

void printSong(Song* song) {
    printf("%s: ", song->name);
    for (int i = 0; i < song->numTags - 1; i++) {
        printf("%s, ", song->tags[i]);
    }
    printf("%s\n", song->tags[song->numTags - 1]);
}

void freeSong(Song* song) {
    free(song);
}