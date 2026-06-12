# Library Management System

![C](https://img.shields.io/badge/C-C99-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-1.0-orange.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)

![GitHub Stars](https://img.shields.io/github/stars/Adrish1100/LIBRARY-MANAGEMENT-SYSTEM?style=social)
![GitHub Forks](https://img.shields.io/github/forks/Adrish1100/LIBRARY-MANAGEMENT-SYSTEM?style=social)
![GitHub Watchers](https://img.shields.io/github/watchers/Adrish1100/LIBRARY-MANAGEMENT-SYSTEM?style=social)
![GitHub Issues](https://img.shields.io/github/issues/Adrish1100/LIBRARY-MANAGEMENT-SYSTEM)
![Repo Views](https://komarev.com/ghpvc/?username=Adrish1100&repo=LIBRARY-MANAGEMENT-SYSTEM&color=blue)

---

# 📚 Library Management System

A menu-driven **Library Management System** written in **C**, designed to manage books and library memberships through a simple command-line interface.

The system demonstrates practical applications of:

- File handling
- Structures and typedefs
- Function pointers
- Enumerations
- String manipulation
- Date and time operations
- Input validation
- Modular programming principles

This project was developed as an educational yet functional system capable of handling common library operations.

---

# 📌 Overview

The Library Management System provides librarians with the ability to:

- Add new books to the library database
- Issue books to members
- Process returned books
- Search books efficiently
- Edit book information
- Register new library members
- Renew memberships
- Cancel memberships
- Display member information
- Automatically expire memberships based on validity dates

All records are maintained using plain text files, making the project lightweight and easy to understand for students learning file-based data management.

---

# ✨ Features

## 📖 Book Management

- Add books to the library
- Display all available books
- Search books by:
  - Book title
  - Author name
  - ISBN number
- Modify existing book records
- View book issue status

---

## 🔄 Circulation Management

- Issue books
- Return books
- Automatic issue date generation
- Automatic return date calculation
- Prevent issuing already issued books

---

## 👥 Membership Management

- Register library members
- Generate unique membership IDs
- Store member details:
  - Name
  - Address
  - Nationality
  - Age
  - Phone Number
  - Aadhaar Number (for Indian citizens)
- Renew memberships
- Cancel memberships
- View all registered members

---

## ⏳ Automatic Membership Expiry

The system automatically checks membership validity and updates expired memberships without manual intervention.

---

# 🖥️ Main Menu

```text
**************************************
*                                    *
*      Library Management System     *
*            BY: ADRISH DATTA        *
*                                    *
**************************************

1. ADD BOOKS
2. ISSUE BOOK
3. RETURN BOOK
4. SHOW BOOKS
5. SEARCH
6. CHANGE
7. ADD MEMBERSHIP
8. CANCEL MEMBERSHIP
9. RENEW MEMBERSHIP
10. SHOW MEMBERS
11. EXIT
```

---

# ⚙️ Technologies Used

| Technology | Purpose |
|------------|----------|
| C (C99) | Core Programming Language |
| Standard I/O Library | File and console operations |
| Structures | Book and membership records |
| Function Pointers | Menu dispatch mechanism |
| Enumerations | Menu option management |
| String Functions | Data processing |
| Time Library | Membership and issue date calculations |

---

# 📁 Project Structure

```text
Library_Management_System/
│
├── LIBRARY MANAGEMENT SYSTEM.c
├── books.txt
├── membership.txt
├── README.md
└── LICENSE
```

---

# 🏗️ Data Structures

## Book Structure

```c
struct BOOK
{
    char name[100];
    char author[100];
    char isbn[50];
    char price[20];
    char status[20];
    char issue_date[20];
    char return_date[20];
};
```

---

## Membership Structure

```c
typedef struct membership
{
    char id[25];
    char name[100];
    char phone[15];
    char address[200];
    char join_date[20];
    char expiry_date[20];
    char status[20];
    char adhaar[15];
    char nation[25];
    int act_age;
} mem;
```

---

# 📂 File Management

The application stores data using text files.

## Books Database

```text
books.txt
```

Format:

```text
Book Name|Author|ISBN|Price|Status|Issue Date|Return Date
```

Example:

```text
The Alchemist|Paulo Coelho|9780061122415|299|available|NA|NA
```

---

## Membership Database

```text
membership.txt
```

Format:

```text
ID|Name|Age|Phone|Nationality|Address|Aadhaar|Join Date|Expiry Date|Status
```

Example:

```text
M0|John Doe|21|9876543210|Indian|Delhi|123456789012|2026-06-01|2026-07-01|active
```

---

# 🚀 How To Compile

## Using GCC

```bash
gcc "LIBRARY MANAGEMENT SYSTEM.c" -o library
```

---

# ▶️ How To Run

## Linux / macOS

```bash
./library
```

---

## Windows

```bash
library.exe
```

---

# 🔍 Functional Overview

| Module | Description |
|---------|-------------|
| Add Books | Inserts book records into the database |
| Issue Book | Marks books as issued |
| Return Book | Updates issued books as available |
| Show Books | Displays all books |
| Search | Finds books using keywords |
| Change | Edits book information |
| Add Membership | Registers new members |
| Cancel Membership | Cancels active memberships |
| Renew Membership | Extends membership validity |
| Show Members | Displays member records |
| Auto Expire | Updates expired memberships |

---

# 🛡️ Input Validation Features

The project includes several validation mechanisms:

- Numeric validation for age input
- Phone number validation
- Aadhaar number validation
- Menu option validation
- Membership expiry verification
- Prevention of issuing unavailable books

---

# 📊 Complexity Analysis

| Operation | Time Complexity |
|------------|----------------|
| Add Book | O(1) |
| Search Book | O(n) |
| Show Books | O(n) |
| Edit Book | O(n) |
| Issue Book | O(n) |
| Return Book | O(n) |
| Membership Operations | O(n) |

Where:

```text
n = Number of records stored in the text file
```

Overall space complexity:

```text
Space Complexity: O(1)
```

excluding external storage files.

---

# ⚠️ Current Limitations

The present implementation has several limitations:

- Uses plain text files instead of a database.
- No authentication system for administrators.
- Limited error recovery for corrupted files.
- No fine calculation for overdue books.
- Book reservations are not supported.
- Simultaneous multi-user access is not supported.
- File locking mechanisms are absent.

---

# 🔮 Future Improvements

## Database Integration

- SQLite support
- MySQL backend support

---

## Security Enhancements

- User authentication
- Password hashing
- Role-based access control

---

## Library Features

- Fine calculation system
- Book reservation system
- Borrowing history tracking
- ISBN validation

---

## Technical Improvements

- Modular source files
- Header file separation
- Unit testing framework
- Logging system
- Enhanced exception handling

---

## User Experience

- Improved terminal UI
- Colored output support
- Pagination for large datasets
- Search filters

---

# 📚 Educational Concepts Demonstrated

This project showcases practical usage of:

- Structures (`struct`)
- Typedefs
- Enumerations (`enum`)
- Arrays
- String manipulation
- Dynamic date calculations
- File handling
- Function pointers
- Modular function design
- Input validation techniques

---

# 👨‍💻 Author

**Adrish Datta**

Student Developer | Software Enthusiast

---

# 🤝 Contributions

Contributions are welcome.

To contribute:

1. Fork the repository.
2. Create a feature branch.

```bash
git checkout -b feature-name
```

3. Commit your changes.

```bash
git commit -m "Add new feature"
```

4. Push to GitHub.

```bash
git push origin feature-name
```

5. Open a Pull Request.

---

# 📜 License

MIT License

Copyright (c) 2026 Adrish Datta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

⭐ If you found this project useful, consider giving it a star on GitHub.
