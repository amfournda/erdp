CC = gcc
NAME = erdp
SRC = erdp.c rdp_connect.c


PKGCONFIG = $(shell which pkg-config)
CFLAGS = `$(PKGCONFIG) --cflags gtk+-3.0` -rdynamic
LIBS = `$(PKGCONFIG) --libs gtk+-3.0` -rdynamic

OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

erdp: $(OBJS)
	$(CC) -o $(NAME) $(LIBS) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(NAME)
