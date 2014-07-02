COMPILER 	= mpiCC
OPTI		= -O3
OMP			= -fopenmp
LOAD_EIGEN	= -I ~/my_libs/EIGEN
HEADERS		= output.hpp

#final
all: cannon


final: gemm.cpp timer.cpp timer.h $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) $(OMP) $(OPTI) gemm.cpp timer.cpp -o GEMM.out

tests: send_t, io_t

send_t: send_test.cpp $(HEADERS) timer.cpp timer.h
	$(COMPILER) $(LOAD_EIGEN) send_test.cpp timer.cpp -o send_t.out -o send_test.out

io_t:print_simple.cpp $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) print_simple.cpp -o test.out

io_t_wrong: print_test.cpp $(HEADERS)
	$(COMPILER) $(LOAD_EIGEN) print_test.cpp -o test.out

both: ohnebeni.cpp $(HEADERS) timer.cpp timer.h
	$(COMPILER) $(LOAD_EIGEN) ohnebeni.cpp timer.cpp timer.h -o testmult.out

cannon: cannon_square.cpp $(HEADERS) timer.cpp timer.h
	$(COMPILER) $(LOAD_EIGEN) cannon_square.cpp timer.cpp timer.h -o cannon.out
clean:
	rm -f *.out

run:
	mpirun -np 9 cannon.out
