#include "rim.h"

void run_rim(const char* file_name) {
	Rim r{file_name};	

	int character;
	while (true) {
		character = getch();
		r.process_keypress(character);
	}
}

int main(int argc, char** argv) {
	if (argc > 0) {
		run_rim(argv[1]);
	}
}
