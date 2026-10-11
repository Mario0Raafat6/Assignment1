#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
int main(){
    string oldimage, newimage;
    cout << "enter oldimage name";
    cin >> oldimage;
    Image img(oldimage);
    for (int i=0; i< img.width; ++i){
        for(int j=0; j< img.height; ++j){
            for(int k=0; k< img.channels; ++k){
                img(i,j,k)= 255 - img(i,j,k);
            }
        }
    }
    cout << "enter new image name";
    cin >> newimage;
    img.saveImage(newimage);
    return 0;
}