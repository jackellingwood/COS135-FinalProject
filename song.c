#include "song.h"

Song* createSong(char* name, int numTags, char** tags) {
    Song* n = malloc(sizeof(Song));

    strcpy(n->name, name);

    n->numTags = numTags;
    n->tags = tags;

    return n;
}

Song* copySong(Song* c) {
    char** copiedTags = malloc(sizeof(char*) * c->numTags);
    for (int j = 0; j < c->numTags; j++) { // copy tags
        copiedTags[j] = malloc(sizeof(char) * MAX_TAG_LENGTH);
        strcpy(copiedTags[j], c->tags[j]);
    }
    return createSong(c->name, c->numTags, copiedTags);
}

void printSong(Song* song) {
    printf("%s: ", song->name);
    for (int i = 0; i < song->numTags - 1; i++) {
        printf("%s, ", song->tags[i]);
    }
    printf("%s\n", song->tags[song->numTags - 1]);
    // printf("%s: %d tags\n", song->tags[song->numTags - 1], song->numTags);
}

void freeSong(Song* song) {
    for (int i = 0; i < song->numTags; i++) {
        free(song->tags[i]);
    }
    free(song->tags);
    free(song);
}