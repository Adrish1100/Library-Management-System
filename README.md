# 📚 Library Management System

> A console-based Library Management System written in **C** that allows users to manage books — add, issue, return, search, and edit — all through a clean interactive menu.

---

## 🗂️ Table of Contents

- [About](#about)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Known Issues & Limitations](#known-issues--limitations)
- [Future Improvements](#future-improvements)
- [License](#license)

---

## 📖 About

This project is a simple but functional **Library Management System** built in C. It stores book data persistently to a text file (`books.txt`) and provides an interactive terminal menu for library operations. It was designed as a learning project to practice file I/O, structs, and modular programming in C.

---

## ✨ Features

| Feature | Description |
|---|---|
| ➕ Add Books | Add one or more books with name, author, ISBN, and price |
| 📤 Issue Book | Mark a book as issued using its ISBN |
| 📥 Return Book | Mark an issued book as returned |
| 📋 Show Books | Display all books with their current availability status |
| 🔍 Search | Search books by name, author, or ISBN (case-insensitive) |
| ✏️ Edit Data | Update any field of an existing book record |

---

## 🚀 Getting Started

### Prerequisites

- A C compiler such as **GCC**
- A Linux/macOS terminal, or **MinGW** on Windows

### Compilation

```bash
gcc library.c -o library
```

### Run

```bash
./library
```

> **Note:** On Android (Termux), the file is saved to `/sdcard/books.txt`. On other platforms, update the path in `add_book()` accordingly.

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

Navigate by entering the number corresponding to your desired action and follow the on-screen prompts.

### Book Data Format (books.txt)

Each book is stored as a pipe-delimited line:

```
Book Name|Author|ISBN|RS. Price|Status
```

**Example:**
```
The Pragmatic Programmer|David Thomas|978-0135957059|RS. 799.00|available
Clean Code|Robert C. Martin|978-0132350884|RS. 649.00|issued
```

---

## 📁 File Structure

```
.
├── library.c       # Main source file
└── books.txt       # Auto-generated data file (created on first run)
```

---

## ⚠️ Known Issues & Limitations

- **No persistent load on startup** — book data is written to `books.txt` but not read back when the program restarts. The in-memory `count` and struct array reset each session.
- **Fixed array size** — the program uses a single global `struct books b` (not an array), which causes undefined behavior when accessing `b[i]`. Needs to be declared as `b[MAX]`.
- **Hardcoded file path** — `/sdcard/books.txt` is Android-specific and must be changed for other platforms.
- **`system("cls")`** — only works on Windows; use `system("clear")` on Linux/macOS.
- **No input validation** — long inputs can overflow fixed-size character buffers.

---

## 🔮 Future Improvements

- [ ] Load books from file on startup for full persistence
- [ ] Replace fixed-size array with dynamic memory allocation
- [ ] Add a student/member management module
- [ ] Due date tracking and fine calculation
- [ ] Cross-platform screen clearing
- [ ] Input sanitization and buffer overflow protection
- [ ] Export reports to CSV

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

> Made with ❤️ in C
