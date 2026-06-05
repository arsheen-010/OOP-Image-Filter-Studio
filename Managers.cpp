#include "Managers.h"
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;
CustomerManager::CustomerManager() { 
filename = "customers.txt"; }

void CustomerManager::save(string cnic, string pass, string name, string gender, string phone, string city) {
    ofstream fout(filename, ios::app);
    fout << cnic << "|" << pass << "|" << name << "|" << gender << "|" << phone << "|" << city << "|0" << endl;
    fout.close();
}

void CustomerManager::load() {
    ifstream fin(filename);
    string line;
    cout << "\nCustomer List \n";
    while (getline(fin, line))
        cout << line << endl;
    fin.close();
}

int CustomerManager::search(const string& cnic, const string& pass) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fcnic, fpass, name, gender, phone, city, block;
        getline(ss, fcnic, '|');
        getline(ss, fpass, '|');
        getline(ss, name, '|');
        getline(ss, gender, '|');
        getline(ss, phone, '|');
        getline(ss, city, '|');
        getline(ss, block, '|');
        if (fcnic == cnic && fpass == pass) {
            fin.close();
            if (block == "1") return 1;
            return 0;
        }
    }
    fin.close();
    return -1;
}

bool CustomerManager::cnicExists(const string& cnic) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        if (line.find(cnic) != string::npos) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool CustomerManager::isBlockedCnic(const string& cnic) {
    ifstream fin("blocked_cnics.txt");
    string line;
    while (getline(fin, line)) {
        if (line == cnic) { fin.close(); return true; }
    }
    fin.close();
    return false;
}

string CustomerManager::getNameByCnic(const string& cnic) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fcnic, pass, name;
        getline(ss, fcnic, '|');
        getline(ss, pass, '|');
        getline(ss, name, '|');
        if (fcnic == cnic) { fin.close(); return name; }
    }
    fin.close();
    return "Customer";
}

void CustomerManager::blockUser(string cnic) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fcnic, pass, name, gender, phone, city, block;
        getline(ss, fcnic, '|');
        getline(ss, pass, '|');
        getline(ss, name, '|');
        getline(ss, gender, '|');
        getline(ss, phone, '|');
        getline(ss, city, '|');
        getline(ss, block, '|');
        if (fcnic == cnic) block = "1";
        fout << fcnic << "|" << pass << "|" << name << "|" << gender << "|" << phone << "|" << city << "|" << block << endl;
    }
    fin.close(); fout.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");
    ofstream fblock("blocked_cnics.txt", ios::app);
    fblock << cnic << "\n";
    fblock.close();
    cout << "Customer " << cnic << " blocked.\n";
}

void CustomerManager::deleteUser(string cnic) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line)) {
        if (line.find(cnic) == string::npos)
            fout << line << endl;
    }
    fin.close(); fout.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");
    cout << "Customer " << cnic << " deleted.\n";
}
CatalogManager::CatalogManager() {
    filename = "catalog.txt";
    createIfMissing();
}

void CatalogManager::createIfMissing() {
    ifstream fin(filename);
    if (fin.good()) { fin.close(); 
    return; }
    fin.close();
    ofstream fout(filename);
    fout << "01 Grayscale           |Pixeltransform|1\n";
    fout << "02 Invert              |Pixel transform|1\n";
    fout << "03 Brightness adjust   |Pixel Transform|1\n";
    fout << "04 contrast stretch    | Pixel Transform|1\n";
    fout << "05 Red channel         |Pixel Transform|1\n";
    fout << "06 Green channel       |Pixel Transform|1\n";
    fout << "07 Blue channel        | Pixel Transform|1\n";
    fout << "08 Box blur            |Spatial Filter|1\n";
    fout << "09 Flip horizontal     |Geometric|1\n";
    fout << "10 Flip vertical       |Geometric|1\n";
    fout.close();
}

void CatalogManager::load() {
    ifstream fin(filename);
    string line;
    cout << "\nFilter Catalog \n";
    cout << "ID | Filter Name          | Category        | Status\n";
    while (getline(fin, line)) {
        stringstream ss(line);
        string fid, name, cat, enable;
        getline(ss, fid, '|');
        getline(ss, name, '|');
        getline(ss, cat, '|');
        getline(ss, enable, '|');
        cout << fid << " | ";
        cout << name;
        for (int i = name.size(); i < 21; i++) cout << " ";
        cout << "| ";
        cout << cat;
        for (int i = cat.size(); i < 16; i++) cout << " ";
        cout << "| " << (enable == "1" ? "enabled" : "disabled") << "\n";
    }
    fin.close();
}

bool CatalogManager::isEnabled(const string& id) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fid, name, cat, enable;
        getline(ss, fid, '|');
        getline(ss, name, '|');
        getline(ss, cat, '|');
        getline(ss, enable, '|');
        if (fid == id) { fin.close(); return (enable == "1"); }
    }
    fin.close();
    return false;
}

void CatalogManager::toggle(string id) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fid, name, cat, enable;
        getline(ss, fid, '|');
        getline(ss, name, '|');
        getline(ss, cat, '|');
        getline(ss, enable, '|');
        if (fid == id) enable = (enable == "1") ? "0" : "1";
        fout << fid << "|" << name << "|" << cat << "|" << enable << endl;
    }
    fin.close(); fout.close();
    remove("catalog.txt");
    rename("temp.txt", "catalog.txt");
    cout << "Filter " << id << " toggled.\n";
}
SessionManager::SessionManager() { filename = "sessions.txt"; }

string SessionManager::timestamp() {
    time_t now = time(0);
    struct tm* t = localtime(&now);
    char buf[32];
    sprintf(buf, "%04d%02d%02d_%02d%02d%02d",
        1900+t->tm_year, 1+t->tm_mon, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
    return string(buf);
}

void SessionManager::save(const string& cnic, const string& filters, const string& output) {
    ofstream fout(filename, ios::app);
    fout << cnic << "|" << timestamp() << "|" << filters << "|" << output << endl;
    fout.close();
}

void SessionManager::load(const string& cnic) {
    ifstream fin(filename);
    string line;
    cout << "\nsession history for " << cnic << " ---\n";
    while (getline(fin, line)) {
        if (line.find(cnic) != string::npos)
            cout << line << endl;
    }
    fin.close();
}

void SessionManager::loadAll() {
    ifstream fin(filename);
    string line;
    cout << "\nall sessions : \n";
    while (getline(fin, line))
        cout << line << endl;
    fin.close();
}

bool ImageManager::load(const string& path, Image& outImg) {
    int w, h, ch;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &ch, 3);
    if (data == NULL) {
        cout << "image load failed\n";
        return false;
    }
    cout << "loaded: " << w << " x " << h << "\n";
    Image tmp(w, h);
    for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++) {
        int idx = (i * w + j) * 3;
        tmp.at(i, j).set(data[idx], data[idx+1], data[idx+2]);
    }
    stbi_image_free(data);
    outImg = tmp;
    return true;
}
