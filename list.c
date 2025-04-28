#include "list.h"
#include "song.h"

List* readFromFile(char* path) {

    List* n = malloc(sizeof(List));

    n->size = 0;
    n->maxSize = INIT_LIST_MAX_SIZE;
    n->songs = malloc(sizeof(Song*) * INIT_LIST_MAX_SIZE);

    FILE* f = fopen(path, "r");
    if (f == NULL) {
        printf("File Not Found: %s", path);
        return NULL;
    }
    
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), f) != NULL) {

        //trim whitespace
        char* ptr = buffer + strlen(buffer) - 1;
        while(isspace(*ptr)) ptr--;
        *(ptr + 1) = 0;
        ptr = buffer;
        while(isspace(*ptr)) ptr++;

        //TODO: the problem may be that the below variables do not point to malloc'd memory

        char* name = strtok(ptr, ": ");

        char* tag = strtok(NULL, ", ");
        int numTags = 0;
        char** tags = malloc(sizeof(char*) * MAX_TAGS);
        while (tag != NULL) {
            tags[numTags] = malloc(sizeof(char) * MAX_TAG_LENGTH);
            strcpy(tags[numTags], tag);
            tag = strtok(NULL, ", ");
            numTags++;
        }

        // add song, make sure to resize
        addSong(n, createSong(name, numTags, tags));
    }

    fclose(f);

    return n;
}

void addSong(List* list, Song* song) {
    if (list->size == list->maxSize) {
        Song** temp;
        list->maxSize *= 2;
        temp = realloc(list->songs, sizeof(Song*) * list->maxSize);
        if (temp != NULL) {
            list->songs = temp;
        }
    }
    list->songs[list->size++] = song;
}

int editSong(List* list, Song* song) {}
int removeSong(List* list, Song* song) {}

void printList(List* list) {
    for (int i = 0; i < list->size; i++) {
        printSong(list->songs[i]);
    }
}

void freeList(List* list) {
    for (int i = 0; i < list->size; i++) {
        freeSong(list->songs[i]);
    }
    free(list->songs);
    free(list);
}