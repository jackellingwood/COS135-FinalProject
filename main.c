#include "song.h"

int main(int argc, char* argv[]) {
    Song* s = createSong(argv[1], argc - 2, argv);
    printSong(s);
    freeSong(s);
    return 0;
}