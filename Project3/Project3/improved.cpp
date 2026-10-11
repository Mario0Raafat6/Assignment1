#include <iostream>
#include "Image_Class.h"
using namespace std;

void frame(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height * 0.01; j++) {
            img(i, j, 0) = 173;
            img(i, j, 1) = 216;
            img(i, j, 2) = 230;
        }
    }

    for (int i = 0; i < img.width * 0.01; i++) {
        for (int j = 0; j < img.height; j++) {
            img(i, j, 0) = 173;
            img(i, j, 1) = 216;
            img(i, j, 2) = 230;
        }
    }

    for (int i = 0; i < img.width; i++) {
        for (int j = img.height - img.height * 0.01; j < img.height; j++) {
            img(i, j, 0) = 173;
            img(i, j, 1) = 216;
            img(i, j, 2) = 230;
        }
    }

    for (int i = img.width - img.width * 0.01; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            img(i, j, 0) = 173;
            img(i, j, 1) = 216;
            img(i, j, 2) = 230;
        }
    }
}

void blur(Image& img) {
    cout << "Enter the number of times you want to blur the image (1-10): ";
    int n;
    cin >> n;

    if (n > 0 && n <= 10) {
        for (int times = 0; times < n; times++) {
            for (int i = 1; i < img.width - 1; i++) {
                for (int j = 1; j < img.height - 1; j++) {
                    for (int k = 0; k < 3; k++) {
                        img(i, j, k) =
                            (img(i + 1, j, k) +
                                img(i - 1, j, k) +
                                img(i, j + 1, k) +
                                img(i, j - 1, k)) / 4;
                    }
                }
            }
        }
    }
    else {
        cout << "Invalid number of times. Please enter a number between 1 and 10." << endl;
    }
}

void invert(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

void rotate(Image& img) {
    cout << "Select the degree of rotation (90, 180, 270): ";
    int rotation;
    cin >> rotation;

    if (rotation == 90) {
        Image rotated(img.height, img.width);

        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int c = 0; c < 3; c++) {
                    int newX = img.height - 1 - y;
                    int newY = x;
                    rotated.setPixel(newX, newY, c, img.getPixel(x, y, c));
                }
            }
        }

        img = rotated;
    }
    else if (rotation == 180) {
        Image rotated(img.width, img.height);

        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int c = 0; c < 3; c++) {
                    int newX = img.width - 1 - x;
                    int newY = img.height - 1 - y;
                    rotated.setPixel(newX, newY, c, img.getPixel(x, y, c));
                }
            }
        }

        img = rotated;
    }
    else if (rotation == 270) {
        Image rotated(img.height, img.width);

        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int c = 0; c < 3; c++) {
                    int newX = y;
                    int newY = img.width - 1 - x;
                    rotated.setPixel(newX, newY, c, img.getPixel(x, y, c));
                }
            }
        }

        img = rotated;
    }
    else {
        cout << "Invalid rotation angle." << endl;
    }
}

void blackAndWhite(Image& img) {
    int threshold = 127;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            unsigned char avg = (r + g + b) / 3;
            unsigned char value = (avg >= threshold) ? 255 : 0;

            img.setPixel(x, y, 0, value);
            img.setPixel(x, y, 1, value);
            img.setPixel(x, y, 2, value);
        }
    }
}

void grayScale(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; k++) {
                avg += img(i, j, k);
            }

            avg /= 3;

            img(i, j, 0) = avg;
            img(i, j, 1) = avg;
            img(i, j, 2) = avg;
        }
    }
}

void brightenOrDarken(Image& img) {
    cout << "Enter 1 to brighten or 2 to darken: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {
                for (int k = 0; k < img.channels; k++) {
                    int value = img(i, j, k) +
                        (255 - img(i, j, k)) * 0.5;
                    img(i, j, k) = value;
                }
            }
        }
        cout << "Image brightened." << endl;
    }
    else if (choice == 2) {
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {
                for (int k = 0; k < img.channels; k++) {
                    int value = img(i, j, k) * 0.5;
                    img(i, j, k) = value;
                }
            }
        }
        cout << "Image darkened." << endl;
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

void flip(Image& img) {
    cout << "Enter 1 for horizontal flip or 2 for vertical flip: ";
    int direction;
    cin >> direction;

    if (direction == 1) {
        for (int i = 0; i < img.width / 2; i++) {
            for (int j = 0; j < img.height; j++) {
                for (int k = 0; k < 3; k++) {
                    int temp = img(i, j, k);
                    img(i, j, k) = img(img.width - 1 - i, j, k);
                    img(img.width - 1 - i, j, k) = temp;
                }
            }
        }
    }
    else if (direction == 2) {
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    int temp = img(i, j, k);
                    img(i, j, k) = img(i, img.height - 1 - j, k);
                    img(i, img.height - 1 - j, k) = temp;
                }
            }
        }
    }
    else {
        cout << "Invalid flip direction." << endl;
    }
}
void crop(Image& img) {
    int x, y, w, h;
    cout << "enter x,y,w,h";
    cin >> x >> y >> w >> h;
    Image crop(w, h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int c = 0; c < 3; c++) {
                crop(i, j, c) = img(x + i, y + j, c);
            }
        }
    }
}
void purple(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            int r = img(i, j, 0) * 1.1;
            int g = img(i, j, 1) * 0.7;
            int b = img(i, j, 2) * 1.2;
            img(i, j, 0) = (r > 255) ? 255 : r;
            img(i, j, 1) = g;
            img(i, j, 2) = (b > 255) ? 255 : b;
        }
    }
}
void resize (Image& img){}


int main() {
    string filename;

    cout << "Enter file name: ";
    cin >> filename;

    Image img(filename);

    cout << "Choose what you want to do with the image\n";
    cout << "1. Frame\n";
    cout << "2. Blur\n";
    cout << "3. Invert\n";
    cout << "4. Rotate\n";
    cout << "5. Black and White\n";
    cout << "6. Gray Scale\n";
    cout << "7. Brighten or Darken\n";
    cout << "8. Flip\n";
	cout << "9. Crop\n";
	cout << "10. Purple\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        frame(img);
    }
    else if (choice == 2) {
        blur(img);
    }
    else if (choice == 3) {
        invert(img);
    }
    else if (choice == 4) {
        rotate(img);
    }
    else if (choice == 5) {
        blackAndWhite(img);
    }
    else if (choice == 6) {
        grayScale(img);
    }
    else if (choice == 7) {
        brightenOrDarken(img);
    }
    else if (choice == 8) {
        flip(img);
    }
	else if (choice == 9) {
		crop(img);
	}
	else if (choice == 10) {
		purple(img);
	}
    else {
        cout << "Invalid choice." << endl;
        return 0;
    }

    cout << "Enter file name to save the image (with extension): ";
    cin >> filename;

    if (img.saveImage(filename)) {
        cout << "Image saved successfully!" << endl;
    }
    else {
        cout << "Error saving image." << endl;
    }

    return 0;
}