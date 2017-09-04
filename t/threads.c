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

void
printLongHex( long i )
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

#define DEFAULT_STACK_SIZE() ( 4096 * 1024 )

#define MAP_GROWSDOWN	0x0100
#define MAP_ANONYMOUS	0x0020
#define MAP_PRIVATE	0x0002
#define PROT_READ	0x1
#define PROT_WRITE	0x2
#define PROT_EXEC	0x4

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
   return( mmap( 0, DEFAULT_STACK_SIZE(), PROT_WRITE | PROT_READ | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE | MAP_GROWSDOWN ) );
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
   void* newSP = ( void* )( ( char* )newStack + DEFAULT_STACK_SIZE() - 8 );
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

void*
sys_brk( void* addr )
{
   return( ( void* )( syscall1( SYS_brk, ( long )( addr ) ) ) );
}

void* start_brkp = ( void* )( 0 - 1 );
void* new_brkp = 0;

int
brk( void* addr )
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

void*
sbrk( long inc )
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

int
main( int argc, char **argv, char **envp )
{
   /*
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
   */
   threadCreate( dummyThread );
   threadCreate( dummyThread );
   for( int i = 0; i < 5; i++ )
   {
      print( "Parent Thread!\n");
   }

   return( 0 );
}
