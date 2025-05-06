#include "song.h"
#include "library.h"

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

        // sadly, switch statements cannot be used with strings...
        if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "help") == 0) {
            printf("Supported functions:\nquit\nhelp\nadd\nremove\nedit\nprint\nsort\nplaylist\ncopy\nsave\n");
        } else if (strcmp(command, "add") == 0) {
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
            }
        } else if (strcmp(command, "remove") == 0) {
            if (song == NULL) {
                printf("Usage: remove [song_name]\n");
            } else {
                if (removeSong(l, song) == 0) {
                    printf("Song removed successfully.\n");
                } else {
                    printf("Couldn't find song: \"%s\"\n", song);
                }
            }
        } else if (strcmp(command, "edit") == 0) {
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
        } else if (strcmp(command, "print") == 0) {
            printLibrary(l);
        } else if (strcmp(command, "sort") == 0) {
            sortLibrary(l);
        } else if (strcmp(command, "playlist") == 0) {
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
        } else if (strcmp(command, "copy") == 0) {
            // once again using song for path
            if (song == NULL) {
                printf("Usage: copy [new_library].txt\n");
            } else {
                Library* c = copyLibrary(l);
                saveToFile(c, song);
                freeLibrary(c);
            }
        } else if (strcmp(command, "save") == 0) {
            // using song variable as path
            if (song == NULL) {
                saveToFile(l, path);
            } else {
                saveToFile(l, song);
            }
        } else {
            printf("Unrecognized command: \"%s\"", command);
        }
    }

    freeLibrary(l);
}


// for testing of individual funcs
// int main(int argc, char* argv[]) {

//     // demo of how I could take tags from input
//     char** cmdTags = malloc(sizeof(char*) * MAX_TAGS);
//     for (int i = 0; i < argc - 2; i++) {
//         cmdTags[i] = malloc(sizeof(char) * MAX_TAG_LENGTH);
//         strcpy(cmdTags[i], argv[i + 2]);
//     }

//     Song* s = createSong(argv[1], argc - 2, cmdTags);
//     printSong(s);

//     printf("\n");

//     Library* l = readFromFile("library.txt");
//     printLibrary(l);
//     printf("\n");

//     addSong(l, s);

//     char** evilTags = malloc(sizeof(char*) * MAX_TAGS);
//     evilTags[0] = malloc(sizeof(char) * MAX_TAG_LENGTH);
//     strcpy(evilTags[0], "pop");

//     editSong(l, "dark", "evil", 1, evilTags);
//     printLibrary(l);
//     sortLibrary(l);
//     printf("\n");
//     printLibrary(l);
//     printf("\n");
//     Library* c = copyLibrary(l);
//     printLibrary(c);

//     saveToFile(c, "newLibrary.txt");

//     printf("\n");

//     printLibrary(l);

//     printf("\n");

//     char* tagsToCmp[] = {"fun", "pop"};
//     Library* m = containsTags(l, tagsToCmp, 2);
//     printLibrary(m);

//     printf("\n");

//     Library* n = anyTags(l, tagsToCmp, 2);
//     printLibrary(n);

//     freeLibrary(l);
//     freeLibrary(c);
//     freeLibrary(m);
//     freeLibrary(n);

//     return 0;
// }