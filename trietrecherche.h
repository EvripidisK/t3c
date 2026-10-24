#ifndef TRI_ET_RECHERCHE_H
#define TRI_ET_RECHERCHE_H

#include "structures.h"

void quicksort(entree *table, int bas, int haut, int hash_len);
int recherche_dicho(entree *table, int taille, const unsigned char *cible,int hash_len);
int rechercherT3C(const char *cheminTable);
void swap_entree(entree *a, entree *b);
#endif

