# URISC-Emulation
> HW of THUEEmap Lec5 

## Log
- `2023.4.6 v 0.1`
  - The first version.
  - Function`command::command(char *read, int myLine)` to be improved.
  - A more reliable error reporting system needed to provide more detailed error-messages.
  - Hidden bugs to be found and fixed.

## GUIDE(Written by ChatGPT)

- Introduction To URISC

  [One-instruction set computer - Wikipedia](https://en.wikipedia.org/wiki/One_instruction_set_computer)

- Brief Introduction To the Program

  This program mainly implements a brief simulation of the URISC computer. The program will read the URISC code sourcefile and simulate its operation.

  The program will output the initial values of each variable and output the values of each variable again after the operation is completed.

- URISC Code Specification

  - General instruction format: `L: a,b,c;notes`
    - `L`,`a`,`b`,`c` must be a combination of uppercase and lowercase letters and cannot contain other characters
    - `:` cannot be omitted
    - `,` can be replaced by a space
    - Comments can be added after `:`
    - `c` can be omitted, in which case the next instruction will always be executed in sequence
  - End instruction format: `END: a,b,c;notes`
    - Must be included, the program ends here, and no general instructions can appear after this line
    - Other instruction names and variable names cannot be `END`
  - Assignment pseudo-instruction format: `P:WORD num`
    - `P` is the variable name and `num` is the constant value to be assigned. Here `num` is limited to the `int` data type
    - The assignment pseudo-instruction can only appear after the end instruction
    - `WORD` and `num` can also be separated by `,`
  - In program writing, all instructions are abstracted as `command` objects. Whether it is a general instruction, an end instruction or an assignment pseudo-instruction variable, it has an `int` value for calculation. If it has not been assigned by a pseudo-instruction, this value defaults to 0.

## EXAMPLE

- sample code

  ```assembly
  ;This program computes a*b, and give it to c
  START: TEMP TEMP LOOP
  LOOP: ONE b END;Loop judge
  RESTEMP: TEMP TEMP INVA
  INVA: a TEMP ADD
  ADD: TEMP c BACK;c+=a
  BACK: c TEMP LOOP;Back to LOOP
  END:TEMP TEMP
       
  ONE: WORD 1
  COUNT: WORD 0
  TEMP: WORD 0
  a: WORD 45
  b: WORD 9
  c: WORD 0
  ```

- operation result

  ![image-20230406021213143](https://s2.loli.net/2023/04/06/NoE6zgtUSAejpT3.png)
