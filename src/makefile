TARGETS = launcher readData taxis

CC = gcc
CFLAGS = -Wall -g -Werror

all: clean $(TARGETS)

$(TARGETS): 
	$(CC) $(CFLAGS) $@.c auxiliaire.c -o $@

clean:
	rm -f $(TARGETS); rm -f auxiliaire.o

clearMsgq:
	ipcrm -Q 1234