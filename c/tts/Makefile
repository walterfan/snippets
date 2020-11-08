FLITEDIR := ~/workspace/cpp/flite
FLITEDIR_LIB := $(FLITEDIR)/build/x86_64-darwin19.6.0/lib
LD_FLAGS = -lflite_cmu_us_kal -lflite_usenglish -lflite_cmulex -lflite -lm

build_flite_test:
	gcc -Wall -g -o ./flite_test flite_test.c -I$(FLITEDIR)/include -L$(FLITEDIR_LIB) $(LD_FLAGS)

run_flite_test:
	./flite_test

clean:
	rm -f flite_test
	rm -rf flite_test.dSYM
