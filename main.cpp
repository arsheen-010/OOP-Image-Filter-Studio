#include <iostream>
#include <string>
#include "User.h"
#include "Pixel.h"
#include "Image.h"
#include "Filter.h"
#include "FilterSession.h"
#include "Managers.h"
using namespace std;
bool validCnic(const string& cnic) {
    if (cnic.length() != 13) return false;
    for (char c : cnic)
        if (!isdigit(c)) return false;
    return true;
}

bool validPassword(const string& pass) {
    if (pass.length() != 9) return false;
    bool hasUpper = false, hasDigit = false;
    for (char c : pass) {
        if (isupper(c)) hasUpper = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasDigit;
}

int readInt() {
    int val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a number: ";
    }
    return val;
}

// ── Menus ──
void showMain() {
    cout << "\nImage Filter Studio\n";
    cout << "Please select an option\n";
    cout << "1. Admin Login     \n";
    cout << "2. Customer Login \n";
    cout << "3. New Customer? Register here \n";
    cout << "4. Exit   \n";
    cout << "Your choice: ";
}

void showAdminPanel() {
    cout <<   "ADMIN PANEL \n";
    cout <<" Image Filter Studio\n";
    cout <<  " 1. Manage Filter Catalog    \n";
    cout <<  "2. Manage Customers      \n";
    cout <<  "3. View All Sessions\n";
    cout <<  "4. Logout   \n";
    cout << "Your choice: ";
}

