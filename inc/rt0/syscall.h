/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#ifndef __RT0_SYSCALL__
#define __RT0_SYSCALL__

#include <sys/syscall.h>

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 );
long inline syscall5( long n, long a0, long a1, long a2, long a3, long a4 );
long inline syscall4( long n, long a0, long a1, long a2, long a3 );
long inline syscall3( long n, long a0, long a1, long a2 );
long inline syscall2( long n, long a0, long a1 );
long inline syscall1( long n, long a0 );
long inline syscall0( long n );

#endif
