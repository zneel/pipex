<div align="center">
<h1 align="center">
<img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" />
<br>pipex
</h1>
<h3>◦ Unlock limitless potential with Pipex!</h3>
<h3>◦ Developed with the software and tools listed below.</h3>

<p align="center">
<img src="https://img.shields.io/badge/C-A8B9CC.svg?style&logo=C&logoColor=black" alt="C" />
</p>
<img src="https://img.shields.io/github/languages/top/zneel/pipex?style&color=5D6D7E" alt="GitHub top language" />
<img src="https://img.shields.io/github/languages/code-size/zneel/pipex?style&color=5D6D7E" alt="GitHub code size in bytes" />
<img src="https://img.shields.io/github/commit-activity/m/zneel/pipex?style&color=5D6D7E" alt="GitHub commit activity" />
<img src="https://img.shields.io/github/license/zneel/pipex?style&color=5D6D7E" alt="GitHub license" />
</div>

---

## 📒 Table of Contents
- [📒 Table of Contents](#-table-of-contents)
- [📍 Overview](#-overview)
- [⚙️ Features](#-features)
- [📂 Project Structure](#project-structure)
- [🧩 Modules](#modules)
- [🚀 Getting Started](#-getting-started)
- [🗺 Roadmap](#-roadmap)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👏 Acknowledgments](#-acknowledgments)

---


## 📍 Overview

The "pipex" project is a command-line utility that enables the execution of commands with input/output redirection and piping between processes. It manages pipes, forks child processes, handles file descriptors, and executes commands in a controlled environment. The project provides a valuable tool for manipulating and redirecting data flow in a UNIX-like operating system, enhancing productivity and convenience for users working with command-line applications.

---

## ⚙️ Features

| Feature                | Description                           |
| ---------------------- | ------------------------------------- |
| **⚙️ Architecture**     | The system follows a modular architecture, with separate files for handling paths, commands, pipes, and execution. It utilizes the fork-exec technique for executing commands in child processes and managing pipes for inter-process communication. The architecture focuses on separation of concerns and easy extensibility.    |
| **📖 Documentation**   | The codebase contains comments and function descriptions for most of the files, providing some level of documentation. However, there is room for improvement in terms of comprehensive documentation, especially regarding the overall project structure and principles.    |
| **🔗 Dependencies**    | The system depends on the "libft" library for compilation and linking. It utilizes standard C libraries such as "stdio.h" and "stdlib.h" for program functionality. No further significant external dependencies are observed.    |
| **🧩 Modularity**      | The system demonstrates good modularity by organizing code into separate files based on their functionalities, such as paths, commands, pipes, execution, utilities, and bonus features. This approach allows easier maintenance and reusability of code segments, enabling developers to swap and modify components without impacting other system functionalities.    |
| **✔️ Testing**          | There is no explicit mention of testing strategies or tools within the codebase. The lack of automated tests raises concerns about the reliability of individual components and the system as a whole. Additional testing efforts, such as unit tests and integration tests, would be beneficial for better code quality and bug prevention.    |
| **⚡️ Performance**      | The codebase appears to focus on functionality rather than performance optimization. Although the use of pipes and child processes promotes efficient execution, there is no specific implementation demonstrating significant performance improvements. Overall resource usage, efficiency, and speed are dependent on the underlying system performance.    |
| **🔐 Security**        | The codebase does not showcase explicit security measures apart from regular process isolation. However, the interaction with external commands and handling of input/output streams might introduce security vulnerabilities if not implemented with caution. Secure coding practices and input validation would enhance security aspects.    |
| **🔀 Version Control** | The system's version control relies on Git, as indicated by the repository. It provides the ability to track changes, collaborate on development, and rollback to previous versions. However, no specific mention of branching strategies or tools is evident within the codebase.    |
| **🔌 Integrations**    | The system does not integrate directly with other systems or services. It focuses on command execution, managing pipes, and handling input/output redirection within its own scope. However, it could be extended to interact with external systems or processes using appropriate interfaces and protocols.    |
| **📶 Scalability**     | The system demonstrates decent scalability potential due to its modular architecture. Adding new functionalities or extending existing features can be achieved with relative ease using the current design. However, without further details or specific performance benchmarks, it is challenging to provide a comprehensive assessment of its scalability characteristics.    |

---


## 📂 Project Structure




---

## 🧩 Modules

<details closed><summary>Root</summary>

| File                                                          | Summary                                                                                                                                                                                                                                                                      |
| ---                                                           | ---                                                                                                                                                                                                                                                                          |
| [Makefile](https://github.com/zneel/pipex/blob/main/Makefile) | This code is for a program called "pipex." It is responsible for executing commands and managing pipes. It has a bonus version that includes additional features. The code is compiled using the "cc" compiler and the resulting binary is dependent on the "libft" library. |

</details>

<details closed><summary>Src</summary>

| File                                                                  | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| ---                                                                   | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [path.c](https://github.com/zneel/pipex/blob/main/src/path.c)         | The code provides functionalities to validate and find the correct path for a given command. It tests whether a command is valid, splits the paths in the environment variable, and checks if the command exists in any of the paths. If the command is not found, it joins the path with the command to create a complete path and checks its validity. The code also includes functions to retrieve the command with the correct path from the input, taking the environment into consideration. |
| [commands.c](https://github.com/zneel/pipex/blob/main/src/commands.c) | This code file provides functions for managing commands in a command-line utility. It includes functions for creating a new command, cleaning up command memory, adding commands to a list, and cleaning up the list of commands.                                                                                                                                                                                                                                                                  |
| [pipe.c](https://github.com/zneel/pipex/blob/main/src/pipe.c)         | The code defines functions to parse, execute, and handle commands in a piped execution context. It initializes and manages pipes, forks child processes, and executes the commands with correct redirection and input/output handling. Finally, it waits for the child processes to finish execution.                                                                                                                                                                                              |
| [pipes.c](https://github.com/zneel/pipex/blob/main/src/pipes.c)       | The code provides functions to handle piping in a shell program. The functions configure the file descriptors for communication between processes through pipes, including handling input/output redirection.                                                                                                                                                                                                                                                                                      |
| [utils.c](https://github.com/zneel/pipex/blob/main/src/utils.c)       | The code defines three functions: 1. "close_pipe" to close read and write file descriptors of a pipe.2. "free_split" to deallocate memory allocated to a dynamic array of strings.3. "exit_error" to close a pipe and exit the program with an error code.                                                                                                                                                                                                                                         |
| [execute.c](https://github.com/zneel/pipex/blob/main/src/execute.c)   | The `execute.c` code consists of several functions related to executing commands. The `wait_for_cmds` function waits for all commands to finish execution. The `execute` function executes a command by calling `execve` and handles potential errors. The `pipe_exec` function handles the execution of commands with pipe redirection.                                                                                                                                                           |
| [main.c](https://github.com/zneel/pipex/blob/main/src/main.c)         | The main function initializes the pipeline structure, parses command-line arguments, opens input and output files, executes the pipex function, cleans up resources, and returns 0.                                                                                                                                                                                                                                                                                                                |
| [usage.c](https://github.com/zneel/pipex/blob/main/src/usage.c)       | The code provides a `print_usage` function that displays the correct usage of the program.The `check_args` function checks the number of arguments passed to the program and exits with an error message if it is not equal to 5.                                                                                                                                                                                                                                                                  |

</details>

<details closed><summary>Include</summary>

| File                                                                              | Summary                                                                                                                                                                                                                                                                                                                                                               |
| ---                                                                               | ---                                                                                                                                                                                                                                                                                                                                                                   |
| [pipex_bonus.h](https://github.com/zneel/pipex/blob/main/include/pipex_bonus.h)   | The code provided includes the declarations of functions for handling a pipex bonus feature, such as checking for a here-doc token, validating command line arguments, and handling the here-doc input redirection.                                                                                                                                                   |
| [pipex.h](https://github.com/zneel/pipex/blob/main/include/pipex.h)               | The code in pipex.h is a header file that defines various functions and includes necessary libraries for a program called "pipex". It handles piping data between processes and executing commands with input/output redirection. The code also has error handling functionalities and defines data structures and utility functions for managing commands and pipes. |
| [pipex_struct.h](https://github.com/zneel/pipex/blob/main/include/pipex_struct.h) | This code defines two structs: t_pipe and t_cmd. t_pipe represents information related to pipes, file descriptors, command arguments, and the last command's execution status. t_cmd represents a single command line input, storing the parsed command, the raw input, and information about pipes and its index.                                                    |

</details>

<details closed><summary>Src_bonus</summary>

| File                                                                                    | Summary                                                                                                                                                                                                                                                                                                                                                                                                                             |
| ---                                                                                     | ---                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| [utils_bonus.c](https://github.com/zneel/pipex/blob/main/src_bonus/utils_bonus.c)       | This code contains three functions: 1. "close_pipe" closes file descriptors for reading and writing.2. "free_split" frees memory allocated for a split string.3. "exit_error" closes the pipe and exits the program with an error code.                                                                                                                                                                                             |
| [here_doc_bonus.c](https://github.com/zneel/pipex/blob/main/src_bonus/here_doc_bonus.c) | This code implements the functionality for here documents, which allows the user to input text that is then used as input for the command in a pipeline. It checks for the presence of a "here_doc" argument, creates temporary files for the input, prompts the user for input, and handles the input until the user enters a specified delimiter. Finally, it opens the temporary file and sets it as the input for the pipeline. |
| [usage_bonus.c](https://github.com/zneel/pipex/blob/main/src_bonus/usage_bonus.c)       | The code provides error checking and usage display for a program called `pipex_bonus`. It checks the number of arguments passed to the program and calls the appropriate printing functions. It also checks for a specific argument format for a `here_doc` case.                                                                                                                                                                   |
| [main_bonus.c](https://github.com/zneel/pipex/blob/main/src_bonus/main_bonus.c)         | The code implements the main program flow for a pipex command, which is used to redirect input and output of commands in a UNIX-like operating system. It initializes the necessary variables, parses the command-line arguments and environment variables, performs input/output redirection, executes the pipex command, and cleans up resources before exiting.                                                                  |

</details>

---

## 🚀 Getting Started

### ✔️ Prerequisites

Before you begin, ensure that you have the following prerequisites installed:
> - `ℹ️ Requirement 1`
> - `ℹ️ Requirement 2`
> - `ℹ️ ...`

### 📦 Installation

1. Clone the pipex repository:
```sh
git clone https://github.com/zneel/pipex
```

2. Change to the project directory:
```sh
cd pipex
```

3. Install the dependencies:
```sh
gcc -o myapp main.c
```

### 🎮 Using pipex

```sh
./myapp
```

### 🧪 Running Tests
```sh
/* No common unit test framework in C */
```

---


## 🗺 Roadmap

> - [X] `ℹ️  Task 1: Implement X`
> - [ ] `ℹ️  Task 2: Refactor Y`
> - [ ] `ℹ️ ...`


---

## 🤝 Contributing

Contributions are always welcome! Please follow these steps:
1. Fork the project repository. This creates a copy of the project on your account that you can modify without affecting the original project.
2. Clone the forked repository to your local machine using a Git client like Git or GitHub Desktop.
3. Create a new branch with a descriptive name (e.g., `new-feature-branch` or `bugfix-issue-123`).
```sh
git checkout -b new-feature-branch
```
4. Make changes to the project's codebase.
5. Commit your changes to your local branch with a clear commit message that explains the changes you've made.
```sh
git commit -m 'Implemented new feature.'
```
6. Push your changes to your forked repository on GitHub using the following command
```sh
git push origin new-feature-branch
```
7. Create a new pull request to the original project repository. In the pull request, describe the changes you've made and why they're necessary.
The project maintainers will review your changes and provide feedback or merge them into the main branch.

---

## 📄 License

This project is licensed under the `ℹ️  INSERT-LICENSE-TYPE` License. See the [LICENSE](https://docs.github.com/en/communities/setting-up-your-project-for-healthy-contributions/adding-a-license-to-a-repository) file for additional info.

---

## 👏 Acknowledgments

> - `ℹ️  List any resources, contributors, inspiration, etc.`

---
