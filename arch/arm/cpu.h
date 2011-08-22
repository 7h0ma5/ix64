#ifndef IX_ARCH_CPU
#define IX_ARCH_CPU

typedef struct{
  unsigned usr_sp, usr_lr;
  unsigned cpsr, svc_spsr;
  unsigned svc_sp, svc_lr;

  unsigned r0, r1, r2, r3, r4, r5, r6, r7;
  unsigned r8, r9, r10, r11, r12, pc;
} __attribute__((packed)) cpu_state;

#endif
