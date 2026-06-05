#ifndef Filter_h
#define Filter_h
#include <string>
#include "Image.h"
using namespace std;
class Filter {
public:
    virtual void apply(Image& img) = 0;
    virtual string getName() const = 0;
    virtual ~Filter() {}
};

class Grayscale : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class Invert : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class Brightness : public Filter {
private:
    int value;
public:
    Brightness(int v);
    string getName() const override;
    void apply(Image& img) override;
};

class ContrastStretch : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class RedChannel : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class GreenChannel : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class BlueChannel : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class FlipH : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class FlipV : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

class BoxBlur : public Filter {
public:
    string getName() const override;
    void apply(Image& img) override;
};

Filter* makeFilter(const string& fid, int bval);

#endif
