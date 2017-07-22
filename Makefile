CC = g++


#Executable
RUNNER : $(OBJS) main.cpp
	$(CC) -o runner main.cpp

clean:
	rm -f *.o
	rm -f RUNNER

run:
	make clean
	make
	./runner
