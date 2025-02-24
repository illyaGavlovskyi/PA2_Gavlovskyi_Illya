make:threaded_sum.o
	gcc -o threaded_sum threaded_sum.c

clean: 
	rm *o threaded_sum