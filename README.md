# Advent of Code 2023

This is a yearly challenge many people take part in. You can do so too, [here](https://adventofcode.com/2023).

## How I'm doing it

My challenge was to write all of my solutions in pure C99 without anything but libc to support me. Additionally,
all tools are being written by hand as they become necessary. This so far includes a Rust-like set of string
utilities such as run length encoded string slices and heap allocated mutable strings. I've also prototyped some
simple structures for line- and whitespace-based splitting and iteration.

I'm compiling with GNU C, specifically GCC 13.2.0 (MSYS2 edition). A Makefile is provided.

