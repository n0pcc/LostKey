#define _GNU_SOURCE
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "openssl/aes.h"
#include "openssl/md5.h"

#include "rop.h"

static void create() __attribute__((constructor));
static void destroy() __attribute__((destructor));

int flag_0(void *);
int flag_1(void *);
int flag_2(void *);
int flag_3(void *);

struct clone_args {
  unsigned char *decoy_key;
  char *argv;
};

static char flag[100] = {0};
// Final key: {0xC2E1FAFF, 0xFFFAE1C2, 0xFFFAE1C2, 0xC2E1FAFF}
uint32_t tea_key[4] = {0};

static unsigned char decoy_keys[4][16] = {
    {'\xBF', '\xE3', '\x80', '\x6E', '\x8C', '\xB7', '\x0A', '\x4E', '\x6E',
     '\x96', '\x00', '\x63', '\x88', '\x00', '\x09', '\x9E'},
    {'\xC7', '\x7F', '\x3A', '\x98', '\xB1', '\xD3', '\x12', '\xC0', '\x14',
     '\x5E', '\x29', '\xEE', '\x42', '\x76', '\xE8', '\x27'},
    {'\xA7', '\x2B', '\x91', '\x7D', '\x05', '\xB8', '\xBC', '\x4B', '\x6A',
     '\xA9', '\x02', '\x4F', '\x13', '\xF2', '\xBB', '\x9D'},
    {'\xAD', '\x6E', '\xFB', '\xE2', '\x4C', '\x2E', '\x26', '\xD9', '\x7A',
     '\x6B', '\x68', '\xB2', '\x37', '\xC7', '\xA7', '\x35'}};

static void *stack = NULL;
static size_t stack_size = 1024 * 1024;

static uintptr_t flag_funcs[] = {(uintptr_t)flag_0, (uintptr_t)flag_1,
                                 (uintptr_t)flag_2, (uintptr_t)flag_3};

int main(int argc, char *argv[]) {
  if (argc != 5 || stack == NULL) {
    return -1;
  }

  printf("Speak, flag, and get your key's location.\n");

  for (int i = 0; i < 4; i++) {
    struct clone_args *args = malloc(sizeof(struct clone_args));
    args->decoy_key = decoy_keys[i];
    args->argv = argv[i + 1];

    pid_t pid = clone((int (*)(void *))flag_funcs[i],
                      stack + stack_size - (i + 1) * 0x1000, CLONE_VM | SIGCHLD,
                      (void *)args);

    if (waitpid(pid, NULL, 0) == -1) {
      return -1;
    }

    free(args);
  }

  printf("Did you speak flag?\n%s\n", flag);

  return 0;
}

int flag_0(void *key) {
  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == 0) {
    tea_key[0] = 0x466C7578;
    tea_key[1] = 0x78756C46;
    tea_key[2] = 0x78756C46;
    tea_key[3] = 0x466C7578;
  }

  *(uintptr_t *)(&key - 1) = (uintptr_t)rop_get_arg;

  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
    tea_key[0] ^= 0x6861636B;
    tea_key[1] ^= 0x6B636168;
    tea_key[2] ^= 0x6B636168;
    tea_key[3] ^= 0x6861636B;
  }

  static const unsigned char cipher[80] = {
      '\x35', '\x6F', '\x21', '\xDE', '\xF7', '\xBD', '\x78', '\xFE', '\x6D',
      '\xB1', '\x3C', '\xC6', '\xBC', '\x49', '\x9C', '\xA9', '\x14', '\x44',
      '\x5C', '\xAC', '\x2B', '\xFD', '\xB9', '\x56', '\x7E', '\x62', '\xB1',
      '\x59', '\x6B', '\x7B', '\xFE', '\x75', '\xA1', '\x29', '\x31', '\xBC',
      '\x8F', '\x46', '\x51', '\x73', '\x52', '\x3A', '\xA0', '\xAC', '\x94',
      '\x7C', '\x9E', '\xC2', '\x03', '\xE0', '\xE4', '\xA4', '\x23', '\x11',
      '\x39', '\x10', '\x70', '\xC6', '\x96', '\x22', '\x99', '\xC5', '\x7A',
      '\x53', '\xEF', '\xC1', '\xD9', '\x0E', '\x01', '\x8C', '\x1F', '\x18',
      '\xB1', '\x70', '\x95', '\x80', '\xD5', '\x9E', '\xC4', '\xCC'};

  if (key == NULL || ((struct clone_args *)key)->decoy_key == NULL ||
      ((struct clone_args *)key)->argv == NULL) {
    return -1;
  }

  AES_KEY dec_key;
  unsigned char plain[17] = {0};

  if (AES_set_decrypt_key(((struct clone_args *)key)->decoy_key, 128,
                          &dec_key) != 0) {
    return -1;
  }

  for (int i = 0; i < 5; i++) {
    AES_decrypt(cipher + 16 * i, plain, &dec_key);
    printf("%s", plain);
  }

  printf("\n");

  return 0;
}

