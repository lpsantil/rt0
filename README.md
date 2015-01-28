# rt0
A minimal C runtime for Linux i386 &amp; x86_64

## Features
* Implemented in just 98 SLOC of C89-ish code.
* Just 2 lines of GCC inline ASM for i386, or,
* Just 6 lines GCC inline ASM for x86_64 (because the SysV x86_64 ABI is register-based vs. the stack-based SysV i386 ABI)
* Small runtime providing just `argc`, `argv`, `envp`, `__environ`, `_exit`, and `syscall0/1/2/3/4/5/6`
* Small binary sizes vs. other libc's

| Binary      | Arch   | Size | Purpose                  | Compile Args                          |
-------------:|:-------|-----:|:-------------------------|:--------------------------------------|
| librt0.a    | i386   | 5160 | Startup code+syscall     | -Os -s -nostdlib -fomit-frame-pointer |
| librt0.a    | x86_64 | 6772 | Startup code+syscall     | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | i386   | 1760 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1800 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| hello.exe   | i386   | 5532 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |
| hello.exe   | x86_64 | 6240 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |

Compiler: GCC 4.8.2
OS: Ubuntu 14.04.1
Source: Author

See the [musl libc comparison][0] to see how other libc's fare.

## Building
Try:
* `make`
* `make librt0.a`
* `make install`
* `make test`
* `make runtest`

## Usage
* Include `rt0/rt0.h` for `__environ`, `_exit`
* Include `rt0/syscall.h` for `SYS_*`, `syscall0/1/2/3/4/5/6`
* Define `main` as `int main( int, char**, char** )`
* Compile your code with `-nostdlib`, e.g., `cc -c prog.c -nostdlib -o prog.o`
* Link with librt0, e.g., `cc prog.o -nostdlib -lrt0 -o prog`


[0]: http://www.etalabs.net/compare_libcs.html
