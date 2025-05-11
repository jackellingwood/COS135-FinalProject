// library.c
// contains all functions that can act on a Library struct

#include "library.h"

// parses a Library from the given txt file or creates a txt file if one doesn't exist
// returns Library*, either filled with songs or empty
Library* readFromFile(char* path) {

    Library* n = malloc(sizeof(Library));

    n->size = 0;
    n->maxSize = INIT_LIBRARY_MAX_SIZE;
    n->songs = malloc(sizeof(Song*) * INIT_LIBRARY_MAX_SIZE);

    FILE* f = fopen(path, "r");
    if (f == NULL) { // if file doesn't exist, create new file and return empty library
        f = fopen(path, "w+");
    } else {
        char buffer[1024];

        while (fgets(buffer, sizeof(buffer), f) != NULL) {

            //trim whitespace
            char* ptr = buffer + strlen(buffer) - 1;
            while(isspace(*ptr)) ptr--;
            *(ptr + 1) = 0;
            ptr = buffer;
            while(isspace(*ptr)) ptr++;

            char* name = strtok(ptr, ":");

            char* tag = strtok(NULL, ",");
            int numTags = 0;
            char** tags = malloc(sizeof(char*) * MAX_TAGS);
            while (tag != NULL) {
                tags[numTags] = malloc(sizeof(char) * MAX_TAG_LENGTH);
                strcpy(tags[numTags], tag);
                tag = strtok(NULL, ",");
                numTags++;
            }

            // add song, make sure to resize
            addSong(n, createSong(name, numTags, tags));
        }
    }

    fclose(f);

    return n;
}

// performs a deep copy on the given library and returns the pointer to the new Library*
Library* copyLibrary(Library* c) {
    Library* n = malloc(sizeof(Library));

    // copy basic details
    n->size = 0;
    n->maxSize = INIT_LIBRARY_MAX_SIZE;
    n->songs = malloc(sizeof(Song*) * INIT_LIBRARY_MAX_SIZE);

    // copy songs
    for (Song** songToCopy = c->songs; songToCopy < c->songs + c->size; songToCopy++) {
        addSong(n, copySong(*songToCopy));
    }

    return n;
}

// filters out songs that do not contain all of the given tags and returns the resulting new Library*
Library* containsTags(Library* library, char* tags[], int numTags) {
    Library* n = malloc(sizeof(Library));

    n->size = 0;
    n->maxSize = INIT_LIBRARY_MAX_SIZE;
    n->songs = malloc(sizeof(Song*) * INIT_LIBRARY_MAX_SIZE);

    for (int i = 0; i < library->size; i++) {
        Song* songToCmp = library->songs[i];
        if (isTagSubset(songToCmp->tags, songToCmp->numTags, tags, numTags)) {
            addSong(n, copySong(songToCmp));
        }
    }

    return n;
}

// filters out songs that do not contain any of the given tags and returns the resulting new Library*
Library* anyTags(Library* library, char* tags[], int numTags) {
    Library* n = malloc(sizeof(Library));

    n->size = 0;
    n->maxSize = INIT_LIBRARY_MAX_SIZE;
    n->songs = malloc(sizeof(Song*) * INIT_LIBRARY_MAX_SIZE);

    for (int i = 0; i < library->size; i++) {
        Song* songToCmp = library->songs[i];
        if (isAnyTagIn(songToCmp->tags, songToCmp->numTags, tags, numTags)) {
            addSong(n, copySong(songToCmp));
        }
    }

    return n;
}

// adds the given Song to the given Library, realloc'ing to double the size if necessary
void addSong(Library* library, Song* song) {
    if (library->size == library->maxSize) { // realloc library if needed
        // printf("Resizing arr: old:%d new:%d\n", library->maxSize, library->maxSize * 2);
        Song** temp;
        library->maxSize *= 2;
        temp = realloc(library->songs, sizeof(Song*) * library->maxSize);
        if (temp != NULL) {
            library->songs = temp;
        }
    }
    library->songs[library->size++] = song;
}

// edits the Song with the given name in the given Library to contain new information
// returns 0 if successful, 1 if song was not found
int editSong(Library* library, char* name, char* newName, int numNewTags, char** newTags) {
    // search through songs
    // if song if found, free it and replace the pointer with the new info

    for (int i = 0; i < library->size; i++) {
        if (strcmp(library->songs[i]->name, name) == 0) { // if strings are equal
            freeSong(library->songs[i]);
            library->songs[i] = createSong(newName, numNewTags, newTags);

            return 0;
        }
    }

    return 1;
}

// removes the Song with the given name in the given Library and shifts all Songs in the Library back one
// realloc's the Library to half of the current size if possible 
// returns 0 if successful, 1 if song was not found
int removeSong(Library* library, char* name) {
    // iterate through songs
    // if song is found, free it and shift all of the songs back one

    int i = 0;
    while (i < library->size) {
        if (strcmp(library->songs[i]->name, name) == 0) {
            freeSong(library->songs[i]);
            break;
        }
        i++;
    }

    if (i == library->size) { // didn't find song, exit with error
        return 1;
    }

    for (int j = i + 1; j < library->size; j++) {
        library->songs[j - 1] = library->songs[j];
    }

    library->size--;

    if (library->size <= library->maxSize / 2) {
        // printf("Downsizing arr: old:%d new:%d\n", library->maxSize, library->maxSize / 2);
        Song** temp;
        library->maxSize /= 2;
        temp = realloc(library->songs, sizeof(Song*) * library->maxSize);
        if (temp != NULL) {
            library->songs = temp;
        }
    }

    return 0;
}

// sorts the Songs in the given Library by name using bubble sort
void sortLibrary(Library* library) { // bubble sort
    int swaps = 0;
    do { // continue until sorted
        swaps = 0;
        for (int i = 0; i < library->size - 1; i++) { // iterate through library
            if (strcmp(library->songs[i]->name, library->songs[i + 1]->name) > 0) {
                Song* temp = library->songs[i];
                library->songs[i] = library->songs[i + 1];
                library->songs[i + 1] = temp;
                swaps++;
            }
        }
    } while (swaps > 0);
}

// saves the Library to the given txt file
void saveToFile(Library* library, char* path) {

    FILE* f = fopen(path, "w");

    for (int i = 0; i < library->size; i++) {
        Song* songToAdd = library->songs[i];
        fprintf(f, "%s:", songToAdd->name);
        if (songToAdd->numTags >= 1) {
            for (int i = 0; i < songToAdd->numTags - 1; i++) {
                fprintf(f, "%s,", songToAdd->tags[i]);
            }
            fprintf(f, "%s", songToAdd->tags[songToAdd->numTags - 1]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

// print all songs in the given library
void printLibrary(Library* library) {
    for (int i = 0; i < library->size; i++) {
        printSong(library->songs[i]);
    }
}

// frees all attributes of the given Library
void freeLibrary(Library* library) {
    for (int i = 0; i < library->size; i++) {
        freeSong(library->songs[i]);
    }
    free(library->songs);
    free(library);
}