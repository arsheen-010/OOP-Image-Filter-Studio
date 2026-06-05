#include "Pixel.h"

Pixel::Pixel() { R = G = B = 0; }

Pixel::Pixel(int r, int g, int b) { set(r, g, b); }

int Pixel::clamp(int val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return val;
}

void Pixel::set(int r, int g, int b) {
    R = clamp(r);
    G = clamp(g);
    B = clamp(b);
}

int Pixel::getR() { return R; }
int Pixel::getG() { return G; }
int Pixel::getB() { return B; }

int Pixel::brightness() { return (R + G + B) / 3; }

char Pixel::toASCII() {
    int br = brightness();
    if (br >= 0   && br < 64)  return ' ';
    if (br >= 64  && br < 80)  return '.';
    if (br >= 80  && br < 120) return ':';
    if (br >= 120 && br < 128) return '=';
    if (br >= 128 && br < 150) return '+';
    if (br >= 150 && br < 192) return '*';
    if (br >= 192 && br < 200) return '#';
    return '@';
}

Pixel Pixel::operator+(Pixel p) {
    return Pixel(R + p.R, G + p.G, B + p.B);
}

ostream& operator<<(ostream& out, Pixel& p) {
    out << " the: " << p.R << "," << p.G << "," << p.B << " ";
    return out;
}
