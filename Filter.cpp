#include "Filter.h"
#include <iostream>
using namespace std;
string Grayscale::getName() const { 
return 
"Grayscale"; 
}
void Grayscale::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        int avg = p.brightness();
        p.set(avg, avg, avg);
    }
    cout << "grayscale applied\n";
    img.displayASCII();
}
string Invert::getName() const { 
return "Invert";
 }
void Invert::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        p.set(255 - p.getR(), 255 - p.getG(), 255 - p.getB());
    }
    cout << "invert applied\n";
    img.displayASCII();
}
Brightness::Brightness(int v) { value = v; }
string Brightness::getName() const { 
return "Brightness(" + to_string(value) + ")"; }
void Brightness::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        p.set(p.getR() + value, p.getG() + value, p.getB() + value);
    }
    cout << "brightness applied\n";
    img.displayASCII();
}
string ContrastStretch::getName() const { return "ContrastStretch"; }
void ContrastStretch::apply(Image& img) {
    int minV = 255, maxV = 0;
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        int v = img.at(i, j).brightness();
        if (v < minV) minV = v;
        if (v > maxV) maxV = v;
    }
    int range = maxV - minV;
    if (range == 0) { cout << " no range to stretch.\n"; return; }
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        int r = (p.getR() - minV) * 255 / range;
        int g = (p.getG() - minV) * 255 / range;
        int b = (p.getB() - minV) * 255 / range;
        p.set(r, g, b);
    }
    cout << "contrastStretch applied\n";
    img.displayASCII();
}
string RedChannel::getName() const { 
return "RedChannel"; }
void RedChannel::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        p.set(p.getR(), 0, 0);
    }
    cout << "redChannel applied\n";
}
string GreenChannel::getName() const { 
return "GreenChannel"; }
void GreenChannel::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        p.set(0, p.getG(), 0);
    }
    cout << "greenChannel applied\n";
}

// ── BlueChannel ──
string BlueChannel::getName() const { return "BlueChannel"; }
void BlueChannel::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel& p = img.at(i, j);
        p.set(0, 0, p.getB());
    }
    cout << "BlueChannel applied\n";
}
string FlipH::getName() const {
 return "FlipHorizontal"; }
void FlipH::apply(Image& img) {
    int w = img.getWidth();
    for (int i = 0; i < img.getHeight(); i++)
    for (int j = 0; j < w / 2; j++) {
        Pixel temp = img.at(i, j);
        img.at(i, j) = img.at(i, w - 1 - j);
        img.at(i, w - 1 - j) = temp;
    }
    cout << "flip horizontal \n";
    img.displayASCII();
}
string FlipV::getName() const { return "FlipVertical"; }
void FlipV::apply(Image& img) {
    int h = img.getHeight();
    for (int i = 0; i < h / 2; i++)
    for (int j = 0; j < img.getWidth(); j++) {
        Pixel temp = img.at(i, j);
        img.at(i, j) = img.at(h - 1 - i, j);
        img.at(h - 1 - i, j) = temp;
    }
    cout << "Flip vertical  \n";
    img.displayASCII();
}
string BoxBlur::getName() const {
 return "BoxBlur"; }
void BoxBlur::apply(Image& img) {
    int h = img.getHeight();
    int w = img.getWidth();
    Image copy = img;
    for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
        int sumR = 0, sumG = 0, sumB = 0;
        int count = 0;
        for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x >= 0 && x < h && y >= 0 && y < w) {
                Pixel p = copy.at(x, y);
                sumR += p.getR();
                sumG += p.getG();
                sumB += p.getB();
                count++;
            }
        }}
        img.at(i, j).set(sumR / count, sumG / count, sumB / count);
    }}
    cout << "Box Blur \n";
    img.displayASCII();
}
Filter* makeFilter(const string& fid, int bval) {
    if (fid == "01") return new Grayscale();
    if (fid == "02") return new Invert();
    if (fid == "03") return new Brightness(bval);
    if (fid == "04") return new ContrastStretch();
    if (fid == "05") return new RedChannel();
    if (fid == "06") return new GreenChannel();
    if (fid == "07") return new BlueChannel();
    if (fid == "08") return new BoxBlur();
    if (fid == "09") return new FlipH();
    if (fid == "10") return new FlipV();
    return NULL;
}
