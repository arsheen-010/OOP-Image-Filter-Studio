#ifndef User_h
#define User_h

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string name;
    string password;
    string number;
    int count;

public:
    User(string n, string p, string no);
    virtual void login() = 0;
    virtual ~User() {}
};

class Admin : public User {
public:
    Admin(string n, string p, string no);
    void checkPassword();
    void login() override;
};

class Customer : public User {
private:
    string city;
    string cnic;
    bool isBlocked;

public:
    Customer(string n, string p, string no, string c, string cn);
    void checkcnic(const string& inputCnic);
    void login() override;
    void block();
};

#endif
