#ifndef Image_h
#define Image_h

#include <iostream>
#include <string>
#include "Pixel.h"
using namespace std;

class FilterSession; 
class Image {
private:
    int width;
    int height;
    Pixel** grid;

public:
    Image();
    Image(int w, int h);
    Image(const Image& other);
    Image& operator=(const Image& other);
    ~Image();

    int getWidth();
    int getHeight();
    Pixel& at(int r, int c);

    void fill();
    void display();
    void displayASCII();
    void saveToFile(const string& path);

    friend class FilterSession;
};

#endif
