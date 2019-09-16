build:
	gcc -g -msse4.1 -lm -mavx -mavx2 -std=c11 -march=native -o bin/main src/matrix_lib_test.c src/matrix_lib.c
	./bin/main 5.0 8 16 16 8 dats/floats_256_2.0f.dat dats/floats_256_5.0f.dat dats/result1.dat dats/result2.dat


dat:
	gcc -g -o bin/dat src/dat.c


