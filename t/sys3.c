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

int main( int argc, char** argv, char** envp )
{
   int f;
   char* fn = "f.tmp";

   print( "creat'ing f.tmp\n" );
   f = syscall2( SYS_creat, ( long )( fn ), 0644 );
   if( 0 > f )
   {
      print( "\tSYS_creat failed\n" );
      return( -1 );
   }

   syscall3( SYS_write, f, ( long )( fn ), str_len( fn ) );
   print( "Did a write to f.tmp\n" );

   syscall1( SYS_close, f );
   print( "close'd f.tmp\n" );

   return( 0 );
}

