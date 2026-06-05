#include "User.h"
#include <iostream>
using namespace std;
User::User(string n, string p, string no) : name(n), password(p), number(no), count(0) {}

Admin::Admin(string n, string p, string no) : User(n, p, no) {}

void Admin::checkPassword() {
    string input;
    cout << "Enter the password: ";
    cin >> input;
    if (input.length() != 9) {
        cout << "invalid password must be exactly 9 characters.\n";
        return;
    }
    bool hasUpper = false, hasDigit = false;
    for (char c : input) {
        if (isupper(c)) hasUpper = true;
        if (isdigit(c)) hasDigit = true;
    }
    if (!hasUpper || !hasDigit) {
        cout << "not allowed need at least 1 uppercase and 1 digit.\n";
    } else {
        cout << "Password set.\n";
        password = input;
    }
}

void Admin::login() {
    string pass;
    cout << "Enter admin password: ";
    cin >> pass;
    if (pass == password)
        cout << "Access Granted\n";
    else
        cout << "Access Denied\n";
}

// ── Customer ──
Customer::Customer(string n, string p, string no, string c, string cn)
    : User(n, p, no), city(c), cnic(cn), isBlocked(false) {}

void Customer::checkcnic(const string& inputCnic) {
    if (inputCnic.length() != 13) {
        cout << "Invalid count: CNIC must be exactly 13 digits.\n";
        return;
    }
    for (char ch : inputCnic) {
        if (!isdigit(ch)) {
            cout << "CNIC must contain only digits.\n";
            return;
        }
    }
    cout << "Valid CNIC.\n";
}

void Customer::login() {
    string n, p;
    count = 0;
    while (count < 3) {
        cout << "Enter name: ";
        cin >> n;
        cout << "Enter password: ";
        cin >> p;

        if (n == name && p == password && !isBlocked) {
            cout << "Login successful\n";
            return;
        } else if (isBlocked) {
            cout << "Account is blocked.\n";
            return;
        } else {
            count++;
            cout << "failed attempt " << count << "/3\n";
        }
    }
    cout << "Too many failed attempts.\n";
}

void Customer::block() { isBlocked = true; }
