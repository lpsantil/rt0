#include <rt0/syscall.h>

void print( const char* string )
{
   write( 1, string, str_len( string ) );
}

int write( int f, char* d, int l )
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

int main( int argc, char** argv, char** envp )
{
   int f;
   char* fn = "f.tmp";

   print( "creat'ing f.tmp\n" );
   f = syscall2( SYS_creat, ( long )( fn ), 0644 );
   if( 0 > f )
   {
      print( "\topen failed\n" );
      return( -1 );
   }

   syscall1( SYS_close, f );
   print( "close'd f.tmp\n" );

   return( 0 );
}

