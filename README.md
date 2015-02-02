# rt0
A minimal C runtime for Linux i386 &amp; x86_64

## Features
* Implemented in just 101 SLOC of C code.
* Just 9 lines of GCC inline ASM for i386, or,
* Just 6 lines GCC inline ASM for x86_64
* Small runtime providing just `argc`, `argv`, `envp`, `__environ`, `_exit`, and `syscall0/1/2/3/4/5/6`
* Small binary sizes vs. other libc's

| Binary      | Arch   | Size | Purpose                  | Compile Args                          |
-------------:|:-------|-----:|:-------------------------|:--------------------------------------|
| librt0.a    | i386   | 4410 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| librt0.a    | x86_64 | 4590 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| t/hello.exe | i386   | 1232 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1464 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| hello.exe   | i386   | 5532 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |
| hello.exe   | x86_64 | 6240 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |

Compiler: GCC 4.8.2, OS: Ubuntu 14.04.1, Source: Author

See the [musl libc comparison][0] to see how other libc's fare.

## Building
Try:
* `make`
* `make librt0.a`
* `make test`
* `make runtest`
* In bash, `DEST=/ PREFIX=usr/local make install`, or simply, `make install`

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

## Other small libc's and runtimes
* [musl libc][8]
* [newlib libc][9]
* [uclibc][10]
* [dietlibc][11]
* [Plan9 libc][12]
* [lib43][13]
* [libowfat][14]
* [libdjb][15]
* [x86_64 crt0 in a single file][16]

[0]: http://www.etalabs.net/compare_libcs.html
[1]: https://blogs.oracle.com/ksplice/entry/hello_from_a_libc_free
[2]: http://git.musl-libc.org/cgit/musl/tree/
[3]: http://www.erik-n.net/studies/linux_boot_c/linux_boot_c.pdf
[4]: https://github.com/alexfru/SmallerC/blob/master/
[5]: http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
[6]: http://wiki.osdev.org/System_V_ABI#Calling_Convention
[7]: http://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux#Making_a_syscall
[8]: http://www.musl-libc.org/
[9]: https://sourceware.org/newlib/
[10]: http://www.uclibc.org/
[11]: http://www.fefe.de/dietlibc/
[12]: http://git.suckless.org/9base/tree/lib9/libc.h
[13]: https://github.com/lunixbochs/lib43
[14]: http://www.fefe.de/libowfat/
[15]: http://www.fefe.de/djb/
[16]: https://gist.github.com/lunixbochs/462ee21c3353c56b910f
