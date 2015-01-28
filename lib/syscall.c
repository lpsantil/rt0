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

inline long syscall5( long n, long a0, long a1, long a2, long a3, long a4 )
{
   return( syscall6( n, a0, a1, a2, a3, a4, ( long )( 0 ) ) );
}

inline long syscall4( long n, long a0, long a1, long a2, long a3 )
{
   return( syscall5( n, a0, a1, a2, a3, ( long )( 0 ) ) );
}

inline long syscall3( long n, long a0, long a1, long a2 )
{
   return( syscall4( n, a0, a1, a2, ( long )( 0 ) ) );
}

inline long syscall2( long n, long a0, long a1 )
{
   return( syscall3( n, a0, a1, ( long )( 0 ) ) );
}

inline long syscall1( long n, long a0 )
{
   return( syscall2( n, a0, ( long )( 0 ) ) );
}

inline long syscall0( long n )
{
   return( syscall1( n, ( long )( 0 ) ) );
}

