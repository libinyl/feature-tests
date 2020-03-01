clean:
	rm -rf *.o *.out
	make -C net clean
	make -C c++ clean