# BSDSF23M046-OS-A03: Advanced Command-Line Interpreter (Shell)

## 🌟 Operating Systems Programming Assignment - 03

This repository contains the complete implementation of an advanced command-line interpreter (shell), developed as part of the Operating Systems course. The project is an incremental build on a base UNIX shell, adding professional features that demonstrate a deep understanding of process management, I/O handling, and system programming in a UNIX-like environment.

**Instructor:** Muhammad Arif Butt, PhD

---

## 🚀 Learning Objectives & Implemented Features

The core objective of this assignment was to master the complete development lifecycle of a complex system utility and implement the following key shell features:

| Feature | Marks | Concepts Covered | Tag Version |
| :--- | :---: | :--- | :--- |
| **Feature-1: The Base Shell** | 05 | Initial Project Setup and Git Workflow | `v1.0-base` |
| **Feature-2: Built-in Commands** | 10 | `exit`, `cd`, `help`, `jobs` (placeholder) | `v2` |
| **Feature-3: Command History** | 10 | Storing, displaying (`history`), and re-executing (`!n`) commands. | `v3` |
| **Feature-4: Tab Completion with Readline** | 15 | Integration of the GNU Readline library for command-line editing and tab completion. | `v4` |
| **Feature-5: I/O Redirection and Pipes** | 15 | Implementation of Input (`<`), Output (`>`), and Pipes (`|`) using `dup2()`, `open()`, and `pipe()`. | `v5` |
| **Feature-6: Command Chaining and Background Execution** | 15 | Sequential command execution (`;`) and non-blocking background processes (`&`), including zombie reaping with `waitpid(WNOHANG)`. | `v6` |
| **Feature-7: The if-then-else-fi Structure** | 10 | Implementation of conditional logic based on the exit status of commands. | `v7` |
| **Feature-8: Shell Variables** | 10 | Variable assignment (`VAR=value`) and variable expansion (`$VARNAME`) before execution. | `v8` |
| **Feature-9: Professional Git Workflow** | 10 | Simulation of a collaborative workflow using Forks, Issues, and Pull Requests. | N/A |

---

## 🛠️ Project Structure and Setup

The shell is built from modular C source files:
