/*
 * Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */
#include <rt0/syscall.h>

int main( int argc, char **argv, char **envp )
{
   syscall3( SYS_write, 1, ( long )( "Hello World!\n" ), 13 );

   return( 0 );
}
