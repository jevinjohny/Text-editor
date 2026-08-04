# 🧠 Terminal Text Editor

### Command-Based Text Editing System
A lightweight terminal text editor built in C for creating, viewing, and managing text files through a simple command-driven interface. The project supports line-based editing, cursor movement, undo/redo operations, clipboard actions, and file open/save functionality.

---

## 🚀 Key Features

- 📝 **Line-Based Editing**
  - Insert and delete lines dynamically
  - Add text content directly through commands
- ⌨️ **Interactive Command Interface**
  - Simple terminal commands for navigation and editing
  - Easy to use for basic text manipulation
- 🔄 **Undo and Redo Support**
  - Restore previous edits efficiently
  - Reapply changes when needed
- 📋 **Clipboard Operations**
  - Copy and paste content within the editor
- 📂 **File Handling**
  - Open existing text files
  - Save changes to disk
  - Close active files safely

---

## 🧠 System Overview

### 1️⃣ Main Application
- Starts the editor and processes user commands
- Dispatches operations such as insert, delete, move, save, and exit
- Serves as the central control loop

### 2️⃣ Editor Logic
- Maintains the document as a linked list of lines
- Tracks cursor position and current line
- Supports editing operations and view updates

### 3️⃣ File Management
- Reads and writes text files from the terminal
- Keeps the document state synchronized with stored content

---

## 🔧 Requirements

- GCC or any standard C compiler
- Linux/Unix-like terminal environment
- Basic terminal support for input/output

## ▶️ Build

1. Open the project folder in a terminal.
2. Compile the source files:

```bash
gcc main.c editor.c -o texteditor
```

3. Run the executable:

```bash
./texteditor
```

## 📁 Main Files

- [main.c](main.c) — main application flow and command handling
- [editor.c](editor.c) — editor operations and document management
- [main.h](main.h) — shared structures, constants, and function declarations
- [sample.txt](sample.txt) — sample text file for testing

## 🛠️ Example Commands

- insert_line hello
- delete_line
- undo
- redo
- print
- moveup 2
- movedown 1
- moveleft 3
- moveright 2
- open sample.txt
- save file.txt
- insert some text
- copy
- paste
- exit
