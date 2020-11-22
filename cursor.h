#ifndef CURSOR_H
#define CURSOR_H

struct Cursor {
	std::size_t x = 0;
	std::size_t y = 0;
	std::size_t row_offset = 0;
	Cursor() = default;
};

#endif
