#include "helpers.h"
#include "song.h"

// modified from https://www.geeksforgeeks.org/find-whether-an-array-is-subset-of-another-array-set-1/
int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int isTagSubset(char* a[], int aSize, char* b[], int bSize) {
    qsort(a, aSize, sizeof(char*), compare);
    qsort(b, bSize, sizeof(char*), compare);

    int i = 0, j = 0;

    // Traverse both arrays using two pointers
    while (i < aSize && j < bSize) {
        if (strcmp(a[i], b[j]) < 0) {
            // Element in a is smaller, move to the next element in a
            i++;
        } else if (strcmp(a[i], b[j]) == 0) {
            // Element found in both arrays, move to the next element in both arrays
            i++;
            j++;
        } else {
            // Element in b not found in a, not a subset
            return 0;
        }
    }

    // If we have traversed all elements in b, it is a subset
    return j == bSize;
}