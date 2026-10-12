/*  Daniel Guirguis Ayoub  20250218 (gray scale , flip , merge and wano sunlight)
    Kirolos Tadros Mikhael 20250501 (Rotate , Black and White , detect edges and wano tv filter)
    Maria Samy 20250517 (Invert , Brighten/Darken , crop and purple)
    Mario Raafat Hanna 20250899 ( Frame , resize, Blur and infrared ) */
#include <iostream>
#include <vector>
#include <cmath>
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
void wanotvfilter(Image& img) {
    int scanlineInterval = 2;
    float scanlineDarkness = 0.5f;
    int noiseAmount = 12;

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            int noise = rand() % (2 * noiseAmount + 1) - noiseAmount;
            for (int k = 0; k < 3; k++) {
                int val = (int)img(i, j, k) + noise;
                val = max(0, min(255, val));
              
                if (j % scanlineInterval == 0) {
                    val = (int)(val * scanlineDarkness);
                }

                img(i, j, k) = (unsigned char)val;
            }
        }
    }
    cout << "Wanotv filter applied." << endl;
}
void edgeDetection(Image& img) {
    int width = img.width;
    int height = img.height;

    vector<vector<int>> gray(height, vector<int>(width));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            gray[y][x] = (int)(0.299 * r + 0.587 * g + 0.114 * b);
        }
    }

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    Image outputImg(width, height);

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sumX += gray[y + k][x + l] * gx[k + 1][l + 1];
                    sumY += gray[y + k][x + l] * gy[k + 1][l + 1];
                }
            }

            int val = (int)sqrt((double)(sumX * sumX + sumY * sumY));
            if (val > 255) val = 255;

            unsigned char edgeVal = (unsigned char)val;
            outputImg.setPixel(x, y, 0, edgeVal);
            outputImg.setPixel(x, y, 1, edgeVal);
            outputImg.setPixel(x, y, 2, edgeVal);
        }
    }

    img = outputImg;
    cout << "Edge Detection completed successfully!" << endl;
}
void resize(Image& img) {
    int newWidth, newHeight;
    cout << "Enter new width: ";
    cin >> newWidth;
    cout << "Enter new height: ";
    cin >> newHeight;
	Image resized(newWidth, newHeight);
	for (int y = 0; y < newHeight; y++) {
		for (int x = 0; x < newWidth; x++) {
			int origX = x * img.width / newWidth;
			int origY = y * img.height / newHeight;
			for (int c = 0; c < 3; c++) {
				resized.setPixel(x, y, c, img.getPixel(origX, origY, c));
			}
		}
	}
	img = resized;
}
void infrared(Image& img) {
	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < img.height; j++) {
			int r = img(i, j, 0) * 1000;
			int g = img(i, j, 1) ;
			int b = img(i, j, 2) ;
			img(i, j, 0) = (r > 255) ? 255 : r;
			img(i, j, 1) = g;
			img(i, j, 2) = b;
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
    string filename;

    cout << "Enter file name: ";
    cin >> filename;

    Image img(filename);
    int choice;
    bool saved = false;

    do {
        cout << "\nChoose what you want to do with the image\n";
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
        cout << "11. Wanotv Filter\n";
        cout << "12. Edge Detection\n";
        cout << "13. Resize\n";
        cout << "14. Infrared\n";
        cout << "15. Merge with another image\n";
        cout << "16. Wano Sunlight Fix\n";
        cout << "17. Save Image\n";
        cout << "18. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            frame(img);
            break;

        case 2:
            blur(img);
            break;

        case 3:
            invert(img);
            break;

        case 4:
            rotate(img);
            break;

        case 5:
            blackAndWhite(img);
            break;

        case 6:
            grayScale(img);
            break;

        case 7:
            brightenOrDarken(img);
            break;

        case 8:
            flip(img);
            break;

        case 9:
            crop(img);
            break;

        case 10:
            purple(img);
            break;

        case 11:
            wanotvfilter(img);
            break;

        case 12:
            edgeDetection(img);
            break;

        case 13:
            resize(img);
            break;

        case 14:
            infrared(img);
            break;

        case 15: {
            string secondFilename;
            cout << "Enter the second image file name: ";
            cin >> secondFilename;

            Image img2(secondFilename);

            if (img.width == img2.width &&
                img.height == img2.height) {
                mergeImages(img, img2);
                cout << "Images merged successfully!\n";
            }
            else {
                cout << "Images must have the same dimensions.\n";
            }
            break;
        }

        case 16:
            wanoSunlightFix(img);
            break;

        case 17: {
            

            while (!saved) {
                cout << "Enter file name to save the image (or 0 to cancel): ";
                cin >> filename;

                if (filename == "0") {
                    cout << "Save cancelled.\n";
                    break;
                }

                if (img.saveImage(filename)) {
                    cout << "Image saved successfully!\n";
                    saved = true;
                }
                else {
                    cout << "Error saving image. Please check the file name and extension (e.g. .jpg, .png, .bmp) and try again.\n";
                }
            }
            break;
        }

        case 18:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 18 || !saved);

    return 0;
}


