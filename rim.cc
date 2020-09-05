#include <iostream>
#include <vector>
#include <cstdio>
#include <termios.h>
using namespace std;

vector<vector<char> > text;

unsigned int row = 0, col = 0;

bool command = false;

void left(){
  if(col > 0){
	 col--;
}else if(row > 0) {
	row--;
	col = text.at(row).size();
	}
      }

void right(){
  if(col < text.at(row).size()){
	col++;
} else if(row < text.size() - 1){
	row++;
	col = 0;
 }
}

void up(){
  if(row > 0){
	row--;
	if(col > text.at(row).size())
		col = text.at(row).size();
 }
}

void down(){
  if(row < text.size() - 1){
	row++;
  if(col > text.at(row).size())
	col = text.at(row).size();
 }
}

void insert(char c){
  if(c == '\n'){
	vector<char> line;
	for(unsigned int i = col; i < text.at(row).size(); i++)
	line.push_back(text.at(row).at(i));
	text.at(row).resize(col);

	text.insert(text.begin() + row + 1, line);
}else{
	text.at(row).insert(text.at(row).begin() + col, c);
}

right();

}

void remove(){
	if(row == 0 && col == 0) return;
	left();

if(col < text.at(row).size()) {
	text.at(row).erase(text.at(row).begin() + col); 
	} else {
		for(unsigned int i = 0; i < text.at(row + 1).size(); i++)
			text.at(row).push_back(text.at(row + 1).at(i));
		text.erase(text.begin() + row + 1); 
	}
}

int getch() {
	struct termios old;
	tcgetattr(0, &old);
	struct termios current = old;
	current.c_lflag &= ~ICANON;
	current.c_lflag &= ~ECHO; 
	tcsetattr(0, TCSANOW, &current); 
	int ch = getchar();
	tcsetattr(0, TCSANOW, &old);
	return ch;
}


void display() {
	cout << "\x1B[2J";
	cout << "\x1B[0;0f"; 
	for(unsigned int i = 0; i < text.size(); i++) {
		cout << "\x1B[K"; 
		for(unsigned int j = 0; j < text.at(i).size(); j++)
			cout << text.at(i).at(j);
		cout << "\n";
	}
	
	cout << "\x1B[K" << (command ? "command mode\n" : "insert mode\n");
	cout << "\x1B[" << row + 1 << ';' << col + 1 << 'H';
}

void go(int ch) {
	switch(ch) {
		case 'i': command = false; break; 
		case 'l': left(); break;
		case 'u': up(); break;
		case 'd': down(); break;
		case 'r': right(); break;
		
		case 'q': exit(0); break;
	}
}
int main() {
	text.push_back(vector<char>()); 
	
	for(;;) {
		display();
		int ch = getch();
		if(command) 
			go(ch);
		else if(ch == '\e')
			command = true;
		else if(ch == 127) 
			remove();
		else
			insert(ch);
	}
}
