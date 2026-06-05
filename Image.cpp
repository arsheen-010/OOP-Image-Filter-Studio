#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.h"
#include <iostream>
using namespace std;

Image::Image() {
    width = 0;
    height = 0;
    grid = NULL;
}

Image::Image(int w, int h) {
    width = w;
    height = h;
    grid = new Pixel*[height];
    for (int i = 0; i < height; i++)
        grid[i] = new Pixel[width];
}

Image::Image(const Image& other) {
    width = other.width;
    height = other.height;
    grid = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Pixel[width];
        for (int j = 0; j < width; j++)
            grid[i][j] = other.grid[i][j];
    }
}

Image& Image::operator=(const Image& other) {
    if (this == &other) return *this;
    for (int i = 0; i < height; i++)
        delete[] grid[i];
    delete[] grid;

    width = other.width;
    height = other.height;
    grid = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Pixel[width];
        for (int j = 0; j < width; j++)
            grid[i][j] = other.grid[i][j];
    }
    return *this;
}

Image::~Image() {
    for (int i = 0; i < height; i++)
        delete[] grid[i];
    delete[] grid;
}

int Image::getWidth()  { return width; }
int Image::getHeight() { return height; }

Pixel& Image::at(int r, int c) { return grid[r][c]; }

void Image::fill() {
    for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
        grid[i][j].set(i * 20, j * 20, (i + j) * 20);
}

void Image::display() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            cout << grid[i][j].brightness() << " ";
        cout << endl;
    }
}

void Image::displayASCII() {
    cout << "\nASCII " << width << " x " << height << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            cout << grid[i][j].toASCII();
        cout << "\n";
    }
    cout << "Image size: " << width << " x " << height
         << " total pixels: " << width * height << "\n";
}

void Image::saveToFile(const string& path) {
    int totalBytes = height * width * 3;
    unsigned char* buf = new unsigned char[totalBytes];
    for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {   //flat array
        int idx = (i * width + j) * 3;
        buf[idx]   = (unsigned char)grid[i][j].getR();
        buf[idx+1] = (unsigned char)grid[i][j].getG();
        buf[idx+2] = (unsigned char)grid[i][j].getB();
    }
    cout << "Top-left pixel RGB: (" << (int)buf[0] << ", " << (int)buf[1] << ", " << (int)buf[2] << ")\n";
    int result = stbi_write_png(path.c_str(), width, height, 3, buf, width * 3);
    delete[] buf;
    if (result != 0)
        cout << "Image saved successfully to " << path << "\n";
    else
        cout << " Failed to save image\n";
}
