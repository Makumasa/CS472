CC          = gcc
LINK_FLAGS  = -lm
CFLAGS      = $(LINK_FLAGS) -std=c99 -O2 -DNDEBUG
DEBUG_FLAGS = $(LINK_FLAGS) -std=c99 -Og -g -Wall -DDEBUG
PROGRAMS    = part3 part4 part5
HEADERS     = 

.PHONY: debug all clean rebuild rebuild_debug

all: $(PROGRAMS)

debug: CFLAGS := $(DEBUG_FLAGS)
debug: $(PROGRAMS)

$(PROGRAMS): %: %.c 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(PROGRAMS) *.o *.s

rebuild: clean all

rebuild_debug: clean debug
