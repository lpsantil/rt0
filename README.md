# rt0
A minimal C runtime for Linux on i386 &amp; x86_64

## Features
* Implemented in just 195 SLOC of C code.
* Just 9 lines of GCC inline ASM for i386, or,
* Just 6 lines GCC inline ASM for x86_64
* Small runtime providing just `argc`, `argv`, `envp`, `__environ`, `errno`, `_exit`, and `syscall0/1/2/3/4/5/6`
* Uses [gold][19] (Google LD, part of GNU Binutils) instead of GNU ld to save 100-200 bytes at static link time
* Hello World in just 1140 bytes (i386) or 1328 bytes (x86_64)
* Small binary sizes vs. other libc's

See STATS.md to see how rt0 fares.
See the [musl libc comparison][0] to see how other libc's fare.

## Building
Try:
* `make`
* `make librt0.a`
* `make test`
* `make runtest`
* `make DESTDIR=/usr/local install`, or simply, `make install`
* You can also do `make uninstall`

## Usage
* Include `rt0/rt0.h` for `__environ`, `_exit`
* Include `rt0/syscall.h` for `SYS_*`, `syscall0/1/2/3/4/5/6`
* Define `main` as `int main( int, char**, char** )`
* Compile your code with `-nostdlib`, e.g., `cc -c prog.c -nostdlib -o prog.o`
* On Linux, link with librt0, e.g., `cc prog.o -nostdlib -lrt0 -o prog`
* On FreeBSD, link with librt0 using, `cc prog.o -Wl,-u_start -nostdlib -lrt0 -o prog`
* To enable GNU ld, type `make LD=ld`
* To enable a slightly faster version of the syscalls, type `make WITH_FAST_SYSCALL=1`
* To enable `-fdata-sections -ffunction-sections`, type `make WITH_SECTIONS=1`
* To enable a debug build, type `make WITH_DEBUG=1`

## References
* [Hello from a libc free world!][1]
* [musl libc][2]
* [Minimum C prgram][3]
* [SmallerC][4]
* [GCC Inline Assembly HOWTO][5]
* [System V ABI/Calling Convention][6]
* [Linux syscall interface][7]
* [gold - Google ld][19]

## Other small libc's and runtimes
* [musl libc][8]
* [newlib libc][9]
* [uclibc][10]
* [dietlibc][11]
* [Plan9 libc][12]
* [ELKS libc][13]
* [gcmurphy libc][13]
* [lib43][15]
* [libowfat][16]
* [libdjb][17]
* [x86_64 crt0 in a single file][18]

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
[13]: https://packages.debian.org/wheezy/elks-libc
[14]: https://bitbucket.org/gcmurphy/libc/src 
[15]: https://github.com/lunixbochs/lib43
[16]: http://www.fefe.de/libowfat/
[17]: http://www.fefe.de/djb/
[18]: https://gist.github.com/lunixbochs/462ee21c3353c56b910f
[19]: http://en.wikipedia.org/wiki/Gold_%28linker%29
