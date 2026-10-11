#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Image_Class.h"

using namespace std;

int main() {
    string inputFile = "input.bmp";
    string outputFile = "wano_tv_output.bmp";

    Image img;
    try {
        img.loadNewImage(inputFile);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    Image outputImg(img.width, img.height);

    int scanlineInterval = 2;
    float scanlineDarkness = 0.5f;
    int noiseAmount = 12;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int noise = rand() % (2 * noiseAmount + 1) - noiseAmount;

            for (int c = 0; c < 3; c++) {
                int val = (int)img.getPixel(x, y, c) + noise;
                val = max(0, min(255, val));

                if (y % scanlineInterval == 0) {
                    val = (int)(val * scanlineDarkness);
                }

                outputImg.setPixel(x, y, c, (unsigned char)val);
            }
        }
    }

    try {
        outputImg.saveImage(outputFile);
        cout << "Wano TV filter applied successfully! Saved to " << outputFile << endl;
    } catch (const exception& e) {
        cerr << "Error saving image: " << e.what() << endl;
        return 1;
    }

    return 0;
}
