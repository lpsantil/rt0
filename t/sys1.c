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
   return( length );
}

void print( const char* string )
{
   write( 1, string, str_len( string ) );
}

void printInt( int i )
{
   char* nums = "0123456789";
   int d = 1,
       r;

   if( i < 0 )
   {
      print( "-" );

      printInt( -i );

      return;
   }

   d = i / 10;
   r = i % 10;

   if( d != 0 )
   {
     printInt( d );
   }

   write( 1, &( nums[ r ] ), 1 );
}

int main( int argc, char** argv, char** envp )
{
   int new_stdout = -1;

   print( "dup'ing fd 1\n" );
   new_stdout = syscall1( SYS_dup, 1 );
   if( new_stdout < 0 )
   {
      print( "\tSYS_dup failed\n" );
      return( -1 );
   }

   write( new_stdout,
          "new_stdout=",
          str_len( "new_stdout=" ) );

   printInt( new_stdout );

   write( new_stdout,
          "\n",
          str_len( "\n" ) );

   return( 0 );
}

