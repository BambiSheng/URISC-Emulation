# URISC-Emulation
> HW of THUEEmap Lec5 

## Log
- `2023.4.6 v 0.1`
  - The first version.
  - Function`command::command(char *read, int myLine)` to be improved.
  - A more reliable error reporting system needed to provide more detailed error-messages.

## GUIDE

- todo

## EXAMPLE

- sample code

  ```assembly
  ;这个程序是用来计算a*b的值，并赋给变量c
  START: TEMP TEMP LOOP
  LOOP: ONE b END;循环判断
  RESTEMP: TEMP TEMP INVA
  INVA: a TEMP ADD
  ADD: TEMP c BACK;实现c+=a
  BACK: c TEMP LOOP;回到循环入口
  END:TEMP TEMP;略写第三个操作数,不影响结果
       
  ONE: WORD 1
  COUNT: WORD 0
  TEMP: WORD 0;初始化参数
  a: WORD 45
  b: WORD 9
  c: WORD 0
  ```

- operation result

  ![image-20230406021213143](https://s2.loli.net/2023/04/06/NoE6zgtUSAejpT3.png)
