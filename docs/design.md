# Chapter 2: System Design

## 2.1 System Architecture

The project is divided into multiple modules.

### main.c
Controls the main program and algorithm selection.

### input.c
Handles user input and input validation.

### simulator.c
Manages frames, page searching and memory initialization.

### fifo.c
Implements FIFO page replacement.

### lru.c
Implements LRU page replacement.

### optimal.c
Implements Optimal page replacement.

### algorithms.h
Declares algorithm functions.

### simulator.h
Defines the main simulation data structures.

### input.h
Declares input functions.

## 2.2 Data Structures

ReferenceString:
Stores page references using dynamic memory.

FrameSet:
Stores pages currently loaded into frames.

SimulationStats:
Stores Page Fault and Page Hit statistics.

## 2.3 Program Workflow

1. Read frame count.
2. Read reference string.
3. Select an algorithm.
4. Initialize frames.
5. Execute the selected algorithm.
6. Calculate statistics.
7. Display simulation results.
8. Release allocated memory.

## 2.4 Memory Management

The project uses malloc() for dynamic
memory allocation and free() for releasing
allocated memory.

## 2.5 Build System

GNU Make is used to automate compilation.
GCC compiles all source files into the
page_simulator executable.
