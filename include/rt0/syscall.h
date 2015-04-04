/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#ifndef __RT0_SYSCALL__
#define __RT0_SYSCALL__

#ifdef __LP64__
   #include <rt0/sys64.h>
#else
   #include <rt0/sys32.h>
#endif

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 );

#ifndef __RT0_WITH_FASTER_SYSCALL__

#define syscall5( m, b0, b1, b2, b3, b4 )                            \
   syscall6( ( m ), ( b0 ), ( b1 ), ( b2 ), ( b3 ), ( b4 ), 0 )
#define syscall4( m, b0, b1, b2, b3 )                                \
   syscall5( ( m ), ( b0 ), ( b1 ), ( b2 ), ( b3 ), 0 )
#define syscall3( m, b0, b1, b2 )                                    \
   syscall4( ( m ), ( b0 ), ( b1 ), ( b2 ), 0 )
#define syscall2( m, b0, b1 )                                        \
   syscall3( ( m ), ( b0 ), ( b1 ), 0 )
#define syscall1( m, b0 )                                            \
   syscall2( ( m ), ( b0 ), 0 )
#define syscall0( m )                                                \
   syscall1( ( m ), 0 )

#else

long syscall5( long n, long a0, long a1, long a2, long a3, long a4 );
long syscall4( long n, long a0, long a1, long a2, long a3 );
long syscall3( long n, long a0, long a1, long a2 );
long syscall2( long n, long a0, long a1 );
long syscall1( long n, long a0 );
long syscall0( long n );

#endif

#endif
