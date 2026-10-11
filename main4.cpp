#include <iostream>
#include "Image_Class.h"
using namespace std;
int main(){
    string ImageName, newImageName;
    cout << "enter Image name";
    cin >> ImageName;
    Image img(ImageName);
    for (int i=0; i< img.width; i++){
        for (int j=0; j< img.height; j++){
            int r = img(i,j,0)*1.1;
            int g = img(i,j,1)*0.7;
            int b = img(i,j,2)*1.2;
            img(i,j,0)= (r>255)? 255: r;
            img(i,j,1)=g;
            img(i,j,2)= (b>255)? 255: b;
        }
    }
    cout << "enter new image name";
    cin >> newImageName;
    img.saveImage(newImageName);
    return 0;
}