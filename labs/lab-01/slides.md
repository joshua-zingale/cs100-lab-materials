% Setting Up Your Development Environment
% Joshua Zingale

# Logistics

- Each lab is assigned on Wednesday on a particular week, and the demo is due during your lab session on the following week
- All labs must be demo'ed either to the TA or a Grader
- For all demos, you will need to schedule the demo slot beforehand
- After Lab 1, all labs are to be done in pairs. There is no exception to this rule. Both teammates need to be enrolled in the same lab section


# Lab Schedule

1. A ~20 minute lecture
2. Time to work on and demo the labs


# Linux

- Ubuntu, Debian, Fedora, etc are operating systems bult on top of the Linux kernel.
- The Linux kernel is used by the operating systems running most of the production services.
- Such operating systems come with a standard set of GNU core utilites:
    - cd
    - ls
    - rm
    - sudo
    - &c.
- The most effective way to interact with production systems is often through the terminal.


# SSH

```bash
ssh <username>@example.com
```

- Connecting to systems in-person is inconvenient.
-  *S*ecure *SH*ell is an encrypted protocol for accessing a machine's terminal over the web.


# GNU Compiler

```bash
g++ -o area_calculator main.cpp
```

- gcc/g++ are C/C++ compilers offered by GNU.
- One or more source files can be linked and compiled into an executable file.


# git

```bash
git init
echo "target/*" > .gitignore
git add .
git commit -m "initial commit"
```

- A version management system that facilitates simultaneous development
- Work is commited to a branch.
- Branches may be merged with each other.
- There are both local and remote git repositories.

# GitHub

```bash
git clone <some GitHub url>
git add .
git commit -m "Added bounds checking on user input"
git push
```

- A comercial platform that offers remote git repositories

# VIM

```bash
vim filename.cpp
```

- Mode-based text-file editor.
- Terminal (i.e. character-based) GUI
- Preinstalled on most common Linux distributions.
- Efficient file navigation and editing operations.
- Easy integration with core utilities.

# Visual Studio Code

- Microsoft-created open-source code editor.
- Full GUI
- Extension marketplace for quick access to programming language support and visualization tools.

