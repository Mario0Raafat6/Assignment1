#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

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
    string outputFile = "output_edges.bmp";

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

    vector<vector<int> > gray(height, vector<int>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char b, g, r;
            in.read((char*)&b, 1);
            in.read((char*)&g, 1);
            in.read((char*)&r, 1);

            gray[i][j] = (int)(0.299 * r + 0.587 * g + 0.114 * b);
        }
        in.seekg(padding, ios::cur);
    }
    in.close();

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

    vector<vector<int> > result(height, vector<int>(width, 0));

    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            int sumX = 0;
            int sumY = 0;

            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sumX += gray[i + k][j + l] * gx[k + 1][l + 1];
                    sumY += gray[i + k][j + l] * gy[k + 1][l + 1];
                }
            }

            int val = sqrt((double)(sumX * sumX + sumY * sumY));
            if (val > 255) val = 255;
            result[i][j] = val;
        }
    }

    ofstream out(outputFile.c_str(), ios::binary);
    out.write((char*)&header, sizeof(header));
    out.write((char*)&dib, sizeof(dib));

    unsigned char padByte = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char val = (unsigned char)result[i][j];
            out.write((char*)&val, 1);
            out.write((char*)&val, 1);
            out.write((char*)&val, 1);
        }
        for (int p = 0; p < padding; p++) {
            out.write((char*)&padByte, 1);
        }
    }
    out.close();

    cout << "Edge Detection completed successfully! Saved to " << outputFile << endl;
    return 0;
}