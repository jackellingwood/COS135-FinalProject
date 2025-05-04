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

    printf("\n");

    Library* l = readFromFile("library.txt");
    printLibrary(l);
    printf("\n");

    addSong(l, s);

    char** evilTags = malloc(sizeof(char*) * MAX_TAGS);
    evilTags[0] = malloc(sizeof(char) * MAX_TAG_LENGTH);
    strcpy(evilTags[0], "shadow");

    editSong(l, "dark", "evil", 1, evilTags);
    printLibrary(l);
    sortLibrary(l);
    printf("\n");
    printLibrary(l);
    printf("\n");
    Library* c = copyLibrary(l);
    printLibrary(c);

    saveToFile(c, "newLibrary.txt");

    printf("\n");
    char* tagsToCmp[] = {"fun", "pop"};
    Library* m = containsTags(l, tagsToCmp, 2);
    printLibrary(m);

    freeLibrary(l);
    freeLibrary(c);
    freeLibrary(m);

    return 0;
}