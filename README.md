# 🎨 Image Filter Studio — C++ OOP Project

A console-based Image Filter Studio built entirely in C++ using
core Object-Oriented Programming principles. This project simulates
a real-world image processing application with user authentication,
role-based access, and a dynamic filter pipeline system.
 🚀 Features

  👤 User System
- Customer registration with CNIC and password validation
- 3-attempt login security with auto-lockout
- Admin panel with hardcoded secure credentials
- Block / Delete customer accounts
- Permanent CNIC blacklist prevents re-registration

### 🎛️ Filter Pipeline
- Build a custom chain of filters applied in sequence
- 10 professional image filters available
- Admin can enable / disable filters from customer access
- Real-time ASCII preview after each filter applied

### 🖼️ Image Processing (via stb_image)
- Load real JPG / PNG images from disk
- Save processed images as PNG output
- Full pixel-level manipulation using custom Pixel and Image classes

### 📁 File Persistence
- All data persists across sessions via text files
- customers.txt — registered users
- catalog.txt — filter status
- sessions.txt — complete history log
- blocked_cnics.txt — permanent blacklist

---

## 🔧 Filters Available

| ID | Filter | Type |
|----|--------|------|
| 01 | Grayscale | Pixel Transform |
| 02 | Invert | Pixel Transform |
| 03 | Brightness Adjust | Pixel Transform |
| 04 | Contrast Stretch | Pixel Transform |
| 05 | Red Channel Only | Pixel Transform |
| 06 | Green Channel Only | Pixel Transform |
| 07 | Blue Channel Only | Pixel Transform |
| 08 | Box Blur 3x3 | Spatial Filter |
| 09 | Flip Horizontal | Geometric |
| 10 | Flip Vertical | Geometric |                                                                                       

# 🏗️ OOP Concepts Used

| Concept | Where |
|---------|-------|
| Inheritance | Admin, Customer → User / All filters → Filter |
| Runtime Polymorphism | Filter pipeline via virtual apply() |
| Compile-time Polymorphism | Pixel operator+ and operator<< |
| Abstract Classes | User and Filter (pure virtual) |
| Encapsulation | Pixel hides RGB with clamp validation |
| Composition | Image owns Pixels / FilterSession owns Filters |
| Aggregation | main() passes managers to functions |
| Friend | FilterSession accesses Image private grid |
| Deep Copy | Image copy constructor and assignment operator |
| Dynamic Memory | 2D Pixel grid / Filter objects with new/delete |
| File Handling | 4 persistent text files |
| STL Vector | Dynamic filter pipeline |
| Factory Pattern | makeFilter() creates correct subclass |

---

## 📂 Proje---

## ⚙️ How to Compile and Run

```bash
# Using Makefile
make
./app

## 🔑 Admin Credentialsct Structure
Password : Admin@123
---

## 📌 Requirements
- g++ with C++11 support
- stb_image.h and stb_image_write.h in same folder
- Any JPG or PNG image file for testing

## 👨‍💻 Built With
- Language: C++
- Libraries: STL, stb_image
- Concepts: Full OOP, File I/O, Dynamic Memory Management
