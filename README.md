# rt0
A minimal C runtime for Linux i386 &amp; x86_64

## Features
* Implemented in just 87 SLOC of C code.
* Just 2 lines of GCC inline ASM for i386, or,
* Just 6 lines GCC inline ASM for x86_64 (because the SysV x86_64 ABI is register-based vs. the stack-based SysV i386 ABI)
* Small runtime providing just `argc`, `argv`, `envp`, `__environ`, `_exit`, and `syscall0/1/2/3/4/5/6`
* Small binary sizes vs. other libc's

| Binary      | Arch   | Size | Purpose                  | Compile Args                          |
-------------:|:-------|-----:|:-------------------------|:--------------------------------------|
| librt0.a    | i386   | 4390 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| librt0.a    | x86_64 | 6086 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| t/hello.exe | i386   | 1272 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1520 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
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

## References
* [Hello from a libc free world!][1]
* [musl libc][2]
* [Minimum C prgram][3]
* [SmallerC][4]
* [GCC Inline Assembly HOWTO][5]
* [System V ABI/Calling Convention][6]
* [Linux syscall interface][7]


[0]: http://www.etalabs.net/compare_libcs.html
[1]: https://blogs.oracle.com/ksplice/entry/hello_from_a_libc_free
[2]: http://git.musl-libc.org/cgit/musl/tree/
[3]: http://www.erik-n.net/studies/linux_boot_c/linux_boot_c.pdf
[4]: https://github.com/alexfru/SmallerC/blob/master/
[5]: http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
[6]: http://wiki.osdev.org/System_V_ABI#Calling_Convention
[7]: http://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux#Making_a_syscall

