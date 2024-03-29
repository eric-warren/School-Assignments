#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

const unsigned int WIDTH = 32, HEIGHT = 20;
const char brush = '*';

void drawVertical(int d, unsigned *posX, unsigned *posY, char img[][HEIGHT]);
void drawHorizontal(int d, unsigned *posX, unsigned *posY, char img[][HEIGHT]);

void drawImg(char[][HEIGHT], ostream&);


int main(int argc, const char* argv[])
{
	char image[WIDTH][HEIGHT];
	unsigned posX = 0, posY = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			image[j][i] = ' ';
		}
	}

	ifstream fin;
	char ifilename[] = "instructions.txt";
	fin.open(ifilename);
	char arg[4];
	while (!fin.eof()) {
		
		fin >> arg;
		
		if (strcmp(arg,"SET") == 0) {
			unsigned x, y;
			fin >> x >> y;
			if (x >= WIDTH) x = WIDTH-1;
			if (y >= HEIGHT) y = HEIGHT - 1;
			posX = x;
			posY = y;
		} else if (strcmp(arg,"DRV") == 0) {
			int d;
			fin >> d;
			drawVertical(d, &posX, &posY, image);

		}
		else if (strcmp(arg, "DRH") == 0) {
			int d;
			fin >> d;
			drawHorizontal(d, &posX, &posY, image);
		}
	}
		


	fin.close();
	fin.clear();

	ofstream fout;
	char ofilename[] = "art.txt";
	fout.open(ofilename);
	drawImg(image, fout);
	fout.close();

    return 0;
}

void drawVertical(int d, unsigned *posX,unsigned *posY, char img[][HEIGHT]) {
	int dir = d > 0 ? 1 : -1;
	d = abs(d);
	while (d > 0 && *posY < HEIGHT && *posY >= 0) {
		img[*posX][(*posY)+=dir] = '*';
		d--;
	}
}

void drawHorizontal(int d, unsigned *posX, unsigned *posY, char img[][HEIGHT]) {
	int dir = d > 0 ? 1 : -1;
	d = abs(d);
	while (d > 0 && *posX < WIDTH && *posX >= 0) {
		img[(*posX)+=dir][*posY] = '*';
		d--;
	}
}

void drawImg(char img[][HEIGHT], ostream& out) {

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			out << img[j][i];
		}
		out << endl;
	}
}


