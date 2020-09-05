output: rim.o
	 g++ rim.o -o output

rim.o: rim.cc
	 g++ -c rim.cc

clean:
	 rm *.o output
