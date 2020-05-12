# Description:
# 	Makefile de la tercera practica de Algoritmica
# 	Sirve para compilar codigos, compilar latex y limpiar la carpeta de trabajo
# Author:
# 	Sergio Quijano Rey
# 	sergiquijano@gmail.com

# Variables del Makefile
#===============================================================================
CPPFLAGS = "-g"

# Proceso de compilacion
#===============================================================================
all:
	@echo "Makefile:"
	@echo "	make: muestra esta ayuda"
	@echo "	clean: limpia el directorio de trabajo"
	@echo ""
	@echo "	naive: compila y ejecuta el TSP Naive"
	@echo "	snf: compila y ejecuta el TSP SNF"
	@echo "	matrix: compila y ejecuta el TSP SNF Matrix"
	@echo "	insertion: compila y ejecuta el TSP por insercion"
	@echo "	perb: compila y ejecuta el TSP por perturbaciones"
	@echo ""
	@echo "	wnaive: compila y ejecuta el problema de los trabajadores Naive"
	@echo "	weasy: compila y ejecuta el problema de los trabajadores greedy solucion simple"
	@echo "	wperb: compila y ejecuta el problema de los trabajadores greedy solucion con perturbaciones"

clean:
	@rm -f *.log
	@rm -f ./Binarios/*
	@rm -f vgcore.*

# Ejecucion de los algoritmos
#===============================================================================
naive: ./Binarios/naive
	./Binarios/naive

snf: ./Binarios/snf
	./Binarios/snf

matrix: ./Binarios/matrix
	./Binarios/matrix

insertion: ./Binarios/insertion
	./Binarios/insertion

perb: ./Binarios/perb
	./Binarios/perb

wnaive: ./Binarios/wnaive
	./Binarios/wnaive

weasy: ./Binarios/weasy
	./Binarios/weasy

wperb: ./Binarios/wperb
	./Binarios/wperb

# Compilacion de los codigos
#===============================================================================
./Binarios/naive: ./Codigos/codigo_tps/tsp_naive.cpp ./Codigos/codigo_tsp/tsp_common.hpp
	g++ $(CPPFLAGS) Codigos/codigo_tps/tsp_naive.cpp -I./Codigos/codigo_tps/tsp_common.hpp -o ./Binarios/naive

./Binarios/snf: ./Codigos/codigo_tsp/tsp_snf.cpp ./Codigos/codigo_tsp/tsp_common.hpp
	g++ $(CPPFLAGS) ./Codigos/tsp_snf.cpp -I./Codigos/tsp_common.hpp -o ./Binarios/snf

./Binarios/matrix: ./Codigos/tsp_matrix.cpp ./Codigos/tsp_common.hpp
	g++ $(CPPFLAGS) ./Codigos/tsp_matrix.cpp -I./Codigos/tsp_common.hpp -o ./Binarios/matrix

./Binarios/insertion: ./Codigos/tsp_insertion.cpp ./Codigos/tsp_common.hpp
	g++ $(CPPFLAGS) ./Codigos/tsp_insertion.cpp -I./Codigos/tsp_common.hpp -o ./Binarios/insertion

./Binarios/perb: ./Codigos/codigo_tsp/tsp_perturbation.cpp ./Codigos/codigo_tsp/tsp_common.hpp
	g++ $(CPPFLAGS) ./Codigos/codigo_tsp/tsp_perturbation.cpp -I./Codigos/codigo_tps/tsp_common.hpp -o ./Binarios/perb

./Binarios/wnaive: ./Codigos/worker_naive.cpp ./Codigos/worker_common.hpp
	g++ $(CPPFLAGS) ./Codigos/worker_naive.cpp -I./Codigos/worker_common.hpp -o ./Binarios/wnaive

./Binarios/weasy: ./Codigos/worker_easy.cpp ./Codigos/worker_common.hpp
	g++ $(CPPFLAGS) ./Codigos/worker_easy.cpp -I./Codigos/worker_common.hpp -o ./Binarios/weasy

./Binarios/wperb: ./Codigos/codigo_worker/worker_perturbation.cpp ./Codigos/codigo_worker/worker_common.hpp
	g++ $(CPPFLAGS) ./Codigos/codigo_worker/worker_perturbation.cpp -I./Codigos/codigo_worker/worker_common.hpp -o ./Binarios/wperb
