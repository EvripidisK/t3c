#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "choixMode.h"
#include "generation.h"
#include "trietrecherche.h"
#include <ctype.h>

// Variables utilisées pour stocker les valeurs des options 
const char *cheminCommande = NULL;
const char *cheminOption = NULL;
const char *choixAlgo = "MD5";

//fonction utilitaire pour comaprer deux chaines de caractères en terme de casse
int ft_strcasecmp(const char *str1, const char *str2)
{
	int i = 0;
	while (tolower((unsigned char)str1[i]) == tolower((unsigned char)str2[i]) && str1[i]!= '\0' && str2[i] != '\0')
	{
		i++;
	}
	return (tolower((unsigned char)str1[i]) - tolower((unsigned char)str2[i]));


}

int choixMode(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Erreur : mode manquant.\n");
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "G") == 0)
	{
		return modeG(argc, argv);
	}
	else if (strcmp(argv[1], "L") == 0)
	{
		return modeL(argc, argv);
	}
	else
	{
		fprintf(stderr, "Erreur : mode invalide. Utilisez G ou L.\n");
		return EXIT_FAILURE;
	}
}


int modeG(int argc, char **argv)
{
	int commande = 0;
	int option = 0;
	int autreAlgo = 0;

	/* Réinitialiser les valeurs pour le mode G */
	cheminCommande = NULL;
	cheminOption = NULL;
	choixAlgo = "MD5";

	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0 ||
				strcmp(argv[i], "--input") == 0)
		{
			if (i + 1 >= argc)
			{
				fprintf(stderr,
						"Erreur : valeur manquante pour l'entrée.\n");
				return EXIT_FAILURE;
			}

			cheminCommande = argv[i + 1];
			commande = 1;
			i++;
		}
		else if (strcmp(argv[i], "-o") == 0 ||
				strcmp(argv[i], "--output") == 0)
		{
			if (i + 1 >= argc)
			{
				fprintf(stderr,
						"Erreur : valeur manquante pour la sortie.\n");
				return EXIT_FAILURE;
			}

			cheminOption = argv[i + 1];
			option = 1;
			i++;
		}
		else if (strcmp(argv[i], "-a") == 0 ||
				strcmp(argv[i], "--algo") == 0)
		{
			if (i + 1 >= argc)
			{
				fprintf(stderr,
						"Erreur : valeur manquante pour l'algorithme.\n");
				return EXIT_FAILURE;
			}
			if (ft_strcasecmp(argv[i+1], "md5") == 0 || ft_strcasecmp(argv[i+1], "sha256")==0)

			{
				choixAlgo = argv[i + 1];
				autreAlgo = 1;
				i++;
			}
			else 
			{
				fprintf(stderr,"Erreur : option inconnue '%s'.\n", argv[i + 1]);
				return EXIT_FAILURE;
			}
		}
		else
		{
			fprintf(stderr,
					"Erreur : option inconnue '%s'.\n", argv[i]);
			return EXIT_FAILURE;
		}
	}

	/* Vérifier la présence des options obligatoires */
	if (!commande || !option)
	{
		fprintf(stderr,
				"Erreur : les options -i et -o sont obligatoires.\n");
		return EXIT_FAILURE;
	}

	/* Appeler le traitement de génération */
	(void)autreAlgo;

	return genererT3C(cheminCommande, cheminOption, choixAlgo);
}


int modeL(int argc, char **argv)
{
	int table_present = 0;
	const char *cheminTable = NULL;

	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-t") == 0 ||
				strcmp(argv[i], "--table") == 0)
		{
			if (i + 1 >= argc)
			{
				fprintf(stderr,
						"Erreur : valeur manquante pour la table.\n");
				return EXIT_FAILURE;
			}

			cheminTable = argv[i + 1];
			table_present = 1;
			i++;
		}
		else
		{
			fprintf(stderr,
					"Erreur : option inconnue '%s'.\n", argv[i]);
			return EXIT_FAILURE;
		}
	}

	/* Vérifier la présence de l'option obligatoire */
	if (!table_present)
	{
		fprintf(stderr,
				"Erreur : l'option -t est obligatoire en mode L.\n");
		return EXIT_FAILURE;
	}

	/* Appeler le traitement de recherche */
	return rechercherT3C(cheminTable);
}
