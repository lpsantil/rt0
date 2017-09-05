/*
 * Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */
#include <rt0/syscall.h>

int write( int f, const char* d, int l )
{
   int ret = syscall3( SYS_write, f, ( long )( d ), l );

   return( ret );
}

int str_len( const char *string )
{
   int length = 0;
   while( *string ) { string++; length++; }
   return length;
}

void print( const char* string )
{
   write( 1, string, str_len( string ) );
}

int main( int argc, char** argv, char** envp )
{
   int i;

   print( "-- Command line --\n" );
   for( i = 0; i < argc; ++i )
   {
      print( argv[ i ] );
      print( " " );
   }
   print( "\n" );

   return( 0 );
}
