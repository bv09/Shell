# TinyShell - Windows API Command-Line Interpreter

[cite_start]TinyShell is a specialized shell (command processor) designed to bridge the communication between users and the Windows Operating System[cite: 22]. [cite_start]Developed as a project for the **Operating System Principles** course at **Hanoi University of Science and Technology**, it simulates core system mechanisms through a Command Line Interface (CLI)[cite: 1, 11, 45].

## 🚀 Key Features

- [cite_start]**Process Management**: Ability to initialize child processes, monitor execution, and manage process lifecycles[cite: 47, 48].
- [cite_start]**Execution Modes**: Supports both **foreground** (blocking) and **background** execution[cite: 240, 241, 243].
- [cite_start]**Batch Processing**: Native support for executing script sequences via `*.bat` files[cite: 51, 372].
- [cite_start]**Interrupt Handling**: Captures keyboard signals like `Ctrl+C` to terminate foreground processes[cite: 50, 243].
- [cite_start]**Windows API Integration**: Built using `windows.h` to interact directly with the Windows kernel via `CreateProcess` and other system functions[cite: 54, 373].

---

## 🏗️ System Architecture & Workflow

[cite_start]TinyShell operates on a continuous lifecycle within a `while(1)` loop, performing three primary tasks[cite: 60, 76]:

1. [cite_start]**Receive Command**: Accepts user input via the `read_line()` function[cite: 61, 86].
2. [cite_start]**Parse Command**: Checks syntax and splits input into tokens using `split_line()`[cite: 62, 96].
3. [cite_start]**Execute Command**: Launches the appropriate process or built-in function via `execute_line()`[cite: 63, 97].

### Core Libraries

- [cite_start]`windows.h`: Essential for system operations and process creation[cite: 54].
- [cite_start]`bits/stdc++.h`: Standard C++ libraries for data structures like vectors and maps[cite: 55].
- [cite_start]`stdio.h`: Basic I/O operations for the command line[cite: 56].

---

## 💻 Command Reference

### Built-in Commands

| Command         | Description                                                                          |
| :-------------- | :----------------------------------------------------------------------------------- |
| `help`          | [cite_start]Provides information on available TinyShell commands[cite: 183].         |
| `exit`          | [cite_start]Gracefully terminates the TinyShell session[cite: 183, 187].             |
| `date`          | [cite_start]Displays the current system date[cite: 183, 197].                        |
| `time`          | [cite_start]Displays the current system time[cite: 183, 191].                        |
| `clear`         | [cite_start]Clears the terminal screen[cite: 183, 203].                              |
| `dir`           | [cite_start]Lists files and subdirectories in the current directory[cite: 183, 208]. |
| `path`          | [cite_start]Displays the current Path environment variables[cite: 183, 213].         |
| `addpath [dir]` | [cite_start]Adds a new directory to the User Path[cite: 183, 226].                   |

### Process Control

- [cite_start]**`start [program] [mode]`**: Executes a program (mode defaults to background)[cite: 183, 235, 241].
- [cite_start]**`list`**: Displays all background processes including ID, PID, State, and Name[cite: 183, 246].
- [cite_start]**`stop [ID]`**: Suspends a running process by its ID[cite: 183, 290].
- [cite_start]**`resume [ID]`**: Resumes a suspended process[cite: 183, 322].
- [cite_start]**`kill [ID]`**: Terminates a specific process (use `-1` to terminate all)[cite: 183, 254].

---

## ⚙️ Installation & Setup

### Requirements

- [cite_start]**OS**: Windows 10 or later[cite: 352].
- [cite_start]**Compiler**: MSVC or MinGW supporting C++14[cite: 45, 353].

### Build Instructions

1. [cite_start]**Clone the project**: `git clone https://github.com/bv09/Shell.git`[cite: 355, 356].
2. [cite_start]**Navigate to directory**: `cd Shell`[cite: 357, 358].
3. [cite_start]**Compile**: `gcc Shell.cpp -o Shell`[cite: 359, 360].
4. [cite_start]**Run**: `.\Shell`[cite: 361, 362].

---

## 👥 Contributors

- [cite_start]**Nguyễn Quốc Anh** - 202416414 [cite: 13]
- [cite_start]**Nguyễn Quốc Bảo** - 202416424 [cite: 14]
- [cite_start]**Lê Anh Dũng** - 202416424 [cite: 15]

**Supervisor**: TS. [cite_start]Phạm Đăng Hải [cite: 12]
