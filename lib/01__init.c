/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#include <rt0/rt0.h>

void __init( int argc, char *stack )
{
   char **argv = &stack;
   char **envp = __environ = argv + ( 1 * sizeof( void* ) );
   int retcode = main( argc, argv, envp );
   _exit( retcode );
}
