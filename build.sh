#!/bin/bash

# Compile the source file into an object file
cc -I./include/electron_node/src -I./include/electron_node/deps/uv/include -I./include/electron_node/deps/uv/include/uv -c -o lib/shim.o src/shim.c

# Create static library from the object file
ar rcs lib/libshim.a lib/shim.o