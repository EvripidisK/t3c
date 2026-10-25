#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "chiffrement.h"
#include "trietrecherche.h"
#include <openssl/evp.h>

int rechercherT3C(const char *cheminTable)
{
	int nb_lignes = 0;
	int hash_len = 0;
	char ligne[BUFFER_SIZE];
	FILE *table = fopen(cheminTable, "r");
	if (table == NULL)
	{
		fprintf(stderr, "Erreur : Impossible d'ouvrir la table %s\n", cheminTable);
		return EXIT_FAILURE;
	}
	while (fgets(ligne, BUFFER_SIZE, table))
	{
		nb_lignes++;
	}
	rewind(table);

	entree *tableau = malloc(nb_lignes * sizeof(entree));
	if (tableau == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire pour la table.\n");
		fclose(table);
		return EXIT_FAILURE;
	}

	int nb_elements = 0;

	while (fgets(ligne, BUFFER_SIZE, table) != NULL && nb_elements < nb_lignes) {
		ligne[strcspn(ligne, "\r\n")] = '\0';

		char *separateur = strrchr(ligne, ':');
		if (separateur == NULL) continue;

		*separateur = '\0'; 
		char *mot_str = ligne;
		char *hash_hex = separateur + 1;
		int val_ref = strlen(hash_hex)/2;
		if (hash_len == 0)
			hash_len = val_ref;
		else if (hash_len != 0)
		{
			if (hash_len != val_ref)
			{		
				fprintf(stderr, "Erreur de format de hash à la ligne %d\n", nb_elements + 1);
				continue;
			}
		}
		tableau[nb_elements].mot = strdup(mot_str);

		tableau[nb_elements].hash = malloc(hash_len);
		if (hex_to_bytes(hash_hex, tableau[nb_elements].hash,hash_len) != 0) {
			fprintf(stderr, "Erreur de format de hash à la ligne %d\n", nb_elements + 1);
			free(tableau[nb_elements].mot);
			free(tableau[nb_elements].hash);
			continue;
		}
		nb_elements++;
	}

	char ligne_saisie[BUFFER_SIZE];
	unsigned char hash_recherche[EVP_MAX_MD_SIZE];
	quicksort(tableau,0,nb_elements-1,hash_len);
	while (fgets(ligne_saisie, BUFFER_SIZE, stdin) != NULL) {
		ligne_saisie[strcspn(ligne_saisie, "\r\n")] = '\0';
		if (hex_to_bytes(ligne_saisie,hash_recherche, hash_len)!=1)
		{
			int indice_trouve = recherche_dicho(tableau, nb_elements, hash_recherche, hash_len);
			if (indice_trouve != -1)
				fprintf(stdout, "%s\n",tableau[indice_trouve].mot);
			else
				fprintf(stdout, "\n");
		}else {

			fprintf(stderr, "Ligne mal formée: %s\n", ligne_saisie);
			fprintf(stdout, "\n");
		}		
	}
	for (int k = 0; k < nb_elements; k++)
	{ 
		free(tableau[k].mot); 
		free(tableau[k].hash); 
	} 
	free(tableau);
	fclose(table);
	return 0;
}

//les 3 foncxtions qui suivent servent a classer le fichier avant de faire la recherche
void swap_entree(entree *a, entree *b)
{
	entree tmp = *a;
	*a = *b;
	*b = tmp;
}

int pivot(entree *table, int bas, int haut,int hash_len)
{
	unsigned char *pivot_val = table[haut].hash;
	int i = bas - 1;

	for (int j = bas; j < haut; j++)
	{
		if (memcmp(table[j].hash, pivot_val, hash_len) < 0)
		{
			i++;
			swap_entree(&table[i], &table[j]);
		}
	}
	swap_entree(&table[i + 1], &table[haut]);
	return i + 1;
}

void quicksort(entree *table, int bas, int haut, int hash_len)
{
	if (bas < haut) 
	{
		int p = pivot(table, bas, haut,hash_len);
		quicksort(table, bas, p - 1, hash_len);
		quicksort(table, p + 1, haut,hash_len);
	}
}

//recherche dichotomique car fichier classé en amont
int recherche_dicho(entree *table, int taille, const unsigned char *cible, int hash_len)
{
	int gauche = 0;
	int droite = taille - 1;

	while (gauche <= droite)
	{
		int milieu = gauche + (droite - gauche) / 2;
		int cmp = memcmp(table[milieu].hash, cible, hash_len);

		if (cmp == 0)
			return milieu;
		else if (cmp < 0)
			gauche = milieu + 1;
		else
			droite = milieu - 1;
	}
	return -1;
}

