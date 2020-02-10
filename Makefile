#!smake
# The above hashbang makes this file is compatible with both BSD and SGI make

include version.mk

RM?=rm -f
LN?=ln -sf

CC?=cc
CFLAGS?=
LDFLAGS?=

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

# test program

TEST=test
TEST_SRCS=test.c
TEST_LIBS=-Wl,-rpath,. -L. -luuid

TEST_OBJS=$(TEST_SRCS:S/.c/.o/)

$(TEST): $(LIB) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) $(LDFLAGS) $(TEST_LIBS)
	./$(TEST)

# cleaning

clean: $(TEST)_clean $(LIB)_clean

$(TEST)_clean:
	$(RM) $(TEST_OBJS) $(TEST)

$(LIB)_clean:
	$(RM) $(LIB_OBJS) $(LIBS)

# conversion

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
