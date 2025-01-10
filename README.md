# SIMPLE SHELL 🐧 
![Mon image](https://imgur.com/9kvWCsB.gif)

## 📄 Description

This project implements a simplified Shell in C, mimicking some of the basic founctionalities of a Unix shell like Bash. It supports command execution, argument handling, built-in commands, path searching, error handling, and operates in both interactive and non-interactive modes.

### 📋 Requirements


* Allowed editors: vi,vim or emacs.
* All the files will be compiled on Ubuntu 20.04 LTS using gcc.
* Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/hs-hq/Betty/blob/main/betty-style.pl) and [betty-doc.pl](https://github.com/hs-hq/Betty/blob/main/betty-doc.pl).
* You are not allowed to use global variables
* No more than 5 functions per file.
* The prototypes of all your functions should be included in your header file called main.h


## ✨Features

| Feature | Description |
| :--------------------: | :--------------------------: |
  |🔨**Command Execution:** |Executes external commands   (e.g.,**ls**, **cat**... ) using **==fork()==** and **==execve()==**.|                                                          
 |🧩 **Argument handling:** |The shell can handle arguments passed to commands (e.g.,**ls -a**).|
  |🤖 **Built-in commands:** |Implementation of the **exit** command which allows you to quit the shell.|
|🧭**Path searching:** |Shell searches for commands in the directories specified by the **PATH** environmentvariable.|
|⚠️ **Error handling:** |Shell handles basics errors such as invalid commands or system call failures|
 |✏️**Two modes:**  |
|| - **Interactive mode:** The shell displays a prompt and waits for the user to type a command.|
||- **Non-interactive mode:** The shell reads commands from a file or a pipe and executes them.|


## 🤔 Flowchart

![Mon image](https://imgur.com/JIRFPRK.png)
## 📂 Files main functions

| FILE  |DESCRIPTION|
| :--------------------: | :--------------------------: |
|`execute_command.c` |contains the functions that are mandatory for the shell to work|
|`shell.h` |contains the main structure and the function prototypes|
|`man_1_simple_shell` |man page of the imple shell program|
|`find_in_path.c`  |contains the functionsearch for a command in the PATH |
|`library.c`   |contains small functions for added value functionality (e.g.print env)|
|`shell.c`|contains my main shell function|
|`simple_shell.c`| contains the functions that does interative and non-interactive mode|
                                                                        
 ## 🚀 Getting Started


### Compilation

Ready to compile? Just use this command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c -o hsh
```

## ⚙️Usage

### 1- Include the header file:

```
#include "shell.h"
```
### 2- This simple shell can be ran in two modes:

#### 👨‍💻 ️Interactive mode

The shell displays a prompt and waits for the user to type a command.

### 💲Examples


![Mon image](https://imgur.com/TS855eT.png) 

#### 📜 Non-Interactive mode

The shell reads commands from a file or a pipe and executes them.
### 💲Examples

![Mon image](https://imgur.com/gvq8Uxs.png) 

### 📖 MAN page

Execution: `man ./man_1_simple_shell`

![Mon image](https://imgur.com/KiOneXz.png)

**This is a simple shell project developed as part of the Holberton School curriculum.**


## 🧑💻 Authors

[Maxime TRUEL](https://github.com/MaKSiiMe),
[Charlène MARTIN](https://github.com/Knarta)

<p align="center">
<img src="https://ml.globenewswire.com/Resource/Download/a08e6c28-55be-44c8-8461-03544f094b38" width="400" height="100">
</p>
