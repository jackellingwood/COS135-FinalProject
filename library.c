#include "library.h"
#include "song.h"

Library* readFromFile(char* path) {

    Library* n = malloc(sizeof(Library));

    n->size = 0;
    n->maxSize = INIT_LIBRARY_MAX_SIZE;
    n->songs = malloc(sizeof(Song*) * INIT_LIBRARY_MAX_SIZE);

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

void addSong(Library* library, Song* song) {
    if (library->size == library->maxSize) { // realloc library if needed
        Song** temp;
        library->maxSize *= 2;
        temp = realloc(library->songs, sizeof(Song*) * library->maxSize);
        if (temp != NULL) {
            library->songs = temp;
        }
    }
    library->songs[library->size++] = song;
}

int editSong(Library* library, char* name) {}
int removeSong(Library* library, char* name) {}

void printLibrary(Library* library) {
    for (int i = 0; i < library->size; i++) {
        printSong(library->songs[i]);
    }
}

void freeLibrary(Library* library) {
    for (int i = 0; i < library->size; i++) {
        freeSong(library->songs[i]);
    }
    free(library->songs);
    free(library);
}