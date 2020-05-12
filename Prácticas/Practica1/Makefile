# Variables auxiliares
#===============================================================================
DOCUMENTO = ./Practica\ 1\ -\ Memoria
TEX = $(DOCUMENTO).tex
PDF = $(DOCUMENTO).pdf
PDFVIEWER = evince


# Utilidades del makefile
#===============================================================================
help:
		@echo "Makefile help:"
		@echo "	make help: muestra esta ayuda"
		@echo "	make clean: limpia archivos auxiliares generados durante la compilación del documento latex"
		@echo "	make tex: genera el pdf a partir del archivo Latex"
		@echo "	make preview: compila y muestra el pdf a partir del archivo Latex"

tex: $(TEX)
	@pdflatex $(TEX)

$(DOCUMENTO).pdf: $(TEX)
	@pdflatex $(TEX)

preview: $(PDF)
	@$(PDFVIEWER) $(PDF) &

clean:
	@rm *.aux
	@rm *.log
	@rm *.toc
