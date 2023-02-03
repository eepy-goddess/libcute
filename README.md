# Libcute
Libcute is a library that has utilities for logging, user input, and argument parsing. Its convenient utilities allow programmers
to free up time that is usually spent on making logging systems, argument parsing and the like for their programs. The goal of this library is to 
have a cute and readable code base as well as having rust-level safe code and providing cute and convenient logging.

## Dependencies
no dependencies needed :)

## Build Instructions
1. Clone the repository
2. Open your terminal, cd into the cloned libcute directory
3. execute `make`

## Install Instructions
There is no installation rule in the makefile yet, but if you want to install this very incomplete library, copy the 
compiled library file(libcute.a if compiled statically, libcute.so if compiled dynamically) to /usr/lib, and if you want the headers, 
copy all files with the .h extention into /usr/include/libcute

## Documentation
Dodumentation is also incomplete, but compress libcute.3 with gzip, then copy the compressed file into /usr/share/man/man3/
