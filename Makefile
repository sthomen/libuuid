#!smake
# The above hashbang makes this file is compatible with both BSD and SGI make

include version.mk

RM?=rm -f
LN?=ln -sf

CC?=cc

PREFIX?=/usr/local

INSTALL?=install

# library

LIB_SUFFIX?=so

LIB_NAME=libuuid
LIB=$(LIB_NAME).$(LIB_SUFFIX).$(MAJOR).$(MINOR)
LIB_LINK1=$(LIB_NAME).$(LIB_SUFFIX)
LIB_LINK2=$(LIB_NAME).$(LIB_SUFFIX).$(MAJOR)

LIBS=$(LIB) $(LIB_LINK1) $(LIB_LINK2)
LIB_HEADERS=uuid.h

LIB_SRCS=uuid.c
LIB_LIBS=-shared

LIB_OBJS=$(LIB_SRCS:S/.c/.o/)

$(LIB): $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $(LIB_OBJS) $(LDFLAGS) $(LIB_LIBS)
	$(LN) $(LIB) $(LIB_LINK1)
	$(LN) $(LIB) $(LIB_LINK2)

install: $(LIB)
	$(INSTALL) -d $(PREFIX)/lib
	$(INSTALL) $(LIBS) $(PREFIX)/lib
	$(INSTALL) -d $(PREFIX)/include/uuid
	$(INSTALL) $(LIB_HEADERS) $(PREFIX)/include/uuid

# test

TEST_CFLAGS?=$(CFLAGS) -I.
TEST_LDFLAGS?=-L. -Wl,-rpath,. -luuid

CMOCKA_CFLAGS?=-I/usr/pkg/include
CMOCKA_LDFLAGS?=-L/usr/pkg/lib -Wl,-rpath,/usr/pkg/lib -lcmocka

test: test_program
	./test

test_program: $(LIB) test.c
	$(CC) $(CMOCKA_CFLAGS) $(TEST_CFLAGS) -o test test.c $(TEST_LDFLAGS) $(CMOCKA_LDFLAGS)

# cleaning

clean:
	$(RM) $(LIB_OBJS) $(LIBS)
	$(RM) test

# conversion

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
