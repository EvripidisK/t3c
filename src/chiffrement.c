#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>
#include "chiffrement.h"
#include "structures.h"
#include "choixMode.h"

void hacher_mot(const char *mot, unsigned char *mot_hash, unsigned int *hash_len, const char *choixAlgo)
{
	EVP_MD_CTX *ctx = EVP_MD_CTX_new();
	if (ctx == NULL)
	{
		fprintf(stderr,"Erreur de creation du contexte\n");
		return;
	}
	if (ft_strcasecmp(choixAlgo,"sha256") ==0) {
		EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
	}
	else if (ft_strcasecmp(choixAlgo,"md5") ==0) {
		EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
	}
	else 
	{
		EVP_MD_CTX_free(ctx);
		return;	
	}
	EVP_DigestUpdate(ctx, mot, strlen(mot));
	EVP_DigestFinal_ex(ctx, mot_hash, hash_len);
	EVP_MD_CTX_free(ctx);
}

int hex_to_bytes(const char *hex, unsigned char *bytes,int hash_len)
{
	const char *base = "0123456789abcdef";
	const char *p1;
	const char *p2;

	if (strlen(hex) !=(size_t)hash_len * 2)
		return 1;

	for (int i = 0; i < hash_len; i++)
	{
		p1 = strchr(base, tolower((unsigned char)hex[2 * i]));
		p2 = strchr(base, tolower((unsigned char)hex[2 * i + 1]));

		if (p1 == NULL || p2 == NULL)
			return 1;

		bytes[i] = (p1 - base) * 16 + (p2 - base);
	}
	return 0;
}

int bytes_to_hex(unsigned char *bytes, char *hex, int hash_len)
{
	const char *base = "0123456789abcdef";

	for (int i = 0; i <  hash_len; i++)
	{
		hex[2 * i]     = base[bytes[i] / 16];
		hex[2 * i + 1] = base[bytes[i] % 16];
	}

	hex[2*hash_len] = '\0';
	return 0;
}



