#include <rt0/syscall.h>

int main( int argc, char **argv, char **envp )
{
   syscall3( SYS_write, 1, ( long )( "Hello World!\n" ), 13 );

   return 0;
}
