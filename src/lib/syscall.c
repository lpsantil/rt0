/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */
#include <rt0/rt0.h>

#ifdef __LP64__
   #include <rt0/sys64.h>
#else
   #include <rt0/sys32.h>
#endif

#define __SYSCALL_OUTPUT_REG__            "=a" ( ret )

#define __SYSCALL_CHK_ERROR__()                      \
   ret = ( 0 > ret ? errno = -ret, -1 : ret )

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
   long ret;
   __SYSCALL_PREAMBLE__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

#ifdef __RT0_WITH_FASTER_SYSCALL__

#ifdef __LP64__
   #define __SYSCALL_PREAMBLE5__()                    \
      register long r10 __asm__( "r10" ) = a3,        \
                    r08	__asm__( "r8" )  = a4
   #define __SYSCALL_PREAMBLE4__()                    \
      register long r10 __asm__( "r10" ) = a3
   #define __SYSCALL_PREAMBLE3__()
   #define __SYSCALL_PREAMBLE2__()
   #define __SYSCALL_PREAMBLE1__()
   #define __SYSCALL_PREAMBLE0__()

   #define __SYSCALL_INPUT_REGS5__                    \
      "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ),  \
      "r" ( r08 ), "r" ( r10 )
   #define __SYSCALL_INPUT_REGS4__                    \
      "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ),  \
      "r" ( r10 )
   #define __SYSCALL_INPUT_REGS3__                    \
      "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 )
   #define __SYSCALL_INPUT_REGS2__                    \
      "a" ( n ), "D" ( a0 ), "S" ( a1 )
   #define __SYSCALL_INPUT_REGS1__                    \
      "a" ( n ), "D" ( a0 )
   #define __SYSCALL_INPUT_REGS0__                    \
      "a" ( n )

#else
   #define __SYSCALL_PREAMBLE5__()
   #define __SYSCALL_PREAMBLE4__()
   #define __SYSCALL_PREAMBLE3__()
   #define __SYSCALL_PREAMBLE2__()
   #define __SYSCALL_PREAMBLE1__()
   #define __SYSCALL_PREAMBLE0__()

   #define __SYSCALL_INPUT_REGS5__                    \
      "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 ),  \
      "S" ( a3 ), "D" ( a4 )
   #define __SYSCALL_INPUT_REGS4__                    \
      "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 ),  \
      "S" ( a3 )
   #define __SYSCALL_INPUT_REGS3__                    \
      "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 )
   #define __SYSCALL_INPUT_REGS2__                    \
      "a" ( n ), "b" ( a0 ), "c" ( a1 )
   #define __SYSCALL_INPUT_REGS1__                    \
      "a" ( n ), "b" ( a0 )
   #define __SYSCALL_INPUT_REGS0__                    \
      "a" ( n )

#endif

long syscall5( long n, long a0, long a1, long a2, long a3, long a4 )
{
   long ret;
   __SYSCALL_PREAMBLE5__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS5__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

long syscall4( long n, long a0, long a1, long a2, long a3 )
{
   long ret;
   __SYSCALL_PREAMBLE4__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS4__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

long syscall3( long n, long a0, long a1, long a2 )
{
   long ret;
   __SYSCALL_PREAMBLE3__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS3__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

long syscall2( long n, long a0, long a1 )
{
   long ret;
   __SYSCALL_PREAMBLE2__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS2__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

long syscall1( long n, long a0 )
{
   long ret;
   __SYSCALL_PREAMBLE1__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS1__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

long syscall0( long n )
{
   long ret;
   __SYSCALL_PREAMBLE0__();

   __asm__ volatile( __SYSCALL_OPCODE__
                     : __SYSCALL_OUTPUT_REG__
                     : __SYSCALL_INPUT_REGS0__
                     : __SYSCALL_CLOBBERS__ );

   __SYSCALL_CHK_ERROR__();

   return( ret );
}

#endif
