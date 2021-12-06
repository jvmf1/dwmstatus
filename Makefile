CC=gcc
CFLAGS=-Wall
LIBS=-lX11 -pthread -lslib
NAME=dwmstatus
OBJ=cell.o
HEADERS=cell.h
SRC=cell.c
DESTDIR=/bin
all = $(NAME)

$(NAME): $(NAME).c config.h $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(NAME).c -o $(NAME) $(OBJ)

$(OBJ): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

config.h:
	cp config.def.h $@

install: $(NAME)
	mkdir -p $(DESTDIR)
	cp -f $(NAME) $(DESTDIR)

uninstall:
	rm -f $(DESTDIR)/$(NAME)

clean:
	rm -f *.o
	rm -f $(NAME)

