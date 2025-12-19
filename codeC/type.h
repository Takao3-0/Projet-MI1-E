#ifndef TYPES_H
#define TYPES_H

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef enum { SRC, REAL } HistoMode;

typedef enum { AVL_HISTO, AVL_LEAKS } AVLKey;

#define CHECK_MALLOC(p, cleanup) do { \
    if (!(p)) { cleanup; return NULL; } \
} while(0)

#endif