void showCustomerPanel(const string& name, int sessions) {
    cout <<   "Welcome, " << name;
    for (int i = name.size(); i < 31; i++) cout << " ";   
    cout << "\n";
    cout <<   "sessions completed: " << sessions;
    for (int i = to_string(sessions).size(); i < 20; i++) cout << " ";  
    cout << "\n";
    cout <<   "1. Browse Filter Catalog \n";
    cout <<   "2. Load Image  \n";
    cout <<   "3. Build Filter Pipeline & Apply \n";
    cout <<   "4. View My Session History  \n";
    cout <<   "5. Logout \n";
    cout << "Your choice: ";
}
void doRegister(CustomerManager& cm) {
    string cnic, pass, confirm, name, gender, phone, city;

    cout << "\nCustomer Registration \n";

    cout << "Enter CNIC (13 digits): "; cin >> cnic;
    if (!validCnic(cnic)) { cout << "CNIC must be  13 digits.\n"; 
    return; }
    if (cm.cnicExists(cnic) || cm.isBlockedCnic(cnic)) {
        cout << "CNIC already registered or blocked.\n"; return;
    }

    cout << "Enter Password (9 chars, 1 uppercase, 1 digit): "; cin >> pass;
    if (!validPassword(pass)) {
        cout << " password. need 9 chars, at least 1 uppercase, 1 digit.\n"; return;
    }

    cout << "confirm Password: "; cin >> confirm;
    if (pass != confirm) { cout << "Passwords do not match.\n"; return; }

    cin.ignore();
    cout << "Full Name: "; getline(cin, name);
    cout << "Gender : "; cin >> gender;
    cout << "Phone: "; cin >> phone;
    cout << "City: "; cin >> city;

    cm.save(cnic, pass, name, gender, phone, city);
    cout << "registration successful!\n";
}
void adminFlow(CustomerManager& cm, CatalogManager& cat, SessionManager& sm) {
    string adminPass = "Admin@123";
    string inputPass;
    cout << "enter Admin Password: "; 
    cin >> inputPass;
    if (inputPass != adminPass) { cout << "Access Denied.\n"; 
    return; }
    cout << "access Granted.\n";

    int choice;
    do {
        showAdminPanel();
        choice = readInt();

        if (choice == 1) {
            cat.load();
            cout << "\nenter filter ID to toggle (0 to back): ";
            string id; cin >> id;
            if (id != "0") cat.toggle(id);

        } else if (choice == 2) {
            cm.load();
            cout << "\n1. Block customer  2. Delete customer  0. Back\nChoice: ";
            int c2 = readInt();
            if (c2 == 1 || c2 == 2) {
                cout << "Enter CNIC: ";
                string cnic; cin >> cnic;
                if (c2 == 1) cm.blockUser(cnic);
                else         cm.deleteUser(cnic);
            }

        } else if (choice == 3) {
            sm.loadAll();
        }

    } while (choice != 4);
}
void customerFlow(CustomerManager& cm, CatalogManager& cat, SessionManager& sm) {
    string cnic, pass;
    int attempts = 0;

    cout << "\nCustomer Login \n";
    while (attempts < 3) {
        cout << "CNIC: "; cin >> cnic;
        cout << "Password: "; cin >> pass;

        int result = cm.search(cnic, pass);
        if (result == 0) break;
        if (result == 1) { cout << "Account is blocked.\n"; return; }
        attempts++;
        cout << ". Attempts: " << attempts << "/3\n";
        if (attempts == 3) { cout << "Too many attempts\n"; return; }
    }

    string customerName = cm.getNameByCnic(cnic);
    int sessionCount = 0;
    Image img(1, 1);
    bool imageLoaded = false;
    ImageManager imgMgr;

    int choice;
    do {
        showCustomerPanel(customerName, sessionCount);
        choice = readInt();

        if (choice == 1) {
            cat.load();

        } else if (choice == 2) {
            cout << "\n1. Load from JPG/PNG file\n2. Generate pattern\nChoice: ";
            int lc = readInt();
            if (lc == 1) {
                cout << "Enter image path: ";
                string path; cin >> path;
                Image newImg(1, 1);
                if (imgMgr.load(path, newImg)) {
                    img = newImg;
                    imageLoaded = true;
                    img.displayASCII();
                }
            } else {
                img = Image(20, 10);
                img.fill();
                imageLoaded = true;
                cout << "Test pattern generated (20x10).\n";
                img.displayASCII();
            }

        } else if (choice == 3) {
            if (!imageLoaded) { cout << "please load an image first.\n"; continue; }

            cat.load();
            FilterSession session;

            cout << "\nBuild Filter Pipeline \n";
            cout << "Enter filter ID (0 to finish): ";
            string fid;
            while (cin >> fid && fid != "0") {
                if (fid.length() == 1 && fid != "0") fid = "0" + fid;
                if (!cat.isEnabled(fid)) {
                    cout << "Filter " << fid << " is disabled.\n";
                    cout << "Next ID (0 to finish): ";
                    continue;
                }
                int bval = 30;
                if (fid == "03") {
                    cout << "Enter brightness amount : ";
                    bval = readInt();
                }
                Filter* f = makeFilter(fid, bval);
                if (f) {
                    session.addFilter(f);
                    cout << "added: " << f->getName() << "\n";
                } else {
                    cout << "invalid filter ID.\n";
                }
                cout << "next ID (0 to finish): ";
            }

            cout << "\nApplying Pipeline \n";
            session.run(img);
            session.showPixelDirect(img, 0, 0);

            cout << "\nSave result? (y/n): ";
            char yn; cin >> yn;
            if (yn == 'y' || yn == 'Y') {
                string ts = sm.timestamp();
                string outFile = cnic + "_" + ts + ".png";
                img.saveToFile(outFile);
                sm.save(cnic, session.getAppliedNames(), outFile);
                sessionCount++;
                cout << "Open " << outFile << " in any image viewer.\n";
            }

        } else if (choice == 4) {
            sm.load(cnic);
        }

    } while (choice != 5);

    cout << "Logged out.\n";
}
int main() {
    CustomerManager cm;
    CatalogManager  cat;
    SessionManager  sm;

    int choice;
    do {
        showMain();
        choice = readInt();

        if (choice == 1) {
            adminFlow(cm, cat, sm);
        } else if (choice == 2) {
            customerFlow(cm, cat, sm);
        } else if (choice == 3) {
            doRegister(cm);
        } else if (choice == 4) {
            cout << "goodbye\n";
        } else {
            cout << "Invalid .\n";
        }

    } while (choice != 4);

    return 0;
}
