# Song Database by Jack Ellingwood
Usage: ```./database [library_name].txt```

A new library will be created if one doesn't exist at that location.

SongDatabase is a program which can store a library of of your favorite music as a txt file, allowing you to tag your songs and filter them depending on what you want to hear!

### Commands: (note, use underscores instead of spaces in song names)
- ```quit (or q)``` : Quits the program. Any unsaved progress will be lost!
- ```help``` : Displays this list.
- ```add [song_name] [tags...]``` : Adds new song to the library with the following tags.
- ```remove [song_name]``` : Removes the song with the name given.
- ```edit [old_song_name] [new_song_name] [new_tags...]``` : Replaces the given song's name and tags.
- ```print``` : Prints the library.
- ```sort``` : Sorts the library by name.
- ```playlist (or pl) ["strictly"|"any"] [tags...]``` : Prints the songs that contain all of or any of the given tags.
- ```save (or s) [path]``` : Saves the library at the prior location or path specified.

### Usage:
Run the above commands in any way you see fit.


### How this satisfies requirements:
- malloc'd array of structs: library.c:3, library.h:10
- Makefile included
- Using pointer to assign value at memory location: library.c:22
- Looping by incrementing a pointer: library.c:57
- All memory frees
- Reading/writing to files: library.c:11, library.c:180
- GitHub Link: https://github.com/COS135-S2025/project-jackellingwood
- switch statement: main.c:41
- Not taught in class:
  - Hashing: helpers.c:107
  - Sorting (bubble sort): library.c:163