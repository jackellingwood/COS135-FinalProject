#include "song.h"
#include "library.h"
#include "helpers.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./database [library_name].txt\n");
        printf("The program will create a new library at the path if none exists.\n");
        return 1;
    }
    char path[256];
    strcpy(path, argv[1]);
    Library* l = readFromFile(path);
    
    char buffer[1024];
    char* ptr;

    printf("Welcome to SongDatabase, use \"help\" for help and \"quit\" to quit.\n");
    printf("Song names must be under %d chars and tags must be %d or fewer and less than %d chars.\n", MAX_NAME_LENGTH, MAX_TAGS, MAX_TAG_LENGTH);

    while (1) {
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);

        //trim whitespace
        ptr = buffer + strlen(buffer) - 1;
        while(isspace(*ptr)) ptr--;
        *(ptr + 1) = 0;
        ptr = buffer;
        while(isspace(*ptr)) ptr++;

        char* command = strtok(ptr, " ");

        char* song = strtok(NULL, " ");

        // potential start to code that would allow spaces in song/tag names
        // if (strchr(song, '\"') == NULL) { 
        //     strcat(song, strtok(ptr, "\""));
        // }

        switch(djb2Hash(command)) {
            case Q:
            case QUIT:
                freeLibrary(l);
                return 0;
            case HELP:
                printf("Supported functions:\nquit q\nhelp\nadd\nremove\nedit\nprint\nsort\nplaylist pl\nsave s\n");
                break;
            case ADD:
                if (song == NULL) {
                    printf("Usage: add [song_name] [tags...]\n");
                } else {
                    char* tag = strtok(NULL, " ");
                    int numTags = 0;
                    char** tags = malloc(sizeof(char*) * MAX_TAGS);
                    while (tag != NULL) {
                        tags[numTags] = malloc(sizeof(char) * MAX_TAG_LENGTH);
                        strcpy(tags[numTags], tag);
                        tag = strtok(NULL, ",");
                        numTags++;
                    }

                    addSong(l, createSong(song, numTags, tags));
                    printf("Added song: \"%s\"\n", song);
                }
                break;
            case REMOVE:
                if (song == NULL) {
                    printf("Usage: remove [song_name]\n");
                } else {
                    if (removeSong(l, song) == 0) {
                        printf("Song removed successfully.\n");
                    } else {
                        printf("Couldn't find song: \"%s\"\n", song);
                    }
                }
                break;
            case EDIT:
                if (song == NULL) {
                    printf("Usage: edit [old_name] [new_name] [new_tags...]\n");
                } else {
                    char* newName = strtok(NULL, " ");

                    if (newName == NULL) {
                        printf("Usage: edit [old_name] [new_name] [new_tags...]\n");
                    } else {
                        char* tag = strtok(NULL, " ");
                        int numTags = 0;
                        char** tags = malloc(sizeof(char*) * MAX_TAGS);
                        while (tag != NULL) {
                            tags[numTags] = malloc(sizeof(char) * MAX_TAG_LENGTH);
                            strcpy(tags[numTags], tag);
                            tag = strtok(NULL, ",");
                            numTags++;
                        }

                        if (editSong(l, song, newName, numTags, tags) == 0) {
                            printf("Song edited successfully.\n");
                        } else {
                            printf("Couldn't find song: \"%s\"\n", song);
                        }
                    }
                }
                break;
            case PRINT:
                printLibrary(l);
                break;
            case SORT:
                sortLibrary(l);
                printf("Library sorted.\n");
                break;
            case PL:
            case PLAYLIST:
                if (strcmp(song, "strictly") != 0 && strcmp(song, "any") != 0) {
                    printf("Usage: playlist [strictly|any] [tags...]\n");
                } else {
                    Library* c;

                    char* tag = strtok(NULL, " ");
                    int numTags = 0;
                    char** tags = malloc(sizeof(char*) * MAX_TAGS);
                    while (tag != NULL) {
                        tags[numTags] = malloc(sizeof(char) * MAX_TAG_LENGTH);
                        strcpy(tags[numTags], tag);
                        tag = strtok(NULL, ",");
                        numTags++;
                    }
                    
                    if (strcmp(song, "strictly") == 0) {
                        c = containsTags(l, tags, numTags);
                    } else if (strcmp(song, "any") == 0) {
                        c = anyTags(l, tags, numTags);
                    }

                    for (int i = 0; i < numTags; i++) {
                        free(tags[i]);
                    }
                    free(tags);

                    printLibrary(c);
                    freeLibrary(c);
                }
                break;
            case S:
            case SAVE:
                if (song == NULL) {
                    saveToFile(l, path);
                    printf("Saved to %s.\n", path);
                } else {
                    saveToFile(l, song);
                    printf("Saved to %s.\n", song);
                }
                break;
            default:
                printf("Unrecognized command: \"%s\"\n", command);
                break;
        }
    }
}