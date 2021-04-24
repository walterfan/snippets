#refer to http://www.thegeekstuff.com/2012/08/gprof-tutorial/
build:
	gcc -Wall -pg test_gprof.c test_gprof_new.c -o test_gprof
test:
	./test_gprof 
clean:
	rm -f ./test_gprof 
report:
	gprof test_gprof gmon.out > analysis.txt
