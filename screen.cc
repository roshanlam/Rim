#include "screen.h"

static const int FILE_BAR_COLOR = 1;

Screen::Screen(const char* file_name) noexcept 
: rows{}, cols{}, file_name{file_name}, file_info_bar{} {
	initscr();
	start_color();
	init_pair(FILE_BAR_COLOR, COLOR_BLACK, COLOR_WHITE);

	noecho();
	raw();
	getmaxyx(stdscr, rows, cols);
	scrollok(stdscr, true);

	rows -= 2;
	file_info_bar = newwin(1, cols, rows, 0);
}

void Screen::display(std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end,
		const Cursor& cursor) const noexcept {
	clear();
	std::size_t i = 0;
	for (auto iterator = begin; i < rows && iterator != end; 
	++iterator, ++i) {
		printw("%s", iterator->c_str());
		if (i != rows - 1) {
			printw("\n");
		}
	}
	for (; i < rows; ++i) {
		printw("~");
		if (i != rows - 1) {
			printw("\n");
		}
	}
	refresh();
	draw_file_info_bar();
	move_cursor(cursor);
}

void Screen::draw_file_info_bar() const noexcept {
	wbkgd(file_info_bar, COLOR_PAIR(FILE_BAR_COLOR));
	wclear(file_info_bar);
	if (is_file_modified) {
		mvwprintw(file_info_bar, 0, 0, "%s [+]", file_name.c_str());
	}
	else {
		mvwprintw(file_info_bar, 0, 0, "%s", file_name.c_str());
	}
	wrefresh(file_info_bar);
}

void Screen::move_cursor(const Cursor& cursor) const noexcept {
	move(cursor.y, cursor.x);		
}

Screen::~Screen() {
	delwin(file_info_bar);
	endwin();
}
