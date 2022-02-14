include config.mk

SRC = src/blanket.c src/dr.c src/util.c

OBJ = $(SRC:.c=.o)

all: blanket

.c.o:
	$(CC) -o $@ -c $(CFLAGS) $<

$(OBJ): config.mk

blanket: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f blanket $(OBJ)

install: all
	mkdir -p $(PREFIX)/bin
	cp -f blanket $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/blanket
	
uninstall:
	rm -f $(PREFIX)/bin/blanket

.PHONY: all clean install uninstall
