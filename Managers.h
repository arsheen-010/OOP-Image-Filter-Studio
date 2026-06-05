#ifndef Managers_h
#define Managers_h
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Image.h"
using namespace std;

class CustomerManager {
private:
    string filename;
public:
    CustomerManager();
    void save(string cnic, string pass, string name, string gender, string phone, string city);
    void load();
    int search(const string& cnic, const string& pass);
    bool cnicExists(const string& cnic);
    bool isBlockedCnic(const string& cnic);
    string getNameByCnic(const string& cnic);
    void blockUser(string cnic);
    void deleteUser(string cnic);
};

class CatalogManager {
private:
    string filename;
public:
    CatalogManager();
    void createIfMissing();
    void load();
    bool isEnabled(const string& id);
    void toggle(string id);
};

class SessionManager {
private:
    string filename;
public:
    SessionManager();
    string timestamp();
    void save(const string& cnic, const string& filters, const string& output);
    void load(const string& cnic);
    void loadAll();
};

class ImageManager {
public:
    bool load(const string& path, Image& outImg);
};

#endif
