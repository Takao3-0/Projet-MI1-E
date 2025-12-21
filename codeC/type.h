#ifndef TYPES_H
#define TYPES_H

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef enum { SRC, REAL , MAX } HistoMode;

typedef enum { AVL_HISTO, AVL_LEAKS } AVLKey;

#define CHECK_MALLOC(p, cleanup) \
    do \
    { \
        if (!(p)) \
        { \
            cleanup; \
            return NULL; \
        } \
    } while(0)

#define SUCCES 0   
#define ERREUR_ARG 1
#define ERREUR_FOPEN 2
#define ERREUR_MALLOC 3
#define ERREUR_USINEIN_CONNU 4
#define ERREUR_NULL 5


#define FILEOPEN(f, filename) \
    do \
    { \
        if (!(f)) \
        { \
            exit(ERREUR_FOPEN); \
        } \
    } while (0)

#endif