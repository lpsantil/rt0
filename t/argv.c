#include <rt0/syscall.h>

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
