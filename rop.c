#include "rop.h"

__attribute__((naked)) void rop_exit() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov eax, 0x1\n"
      "call dword ptr gs:0x10");
}

__attribute__((naked)) void rop_get_arg() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ebp\n"
      "cmp eax, 0\n"
      "cmove ebp, [ebp+4]\n"
      "pop eax\n"
      "pop esi\n"
      "pop edi\n"
      "pop edx\n"
      "pop ebx\n"
      "cmovne eax, ebx\n"
      "add eax, esp\n"
      "xchg eax, esp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_0_0() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov eax, [ebp]\n"
      "pop edx\n"
      "retn 8");
}

__attribute__((naked)) void rop_flag_0_1() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ebx\n"
      "xor eax, ebx\n"
      "pop ebx\n"
      "cmp eax, ebx\n"
      "pop esi\n"
      "pop edi\n"
      "pop edx\n"
      "pop eax\n"
      "pop ebx\n"
      "cmovne esi, ebx\n"
      "add esi, esp\n"
      "xchg esi, esp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_0_2() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov eax, [ebp+4]\n"
      "pop esi\n"
      "pop ebx\n"
      "xor eax, ebx\n"
      "pop ebx\n"
      "cmp eax, ebx\n"
      "pop eax\n"
      "pop esi\n"
      "pop edi\n"
      "pop edx\n"
      "pop ebx\n"
      "cmove edx, eax\n"
      "add edx, esp\n"
      "xchg edx, esp\n"
      "ret");
}

__attribute__((naked)) void rop_copy_correct_flag() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ecx\n"
      "add ecx, eax\n"
      "mov [esp+0xC], ecx\n"
      "pop edx\n"
      "sub edx, eax\n"
      "mov [esp+0x10], edx\n"
      "mov [esp+0xC], ebp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_0() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop edx\n"
      "mov ecx, esp\n"
      "add ecx, 0x624\n"
      "mov [esp+8], ecx\n"
      "mov [esp+0xC], ebp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_1() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ebx\n"
      "pop ecx\n"
      "sub eax, ecx\n"
      "cmp eax, ebx\n"
      "cmovg eax, edx\n"
      "mov [esp+8], ebp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_2() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "cmp eax, 1\n"
      "cmovle edi, esi\n"
      "sub esp, edi\n"
      "retn 4");
}

__attribute__((naked)) void rop_flag_1_3() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "dec eax\n"
      "xor ebx, ebx\n"
      "mov esi, ebp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_4() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "movzx edx, byte ptr [esi]\n"
      "not edx\n"
      "movzx edx, dl\n"
      "mov ecx, edx\n"
      "shl edx, 4\n"
      "shr ecx, 4\n"
      "or edx, ecx\n"
      "mov [esi], dl\n"
      "movzx edx, byte ptr [esi+1]\n"
      "xor [esi], dl\n"
      "inc ebx\n"
      "pop edi\n"
      "xor edx, edx\n"
      "cmp ebx, eax\n"
      "cmovl edx, edi\n"
      "sub esp, edx\n"
      "inc esi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_5() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "movzx edx, byte ptr [esi]\n"
      "not edx\n"
      "movzx edx, dl\n"
      "mov ecx, edx\n"
      "shl edx, 4\n"
      "shr ecx, 4\n"
      "or edx, ecx\n"
      "mov [esi], dl\n"
      "pop edx\n"
      "xor [esi], dl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_6() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "xor ecx, ecx\n"
      "mov ebx, [ebp]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_7() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov ebx, [ebp+4]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_8() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov ebx, [ebp+8]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_9() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov ebx, [ebp+0xC]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_10() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov ebx, [ebp+0x10]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_11() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov ebx, [ebp+0x14]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_12() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "movzx ebx, byte ptr [ebp+0x18]\n"
      "cmp ebx, [esp+0x77C]\n"
      "setne cl\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_13() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "mov ebp, esp\n"
      "add ebp, 0x5D0\n"
      "ret");
}

