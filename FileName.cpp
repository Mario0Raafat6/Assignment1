#include <iostream>
#include "Image_class.h"
using namespace std;
void frame(Image img) {
	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < 10; j++) {
			img(i, j, 0) = 0;
			img(i, j, 1) = 0;
			img(i, j, 2) = 0;

		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < img.height; j++) {
			img(i, j, 0) = 0;
			img(i, j, 1) = 0;
			img(i, j, 2) = 0;
		}
	}
	for (int i = 0; i < img.width; i++) {
		for (int j = img.height - 10; j < img.height; j++) {
			img(i, j, 0) = 0;
			img(i, j, 1) = 0;
			img(i, j, 2) = 0;
		}
	}
	for (int i = img.width - 10; i < img.width; i++) {
		for (int j = 0; j < img.height; j++) {
			img(i, j, 0) = 0;
			img(i, j, 1) = 0;
			img(i, j, 2) = 0;
		}
	}
}

int main() {
	Image img("mario.bmp");
	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < 10; j++) {
			img(i, j, 0) = 0;
			img(i, j, 1) = 0;
			img(i, j, 2) = 0;
		}
	}
	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < img.height; j++) {
			img(i, j, 0) = 0;
			img(i, j, 1) = 0;
			img(i, j, 2) = 0;
		}
	}

	img.saveImage("mario_frame.bmp");
}
