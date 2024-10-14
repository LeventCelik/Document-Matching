# Suffix Tree in Linear Time

Spring 2024 Clemson University Advanced Data Structures Course Project

## Abstract

This project implements the Kärkkäinen & Sanders DC3/Skew algorithm for linear time building of suffix arrays, Kasai's algorithm for linear time building of LCP arrays, and traversals for suffix array to suffix tree / suffix tree to suffix array transformations.

## Building the Program

The program can be built and run by calling using the Makefile. 'make' builds the project, 'make run' runs it, building if necessary, 'make clean' cleans object and executable files, and 'make debug' attaches the program with compiled with debug symbols to gdb.

The Makefile is written for Windows and Unix systems, and was tested on a Windows 10, a MacOS, and an Ubuntu system. Makefile places the executable in bin/, and debug executable in debug/.

Adding "-D DEBUG" to DBGFLAGS in the Makefile enables printing debug text to the standard output. The printing is not too useful, and is quite messy for large string sizes, but I used it for debug purposes only, and the debug_print macros served as my learning experiments with C macros. Thus, I am not too happy with the final debug printing functionality, and I did not configure the Makefile for easier printing because of it.

## Project Structure

The project is divided into three main files.

- *utils.c* contains several helper functions
- *document_matching.c* contains the main functionality: building a suffix array, building an LCP array by using the suffix array, building a suffix tree by using a suffix array together with an LCP array, and building a suffix array using a suffix tree. Functionality for building the LCP array at the same time as building the suffix array is not implemented.
- *test.c* includes tests and the *main()* function. Random strings are tested with a base number to several exponents, which can be configured by altering the define statement in this file.

## Results

Running the program automatically appends the results to output.csv, creating it if it does not exist. The results are averaged over 1000 runs per string size and display an linear time complexity.

## Issues

I dislike two particular things:

- Representing values as 'int' rather than 'unsigned int' and 'size_t', but I decided to go with simplicity, readability, and a portable random generator for a proof of concept program.
- The printing macros and how printing looks. It does not make sense to print arrays of hundreds of thousands of elements and a better way definitely exists, but I leave it as my apprentice product.

## References

Several StackOverflow questions and public lecture slides were employed while implementing this project. GitHub Copilot was used on rare occasions for boilerplate code, explaining C syntax, and debugging.
