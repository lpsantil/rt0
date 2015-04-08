| Binary      | Arch   | Size | Purpose                  | Compile Args                          |
-------------:|:-------|-----:|:-------------------------|:--------------------------------------|
| librt0.a    | i386   | 3502 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| librt0.a    | x86_64 | 4798 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| t/hello.exe | i386   | 1256 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1488 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| hello.exe   | i386   | 5532 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |
| hello.exe   | x86_64 | 6240 | Hello World\n with glibc | -Os -s -fomit-frame-pointer           |
| t/null.exe  | i386   | 1160 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |
| t/null.exe  | x86_64 | 1432 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |
| null.exe    | i386   | 5528 | Empty main               | -Os -s -fomit-frame-pointer           |
| null.exe    | x86_64 | 6232 | Empty main               | -Os -s -fomit-frame-pointer           |
| ...         | ...    | ...  | ...                      | With `__RT0_WITH_FASTER_SYSCALL__`    |
| librt0.a    | i386   | 4168 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| librt0.a    | x86_64 | 5660 | Startup code+syscall     | -Os -nostdlib -fomit-frame-pointer    |
| t/hello.exe | i386   | 1604 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/hello.exe | x86_64 | 1808 | Hello World\n            | -Os -s -nostdlib -fomit-frame-pointer |
| t/null.exe  | i386   | 1532 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |
| t/null.exe  | x86_64 | 1768 | Empty main               | -Os -s -nostdlib -fomit-frame-pointer |

Compiler: GCC 4.8.2, OS: Ubuntu 14.04.1, Source: Author
