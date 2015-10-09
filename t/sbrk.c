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

void* sys_brk( void* addr )
{
   return( ( void* )( syscall1( SYS_brk, ( long )( addr ) ) ) );
}

void* start_brkp = ( void* )( 0 - 1 );
void* new_brkp = 0;

int brk( void* addr )
{
   void* p;

   p = ( void* )( syscall1( SYS_brk, ( long )( addr ) ) );

   if( p != new_brkp )
   {
      new_brkp = p;

      if( ( void* )( -1 ) == start_brkp ) start_brkp = p;

      return( 0 );
   }

   return( -1 );
}

void* sbrk( long inc )
{
   void* old_brkp;

   if( 0 == inc )
   {
      if( 0 != new_brkp ) return( new_brkp );

      /* make sure we have a new_brkp, otherwise */
      brk( 0 );
      return( new_brkp );
   }

   old_brkp = new_brkp;

   if( 0 == brk( ( char* )( new_brkp ) + inc ) ) return( old_brkp );

   /* FIXME: set errno to ENOMEM first */
   return( ( void* )( -1 ) );
}

int main( int argc, char **argv, char **envp )
{
   char* brkp = 0;
   char* p = 0;

   brk( 0 );

   print( "Address of start_brkp/new_brkp/brkp/p/delta:\n" );
   printLongHex( ( long )( start_brkp ) );      print( ":" );
   printLongHex( ( long )( new_brkp ) );        print( ":" );
   printLongHex( ( long )( brkp ) );            print( ":" );
   printLongHex( ( long )( p ) );               print( ":" );
   printLongHex( ( long )( p - brkp ) );        print( "\n" );

   print( "...Allocating 4kb...\n" );
   p = sbrk( 4 * 1024 );
   print( "Address of start_brkp/new_brkp/brkp/p/delta:\n" );
   printLongHex( ( long )( start_brkp ) );      print( ":" );
   printLongHex( ( long )( new_brkp ) );        print( ":" );
   printLongHex( ( long )( brkp ) );            print( ":" );
   printLongHex( ( long )( p ) );               print( ":" );
   printLongHex( ( long )( p - brkp ) );       print( "\n" );

   print( "...Allocating 4kb more...\n" );
   p = sbrk( 4 * 1024 );
   print( "Address of p: " );
   printLongHex( ( long )( p ) );              print( "\n" );
   p = sbrk( 0 );
   print( "Heap Size: " );
   printLongHex( ( long )( p - ( char* )( start_brkp ) ) );   print( "\n" );

   return( 0 );
}
