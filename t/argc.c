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
   print( "argc=" );
   printInt( argc );
   print( "\n" );

   return( 0 );
}
