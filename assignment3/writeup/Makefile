LATEX		= latex -shell-escape
DVIPS		= dvips
DVIPDF  	= dvipdft
XDVI		= xdvi -gamma 4
GH			= gv
FILE		= assignment3

SRC			:= $(shell egrep -l '^[^%]*\\begin\{document\}' *.tex)
TRG		 	= $(SRC:%.tex=%.dvi)
PSF			= $(SRC:%.tex=%.ps)
PDF			= $(SRC:%.tex=%.pdf)

pdf: $(PDF)
	rm -f *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg *.toc *.c.tex

ps: $(PSF)

$(TRG): %.dvi: %.tex part11.eps part12.eps
	pygmentize -f latex -o __part3.c.tex ../part3.c
	pygmentize -f latex -o __part4.c.tex ../part4.c
	pygmentize -f latex -o __part5.c.tex ../part5.c
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

$(PSF):%.ps: %.dvi
	$(DVIPS) -R -Poutline -t letter $< -o $@

$(PDF): %.pdf: %.ps
	ps2pdf $<

show: $(TRG)
	@for i in $(TRG) ; do $(XDVI) $$i & done

showps: $(PSF)
	@for i in $(PSF) ; do $(GH) $$i & done

all: pdf

clean:
	rm -f $(FILE).pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg *.toc *.c.tex

.PHONY: all show clean ps pdf showps
