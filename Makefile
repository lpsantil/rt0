# Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
# All rights reserved.
# See LICENSE for licensing details.

DEST ?=
PREFIX ?= usr/local

INSTALL_PATH = $(DEST)/$(PREFIX)

######################################################################
# Core count
CORES ?= 1

# Basic feature detection
OS = $(shell uname)
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

CFLAGS ?= -Os -nostdlib -fomit-frame-pointer
#CFLAGS ?= -Os -nostdlib -g -fomit-frame-pointer
#CFLAGS ?= -Os -nostdlib -fomit-frame-pointer -fdata-sections -ffunction-sections
LDFLAGS ?= -s
#LDFLAGS ?= -s -Wl,--gc-sections
#LDFLAGS ?=
DDIR = docs
DSRC =
SRC =
OBJ = $(SRC:.c=.o)
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
LIB = $(LDIR)/lib$(LNK).a
TDIR = t
TSRC = $(shell ls t/*.c)
TOBJ = $(TSRC:.c=.o)
TEXE = $(TOBJ:.o=.exe)

#TMPCI = $(shell cat tmp.ci.pid)
#TMPCT = $(shell cat tmp.ct.pid)
#TMPCD = $(shell cat tmp.cd.pid)

# DEPS
DEPS =
LIBDEP =

# TDEPS
TDEPS =
TAP =
LIBTAP =

######################################################################

# Fix up LDFLAGS for FreeBSD
ifeq ($(OS), Freebsd)
	LDFLAGS += -Wl,-u_start
endif

######################################################################

.c.o:
	$(CC) $(CFLAGS) -I$(IDIR) -c $< -o $@

all: $(LIB)

$(SYSINC): /usr/include/$(ARCH)-linux-gnu/asm/unistd_$(MSIZE).h
	grep __NR_ $< | sed -e s/__NR_/SYS_/g > $@

$(LOBJ): Makefile $(INC)

$(OBJ): Makefile $(INC)

$(LIB): $(LOBJ)
	$(AR) -rcs $@ $^

$(EXE): $(OBJ)
	$(LD) $^ -o $(EDIR)/$@

t/%.exe: t/%.o
	$(CC) $< -L$(LDIR) -l$(LNK) $(CFLAGS) $(LDFLAGS) -o $@

test: $(SYSINC) $(LIB) $(TEXE)

$(TOBJ): $(LIB)

$(TEXE): $(TOBJ)

runtest: $(TEXE)
	for T in $^ ; do $(TAP) $$T ; done

start_ci:
	watch time -p make clean all & echo $$! > tmp.ci.pid

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
	rm -f $(OBJ) $(EXE) $(LOBJ) $(LIB) $(TOBJ) $(TEXE) $(SYSINC)

install: $(INC) $(LIB)
	mkdir -p $(INSTALL_PATH)/include/rt0 $(INSTALL_PATH)/lib
	rm -f .footprint
	@for T in $(INC) $(LIB); \
	do ( \
		echo $(INSTALL_PATH)/$$T >> .footprint; \
		cp -v --parents $$T $(INSTALL_PATH) \
	); done

uninstall: .footprint
	@for T in `cat .footprint`; do rm -v $$T; done

showconfig:
	@echo "OS="$(OS)
	@echo "ARCH="$(ARCH)
	@echo "MSIZE="$(MSIZE)
	@echo "SYSINC="$(SYSINC)
	@echo "DEST="$(DEST)
	@echo "PREFIX="$(PREFIX)
	@echo "INSTALL_PATH="$(INSTALL_PATH)
	@echo "CFLAGS="$(CFLAGS)
	@echo "LDFLAGS="$(LDFLAGS)
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
