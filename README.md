# Reconn

## What ?
  A stack-based language to evaluate usefulness of stack-based programming languages for metaprogramming, code generation, and domain specific languages.

## Why ?
  I was reading the code for Jonesforth by Richard W.M. Jones and the book "Threaded Interpretive Languages - Their Design and Implementation" by R.G. Loelinger and realized that stack-based languages are ridiculously easy to implement. I played with the idea of writing some kind of meta-assembler to generate assembly code for different architectures before that, but realized that such a taks would easily explode in scope as soon as you consider adding macros and other features. While reading those documents i realized that the FORTH family, or Threaded Interpretive Languages, could be a great fit for what i wanted to acheive with my meta-assembler concept and decided to write a language to test my hypothesis.

  The only issue i saw was that most of the FORTH/TIL languages i found relied on the beauty of assembly code to provide a way to elegantly compile words as they are entered. Given that i wanted to prototype my language in a higher level language i decided to mostly take the concepts i gathered from reading about FORTH and simmilar languages and integrate them into a "new" design. This abomination also draws some inspiration from languages such as Lisp, BASIC and Factor.

## Goals

  - Be easy to develop with minimal tools
  - Be easy to write on line editors such as "ed"
  - Be reasonably easy on the eyes, trying to use as little punctuation or special characters in the syntax as reasonable
  - Be a testbed to evaluate stack-based languages for certain use cases
  - Attempt to make the language usable for writing games and graphical applications
  - Attempt to use the language to generate code for other languages/formats (like: ASM, C, XML, SVG, ABC, MIDI, BMP and WAV)

## Why that name ?
  I was unable to come up with a reasonable name and chose "Reconn" as a WIP name and it stuck (for now)

  It was chosen as a combination of the word "Reconnect" (because i want to use it to reconnect to a low-level of programming and file formats that are hard or annoying to write by hand) and "Recon" (because i want to use it to survey and evaluate stack-based languages)
