# 📚 Library Management System

> A console-based Library Management System written in **C** that allows users to manage books — add, issue, return, search, and edit — all through a clean interactive menu. All data is stored persistently using a fully file-based system.

---

## 🗂️ Table of Contents

- [About](#about)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [⚠️ Precautions](#️-precautions)
- [File Structure](#file-structure)
- [Future Plans](#future-plans)
- [License](#license)

---

## 📖 About

This project is a **Library Management System** built in C. It stores book data persistently to a text file (`books.txt`) and provides an interactive terminal menu for all library operations. Every function reads and writes directly to the file — no in-memory arrays, fully file-based.

Built and tested on **Android using CxxDroid**.

---

## ✨ Features

| Feature | Description |
|---|---|
| ➕ Add Books | Add one or more books with name, author, ISBN, and price |
| 📤 Issue Book | Mark a book as issued using its ISBN |
| 📥 Return Book | Mark an issued book as returned, with retry support |
| 📋 Show Books | Display all books with their current availability status |
| 🔍 Search | Search books by name, author, or ISBN (case-insensitive) |
| ✏️ Edit Data | Update any field of an existing book record, supports multiple matches |

---

## 🚀 Getting Started

### Prerequisites

- A C compiler such as **GCC**
- Linux/macOS terminal, **MinGW** on Windows, or **CxxDroid** on Android

### Compilation

```bash
gcc library.c -o library
```

### Run

```bash
./library
```

---

## 🖥️ Usage

On launch, you'll see the main menu:

```
------------------------------MAIN MENU----------------------------

1. ADD BOOKS
2. ISSUE BOOK
3. RETURN BOOK
4. SHOW BOOKS
5. SEARCH BAR
6. CHANGE DATA
7. EXIT

Enter an option:
```

### Book Data Format (books.txt)

Each book is stored as a pipe-delimited line:

```
Book Name|Author|ISBN|Price|Status
```

**Example:**
```
The Pragmatic Programmer|David Thomas|978-0135957059|799.00|available
Clean Code|Robert C. Martin|978-0132350884|649.00|issued
```

---

## ⚠️ Precautions

This project was built and tested on **Android (CxxDroid)**. If you're running it on a different platform, keep the following in mind:

### 1. Hardcoded File Path (Android-specific)
All file operations use `/sdcard/books.txt` and `/sdcard/temp.txt`. This path is Android-specific and **will not work** on Windows, Linux, or macOS.

**Fix:** Replace all occurrences of `/sdcard/books.txt` and `/sdcard/temp.txt` with a local path:
```c
// Windows
ptr = fopen("C:\\books.txt", ...);

// Linux / macOS
ptr = fopen("books.txt", ...);
```

### 2. `system("cls")` — Windows/Android Only
The `system("cls")` call clears the screen but only works on **Windows and CxxDroid (Android)**. On Linux or macOS it will do nothing or throw an error.

**Fix:** Replace with:
```c
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
```

---

## 📁 File Structure

```
.
├── library.c       # Main source file
└── books.txt       # Auto-generated data file (created on first add)
```

---

## 🔮 Future Plans

- [ ] Student/Member management module
- [ ] Due date tracking and fine calculation  
- [ ] Separate membership tiers for **students** and **adults (18+)** with different borrowing rules and fine rates

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

> Made with ❤️ in C by Adrish Datta | Built on Android 📱
