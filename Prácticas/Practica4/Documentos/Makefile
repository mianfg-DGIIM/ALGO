# Author:	
# 	Sergio Quijano Rey
# 	sergiquijano@gmail.com
# Description:
# 	Makefile para compilar los documentos de Latex

all:
	@echo "Makefile para generar los documentos de la practica"
	@echo "	make: muestra esta ayuda"
	@echo "	make preview: compila y muestra la presentacion"
	@echo "	make clean: limpia todos los archivos auxiliares"
	@echo ""
	@echo "	make ./Presentacion.pdf: compila la presentacion"

# Funciones auxiliares
preview: ./Presentacion.pdf
	@evince ./Presentacion.pdf &

clean:
	@rm -f *.log *.nav *.snm *.toc *.vrb *.aux *.out

# Compilacion
./Presentacion.pdf: ./Presentacion.tex
	pdflatex ./Presentacion.tex

