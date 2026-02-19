# KL25Z Assembly Intro

Introduction to ARM Cortex-M assembly development using the NXP FRDM-KL25Z microcontroller and Keil uVision (ARM MDK v5.31).

This project focuses on low-level programming concepts, integer-based computation, and understanding how high-level logic translates to assembly instructions.


## Project Overview

This lab introduces:

- ARM Cortex-M assembly syntax and structure  
- Register-level operations  
- Integer arithmetic implementation  
- Subroutine structure and branching  
- Stack usage and function calls  


## Task Summary

### Task 1 – Lab Environment Setup

- Configure Keil uVision project for FRDM-KL25Z  
- Work through initial tutorial steps  
- Verify successful compilation and flashing to hardware  


### Task 2 – Integer Square Root (Bisection Method)

Implemented an assembly subroutine to approximate the square root of an integer using the **bisection method**.

**Key Characteristics**

- All arithmetic performed using integers  
- Resulting square root is also an integer  
- No floating-point operations used  
- Iterative midpoint refinement  
- Conditional branching for convergence  

**Engineering Focus**

- Algorithm-to-assembly translation  
- Control flow implementation (loops and branches)  
- Register management  
- Deterministic execution behavior  


## Concepts Demonstrated

- ARM assembly fundamentals  
- Stack and register discipline  
- Integer math implementation  
- Embedded-level algorithm execution  
- Low-level debugging and verification  


## Platform & Tools

- NXP FRDM-KL25Z Development Board  
- ARM Cortex-M0+ architecture  
- ARM Keil MDK v5.31  
- uVision IDE  


---

This project demonstrates foundational embedded systems knowledge by implementing algorithmic logic directly in assembly, reinforcing low-level system control and hardware-aware programming.