int flag_1(void *key) {
  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == 0) {
    tea_key[0] ^= 0xFFFFFFFF;
    tea_key[1] ^= 0xFFFFFFFF;
    tea_key[2] ^= 0xFFFFFFFF;
    tea_key[3] ^= 0xFFFFFFFF;
  }

  *(uintptr_t *)(&key - 1) = (uintptr_t)rop_get_arg;

  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
    tea_key[0] ^= 0x01010101;
    tea_key[1] ^= 0x01010101;
    tea_key[2] ^= 0x01010101;
    tea_key[3] ^= 0x01010101;
  }

  static const unsigned char cipher[80] = {
      '\x6B', '\xB1', '\x28', '\x40', '\x27', '\xD6', '\xF1', '\x4D', '\x61',
      '\x5E', '\x09', '\x72', '\xED', '\xDF', '\x01', '\xBF', '\x2E', '\x88',
      '\xEF', '\x43', '\xF8', '\xDD', '\x79', '\xAF', '\xBE', '\x1A', '\x00',
      '\x1B', '\xC6', '\x41', '\x14', '\x2A', '\xBC', '\x00', '\xBE', '\x7C',
      '\xA7', '\xAB', '\xF1', '\x27', '\xDA', '\xE6', '\xAC', '\xAC', '\xAE',
      '\xC8', '\x72', '\x04', '\x79', '\x39', '\x07', '\x61', '\x53', '\x36',
      '\x03', '\x33', '\xEA', '\x41', '\xD1', '\x77', '\xCD', '\x59', '\x7C',
      '\xC8', '\xC6', '\xB9', '\xD9', '\x05', '\xCE', '\x89', '\x56', '\x59',
      '\x8E', '\x98', '\x3B', '\x19', '\x22', '\x10', '\x10', '\x59'};

  if (key == NULL || ((struct clone_args *)key)->decoy_key == NULL ||
      ((struct clone_args *)key)->argv == NULL) {
    return -1;
  }

  AES_KEY dec_key;
  unsigned char plain[17] = {0};

  if (AES_set_decrypt_key(((struct clone_args *)key)->decoy_key, 128,
                          &dec_key) != 0) {
    return -1;
  }

  for (int i = 0; i < 5; i++) {
    AES_decrypt(cipher + 16 * i, plain, &dec_key);
    printf("%s", plain);
  }

  printf("\n");

  return 0;
}

