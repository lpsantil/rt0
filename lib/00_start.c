/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#include <rt0/rt0.h>

#ifdef __LP64__
   #define __STARTUP_PREAMBLE__() register long rax __asm__( "rax" )

   /* Setup the base */
   /* argc = RDI = [ RSP ] */
   /* argv = RSI = [ RSP+8 ] */
   /* envp = RDX = [ argv+8*argc+8 ] */
   /* align the stack */
   #define __STARTUP_ASM__                                           \
                     "pop	%rbp\n\t"                            \
                     "mov	%rsp,	%rbp\n\t"                    \
                     "mov	(0)(%rbp),	%rdi\n\t"            \
                     "lea	(8)(%rbp),	%rsi\n\t"            \
                     "lea	(8)(%rsi,%rdi,8),	%rdx\n\t"    \
                     "and	$-16,	%rsp\n\t"

   #define __STARTUP_GETRETVAL__ "=a"( rax )

   #define __STARTUP_RETVAL__ rax
#else
   #define __STARTUP_PREAMBLE__() register long eax __asm__( "eax" )

   /* Setup the base */
   /* Fix GCC's 'helpful" 16-byte alignment */
   /* argc = ECX = [ ESP ] */
   /* argv = EDX = [ ESP+8 ] */
   /* envp = EAX = [ argv+8*argc+8 ] */
   /* align the stack */
   /* push args onto re-aligned stack */
   #define __STARTUP_ASM__                                           \
                     "mov	%esp,	%ebp\n\t"                    \
                     "add	$0x1c,	%ebp\n\t"                    \
                     "mov	(0)(%ebp),	%ecx\n\t"            \
                     "lea	(4)(%ebp),	%edx\n\t"            \
                     "lea	(4)(%edx,%ecx,4),	%eax\n\t"    \
                     "and	$-16,	%esp\n\t"                    \
                     "push	%eax\n\t"                            \
                     "push	%edx\n\t"                            \
                     "push	%ecx\n\t"

   #define __STARTUP_GETRETVAL__ "=a"( eax )

   #define __STARTUP_RETVAL__ eax
#endif

/* pointer to array of char* strings that define the current environment variables */
char **__environ;
int errno;

void _start( void ) __attribute__((noreturn));

void _start( void )
{
   __STARTUP_PREAMBLE__();

   __asm__ volatile( __STARTUP_ASM__
                     "call	main" );

   _exit( __STARTUP_RETVAL__ );

   for(;;);
}
