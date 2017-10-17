#ifndef ROP_H_
#define ROP_H_

void rop_exit() __attribute__((naked));

void rop_get_arg() __attribute__((naked));

void rop_copy_correct_flag() __attribute__((naked));

void rop_flag_0_0() __attribute__((naked));
void rop_flag_0_1() __attribute__((naked));
void rop_flag_0_2() __attribute__((naked));

void rop_flag_1_0() __attribute__((naked));
void rop_flag_1_1() __attribute__((naked));
void rop_flag_1_2() __attribute__((naked));
void rop_flag_1_3() __attribute__((naked));
void rop_flag_1_4() __attribute__((naked));
void rop_flag_1_5() __attribute__((naked));
void rop_flag_1_6() __attribute__((naked));
void rop_flag_1_7() __attribute__((naked));
void rop_flag_1_8() __attribute__((naked));
void rop_flag_1_9() __attribute__((naked));
void rop_flag_1_10() __attribute__((naked));
void rop_flag_1_11() __attribute__((naked));
void rop_flag_1_12() __attribute__((naked));
void rop_flag_1_13() __attribute__((naked));
void rop_flag_1_14() __attribute__((naked));

void rop_flag_2_0() __attribute__((naked));
void rop_flag_2_1() __attribute__((naked));
void rop_flag_2_2() __attribute__((naked));

void rop_flag_3_tea_init_0() __attribute__((naked));
void rop_flag_3_tea_init_1() __attribute__((naked));
void rop_flag_3_tea_init_2() __attribute__((naked));
void rop_flag_3_tea_add_delta_to_sum() __attribute__((naked));
void rop_flag_3_tea_v1_shl() __attribute__((naked));
void rop_flag_3_tea_add_k0() __attribute__((naked));
void rop_flag_3_tea_add_sum() __attribute__((naked));
void rop_flag_3_tea_1st_xor() __attribute__((naked));
void rop_flag_3_tea_v1_shr() __attribute__((naked));
void rop_flag_3_tea_add_k1_or_k3() __attribute__((naked));
void rop_flag_3_tea_2nd_and_4th_xor() __attribute__((naked));
void rop_flag_3_tea_add_to_v0() __attribute__((naked));
void rop_flag_3_tea_add_k2() __attribute__((naked));
void rop_flag_3_tea_3rd_xor() __attribute__((naked));
void rop_flag_3_tea_add_to_v1() __attribute__((naked));
void rop_flag_3_tea_loop_tail() __attribute__((naked));
void rop_flag_3_check_tea() __attribute__((naked));

#endif  // ROP_H_
