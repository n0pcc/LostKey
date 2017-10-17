/*
 * gcc encrypt_decoy.c -lcrypto
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "openssl/aes.h"

int main() {
  AES_KEY enc_key;

  unsigned char plain[80] =
      "Oh my, there's nothing here... Move along, but don't fall off the "
      "edge!\0",
                keys[4][16], cipher[4][80];

  // Getting 4 random 128 bit keys.
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd == -1) {
    exit(-1);
  }

  for (int i = 0; i < 4; i++) {
    if (read(fd, keys[i], 16) != 16) {
      exit(-1);
    }
  }

  close(fd);

  // Encrypting the plain text with the 4 keys to 4 cipher texts.
  for (int i = 0; i < 4; i++) {
    AES_set_encrypt_key(keys[i], 128, &enc_key);

    for (int j = 0; j < 5; j++) {
      AES_encrypt(plain + 16 * j, cipher[i] + 16 * j, &enc_key);
    }
  }

  // PP the key for copy & paste to the challenge source.
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      printf("static unsigned char decoy_keys[4][16] = {{");
    } else {
      printf("                                          {");
    }

    for (int j = 0; j < 16; j++) {
      if (j == 15) {
        printf("'\\x%02X'", keys[i][j]);
      } else {
        printf("'\\x%02X', ", keys[i][j]);
      }
    }

    if (i == 3) {
      printf("}};\n");
    } else {
      printf("},\n");
    }
  }

  // PP the cipher texts.
  for (int i = 0; i < 4; i++) {
    printf("static const unsigned char cipher[80] = {");

    for (int j = 0; j < 80; j++) {
      if (j == 79) {
        printf("'\\x%02X'};\n", cipher[i][j]);
      } else {
        printf("'\\x%02X', ", cipher[i][j]);
      }
    }
  }

  return 0;
}