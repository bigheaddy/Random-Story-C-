CFLAGS= -Wall -Werror -std=gnu++98 -pedantic -ggdb3


test: randstory.cpp randmain.cpp
	g++ $(CFLAGS) -o rand randstory.cpp randmain.cpp


clean:
	rm -f rand *~