__attribute__((naked)) void rop_flag_1_14() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "cmp ecx, 0\n"
      "ret");
}

__attribute__((naked)) void rop_flag_2_0() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop edx\n"
      "lea eax, [esp+0x250]\n"
      "mov [esp+8], ebp\n"
      "mov [esp+0x10], eax\n"
      "ret");
}

__attribute__((naked)) void rop_flag_2_1() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "add esp, 0xC\n"
      "xor edx, edx\n"
      "pop esi\n"
      "cmp esi, [esp+0x238]\n"
      "setne dl\n"
      "pop esi\n"
      "cmp esi, [esp+0x238]\n"
      "setne dl\n"
      "pop esi\n"
      "cmp esi, [esp+0x238]\n"
      "setne dl\n"
      "pop esi\n"
      "cmp esi, [esp+0x238]\n"
      "setne dl\n"
      "cmp edx, 0\n"
      "ret 0x10");
}

__attribute__((naked)) void rop_flag_2_2() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop eax\n"
      "pop esi\n"
      "pop edi\n"
      "pop edx\n"
      "pop ebx\n"
      "cmove edx, eax\n"
      "add edx, esp\n"
      "xchg edx, esp\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_init_0() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop edx\n"
      "xor eax, eax\n"
      "pop ecx\n"
      "mov byte ptr [ecx], al\n"
      "pop ebx\n"
      "mov edi, [ebp]\n"
      "mov esi, [ebp+4]\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_init_1() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "xor eax, eax\n"
      "pop ebx\n"
      "mov byte ptr [ebx], al\n"
      "xor ebx, ebx\n"
      "mov edi, [ebp+8]\n"
      "mov esi, [ebp+0xC]\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_init_2() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "xor eax, eax\n"
      "pop edx\n"
      "mov byte ptr [edx], al\n"
      "xor ebx, ebx\n"
      "mov edi, [ebp+0x10]\n"
      "mov esi, [ebp+0x14]\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_delta_to_sum() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ecx\n"
      "inc ecx\n"
      "add ebx, ecx\n"
      "mov ecx, esi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_v1_shl() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "shl ecx, 4\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_k0() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop eax\n"
      "mov eax, [eax]\n"
      "add ecx, eax\n"
      "mov edx, esi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_sum() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "add edx, ebx\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_1st_xor() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "xor ecx, edx\n"
      "mov edx, esi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_v1_shr() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "shr edx, 5\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_k1_or_k3() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop eax\n"
      "mov eax, [eax]\n"
      "add edx, eax\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_2nd_and_4th_xor() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "xor ecx, edx\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_to_v0() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "add edi, ecx\n"
      "mov ecx, edi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_k2() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop eax\n"
      "mov eax, [eax]\n"
      "add ecx, eax\n"
      "mov edx, edi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_3rd_xor() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "xor ecx, edx\n"
      "mov edx, edi\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_add_to_v1() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "add esi, ecx\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_tea_loop_tail() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ecx\n"
      "xor eax, eax\n"
      "mov al, byte ptr [ecx]\n"
      "inc eax\n"
      "mov byte ptr [ecx], al\n"
      "pop edx\n"
      "cmp eax, edx\n"
      "pop ecx\n"
      "pop edx\n"
      "cmovbe edx, ecx\n"
      "sub esp, edx\n"
      "ret");
}

__attribute__((naked)) void rop_flag_3_check_tea() {
  __asm__ volatile(
      ".intel_syntax noprefix\n"
      "pop ecx\n"
      "xor eax, eax\n"
      "cmp edi, ecx\n"
      "setne al\n"
      "pop ecx\n"
      "cmp esi, ecx\n"
      "setne al\n"
      "xor ebx, ebx\n"
      "inc ebx\n"
      "inc ebx\n"
      "inc ebx\n"
      "inc ebx\n"
      "xor ecx, ecx\n"
      "cmp eax, ecx\n"
      "cmove ecx, ebx\n"
      "add esp, ecx\n"
      "ret");
}
