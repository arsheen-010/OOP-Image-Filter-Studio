#ifndef Pixel_h
#define Pixel_h

#include <iostream>
using namespace std;

class Pixel {
private:
    int R, G, B;

public:
    Pixel();
    Pixel(int r, int g, int b);

    static int clamp(int val);
    void set(int r, int g, int b);

    int getR();
    int getG();
    int getB();
    int brightness();
    char toASCII();

    Pixel operator+(Pixel p);
    friend ostream& operator<<(ostream& out, Pixel& p);
};

#endif
