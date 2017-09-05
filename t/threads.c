/*
 * Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */
/*
 * Based on a full C/rt0 conversion of the blog post at
 * http://nullprogram.com/blog/2015/05/15/
 * and the repo at
 * https://github.com/skeeto/pure-linux-threads-demo
 */

#include <rt0/syscall.h>

int
write( int f, const char* d, int l )
{
   int ret = syscall3( SYS_write, f, ( long )( d ), l );

   return( ret );
}

int
str_len( const char *string )
{
   int length = 0;
   while( *string ) { string++; length++; }
   return length;
}

void
print( const char* string )
{
   write( 1, string, str_len( string ) );
}

#define DEFAULT_STACK_SIZE ( 4096 * 1024 )

#define MAP_GROWSDOWN	0x0100
#define MAP_ANONYMOUS	0x0020
#define MAP_PRIVATE	0x0002
#define PROT_READ	0x1
#define PROT_WRITE	0x2
#define PROT_EXEC	0x4

#define THREAD_PROT_FLAGS ( PROT_WRITE | PROT_READ | PROT_EXEC )
#define THREAD_MAP_FLAGS  ( MAP_ANONYMOUS | MAP_PRIVATE | MAP_GROWSDOWN )

#define size_t long

void*
mmap( void* addr, size_t length, int prot, int flags )
{
   return( ( void* )
           ( syscall4( SYS_mmap, ( long )( addr ), ( long )( length ),
                       ( long )( prot ), ( long )( flags ) ) ) );
}

void*
newThreadStack( void )
{
   return( mmap( 0,
                  DEFAULT_STACK_SIZE,
                  THREAD_PROT_FLAGS,
                  THREAD_MAP_FLAGS ) );
}

#define CLONE_VM	0x00000100
#define CLONE_FS	0x00000200
#define CLONE_FILES	0x00000400
#define CLONE_SIGHAND	0x00000800
#define CLONE_PARENT	0x00008000
#define CLONE_THREAD	0x00010000
#define CLONE_IO	0x80000000

#define NEW_THREAD_FLAGS \
   ( CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | \
     CLONE_PARENT | CLONE_THREAD | CLONE_IO )

long
clone( unsigned long flags, void* childStack )
{
   return( syscall2( SYS_clone, ( long )( flags ),
                     ( long )( childStack ) ) );
}

long
threadCreate( void ( *func )( void ) )
{
   void* newStack;
   newStack = newThreadStack();
   void* newSP = ( void* )( ( char* )newStack + DEFAULT_STACK_SIZE - 8 );
   *( long* )newSP = ( long )func;
   long ret = clone( NEW_THREAD_FLAGS, newSP );
   return( ret );
}

void
dummyThread( void )
{
   print( "\tChild Thread\n" );
   print( "\tDone.\n" );
   _exit( 0 );
}

int
main( int argc, char **argv, char **envp )
{
   threadCreate( dummyThread );
   threadCreate( dummyThread );
   for( int i = 0; i < 5; i++ )
   {
      print( "Parent Thread!\n");
   }

   return( 0 );
}
