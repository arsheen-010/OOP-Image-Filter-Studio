#include "FilterSession.h"
#include <iostream>
using namespace std;

void FilterSession::addFilter(Filter* f) {
    filters.push_back(f);
    appliedNames.push_back(f->getName());
}

void FilterSession::run(Image& img) {
    for (int i = 0; i < (int)filters.size(); i++) {
        cout << "applying filter " << (i+1) << "/" << filters.size()
             << ": " << filters[i]->getName() << " ...\n";
        filters[i]->apply(img);
    }
}

void FilterSession::showPixelDirect(Image& img, int r, int c) {
    cout << "Pixel[0][0]  " << img.grid[r][c] << "\n";
}

string FilterSession::getAppliedNames() {
    string result = "";
    for (int i = 0; i < (int)appliedNames.size(); i++) {
        if (i > 0) result += ">";
        result += appliedNames[i];
    }
    return result;
}

FilterSession::~FilterSession() {
    for (int i = 0; i < (int)filters.size(); i++)
        delete filters[i];
}
