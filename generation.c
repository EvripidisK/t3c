#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chiffrement.h"
#include "generation.h"
#include "structures.h"
#include <openssl/evp.h>

int ft_str_is_printable(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] < 32 || str[i] > 126)
            return (0);
        i++;
    }
    return (1);
}

int genererT3C(const char *cheminCommande, const char *cheminOption, const char *choixAlgo)
{

	FILE *dico = fopen(cheminCommande, "r");
	if (dico == NULL)
	{
		fprintf(stderr, "Erreur : Impossible d'ouvrir le dictionnaire %s\n", cheminCommande);
		return EXIT_FAILURE;
	}

	FILE *rainbowTable = fopen(cheminOption, "w");

	if (rainbowTable == NULL)
	{
		fprintf(stderr, "Erreur : Impossible de créer le fichier de rainbowTable %s\n", cheminOption);
		fclose(dico); 
		return EXIT_FAILURE;
	}

	char ligne[BUFFER_SIZE];
	unsigned char hash_binaire[EVP_MAX_MD_SIZE]; 
	char hash_hex[65];                     
	unsigned int hash_len = 0;
	int compteur = 0;

	while (fgets(ligne, sizeof(ligne), dico) != NULL) {

		ligne[strcspn(ligne, "\r\n")] = '\0';
		if (ft_str_is_printable(ligne) == 1)
		{
			hacher_mot(ligne, hash_binaire, &hash_len, choixAlgo);
			bytes_to_hex(hash_binaire, hash_hex,hash_len);	 	
			fprintf(rainbowTable, "%s:%s\n", ligne, hash_hex);
			compteur++;
		}
	}

	if (compteur == 0 )
	{
		fprintf(stderr, "Erreur : Dictionnaire vide\n");
		fclose(dico); 
		fclose(rainbowTable);
		remove(cheminOption);
		return EXIT_FAILURE;
	}
	
	fclose(dico);
	fclose(rainbowTable);

	fprintf(stderr, "[Succès] %d mots ont été hachés et sauvegardés.\n", compteur);

	return EXIT_SUCCESS;
}

