PREFIX = /usr/local

X11INC = /usr/include/X11
X11LIB = /usr/lib/X11

INCS = -I$(X11INC)
LIBS = -L$(X11LIB) -lX11 -lIL
# libs: -lXext

CFLAGS= -O2 -march=znver2 -pipe -std=gnu18 -Wall -Wextra -Wno-deprecated-declarations $(INCS)
LDFLAGS = $(LIBS)

CC = cc

