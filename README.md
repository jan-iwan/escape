# ANSI Escape Sequences

My attempt to write a simple library in C to make writing ANSI escape sequences easy.
I'm sorry for the use of gotos.

This library provides functions for printing single escape sequences, colored output, formatted colored output and move the cursor around.

## Installation
The library has no external dependencies so simply compile by running:
```sh
make
```
And install by running (as root):
```sh
make install
```
Alternatively, you can also copy the shared object and the header (located at src/escape.h) manually

## Usage
To use in C simply add `#include <escape.h>` to your source code and compile with "-lescape".
By default the shared object (libescape.so) is installed at /usr/local/lib which may need to be added to the environment variable LD_LIBRARY_PATH for the library to be found by the linker.
An explanation in how to use the function provided by the library is available in the header (escape.h).

Not all the cursor control sequences were implemented.
All the other escape sequences were not implemented
