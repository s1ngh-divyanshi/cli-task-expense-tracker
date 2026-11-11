# CLI Task & Expense Tracker

A lightweight, terminal-based personal productivity tool written in modern C++ (C++17). Track daily tasks and manage personal expenses with structured CSV persistence and zero external dependencies.

---

## Features

- **Unified Management**: Track tasks (with completion statuses) and financial expenses in a single CLI interface.
- **Categorization & Aggregation**: Categorize entries (e.g., *Work*, *Food*, *Travel*) with automatic expense totals and category breakdowns.
- **Persistent Storage**: Automatically saves state to `tracker_data.csv` using atomic file writes to prevent data corruption.
- **Input Validation**: Clean input stream handling resistant to malformed entries and invalid types.
- **Developer Ready**: Preconfigured with `Makefile` and VS Code tasks for single-shortcut building and GDB/LLDB debugging.

---

## Project Structure

```text
cli-tracker/
├── Makefile               # Build automation script
├── README.md              # Project documentation
├── include/               # Header interfaces (.hpp)
│   ├── Item.hpp           # Entity definitions and CSV serialization contracts
│   └── Tracker.hpp        # Core business logic and storage management
└── src/                   # Source implementations (.cpp)
    ├── Item.cpp           # Parsing and serialization logic
    ├── Tracker.cpp        # Data manipulation and file I/O
    └── main.cpp           # Interactive CLI menu loop (REPL)
```

---

## Prerequisites

- **C++ Compiler**: `g++` (GCC 9+) or `clang++` (LLVM 10+) with C++17 support
- **Build Tool**: `make` (optional, but recommended)
- **Debugger**: `gdb` (Linux/Windows) or `lldb` (macOS)

---

## Quick Start

### 1. Build the Executable

Using `make`:
```bash
make
```

Or compile directly via `g++`:
```bash
mkdir -p bin
g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/Item.cpp src/Tracker.cpp -o bin/tracker
```

### 2. Run the Application

```bash
# Linux / macOS
./bin/tracker

# Windows
.\bin\tracker.exe
```

### 3. Clean Build Artifacts

```bash
make clean
```

---

## Storage Schema

Data persists automatically in `tracker_data.csv` using the following comma-separated structure:

| Column | Type | Description |
| :--- | :--- | :--- |
| `id` | Integer | Unique identifier generated on creation |
| `type` | String | `TASK` or `EXPENSE` |
| `title` | String | Description or item name |
| `category` | String | Grouping tag (e.g., `Work`, `Study`, `Food`) |
| `amount` | Float | Monetary value (`0.00` for tasks) |
| `isCompleted`| Integer | `1` for completed/cleared, `0` for pending |
| `date` | String | Formatted date string (`YYYY-MM-DD`) |

---

## Development & Debugging

This project includes `.vscode` integration for development:

- **Build**: Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS) to run the `make` build task.
- **Debug**: Press `F5` to trigger the build and launch GDB/LLDB with breakpoints enabled.

---

## License

Distributed under the [MIT License](https://www.google.com/search?q=LICENSE).
