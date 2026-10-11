#include <iostream>
#include "Image_Class.h"
using namespace std;
int main(){
    string oldimage;
    cout << "image name?";
    cin >> oldimage;
    Image image (oldimage);
    int choice;
    cout << "enter choice 1 or 2?";
    cin >> choice;
    switch (choice){
       case 1:{
        for(int i=0; i<image.width;++i){
            for(int j=0; j<image.height;++j){
                for(int k=0; k<image.channels;++k){
                    int imagevalue= image(i,j,k) + (255 - image(i,j,k))*0.5;
                    image(i,j,k)=imagevalue;
                }
            }
        }
        cout<< "image brightened\n";
        break;
    } 
       case 2:{
        for(int i=0; i<image.width;++i){
            for(int j=0; j<image.height;++j){
                for(int k=0; k<image.channels;++k){
                    int imagevalue= image(i,j,k)*0.5;
                    image(i,j,k)= imagevalue;
                }
            }
        }
        cout << "image darkend\n";
        break;
    }
    default:{
        cout<<"invalid choice\n";
        return 0;
    }
    }
    string newimage;
    cout << "enter image name to save";
    cin >> newimage;
    image.saveImage(newimage);
    return 0;
}
