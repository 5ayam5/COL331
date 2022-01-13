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
title: Lecture 4 (PC Architecture)
--- 

# Introduction
1. We will be discussing x86 Architecture
1. It is a fairly complex architecture
1. However it is the most common architecture in use right now

# CPU
1. Components are:
    i. Registers (integer and floating point)
    i. Memory Management Unit (MMU)
1. Instructions are executed one after the other

# x86 Architecture
1. The actual processor that will be taken as reference is Intel 8086
1. 4 16-bit registers are present - AX, BX, CX, DX
1. These registers were also divided into halves - ?H, ?L (? = A, B, C, D)
1. 4 more registers were present:
    i. SP = Stack Pointer
    i. BP = Base Pointer
    i. SI = Source Index
    i. DI = Destination Index
1. PC register was also present (gets incremented on every IF (Instruction Fetch), if no branches or jumps)
1. FLAGS register is also present (cannot be modified directly) - flags here are set when some arithmetic or other errors happen
1. AT&T syntax is going to be used for x86
1. 4 segments are also present:
    i. CS - Code Segment
    i. DS - Data Segment
    i. SS - Stack Segment
    i. ES (for anything else)
1. This suggests that more than $2^{16}$ memory locations are not possible but it is possible to read until $2^{20}$ ($segment \times 16 + PC$)

Backward compatibility is provided till date, so an OS first boots in 16-bit mode and then it switches to 32-bit (and then to 64-bit) mode as required

# Extension from 16 to 32 bits
1. Each register has been renamed as E??
1. Old names can still be used to refer the lower 16 bits
1. Instructions have been modified to work with 32-bit registers
1. New prefixes (for each instruction) have been created to work with 16 bits (0x66 for data and 0x67 for address)
1. .code32 directive is used to inform assembler that the instructions after this are in 32-bit by default

# AT&T Syntax
```x86asm
movl %eax, %edx // edx = eax
movl $0x123, %edx // edx = 0x123
movl 0x123, %edx // edx = *(int *) 0x123
movl (%ebx), %edx // edx = *(int32 *)ebx
movl (%ebx), %edx // edx = *(int32 *)(ebx + 4)
```

