#ifndef CHIFFREMENT_H
#define CHIFFREMENT_H

void hacher_mot(const char *mot, unsigned char *mot_hash, unsigned int *hash_len, const char *choixAlgo);
int hex_to_bytes(const char *hex, unsigned char *bytes, int hash_len);
int bytes_to_hex(unsigned char *bytes, char *hex, int hash_len);
#endif

