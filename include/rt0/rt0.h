/* Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#ifndef __RT0__
#define __RT0__

extern char **__environ; /* pointer to array of char * strings that define the current environment variables */
extern int errno;
extern char _end, _edata, _etext, __executable_start;

void _exit( int r ) __attribute__((noreturn));
/*
int close( int file );
int execve( char* name, char** argv, char** env );
int fork();
int fstat( int file, struct stat* st );
int getpid();
int isatty( int file );
int kill( int pid, int sig );
int link( char* src, char* dest );
int lseek( int file, int ptr, int dir );
int open( const char* name, int flags, ... );
int read( int file, char* ptr, int len );
caddr_t sbrk( int incr );
int stat( const char *file, struct stat *st );
clock_t times( struct tms *buf );
int unlink( char* name );
int wait( int* status );
int write( int file, char* ptr, int len );
int gettimeofday( struct timeval* p, struct timezone* z );
*/

#endif
