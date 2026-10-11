#include <iostream>
#include <cmath>
#include <vector>
#include "Image_Class.h"

using namespace std;

int main() {
    string inputFile = "input.bmp";
    string outputFile = "output_edges.bmp";

    Image img;
    try {
        img.loadNewImage(inputFile);
    } catch (const exception& e) {
        cerr << "Error loading image: " << e.what() << endl;
        return 1;
    }

    int width = img.width;
    int height = img.height;

    vector<vector<int> > gray(height, vector<int>(width));

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

    try {
        outputImg.saveImage(outputFile);
        cout << "Edge Detection completed successfully! Saved to " << outputFile << endl;
    } catch (const exception& e) {
        cerr << "Error saving image: " << e.what() << endl;
        return 1;
    }

    return 0;
}
