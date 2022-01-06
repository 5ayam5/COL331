---
geometry:
- top=25mm
- left=20mm
- right=20mm
- bottom=30mm
documentclass: extarticle
fontsize: 12pt
numbersections: true
title: Lecture 1 (Introduction to UNIX System Calls)
--- 

# History of OS
1. The very first OS was a set of device drivers, it was a uni-process OS
1. UNIX was a breakthrough OS developed by Ken Thompson along with Dennis Ritchie etc

# UNIX Properties
1. Memory was exclusive but data was shared in UNIX
1. Filesystem was developed
1. Shell was implemented inside the kernel
1. Kernel functions are called system calls
1. Shared resources are mediated by the OS (hardware devices)

## Reading from File
1. Filenames were used with directory structure
1. Concept of file descriptor existed (fd)
1. `read/write(fd, buffer, #bytes)` was the way to read/write to file

## Resource Usage
1. They are also used similar to reading from file - `open`, `read`, `write`, `close`
1. Errors are returned for invalid usage

## Shell Program
1. It is the base program which transfers control to executables based on user commands
1. Exiting the program returned back to the shell
1. Opened files were closed on exiting

### Improvements from the Original UNIX Version
1. Shell is no more a part of OS and is made an application, the kernel has been minimised
1. UNIX provides syscalls `fork` and `exec`
    - `exec` replaces current program with the new program
    - `fork` creates identical programs with identical states and program counters
        i. Parent process is stored to disk since only one process can run at any time
        i. Child process calls `exec`
        i. `fork` returns the *pid* of child for parent and 0 for child

### Basic Shell Command
```c
while(1) {
  readCommand(); // calls other system commands
  pid = fork(); // syscall
  if (pid == 0)
    exec(command);
}
```

## File Descriptors
1. On opening a new 'file', the first empty index from **File Descriptor Table** is returned (this table is hidden from the program)
1. Indices 0, 1, 2 are reserved for STDIN, STDOUT, STDERR respectively
