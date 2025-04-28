#include "song.h"
#include "library.h"

int main(int argc, char* argv[]) {

    // demo of how I could take tags from input
    char** cmdTags = malloc(sizeof(char*) * MAX_TAGS);
    for (int i = 0; i < argc - 2; i++) {
        cmdTags[i] = malloc(sizeof(char) * MAX_TAG_LENGTH);
        strcpy(cmdTags[i], argv[i + 2]);
    }

    Song* s = createSong(argv[1], argc - 2, cmdTags);
    printSong(s);
    freeSong(s);

    printf("\n");

    Library* l = readFromFile("library.txt");
    printLibrary(l);
    freeLibrary(l);

    return 0;
}