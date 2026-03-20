#ifndef BLINDTEST
#define BLINDTEST

typedef struct
{
    char filename[30];
    char artist[30];
    char title[30];
    struct Song *next;
} Song;

typedef struct
{
    char name[30];
    int score;
    struct player *next;
} player;
#endif