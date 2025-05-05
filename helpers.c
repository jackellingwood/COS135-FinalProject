#include "helpers.h"
#include "song.h"

// modified from https://www.geeksforgeeks.org/find-whether-an-array-is-subset-of-another-array-set-1/

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void freeStrings(char** sArr, int aSize) {
    for (int i = 0; i < aSize; i++) {
        free(sArr[i]);
    }
    free(sArr);
}

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
            // Element found in both arrays, move to the next element in both arrays
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