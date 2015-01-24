/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#ifdef __LP64__
   #define __STARTUP_ASM__                                           \
                     "movq	%rsp,	%rbp\n\t"                    \
                     "movq	(0)(%rsp),	%rdi\n\t"            \
                     "movq      (8)(%rsp),	%rsi\n\t"            \
                     "andq	$-16,	%rsp\n\t"
#else
   #define __STARTUP_ASM__
#endif

/* pointer to array of char* strings that define the current environment variables */
char **__environ;
int errno;

void _start( int argc, char* stack )
{
   __asm__ volatile( __STARTUP_ASM__
                     "call	__init" );
}
