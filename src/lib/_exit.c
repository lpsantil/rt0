/*
 * Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#include <rt0/syscall.h>

void _exit( int r )
{
   long ret = syscall1( SYS_exit, r );

   ret = ( 0 > ret ? errno = -ret, -1 : ret );

   ret = syscall3( SYS_write,
                   1,
                   ( long )( "SYS_exit failed.\n" ),
                   19 );
   for(;;);
}