int flag_2(void *key) {
  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == 0) {
    tea_key[0] ^= 0x10101010;
    tea_key[1] ^= 0x10101010;
    tea_key[2] ^= 0x10101010;
    tea_key[3] ^= 0x10101010;
  }

  *(uintptr_t *)(&key - 1) = (uintptr_t)rop_get_arg;

  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
    tea_key[0] ^= 0x02020202;
    tea_key[1] ^= 0x02020202;
    tea_key[2] ^= 0x02020202;
    tea_key[3] ^= 0x02020202;
  }

  static const unsigned char cipher[80] = {
      '\x51', '\x54', '\x7C', '\x65', '\xEC', '\x8B', '\x27', '\xFF', '\xD7',
      '\x4F', '\xDA', '\xA2', '\xD1', '\x91', '\x63', '\x8A', '\x45', '\x78',
      '\xE8', '\x44', '\xC4', '\xA8', '\x18', '\x5D', '\x91', '\x4F', '\xCD',
      '\xFF', '\xE0', '\x5B', '\x4B', '\x81', '\x59', '\x00', '\xFB', '\x69',
      '\x72', '\xD2', '\xAB', '\x72', '\xF7', '\xA8', '\x9F', '\x40', '\x21',
      '\x9C', '\xC4', '\x8F', '\x54', '\x89', '\xAB', '\x4D', '\xBA', '\x9B',
      '\x3B', '\x8A', '\x33', '\x61', '\xDB', '\xD3', '\x8D', '\x23', '\x14',
      '\xCF', '\xAE', '\xD0', '\x6B', '\x26', '\x2D', '\x8E', '\x73', '\xC4',
      '\xFF', '\x6C', '\xAA', '\x18', '\x53', '\x0E', '\x85', '\x38'};

  if (key == NULL || ((struct clone_args *)key)->decoy_key == NULL ||
      ((struct clone_args *)key)->argv == NULL) {
    return -1;
  }

  AES_KEY dec_key;
  unsigned char plain[17] = {0};

  if (AES_set_decrypt_key(((struct clone_args *)key)->decoy_key, 128,
                          &dec_key) != 0) {
    return -1;
  }

  for (int i = 0; i < 5; i++) {
    AES_decrypt(cipher + 16 * i, plain, &dec_key);
    printf("%s", plain);
  }

  printf("\n");

  return 0;
}

uint32_t tmp[4];

int flag_3(void *key) {
  *(uintptr_t *)(&key - 1) = (uintptr_t)rop_get_arg;

  static const unsigned char cipher[80] = {
      '\xF9', '\x19', '\x1F', '\x45', '\x8D', '\xCB', '\x5F', '\x8C', '\x01',
      '\x0A', '\x8B', '\x76', '\xFD', '\xD6', '\x2E', '\x2D', '\x47', '\x4D',
      '\xA0', '\x7F', '\x48', '\x52', '\xF7', '\xD2', '\x3C', '\x07', '\xB0',
      '\xC7', '\x72', '\x5B', '\xA5', '\x72', '\xA7', '\xC2', '\x0C', '\x77',
      '\xA1', '\x79', '\xC2', '\x10', '\x42', '\xE1', '\x45', '\x0A', '\xFD',
      '\xAD', '\x10', '\xF7', '\x8F', '\x56', '\x8E', '\x85', '\xC1', '\x7F',
      '\x89', '\x3A', '\x8E', '\x85', '\x4F', '\xE2', '\x2E', '\x8B', '\xD0',
      '\x01', '\xCB', '\x0C', '\x13', '\x46', '\xBF', '\x1C', '\x01', '\x9B',
      '\x2C', '\x7F', '\x48', '\x99', '\xA7', '\xEA', '\x56', '\xB4'};

  if (key == NULL || ((struct clone_args *)key)->decoy_key == NULL ||
      ((struct clone_args *)key)->argv == NULL) {
    return -1;
  }

  AES_KEY dec_key;
  unsigned char plain[17] = {0};

  if (AES_set_decrypt_key(((struct clone_args *)key)->decoy_key, 128,
                          &dec_key) != 0) {
    return -1;
  }

  for (int i = 0; i < 5; i++) {
    AES_decrypt(cipher + 16 * i, plain, &dec_key);
    printf("%s", plain);
  }

  printf("\n");

  return 0;
}

