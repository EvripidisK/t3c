#ifndef STRUCTURES_H
#define STRUCTURES_H

#define HASH_SIZE 32
#define BUFFER_SIZE 1024

typedef struct entree
{
    char *mot;
    unsigned char *hash;
} entree;

#endif

