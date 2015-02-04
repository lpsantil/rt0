/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#define __SYSCALL_OUTPUT_REG__            "=a" ( ret )

#ifdef __LP64__
   #define __SYSCALL_OPCODE__                "syscall"

   #define __SYSCALL_PREAMBLE__()                    \
      register long r10 __asm__( "r10" ) = a3,       \
                    r08	__asm__( "r8" )  = a4,       \
                    r09 __asm__( "r9" )  = a5

   #define __SYSCALL_INPUT_REGS__                    \
      "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ), \
      "r" ( r08 ), "r" ( r09 ), "r" ( r10 )

   #define __SYSCALL_CLOBBERS__ "rcx", "r11", "memory"

#else
   #define __SYSCALL_OPCODE__              "int $0x80"

   #define __SYSCALL_PREAMBLE__()                    \
      register long ebp __asm__( "ebp" )  = a5

   #define __SYSCALL_INPUT_REGS__                    \
      "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 ), \
      "S" ( a3 ), "D" ( a4 ), "r" ( ebp )

   #define __SYSCALL_CLOBBERS__               "memory"

#endif

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 )
{
   unsigned long ret;
   __SYSCALL_PREAMBLE__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS__
                     : __SYSCALL_CLOBBERS__ );

   return( ret );
}

