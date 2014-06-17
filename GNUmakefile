N:=c42clia
D:=C42CLIA

LIBSRC:=posix.c mswin.c

DEVDIR:=$(abspath $(or $(DEVDIR),../targets))

TARGET:=$(shell $(CC) -v 2>&1 | grep "^Target: " | sed "s/^Target: //")
TCPFX:=$(CC:%gcc=%)
TCPFX:=$(TCPFX:%clang=%)
TCPFX:=$(TCPFX:%cc=%)
AR:=$(TCPFX)ar
STRIP:=$(TCPFX)strip
CFG:=$(or $(CFG),release)
O:=$(DEVDIR)/$(TARGET)-$(CFG)
B:=/tmp/$(shell whoami)-$(TARGET)-$(CFG)-$N
LIBPFX:=$(if $(findstring mingw,$(CC)),,lib)
LIBEXT:=$(if $(findstring mingw,$(CC)),.dll,.so)
EXEEXT:=$(if $(findstring mingw,$(CC)),.exe,)

LN:=$(LIBPFX)$N$(LIBEXT)
SLIB:=$B/lib$(N).a
CF:=-std=c99 -Wall -Werror -Wextra -fvisibility=hidden -I$O/include
LIBCF:=$(CF)
SLIBCF:=$(LIBCF) -D$D_STATIC

ifeq ($(TARGET),i686-w64-mingw32)
DLIBCF:=$(filter-out -fpic,$(DLIBCF))
endif

CF_debug:=-O0 -D_DEBUG
CF_release:=-O3 -ffast-math -fomit-frame-pointer -DNDEBUG

LIBF:=

OK_MSG=[32mOK[0m
FAILED_MSG=[31;1mFAILED[22m
NORMAL_COLOR=[0m
PROJECT_COLOR=[33;1m
TARGET_COLOR=[35;1m
IMSG="$(PROJECT_COLOR)$(N) $(TARGET_COLOR)$(TARGET)-$(CFG)$(NORMAL_COLOR)"

.PHONY: all install clean

all: $(SLIB)

install: all
	mkdir -p $O/include $O/bin $O/lib
	cp -f $(SLIB) $O/lib/
	@echo $(IMSG)

clean:
	-rm -rf $B

$B:
	mkdir -p $@
	chmod 700 $@

$(SLIB): $(patsubst %.c,$B/%-sta.o,$(LIBSRC)) | $B
	$(AR) rcs $@ $^

$(patsubst %.c,$B/%-sta.o,$(LIBSRC)): $B/%-sta.o: %.c | $B
	$(CC) -c -o $@ $< $(SLIBCF) $(CF_$(CFG))


