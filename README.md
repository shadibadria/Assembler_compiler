# assembler_compiler

## A program that compile assembly code to opcode.

## The pogram does 2 passes and parse the code then  creates output files.
- First pass:
Create symbol table and some of the instruction table.

- Second pass: complete the instruction table and
Create output files.

- Output files:
 1) Filename.ob - object file contain all the opcode in hex.
 2) Filename.ext - extern file contains all extern labels
 3) Filename.ent - entry file contains all entry labels.

## how to use ?

Compile the program:
```sh
make
```
Execute the program:
```sh
./assembler myasmfile.as
```

