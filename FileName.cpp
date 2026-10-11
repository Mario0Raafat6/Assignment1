#include <iostream>
#include "Image_Class.h"
using namespace std;

void frame (Image& img) {
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
void mergeImages(Image& img1, Image& img2) {
	for (int i = 0; i < img1.width; i++) {
		for (int j = 0; j < img1.height; j++) {
			for (int c = 0; c < 3; c++) {
				int pixel1 = img1(i, j, c);
				int pixel2 = img2(i, j, c);

				img1(i, j, c) = (pixel1 + pixel2) / 2;
			}
		}
	}
}
void wanoSunlightFix(Image& img) {
	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < img.height; j++) {
			for (int c = 0; c < 3; c++) {
				int colorValue = img(i, j, c) + 30;

				if (colorValue > 255) {
					colorValue = 255;
				}

				img(i, j, c) = colorValue;
			}
		}
	}
}
int main() {
	Image img("mario.bmp");
	frame(img);
	img.saveImage("mario_frame.bmp");
	cout << "Saved mario_frame.bmp\n";
}