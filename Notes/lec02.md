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
title: Lecture 2 (UNIX System Calls part 2)
--- 

# Inter Process Communication (IPC)
exit code is one way, between child and parent

# Why is `fork` + `exec` good?
1. It seems wasteful to copy information of parent to just destroy the child via `exec`
1. Windows uses `create_process` instead
1. To ensure shell redirection and other features, the command requires 10 arguments
1. Also, `fork` can be made faster by just storing references and copying only when needed

# More about FDT and Processes
1. Each process has its associated FDT
1. Interaction with FDT can only happen via syscalls
1. Each entry in FDT points to a certain resource and offset
1. `write` appends the offset on every successful write
1. The resource can be shared, called file sharing
1. To change the standard output, we do:

    ```c
    close(1);
    open("foo"); // smallest empty entry in FDT is at index 1
    ```
1. Similar as above for standard error

To write simultaneously to same file by STDOUT and STDERR, we do the following:
```c
close(1);
open("foo");
close(2);
dup(1); // opening foo again will not make pointers to same object, but dup will
```
The same command in shell looks like:
```bash
$ program > foo >2 &1
```

# Pipe
1. Connecting the STDOUT of one program to STDIN of a different program
1. `pipe(int[] fdarray)` is the syntax of the syscall
1. Consider the example:

    ```c
    int fdarray[2];
    pipe(fdarray);
    write(fdarray[1], "hello");
    read(fdarray[0], buf, 6); // "hello" is stored at buf
    ```
1. Notice that the pipe is created from right to left
1. `pipe` is used as follows

    ```c
    pipe(fdarray);
    pid = fork(); // pipe is shared
    if (pid > 0) {
      write(fdarray[1], ...);
    } else {
      read(fdarray[0], ...);
    }
    ```
1. Now, this is how shell implements the following pipe command: `command1 | command2`

    ```c
    int fdarray[2];
    if (pipe(fdarray) < 0) panic ("error");
    if ((pid = fork ()) == 0) {  // child (left end of pipe)
      close (1);
      tmp = dup (fdarray[1]);   // fdarray[1] is the write end, tmp will be 1
      close (fdarray[0]);       // close read end
      close (fdarray[1]);       // close fdarray[1]
      exec (command1, args1, 0);
    } else if (pid > 0) {        // parent (right end of pipe)
      close (0);
      tmp = dup (fdarray[0]);   // fdarray[0] is the read end, tmp will be 0
      close (fdarray[0]);
    	close (fdarray[1]);       // close write end
    	exec (command2, args2, 0);
    } else {
      printf ("Unable to fork\n");
    }
    ```
1. Pipe's size is limited, therefore, the commands are actually run together so that the pipe gets emptied along the way and it also helps with scheduling
1. Useful [link](https://linux.die.net/man/7/pipe) (pipe man page)
