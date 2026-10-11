// Daniel Guirguis Ayoub  20250218 (gray scale )
// Kirolos Tadros Mikhael 20250501 (Rotate and Black and White)
// Maria Samy 20250517 (Invert and Brighten/Darken)
// Mario Raafat Hanna 20250899 ( Frame and Blur)
#include <iostream>
#include "Image_Class.h"
using namespace std;

int main() {
	string filename;
	cout << "Enter file name";
	cin >> filename;
	Image img(filename);
	cout << "Choose what u want to do with the image\n";
	cout << "1. Frame\n";
	cout << "2. Blur\n";
	cout << "3. Invert\n";
	cout << "4. Rotate\n";
	cout << "5. Black and White\n";
	cout << "6. Gray Scale\n";
	cout << "7. Brighten or Darken\n";
	cout << "8. Flip\n";
	int choice;
	cin >> choice;

	if (choice == 1)
	 {
		for (int i = 0; i < img.width; i++) {
			for (int j = 0; j < (img.height * 0.01); j++) {
				img(i, j, 0) = 173; 
				img(i, j, 1) = 216; 
				img(i, j, 2) = 230; 
			}
		}
		for (int i = 0; i < (img.width * 0.01); i++) {
			for (int j = 0; j < img.height; j++) {
				img(i, j, 0) = 173; 
				img(i, j, 1) = 216; 
				img(i, j, 2) = 230; 
			}
		}
		for (int i = 0; i < img.width; i++) {
			for (int j = img.height - (img.height * 0.01); j < img.height; j++) {
				img(i, j, 0) = 173; 
				img(i, j, 1) = 216; 
				img(i, j, 2) = 230; 
			}
		}
		for (int i = img.width - (img.width * 0.01); i < img.width; i++) {
			for (int j = 0; j < img.height; j++) {
				img(i, j, 0) = 173; 
				img(i, j, 1) = 216; 
				img(i, j, 2) = 230; 
			}
		}
		
	}
	else if (choice == 2) {
		cout << "Enter the number of times you want to blur the image (1-10): ";
		int n;
		cin >> n;
		if (n > 0 && n <= 10) {
			cout << "Blurring the image " << n << " times..." << endl;
	
		for (n ; n > 0; n--) {
			
			for (int i = 1; i < img.width - 1; i++) {
				for (int j = 1; j < img.height - 1; j++) {
					for (int k = 0; k < 3;k++) {
						img(i, j, k) = (img(i + 1, j, k) + img(i - 1, j, k) + img(i, j + 1, k) + img(i, j - 1, k)) / 4;
					}
				}
			}
		}
		
		}
		else {
			cout << "Invalid number of times. Please enter a number between 1 and 10." << endl;
		}
	}
	else if (choice == 3) {
		cout << "Inverting the image..." << endl;

		for (int i = 0; i < img.width; ++i) {
			for (int j = 0; j < img.height; ++j) {
				for (int k = 0; k < img.channels; ++k) {
					img(i, j, k) = 255 - img(i, j, k);
				}

			}
		}
	}
	else if (choice == 4) {
		cout << "select the degree of rotation (90, 180, 270): ";
		int rotation;
		cin >> rotation;
		if (rotation == 90) {
			Image img90(img.height, img.width);
			for (int y = 0; y < img.height; y++) {
				for (int x = 0; x < img.width; x++) {
					for (int c = 0; c < 3; c++) {
						int newX = img.height - 1 - y;
						int newY = x;
						img90.setPixel(newX, newY, c, img.getPixel(x, y, c));
					}
				}
			}
			img = img90;
		}

		else if (rotation == 180) {
			Image img180(img.width, img.height);
			for (int y = 0; y < img.height; y++) {
				for (int x = 0; x < img.width; x++) {
					for (int c = 0; c < 3; c++) {
						int newX = img.width - 1 - x;
						int newY = img.height - 1 - y;
						img180.setPixel(newX, newY, c, img.getPixel(x, y, c));
					}
				}
			}
			img = img180;
		}
		else if (rotation == 270) {

			Image img270(img.height, img.width);
			for (int y = 0; y < img.height; y++) {
				for (int x = 0; x < img.width; x++) {
					for (int c = 0; c < 3; c++) {
						int newX = y;
						int newY = img.width - 1 - x;
						img270.setPixel(newX, newY, c, img.getPixel(x, y, c));
					}
				}
			}
			img = img270;
		}
	}
	else if (choice == 5) {
		int threshold = 127;

		for (int y = 0; y < img.height; y++) {
			for (int x = 0; x < img.width; x++) {

				unsigned char r = img.getPixel(x, y, 0);
				unsigned char g = img.getPixel(x, y, 1);
				unsigned char b = img.getPixel(x, y, 2);

				unsigned char avg = (r + g + b) / 3;
				unsigned char bwValue = (avg >= threshold) ? 255 : 0;

				img.setPixel(x, y, 0, bwValue);
				img.setPixel(x, y, 1, bwValue);
				img.setPixel(x, y, 2, bwValue);
			}
		}
	}
	else if (choice == 6) {
		for (int i = 0; i < img.width; ++i) {
			for (int j = 0; j < img.height; ++j) {
				unsigned  int avg = 0; 

				for (int k = 0; k < 3; ++k) {
					avg += img(i, j, k);
				}

				avg /= 3; 

				
				img(i, j, 0) = avg;
				img(i, j, 1) = avg;
				img(i, j, 2) = avg;
			}
		}
	}
	else if (choice == 7) {
		int BorD;
		cout << "enter choice 1 brighten or 2 darken?";
		cin >> BorD;
		switch (BorD) {
		case 1: {
			for (int i = 0; i < img.width;++i) {
				for (int j = 0; j < img.height;++j) {
					for (int k = 0; k < img.channels;++k) {
						int imagevalue = img(i, j, k) + (255 - img(i, j, k)) * 0.5;
						img(i, j, k) = imagevalue;
					}
				}
			}
			cout << "image brightened\n";
			break;
		}
		case 2: {
			for (int i = 0; i < img.width;++i) {
				for (int j = 0; j < img.height;++j) {
					for (int k = 0; k < img.channels;++k) {
						int imagevalue = img(i, j, k) * 0.5;
						img(i, j, k) = imagevalue;
					}
				}
			}
			cout << "image darkend\n";
			break;
		}
		default: {
			cout << "invalid choice\n";
			return 0;
		}
		}
	}
	else if (choice == 8) {
		int direction;
		cout << "Enter 1 for horizontal flip or 2 for vertical flip: ";
		cin >> direction;
		if (direction == 1)
		{
		// Horizontal flip
		for (int i = 0; i < img.width / 2; i++)
		{
			for (int j = 0; j < img.height; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					int temp = img(i, j, k);
					img(i, j, k) = img(img.width - 1 - i, j, k);
					img(img.width - 1 - i, j, k) = temp;
				}
			}
		}
	}
	else if (direction == 2)
	{
		// Vertical flip
		for (int i = 0; i < img.width; i++)
		{
			for (int j = 0; j < img.height / 2; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					int temp = img(i, j, k);
					img(i, j, k) = img(i, img.height - 1 - j, k);
					img(i, img.height - 1 - j, k) = temp;
				}
			}
		}
		}
	}
	else {
		cout << "Invalid choice\n";
	}
	
	cout << "Enter file name to save the image"<< endl;
		cout << "Enter file extension (png, bmp, tga, jpg): ";
		cin >> filename;
		img.saveImage(filename);
		if (img.saveImage(filename)) {
			cout << "Image saved successfully!" << endl;
		}
		else {
			cout << "Error saving image." << endl;
		}
		
}