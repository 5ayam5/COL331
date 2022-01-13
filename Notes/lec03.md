---
header-includes:
- \hypersetup{colorlinks=true}
geometry:
- top=25mm
- left=20mm
- right=20mm
- bottom=30mm
documentclass: extarticle
fontsize: 12pt
numbersections: true
title: Lecture 3 (Threads, Address Spaces, Filesystem, Devices)
--- 

# More (Recap?) about Processes
1. Address space of the process is restricted to the process
1. OS on performing `init` creates some processes which create some other processes in return
1. OS cleans up entire data of child process only after wait is called since exit code of child is needed (such child processes are called zombie processes)

# Signals
1. Signals raised by OS are sent to signal handler created by process (else default is used)
1. Such a handler interrupts the execution of the process and executes its tasks
1. Execution resumes after handler returns
1. It is like an async function call

## Syntax
`signal(int signum, void (*handler)(int))`

## Standard Signals
1. SIGINT
1. SIGSTOP (cannot be overwritten)
1. SIGSEGV
1. SIGFPE
1. SIGCHLD (child exits, helps in preventing zombie processes when commands are run as `ls &`, i.e., when parent doesn't wait)

## `kill`
A command used to send signals to other processes

`kill(pid, signum)`

# Pseudo-Filesystem
`/proc/` is a pseudo-fs which contains information about processes (each pid has its own directory), this directory can be read/written using open/close

# Threads
1. `write`, `read` are heavy calls and if processes require many read-write operations, it is not suggested to use these syscalls
1. Instead concept of threading can be used
1. Threads are part of processes which share the same address space but run independently
1. There are two ways of creating threads:
    - Kernel-level: having a syscall
    - User-level: creating 'logical' threads, which don't execute concurrently (when blocking via some syscalls), but only logically - a scheduler is needed
