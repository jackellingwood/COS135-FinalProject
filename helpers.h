#pragma once

#include <stdlib.h>
#include <string.h>

// hashes corresponding to each of my command so that they can be called in the switch statement
#define Q 177686
#define S 177688
#define PL 5863713
#define ADD 193486030
#define QUIT 6385632776
#define HELP 6385292014
#define EDIT 6385183019
#define SORT 6385698413
#define SAVE 6385683284
#define PRINT 210724587794
#define REMOVE 6953974396019
#define PLAYLIST 7572801462537911

unsigned long djb2Hash(unsigned char* str);

int isTagSubset(char** a, int aSize, char** b, int bSize);
int isAnyTagIn(char** a, int aSize, char** b, int bSize);