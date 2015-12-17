FLITEDIR := /workspace/exam/flite-2.0.0-release
FLITEDIR_LIB := $(FLITEDIR)/build/x86_64-darwin14.5.0/lib

build_flite_test:
	gcc -Wall -g -o ./flite_test flite_test.c -I$(FLITEDIR)/include -L$(FLITEDIR_LIB) -lflite_cmu_us_kal -lflite_usenglish -lflite_cmulex -lflite -lm
run_flite_test:
	./flite_test
clean:
	rm -f flite_test
	rm -rf flite_test.dSYM
