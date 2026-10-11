#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

#pragma pack(push, 1)
struct BMPHeader {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
};

struct DIBHeader {
    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int compression;
    unsigned int image_size;
    int x_pixels_per_meter;
    int y_pixels_per_meter;
    unsigned int colors_used;
    unsigned int important_colors;
};
#pragma pack(pop)

int main() {
    string inputFile = "input.bmp";
    string outputFile = "wano_tv_output.bmp";

    ifstream in(inputFile.c_str(), ios::binary);
    if (!in.is_open()) {
        cout << "Error: Could not open input file!" << endl;
        return 1;
    }

    BMPHeader header;
    DIBHeader dib;

    in.read((char*)&header, sizeof(header));
    in.read((char*)&dib, sizeof(dib));

    if (dib.bit_count != 24) {
        cout << "Please use a 24-bit BMP image." << endl;
        return 1;
    }

    int width = dib.width;
    int height = abs(dib.height);
    int padding = (4 - (width * 3) % 4) % 4;

    vector<vector<unsigned char> > r_pixels(height, vector<unsigned char>(width));
    vector<vector<unsigned char> > g_pixels(height, vector<unsigned char>(width));
    vector<vector<unsigned char> > b_pixels(height, vector<unsigned char>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char b, g, r;
            in.read((char*)&b, 1);
            in.read((char*)&g, 1);
            in.read((char*)&r, 1);
            r_pixels[i][j] = r;
            g_pixels[i][j] = g;
            b_pixels[i][j] = b;
        }
        in.seekg(padding, ios::cur);
    }
    in.close();

    int scanlineInterval = 2;
    float scanlineDarkness = 0.5f;
    int noiseAmount = 12;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int noise = rand() % (2 * noiseAmount + 1) - noiseAmount;
            
            int r = max(0, min(255, (int)r_pixels[i][j] + noise));
            int g = max(0, min(255, (int)g_pixels[i][j] + noise));
            int b = max(0, min(255, (int)b_pixels[i][j] + noise));

            if (i % scanlineInterval == 0) {
                r = (int)(r * scanlineDarkness);
                g = (int)(g * scanlineDarkness);
                b = (int)(b * scanlineDarkness);
            }

            r_pixels[i][j] = (unsigned char)r;
            g_pixels[i][j] = (unsigned char)g;
            b_pixels[i][j] = (unsigned char)b;
        }
    }

    ofstream out(outputFile.c_str(), ios::binary);
    out.write((char*)&header, sizeof(header));
    out.write((char*)&dib, sizeof(dib));

    unsigned char padByte = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char r = r_pixels[i][j];
            unsigned char g = g_pixels[i][j];
            unsigned char b = b_pixels[i][j];
            out.write((char*)&b, 1);
            out.write((char*)&g, 1);
            out.write((char*)&r, 1);
        }
        for (int p = 0; p < padding; p++) {
            out.write((char*)&padByte, 1);
        }
    }
    out.close();

    cout << "Wano TV filter applied successfully! Saved to " << outputFile << endl;
    return 0;
}