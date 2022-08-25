all:
	latex text.tex brief.dvi
	latex text.tex brief.dvi
	pdflatex text.tex brief.pdf

.PHONY: clean

clean:
	@rm -rf *.aux
	@rm -rf *.dvi
	@rm -rf *.log
	@rm -rf *.pdf
	@rm -rf ./images/*.pdf
	@rm -rf *.toc