__attribute__((constructor)) void create() {
  if (stack != NULL) {
    return;
  }

  stack = calloc(stack_size, 1);

  if (stack == NULL) {
    return;
  }

  uintptr_t *stack_flag_0 = (stack + stack_size - 0x1000 - 0x0C);

  stack_flag_0[0] = 0;
  stack_flag_0[1] = 1;
  stack_flag_0[2] = 2;
  stack_flag_0[3] = 3;
  stack_flag_0[4] = 4;
  stack_flag_0[5] = (uintptr_t)rop_flag_0_0;
  stack_flag_0[6] = (uintptr_t)rop_exit;
  stack_flag_0[7] = (uintptr_t)rop_flag_0_1;
  stack_flag_0[8] = 0x466C7578;
  stack_flag_0[9] = 0x78756C46;
  stack_flag_0[10] = 0x466C7578;
  stack_flag_0[11] = 0x210D191E;
  stack_flag_0[12] = 0;
  stack_flag_0[13] = 1;
  stack_flag_0[14] = 2;
  stack_flag_0[15] = 3;
  stack_flag_0[16] = 4;
  stack_flag_0[17] = (uintptr_t)rop_flag_0_2;
  stack_flag_0[18] = (uintptr_t)rop_exit;
  stack_flag_0[19] = 0x78756C46;
  stack_flag_0[20] = 0x4B1D383D;
  stack_flag_0[21] = 4;
  stack_flag_0[22] = 8;
  stack_flag_0[23] = 3;
  stack_flag_0[24] = 0;
  stack_flag_0[25] = 7;
  stack_flag_0[26] = (uintptr_t)rop_exit;
  stack_flag_0[27] = (uintptr_t)strlen;
  stack_flag_0[28] = (uintptr_t)rop_copy_correct_flag;
  stack_flag_0[29] = (uintptr_t)flag;
  stack_flag_0[30] = 100;
  stack_flag_0[31] = (uintptr_t)strncpy;
  stack_flag_0[32] = (uintptr_t)rop_exit;
  stack_flag_0[33] = (uintptr_t)flag;
  // &"flag{Th3" (argv)
  // sizeof(flag) - strlen(flag)

  uintptr_t *stack_flag_1 = (stack + stack_size - 0x2000 - 0x0C);

  stack_flag_1[0] = 0;
  stack_flag_1[1] = 0x1C;
  stack_flag_1[2] = 0xFFFFFFFC;
  stack_flag_1[3] = 3;
  stack_flag_1[4] = 4;
  stack_flag_1[5] = (uintptr_t)rop_flag_1_0;
  stack_flag_1[6] = (uintptr_t)rop_exit;
  stack_flag_1[7] = (uintptr_t)strcpy;
  stack_flag_1[8] = (uintptr_t)rop_flag_1_1;
  // &(stack_flag_1[400])
  // &"_key_1s_in_th3_secret_com" (argv)
  stack_flag_1[11] = (uintptr_t)strlen;
  stack_flag_1[12] = (uintptr_t)rop_flag_1_2;
  // &"_key_1s_in_th3_secret_com" (argv)
  stack_flag_1[14] = (uintptr_t)rop_flag_1_3;
  stack_flag_1[15] = 0xFFFFFFFC;
  stack_flag_1[16] = (uintptr_t)rop_flag_1_4;
  stack_flag_1[17] = 8;
  stack_flag_1[18] = (uintptr_t)rop_flag_1_5;
  stack_flag_1[19] = 0x41;
  stack_flag_1[20] = (uintptr_t)rop_flag_1_6;
  stack_flag_1[21] = (uintptr_t)rop_flag_1_7;
  stack_flag_1[22] = (uintptr_t)rop_flag_1_8;
  stack_flag_1[23] = (uintptr_t)rop_flag_1_9;
  stack_flag_1[24] = (uintptr_t)rop_flag_1_10;
  stack_flag_1[25] = (uintptr_t)rop_flag_1_11;
  stack_flag_1[26] = (uintptr_t)rop_flag_1_12;
  stack_flag_1[27] = (uintptr_t)rop_flag_1_13;
  stack_flag_1[28] = (uintptr_t)rop_flag_1_14;
  stack_flag_1[29] = (uintptr_t)rop_flag_2_2;
  stack_flag_1[30] = 4;
  stack_flag_1[31] = 8;
  stack_flag_1[32] = 3;
  stack_flag_1[33] = 0;
  stack_flag_1[34] = 7;
  stack_flag_1[35] = (uintptr_t)rop_exit;
  stack_flag_1[36] = (uintptr_t)strlen;
  stack_flag_1[37] = (uintptr_t)rop_copy_correct_flag;
  stack_flag_1[38] = (uintptr_t)flag;
  stack_flag_1[39] = 100;
  stack_flag_1[40] = (uintptr_t)strncpy;
  stack_flag_1[41] = (uintptr_t)rop_exit;
  stack_flag_1[42] = (uintptr_t)flag;

  stack_flag_1[500] = 0x37D02C61;
  stack_flag_1[501] = 0x63979F3B;
  stack_flag_1[502] = 0xD07E4607;
  stack_flag_1[503] = 0xAD79934A;
  stack_flag_1[504] = 0xDDBDBBCA;
  stack_flag_1[505] = 0x64A669E7;
  stack_flag_1[506] = 0x68;

  uintptr_t *stack_flag_2 = (stack + stack_size - 0x3000 - 0x0C);

  stack_flag_2[0] = 0;
  stack_flag_2[1] = 1;
  stack_flag_2[2] = 2;
  stack_flag_2[3] = 3;
  stack_flag_2[4] = 4;
  stack_flag_2[5] = (uintptr_t)rop_flag_2_0;
  stack_flag_2[6] = (uintptr_t)rop_exit;
  stack_flag_2[7] = (uintptr_t)MD5;
  stack_flag_2[8] = (uintptr_t)rop_flag_2_1;
  // &"p4rtme" (argv)
  stack_flag_2[10] = 6;
  // &md5_result
  stack_flag_2[12] = 0xF46F4D7B;
  stack_flag_2[13] = 0x3F6CC46A;
  stack_flag_2[14] = 0x93CC8A62;
  stack_flag_2[15] = 0x817D930D;
  stack_flag_2[16] = (uintptr_t)rop_flag_2_2;
  stack_flag_2[17] = 0x757960e1;
  stack_flag_2[18] = 0x17733c32;
  stack_flag_2[19] = 0x1ed9caff;
  stack_flag_2[20] = 0xbc6a393e;
  stack_flag_2[21] = 4;
  stack_flag_2[22] = 8;
  stack_flag_2[23] = 3;
  stack_flag_2[24] = 0;
  stack_flag_2[25] = 7;
  stack_flag_2[26] = (uintptr_t)rop_exit;
  stack_flag_2[27] = (uintptr_t)strlen;
  stack_flag_2[28] = (uintptr_t)rop_copy_correct_flag;
  stack_flag_2[29] = (uintptr_t)flag;
  stack_flag_2[30] = 100;
  stack_flag_2[31] = (uintptr_t)strncpy;
  stack_flag_2[32] = (uintptr_t)rop_exit;
  stack_flag_2[33] = (uintptr_t)flag;

  uintptr_t *stack_flag_3 = (stack + stack_size - 0x4000 - 0x0C);

  stack_flag_3[0] = 0;
  stack_flag_3[1] = 1;
  stack_flag_3[2] = 2;
  stack_flag_3[3] = 3;
  stack_flag_3[4] = 4;
  stack_flag_3[5] = (uintptr_t)rop_flag_3_tea_init_0;
  stack_flag_3[6] = (uintptr_t)rop_exit;
  stack_flag_3[7] = (uintptr_t)(flag + 49);
  stack_flag_3[8] = 0;
  stack_flag_3[9] = (uintptr_t)rop_flag_3_tea_add_delta_to_sum;
  stack_flag_3[10] = 0x9e3779b8;
  stack_flag_3[11] = (uintptr_t)rop_flag_3_tea_v1_shl;
  stack_flag_3[12] = (uintptr_t)rop_flag_3_tea_add_k0;
  stack_flag_3[13] = (uintptr_t) & (tea_key[0]);
  stack_flag_3[14] = (uintptr_t)rop_flag_3_tea_add_sum;
  stack_flag_3[15] = (uintptr_t)rop_flag_3_tea_1st_xor;
  stack_flag_3[16] = (uintptr_t)rop_flag_3_tea_v1_shr;
  stack_flag_3[17] = (uintptr_t)rop_flag_3_tea_add_k1_or_k3;
  stack_flag_3[18] = (uintptr_t) & (tea_key[1]);
  stack_flag_3[19] = (uintptr_t)rop_flag_3_tea_2nd_and_4th_xor;
  stack_flag_3[20] = (uintptr_t)rop_flag_3_tea_add_to_v0;
  stack_flag_3[21] = (uintptr_t)rop_flag_3_tea_v1_shl;
  stack_flag_3[22] = (uintptr_t)rop_flag_3_tea_add_k2;
  stack_flag_3[23] = (uintptr_t) & (tea_key[2]);
  stack_flag_3[24] = (uintptr_t)rop_flag_3_tea_add_sum;
  stack_flag_3[25] = (uintptr_t)rop_flag_3_tea_3rd_xor;
  stack_flag_3[26] = (uintptr_t)rop_flag_3_tea_v1_shr;
  stack_flag_3[27] = (uintptr_t)rop_flag_3_tea_add_k1_or_k3;
  stack_flag_3[28] = (uintptr_t) & (tea_key[3]);
  stack_flag_3[29] = (uintptr_t)rop_flag_3_tea_2nd_and_4th_xor;
  stack_flag_3[30] = (uintptr_t)rop_flag_3_tea_add_to_v1;
  stack_flag_3[31] = (uintptr_t)rop_flag_3_tea_loop_tail;
  stack_flag_3[32] = (uintptr_t)(flag + 49);
  stack_flag_3[33] = 31;
  stack_flag_3[34] = 0x6C;
  stack_flag_3[35] = 0;
  stack_flag_3[36] = (uintptr_t)rop_flag_3_check_tea;
  stack_flag_3[37] = 0xA42D6EBF;
  stack_flag_3[38] = 0x0EFE89E7;

  stack_flag_3[39] = (uintptr_t)rop_exit;
  stack_flag_3[40] = (uintptr_t)rop_flag_3_tea_init_1;
  stack_flag_3[41] = (uintptr_t)(flag + 49);
  stack_flag_3[42] = (uintptr_t)rop_flag_3_tea_add_delta_to_sum;
  stack_flag_3[43] = 0x9e3779b8;
  stack_flag_3[44] = (uintptr_t)rop_flag_3_tea_v1_shl;
  stack_flag_3[45] = (uintptr_t)rop_flag_3_tea_add_k0;
  stack_flag_3[46] = (uintptr_t) & (tea_key[0]);
  stack_flag_3[47] = (uintptr_t)rop_flag_3_tea_add_sum;
  stack_flag_3[48] = (uintptr_t)rop_flag_3_tea_1st_xor;
  stack_flag_3[49] = (uintptr_t)rop_flag_3_tea_v1_shr;
  stack_flag_3[50] = (uintptr_t)rop_flag_3_tea_add_k1_or_k3;
  stack_flag_3[51] = (uintptr_t) & (tea_key[1]);
  stack_flag_3[52] = (uintptr_t)rop_flag_3_tea_2nd_and_4th_xor;
  stack_flag_3[53] = (uintptr_t)rop_flag_3_tea_add_to_v0;
  stack_flag_3[54] = (uintptr_t)rop_flag_3_tea_v1_shl;
  stack_flag_3[55] = (uintptr_t)rop_flag_3_tea_add_k2;
  stack_flag_3[56] = (uintptr_t) & (tea_key[2]);
  stack_flag_3[57] = (uintptr_t)rop_flag_3_tea_add_sum;
  stack_flag_3[58] = (uintptr_t)rop_flag_3_tea_3rd_xor;
  stack_flag_3[59] = (uintptr_t)rop_flag_3_tea_v1_shr;
  stack_flag_3[60] = (uintptr_t)rop_flag_3_tea_add_k1_or_k3;
  stack_flag_3[61] = (uintptr_t) & (tea_key[3]);
  stack_flag_3[62] = (uintptr_t)rop_flag_3_tea_2nd_and_4th_xor;
  stack_flag_3[63] = (uintptr_t)rop_flag_3_tea_add_to_v1;
  stack_flag_3[64] = (uintptr_t)rop_flag_3_tea_loop_tail;
  stack_flag_3[65] = (uintptr_t)(flag + 49);
  stack_flag_3[66] = 31;
  stack_flag_3[67] = 0x6C;
  stack_flag_3[68] = 0;
  stack_flag_3[69] = (uintptr_t)rop_flag_3_check_tea;
  stack_flag_3[70] = 0xAADD934D;
  stack_flag_3[71] = 0x4E4E7F13;

  stack_flag_3[72] = (uintptr_t)rop_exit;
  stack_flag_3[73] = (uintptr_t)rop_flag_3_tea_init_2;
  stack_flag_3[74] = (uintptr_t)(flag + 49);
  stack_flag_3[75] = (uintptr_t)rop_flag_3_tea_add_delta_to_sum;
  stack_flag_3[76] = 0x9e3779b8;
  stack_flag_3[77] = (uintptr_t)rop_flag_3_tea_v1_shl;
  stack_flag_3[78] = (uintptr_t)rop_flag_3_tea_add_k0;
  stack_flag_3[79] = (uintptr_t) & (tea_key[0]);
  stack_flag_3[80] = (uintptr_t)rop_flag_3_tea_add_sum;
  stack_flag_3[81] = (uintptr_t)rop_flag_3_tea_1st_xor;
  stack_flag_3[82] = (uintptr_t)rop_flag_3_tea_v1_shr;
  stack_flag_3[83] = (uintptr_t)rop_flag_3_tea_add_k1_or_k3;
  stack_flag_3[84] = (uintptr_t) & (tea_key[1]);
  stack_flag_3[85] = (uintptr_t)rop_flag_3_tea_2nd_and_4th_xor;
  stack_flag_3[86] = (uintptr_t)rop_flag_3_tea_add_to_v0;
  stack_flag_3[87] = (uintptr_t)rop_flag_3_tea_v1_shl;
  stack_flag_3[88] = (uintptr_t)rop_flag_3_tea_add_k2;
  stack_flag_3[89] = (uintptr_t) & (tea_key[2]);
  stack_flag_3[90] = (uintptr_t)rop_flag_3_tea_add_sum;
  stack_flag_3[91] = (uintptr_t)rop_flag_3_tea_3rd_xor;
  stack_flag_3[92] = (uintptr_t)rop_flag_3_tea_v1_shr;
  stack_flag_3[93] = (uintptr_t)rop_flag_3_tea_add_k1_or_k3;
  stack_flag_3[94] = (uintptr_t) & (tea_key[3]);
  stack_flag_3[95] = (uintptr_t)rop_flag_3_tea_2nd_and_4th_xor;
  stack_flag_3[96] = (uintptr_t)rop_flag_3_tea_add_to_v1;
  stack_flag_3[97] = (uintptr_t)rop_flag_3_tea_loop_tail;
  stack_flag_3[98] = (uintptr_t)(flag + 49);
  stack_flag_3[99] = 31;
  stack_flag_3[100] = 0x6C;
  stack_flag_3[101] = 0;
  stack_flag_3[102] = (uintptr_t)rop_flag_3_check_tea;
  stack_flag_3[103] = 0x8EC32CA9;
  stack_flag_3[104] = 0x8559D4E9;

  stack_flag_3[105] = (uintptr_t)rop_exit;
  stack_flag_3[106] = (uintptr_t)strlen;
  stack_flag_3[107] = (uintptr_t)rop_copy_correct_flag;
  stack_flag_3[108] = (uintptr_t)flag;
  stack_flag_3[109] = 100;
  stack_flag_3[110] = (uintptr_t)strncpy;
  stack_flag_3[111] = (uintptr_t)rop_exit;
  stack_flag_3[112] = (uintptr_t)flag;
}

__attribute__((destructor)) void destroy() {
  if (stack != NULL) {
    free(stack);
  }
}
