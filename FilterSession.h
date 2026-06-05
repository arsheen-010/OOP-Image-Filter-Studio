#ifndef Filtersession_h
#define Filtersession_h
#include <vector>
#include <string>
#include "Filter.h"
#include "Image.h"
using namespace std;

class FilterSession {
private:
    vector<Filter*> filters;
    vector<string> appliedNames;

public:
    void addFilter(Filter* f);
    void run(Image& img);
    void showPixelDirect(Image& img, int r, int c);
    string getAppliedNames();
    ~FilterSession();
};

#endif
