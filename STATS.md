# rt0 library & binary sizes

| Binary      | Arch   | Size | Purpose                  | Compile Args                          |
-------------:|:-------|-----:|:-------------------------|:--------------------------------------|
| librt0.a    | i386   | 3502 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| librt0.a    | x86_64 | 4798 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| t/hello.exe | i386   | 1140 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1328 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| hello.exe   | i386   | 5532 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |
| hello.exe   | x86_64 | 6240 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |
| t/null.exe  | i386   | 1044 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |
| t/null.exe  | x86_64 | 1272 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |
| null.exe    | i386   | 5528 | Empty main               | -Os -s -fomit-frame-pointer           |
| null.exe    | x86_64 | 6232 | Empty main               | -Os -s -fomit-frame-pointer           |
| ...         | ...    | ...  | ...                      | With `__RT0_WITH_FASTER_SYSCALL__`    |
| librt0.a    | i386   | 4168 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| librt0.a    | x86_64 | 5660 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| t/hello.exe | i386   | 1440 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1600 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/null.exe  | i386   | 1368 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |
| t/null.exe  | x86_64 | 1560 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |

Compiler: GCC 4.8.2, gold linker 1.11 (binutils 2.24) OS: Ubuntu 14.04.2, Source: Author
