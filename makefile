cc = g++
CFLAGS = -stdlib=libc++ -std=c++11 -Wall -Werror
RM = rm -f
.PHONY : clean

main: main.o implement.o 
	$(cc) $(CFLAGS) -o program main.o implement.o
	$(RM) *.o

implement.o : implement.cpp head.h
	$(cc) $(CFLAGS) -c implement.cpp

main.o : main.cxx head.h
	$(cc) $(CFLAGS) -c main.cxx

clean :
	$(RM) -- *.o program
