# assembler_compiler

## A program that compile assembly code to opcode.

## The pogram does 2 passes and parse the code then  creates output files.
- First pass:
Create symbol table and some of the instruction table.

- Second pass: complete the instruction table and
Create output files.

-Output files:
Filename.ob - object file contain all the opcode in hex.
Filename.ext - extern file contains all extern labels
Filename.ent - entry file contains all entry labels.

## how to use ?

Compile the program:
```sh
make
```
Execute the program:
```sh
./assembler myasmfile.as
```
 ## this program have tests in it.
