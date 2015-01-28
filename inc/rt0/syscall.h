/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#ifndef __RT0_SYSCALL__
#define __RT0_SYSCALL__

#include <sys/syscall.h>

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 );
inline long syscall5( long n, long a0, long a1, long a2, long a3, long a4 );
inline long syscall4( long n, long a0, long a1, long a2, long a3 );
inline long syscall3( long n, long a0, long a1, long a2 );
inline long syscall2( long n, long a0, long a1 );
inline long syscall1( long n, long a0 );
inline long syscall0( long n );

#endif
