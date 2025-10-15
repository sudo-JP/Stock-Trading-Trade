#!/bin/bash

rm -rf build/
cmake -B build -G Ninja
cmake --build build

# Create symlink for Neovim LSP
ln -sf build/compile_commands.json ./
