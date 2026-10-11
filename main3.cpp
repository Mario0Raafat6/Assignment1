#include "Image_Class.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    string filename;
    cout << "enter image name";
    cin >> filename;
    Image img(filename);
    int x,y,w,h;
    cout << "enter x,y,w,h";
    cin >> x >> y >> w >> h;
    Image crop(w,h);
    for (int i=0; i<w; i++){
        for (int j=0; j<h; j++){
            for (int c=0; c<3; c++){
                crop(i,j,c)=img( x+i , y+j , c);
            }
        }
    }
    cout << "enter new image name";
    cin >> filename;
    crop.saveImage(filename);
    return 0;
}