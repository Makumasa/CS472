CC      = gcc
CFLAGS  = -std=c99
SOURCES = cpuid.c
HEADERS = 
FILES   = $(SOURCES) $(HEADERS)
OUTDIR  = ./build
OUTPUT  = $(OUTDIR)/assignment1

release: create_outdir $(FILES)
	$(CC) $(CFLAGS) -O2 -o $(OUTPUT) $(SOURCES)

debug: create_outdir $(FILES)
	$(CC) $(CFLAGS) -g -Wall -o $(OUTPUT) $(SOURCES)

clean:
	rm -rf $(OUTPUT)

rebuild_release: clean release

rebuild_debug: clean debug

create_outdir:
	mkdir -p $(OUTDIR)
