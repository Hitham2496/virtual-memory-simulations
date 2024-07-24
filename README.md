
# Simple Simulation of Virtual Memory Management

This repository is intended as a learning tool for virtual memory management in Linux.

There is a C and python implementation of memory management in linux including:
1. Page access
2. Page loading into frames
3. Page swapping with disk
4. Handling page faults

The main method accesses pages in a simulated (and highly simplified!) virtual memory
framework, handling page faults for each new access and swapping when the physical memory
is full.

## C Implementation

Navigate to `c-implemtation` with `cd c-implementation`

Compile the code with `make`

This will create a directory called `build` which contains the build files and binary.

To run:

```bash
./build/bin/memory_manager
```

## Python Implementation

Navigate to `python-implemtation` with `cd python-implementation`

Run with:

```bash
python3 memory_manager.py
```

## To Add

Expanding this to include description (in presentation format of):

1. Consequences of virtual memory management for user/developer
2. How virtual memory management fits in with LSF/HPC
3. Discussion of shared memory
4. Common pitfalls with virtual memory management systems
