CC          = gcc
LINK_FLAGS  = -lm
CFLAGS      = $(LINK_FLAGS) -std=c99 -O2 -DNDEBUG
DEBUG_FLAGS = $(LINK_FLAGS) -std=c99 -Og -g -Wall -DDEBUG
PROGRAMS    = my_frexp ops_test ops_timing interpret_64
HEADERS     = my_double.h mt19937-64.h

.PHONY: debug all clean rebuild rebuild_debug

all: $(PROGRAMS)

debug: CFLAGS := $(DEBUG_FLAGS)
debug: $(PROGRAMS)

my_frexp: my_frexp.c
	$(CC) $(CFLAGS) -o $@ $<

ops_test: ops_test.c my_fp_ops.c my_double.h
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^)

ops_timing: ops_timing.c fp_ops.c my_fp_ops.c mt19937-64.c $(HEADERS)
	$(CC) $(LINK_FLAGS) -std=c99 -O0 -Wall -c $(filter %.c,$^)
	$(CC) $(LINK_FLAGS) -o $@ $(addsuffix .o,$(basename $(filter %.c,$^)))
	rm -rf *.o

interpret_64: interpret_64.c mt19937-64.c mt19937-64.h
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^) 

clean:
	rm -rf $(PROGRAMS) *.o *.s

rebuild: clean all

rebuild_debug: clean debug
