#ifndef MATREAD_H
#define MATREAD_H
#include "headers.h"

class Matread {
public:
	void connect(Mat& M) {
		input = (unsigned char*)(M.data);
	}
	Matread(Mat& M) {
		width = M.cols;
		input = (unsigned char*)(M.data);
	}
	uchar& get(int x, int y, int ch) {
		return input[3 * width * x + y * 3 + ch];
	}
	unsigned char *input;
	int width;
};
#endif