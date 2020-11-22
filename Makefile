CPP_FLAGS = -std=c++14 -Wall -Werror -Wpedantic -Weffc++

FILES = screen.cc rim.cc main.cc

rim: ${FILES}
	g++ -O3 ${CPP_FLAGS} ${FILES} -o rim -lncurses

debug: ${FILES}
	g++ -ggdb ${CPP_FLAGS} ${FILES} -o rim -lncurses
