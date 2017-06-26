# Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
# All rights reserved.
# See LICENSE for licensing details.

DESTDIR ?= /usr/local

######################################################################
# Core count
CORES ?= 1

# Basic feature detection
OS = $(shell cat /etc/os-release | grep "rhel\|fedora\|centos" && echo "rhel" || cat /etc/os-release | grep "debian\|ubuntu" && echo "debian" || uname)
ARCH ?= $(shell uname -m)

ifeq ($(ARCH), i686)
	ARCH = i386
endif
ifeq ($(ARCH), i386)
	MSIZE = 32
endif
ifeq ($(ARCH), x86_64)
	MSIZE = 64
endif

######################################################################

# Comment next line if you want System Default/GNU BFD LD instead
#LD = gold
CFLAGS ?= -Os -Wall -ansi -pedantic -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=sse -mfancy-math-387 -ffunction-sections -fdata-sections -Wl,--gc-sections -flto
#CFLAGS ?= -Os -Wall -std=gnu99 -pedantic -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=sse -mfancy-math-387 -ffunction-sections -fdata-sections -Wl,--gc-sections -flto
LDFLAGS ?= -s -static -nostdlib -z norelro --hash-style=sysv --build-id=none --gc-sections -flto
#LDFLAGS ?= -g -nostdlib
#LDFLAGS ?= -s -nostdlib -Wl,--gc-sections

DDIR = docs
DSRC =
SRC =
OBJ = $(SRC:.c=.o)
SDEPS = $(SRC:.c=.d)
HDR = rt0/rt0.h
IDIR = include
INC = $(IDIR)/$(HDR)
INC += $(IDIR)/rt0/syscall.h
SYSINC = $(IDIR)/rt0/sys$(MSIZE).h
INC += $(SYSINC)
EDIR = .
EXE =
LNK = rt0
LDIR = lib
LSRC = $(shell ls src/lib/*.c)
LOBJ = $(LSRC:.c=.o)
LSDEPS = $(LSRC:.c=.d)
LIB = $(LDIR)/lib$(LNK).a
TDIR = t
TSRC = $(shell ls t/*.c)
TOBJ = $(TSRC:.c=.o)
TSDEPS = $(TSRC:.c=.d)
TEXE = $(TOBJ:.o=.exe)

TMPCI = $(shell cat tmp.ci.pid 2>/dev/null)
TMPCT = $(shell cat tmp.ct.pid 2>/dev/null)
TMPCD = $(shell cat tmp.cd.pid 2>/dev/null)

CILOG ?= tmp.ci.log

# DEPS
DEPS =
LIBDEP =

# TDEPS
TDEPS =
TAP =
LIBTAP =

######################################################################

ifeq ($(WITH_SECTIONS), 1)
	CFLAGS += -fdata-sections -ffunction-sections
endif

ifeq ($(WITH_DEBUG), 1)
	CFLAGS += -g
	LDFLAGS = -nostdlib -g
endif

# Fix up LDFLAGS for FreeBSD
ifeq ($(OS), Freebsd)
	LDFLAGS += -Wl,-u_start
endif

# Fix up the unistd_$(MSIZE) on rhel/fedora/centos vs. debian/ubuntu
ifeq ($(OS), rhel)
	UNISTD_PATH =
endif
ifeq ($(OS), debian)
	UNISTD_PATH = $(ARCH)-linux-gnu/
endif

######################################################################
######################## DO NOT MODIFY BELOW #########################
######################################################################

.PHONY: all test runtest clean start_ci stop_ci start_ct stop_ct
.PHONY: start_cd stop_cd install uninstall showconfig gstat gpush
.PHONY: tarball

%.o: %.c $(INC) Makefile
	$(CC) $(CFLAGS) -MMD -MP -I$(IDIR) -c $< -o $@

t/%.exe: t/%.o $(LIB) Makefile
	$(LD) -L$(LDIR) -l$(LNK) $(LDFLAGS) $< -o $@

all: $(LIB)

$(SYSINC): /usr/include/$(UNISTD_PATH)/asm/unistd_$(MSIZE).h
	echo -e "\n#define __SYSCALL(x,y)\n" >> $@
	grep __NR_ $< | sed -e s/__NR_/SYS_/g >> $@
ifeq ($(WITH_FAST_SYSCALL), 1)
	echo -e "\n#define __RT0_WITH_FASTER_SYSCALL__ 1\n" >> $@
endif
	echo -e "\n#undef __SYSCALL\n" >> $@

$(LIB): $(LOBJ)
	$(AR) -rcs $@ $^

$(EXE): $(OBJ)
	$(LD) $^ $(LDFLAGS) -o $(EDIR)/$@

test: $(SYSINC) $(LIB) $(TEXE) Makefile

runtest: $(TEXE)
	for T in $^ ; do $(TAP) $$T ; done

start_ci:
	( watch time -p make clean all ) &> $(CILOG) & echo $$! > tmp.ci.pid

stop_ci:
	kill -9 $(TMPCI)

start_ct:
	watch time -p make test & echo $$! > tmp.ct.pid

stop_ct:
	kill -9 $(TMPCT)

start_cd:
	watch time -p make install & echo $$! > tmp.cd.pid

stop_cd:
	kill -9 $(TMPCD)

clean:
	rm -f $(OBJ) $(EXE) $(LOBJ) $(LIB) $(TOBJ) $(TEXE) $(SYSINC) *.tmp $(SDEPS) $(LSDEPS) $(TSDEPS)

install: $(INC) $(LIB)
	mkdir -p $(DESTDIR)/include/rt0 $(DESTDIR)/lib
	rm -f .footprint
	@for T in $(INC) $(LIB); \
	do ( \
		echo $(DESTDIR)/$$T >> .footprint; \
		cp -v --parents $$T $(DESTDIR) \
	); done

uninstall: .footprint
	@for T in `cat .footprint`; do rm -v $$T; done

-include $(SDEPS) $(LSDEPS) $(TSDEPS)

showconfig:
	@echo "OS="$(OS)
	@echo "ARCH="$(ARCH)
	@echo "MSIZE="$(MSIZE)
	@echo "SYSINC="$(SYSINC)
	@echo "DESTDIR="$(DESTDIR)
	@echo "CFLAGS="$(CFLAGS)
	@echo "LDFLAGS="$(LDFLAGS)
	@echo "UNISTD_PATH="$(UNISTD_PATH)
	@echo "DDIR="$(DDIR)
	@echo "DSRC="$(DSRC)
	@echo "SRC="$(SRC)
	@echo "OBJ="$(OBJ)
	@echo "HDR="$(HDR)
	@echo "IDIR="$(IDIR)
	@echo "INC="$(INC)
	@echo "EDIR="$(EDIR)
	@echo "EXE="$(EXE)
	@echo "LDIR="$(LDIR)
	@echo "LSRC="$(LSRC)
	@echo "LOBJ="$(LOBJ)
	@echo "LNK="$(LNK)
	@echo "LIB="$(LIB)
	@echo "TSRC="$(TSRC)
	@echo "TOBJ="$(TOBJ)
	@echo "TEXE="$(TEXE)
	@echo "TMPCI="$(TMPCI)
	@echo "TMPCT="$(TMPCT)
	@echo "TMPCD="$(TMPCD)

gstat:
	git status

gpush:
	git commit
	git push

tarball:
	cd ../. && tar jcvf rt0.$(shell date +%Y%m%d%H%M%S).tar.bz2 rt0
