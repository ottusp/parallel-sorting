compile_seq:
	gcc country.c analysis_seq.c studentsseq.c -o studentsseq -lm

run_seq:
	./studentsseq < 1.in

clear_seq:
	rm -f studentsseq

all_seq:
	@make -s compile_seq
	@make -s run_seq
	@make -s clear_seq



compile_par:
	gcc country.c analysis_par.c studentspar.c -fopenmp -o studentspar -lm

run_par:
	./studentspar < 1.in

clear_par:
	rm -f studentspar

all_par:
	@make -s compile_par
	@make -s run_par
	@make -s clear_par