# escape 0.5
![escape](https://raw.githubusercontent.com/jan-iwan/escape/main/docs/images/escape.png)

This is a library for C and C++ which provides functions for printing escape sequences, colored output, formatted colored output and moving the cursor around. Some, like `printc()` and `printfc()` are similar in use to `printf()`.

## Installation
The library has no external dependencies so simply compile by running:
```sh
make
```
And install by running (as root):
```sh
make install
```
This installs for both dynamic and static versions. If you wish to only compile one of them, first run:
```sh
make shared
```
or
```sh
make static
```
Then install normally.

By default the library is installed at `/usr/local/lib`, which might not be sourced by the linker.
In such case you can run (as root):
```sh
ldconfig /usr/local/lib
```

## Usage
To use in C simply add `#include <escape.h>` to your source code and link to the library. In gcc or clang compile with "-lescape" or "-l:libescape.a" to force static linking.
```c
#include <escape.h>

int main() {
    printf("$c1Hello, $c3world!\n");

    return 0;
}
```
```sh
gcc -o example example.c -lescape
```

![example](https://raw.githubusercontent.com/jan-iwan/escape/main/docs/images/simple_example.png)

Every available function is described in the header

Some examples can be found in `example/`:

![demo](https://raw.githubusercontent.com/jan-iwan/escape/main/docs/images/demo.png)

`demo.c`, present in `example/`.


There is support for C++ through the `esc` namespace, e.g `esc::printc()`.

An in-depth explanation on how to use the functions provided by the library is available in the header `escape.h`.

Not all escape sequences were implemented (yet).
