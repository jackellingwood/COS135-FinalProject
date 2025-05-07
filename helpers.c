// helpers.c
// contains functions that help with sorting and hashing
// all outside sources linked

#include "helpers.h"
#include "song.h"

// frees a list of strings
void freeStrings(char** sArr, int aSize) {
    for (int i = 0; i < aSize; i++) {
        free(sArr[i]);
    }
    free(sArr);
}

// help from https://benjaminwuethrich.dev/2015-03-07-sorting-strings-in-c-with-qsort.html

// wrapper for strcmp that allows it to be used in qsort
int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// modified from https://www.geeksforgeeks.org/find-whether-an-array-is-subset-of-another-array-set-1/

// return 1 if string array b is a subset of string array a, otherwise, return 0
int isTagSubset(char** a, int aSize, char** b, int bSize) {
    // make a deep copy such that we don't have to sort the original arr
    // qsort only seems to like using dynamic allocation?
    char** copyA = malloc(sizeof(char*) * aSize);
    char** copyB = malloc(sizeof(char*) * bSize);

    for (int i = 0; i < aSize; i++) {
        copyA[i] = malloc(sizeof(char) * MAX_TAG_LENGTH);
        strcpy(copyA[i], a[i]);
    }

    for (int i = 0; i < bSize; i++) {
        copyB[i] = malloc(sizeof(char) * MAX_TAG_LENGTH);
        strcpy(copyB[i], b[i]);
    }

    qsort(copyA, aSize, sizeof(char*), compare);
    qsort(copyB, bSize, sizeof(char*), compare);

    int i = 0, j = 0;

    // Traverse both arrays using two pointers
    while (i < aSize && j < bSize) {
        if (strcmp(copyA[i], copyB[j]) < 0) {
            // Element in copyA is smaller, move to the next element in copyA
            i++;
        } else if (strcmp(copyA[i], copyB[j]) == 0) {
            // Element found in both arrays, move to the next element in both arrays
            i++;
            j++;
        } else {
            // Element in copyB not found in copyA, not a subset
            freeStrings(copyA, aSize);
            freeStrings(copyB, bSize);
            return 0;
        }
    }

    // If we have traversed all elements in copyB, it is a subset
    freeStrings(copyA, aSize);
    freeStrings(copyB, bSize);
    return j == bSize;
}

// modified from https://www.geeksforgeeks.org/find-whether-an-array-is-subset-of-another-array-set-1/

// return 1 if string array b contains any of the tags in string array a, otherwise, return 0
int isAnyTagIn(char** a, int aSize, char** b, int bSize) {
    // make a deep copy such that we don't have to sort the original arr
    // qsort only seems to like using dynamic allocation?
    char** copyA = malloc(sizeof(char*) * aSize);
    char** copyB = malloc(sizeof(char*) * bSize);

    for (int i = 0; i < aSize; i++) {
        copyA[i] = malloc(sizeof(char) * MAX_TAG_LENGTH);
        strcpy(copyA[i], a[i]);
    }

    for (int i = 0; i < bSize; i++) {
        copyB[i] = malloc(sizeof(char) * MAX_TAG_LENGTH);
        strcpy(copyB[i], b[i]);
    }

    qsort(copyA, aSize, sizeof(char*), compare);
    qsort(copyB, bSize, sizeof(char*), compare);

    int i = 0, j = 0;

    // Traverse both arrays using two pointers
    while (i < aSize && j < bSize) {
        if (strcmp(copyA[i], copyB[j]) < 0) {
            // Element in copyA is smaller, move to the next element in copyA
            i++;
        } else if (strcmp(copyA[i], copyB[j]) == 0) {
            // Element found in both arrays, copyA contains a tag in copyB
            freeStrings(copyA, aSize);
            freeStrings(copyB, bSize);
            return 1;
        } else {
            // Element in copyB not found in copyA, try next copyB element
            i = 0;
            j++;
        }
    }

    // If we have not found any elements, nothing matches
    freeStrings(copyA, aSize);
    freeStrings(copyB, bSize);
    return 0;
}

// by Dan Bernstein from http://www.cse.yorku.ca/~oz/hash.html
// recommended for the same use case as https://stackoverflow.com/questions/4014827/how-can-i-compare-strings-in-c-using-a-switch-statement

// takes a string and returns to an unsigned long hash
unsigned long djb2Hash(unsigned char* str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

