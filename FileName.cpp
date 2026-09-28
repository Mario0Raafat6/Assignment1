#include <iostream>
#include "Image_class.h"
using namespace std;

int main() {
	Image img("mario.bmp");
	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < img.height; j++) {
			for (int k = 0; k < 3; k++) {
				int lol = img(i, j, 0) + img(i, j, 1) + img(i, j, 2);
				img(i, j, k) = lol / 3;
			}
		}

	}
	img.saveImage("mario_grayscale.bmp");
}