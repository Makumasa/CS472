CC      = gcc
CFLAGS  = -std=c99 -lm
IMP     = my_frexp
OPS     = fp_ops
HEADERS = 
FILES   = $(IMP).c $(OPS).c $(HEADERS)
OUTDIR  = ./build
IMP_OUT = $(OUTDIR)/$(IMP)
OPS_OUT = $(OUTDIR)/$(OPS)
OUTPUTS = $(IMP_OUT) $(OPS_OUT)

release: create_outdir $(FILES)
	$(CC) $(CFLAGS) -O2 -o $(IMP_OUT) $(IMP).c
	$(CC) $(CFLAGS) -O2 -o $(OPS_OUT) $(OPS).c

debug: create_outdir $(FILES)
	$(CC) $(CFLAGS) -g -Wall -o $(IMP_OUT) $(IMP).c
	$(CC) $(CFLAGS) -g -Wall -o $(OPS_OUT) $(OPS).c

clean:
	rm -rf $(OUTPUTS)

rebuild_release: clean release

rebuild_debug: clean debug

create_outdir:
	mkdir -p $(OUTDIR)
