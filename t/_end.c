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

void printLongHex( long i )
{
   char* nums = "0123456789ABCDEF";
   long d = 1,
        r;

   if( i < 0 )
   {
      print( "-" );

      printLongHex( -i );

      return;
   }

   d = i / 16;
   r = i % 16;

   if( d != 0 )
   {
     printLongHex( d );
   }

   write( 1, &( nums[ r ] ), 1 );
}

int main( int argc, char **argv, char **envp )
{
   long addr;

   addr = ( long )( &__executable_start );
   print( "Address of __executable_start: " );
   printLongHex( addr );
   print( "\n" );

   addr = ( long )( &_etext );
   print( "Address of _etext: " );
   printLongHex( addr );
   print( "\n" );

   addr = ( long )( &_edata );
   print( "Address of _edata: " );
   printLongHex( addr );
   print( "\n" );

   addr = ( long )( &_end );
   print( "Address of _end: " );
   printLongHex( addr );
   print( "\n" );

   return( 0 );
}
