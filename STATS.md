# rt0 library & binary sizes

| Binary      | Arch   | Size | Purpose                            |
-------------:|:-------|-----:|:-----------------------------------|
| librt0.a    | i386   | 2810 | Startup code+syscall               |
| librt0.a    | x86_64 | 3974 | Startup code+syscall               |
| t/hello.exe | i386   | 624  | Hello World\n                      |
| t/hello.exe | x86_64 | 824  | Hello World\n                      |
| hello.exe   | i386   | 2988 | Hello World\n with glibc           |
| hello.exe   | x86_64 | 4200 | Hello World\n with glibc           |
| t/null.exe  | i386   | 560  | Empty main                         |
| t/null.exe  | x86_64 | 768  | Empty main                         |
| null.exe    | i386   | 2888 | Empty main with glibc              |
| null.exe    | x86_64 | 2988 | Empty main with glibc              |
| ...         | ...    | ...  | With `__RT0_WITH_FASTER_SYSCALL__` |
| librt0.a    | i386   | 3980 | Startup code+syscall               |
| librt0.a    | x86_64 | 5604 | Startup code+syscall               |
| t/hello.exe | i386   | 608  | Hello World\n                      |
| t/hello.exe | x86_64 | 792  | Hello World\n                      |
| t/null.exe  | i386   | 552  | Empty main                         |
| t/null.exe  | x86_64 | 752  | Empty main                         |

Compiler: GCC 4.8.4, gold linker 1.11, ld/binutils 2.24, OS: Ubuntu 14.04.3, Source: Author

Compile Flags: `-Os -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=387 -mfancy-math-387 -ffunction-sections -fdata-sections Wl,--gc-sections`

Link Flags: `-s -nostdlib -z norelro --hash-style=sysv --build-id=none --gc-sections`

---

`HelloWorld` & `null` compiled with flags above but without `-nostdlib`.

`HelloWorld.glibc.c`
```
#include <unistd.h>

int main( int argc, char** argv, char** envp )
{
   int ret = write( 1, "Hello World!\n", 13 );
   return( 0 );
}
```

---

`null.glibc.c`
```
int main( int argc, char** argv, char** envp )
{
   return( 0 );
}
```
