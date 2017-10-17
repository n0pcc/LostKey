/*
 * gcc -static -m32 rop_in_c.c -L openssl-1.1.0f -l:libcrypto.a
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "openssl/md5.h"

void stringFlag1EncDec(uint32_t *string) {
  string[0] = string[0] ^ 0x466C7578;
  string[1] = string[1] ^ 0x78756C46;
}

void stringFlag2Enc(char *_string) {
  uint8_t *string = (uint8_t *)_string;
  uint8_t tmp;
  int length = strlen(_string);

  if (length < 2) {
    return;
  }

  for (int i = 0; i < length - 1; i++) {
    tmp = ~string[i];
    tmp = (tmp << 4) | (tmp >> 4);
    tmp ^= string[i + 1];
    string[i] = tmp;
  }

  tmp = ~string[length - 1];
  tmp = (tmp << 4) | (tmp >> 4);
  tmp ^= 0x41;
  string[length - 1] = tmp;
}

void stringFlag2Dec(char *_string) {
  uint8_t *string = (uint8_t *)_string;
  uint8_t tmp;
  int length = strlen(_string);

  if (length < 2) {
    return;
  }

  tmp = string[length - 1];
  tmp ^= 0x41;
  tmp = (tmp << 4) | (tmp >> 4);
  string[length - 1] = ~tmp;

  for (int i = length - 2; i >= 0; i--) {
    tmp = string[i];
    tmp ^= string[i + 1];
    tmp = (tmp << 4) | (tmp >> 4);
    string[i] = ~tmp;
  }
}

// From https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
void encrypt(uint32_t *v, uint32_t *k) {
  uint32_t v0 = v[0], v1 = v[1], sum = 0, i; /* set up */
  uint32_t delta = 0x9e3779b9;               /* a key schedule constant */
  uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; /* cache key */
  for (i = 0; i < 32; i++) {                           /* basic cycle start */
    sum += delta;
    v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
    v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
  } /* end cycle */
  v[0] = v0;
  v[1] = v1;
}

int main() {
  char flag[] =
      "flag{Th3_key_1s_in_th3_secret_comp4rtment_of_your_t00l_sh3d...}";
  char flag1[] = "flag{Th3";
  char flag2[] = "_key_1s_in_th3_secret_com";
  char flag3[] = "p4rtme";
  char flag4[] = "nt_of_your_t00l_sh3d...}";

  unsigned char digest[MD5_DIGEST_LENGTH];
  uint32_t tea_key[] = {0xC2E1FAFF, 0xFFFAE1C2, 0xFFFAE1C2, 0xC2E1FAFF};

  stringFlag1EncDec((uint32_t *)flag1);
  printf("Flag part 1: 0x%X 0x%X\n", *(uint32_t *)flag1,
         *(uint32_t *)(flag1 + 4));

  stringFlag1EncDec((uint32_t *)flag1);
  printf("Flag part 1: %s\n", flag1);

  stringFlag2Enc(flag2);
  printf("Flag part 2: 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n",
         *(uint32_t *)flag2, *(uint32_t *)(flag2 + 4), *(uint32_t *)(flag2 + 8),
         *(uint32_t *)(flag2 + 12), *(uint32_t *)(flag2 + 16),
         *(uint32_t *)(flag2 + 20), flag2[24] & 0xFF);

  stringFlag2Dec(flag2);
  printf("Flag part 2: %s\n", flag2);

  MD5((unsigned char *)flag3, strlen(flag3), digest);
  printf("Flag part 3: 0x%X 0x%X 0x%X 0x%X\n", *(uint32_t *)digest,
         *(uint32_t *)(digest + 4), *(uint32_t *)(digest + 8),
         *(uint32_t *)(digest + 12));

  encrypt((uint32_t *)flag4, tea_key);
  encrypt((uint32_t *)(flag4 + 8), tea_key);
  encrypt((uint32_t *)(flag4 + 0x10), tea_key);

  printf("Flag part 4: 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
         *(uint32_t *)flag4, *(uint32_t *)(flag4 + 4), *(uint32_t *)(flag4 + 8),
         *(uint32_t *)(flag4 + 12), *(uint32_t *)(flag4 + 16),
         *(uint32_t *)(flag4 + 20));

  return 0;
}