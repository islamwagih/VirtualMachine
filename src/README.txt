You can simply run the program by running "make build" in your terminal.
The virtual machine has 4 32-bit registers A, B, C, D and consists of the following instruction set.
=============================================================================================================
Instruction             |   Description
-------------------------------------------------------------------------------------------------------------
PSH (X)                 |  push a 32-bit integer to the stack.
POP                     |  pop the top of the stack.
ADD                     |  pop the top two values from the stack and push the result of their addition.
SUB                     |  pop the top two values from the stack and push the result of their subtraction.
MUL                     |  pop the top two values from the stack and push the result of their multiplication.
DIV                     |  pop the top two values from the stack and push the result of their division.
DIS  (REG)              |  display the value of register.
DTOP                    |  display the top of the stack.
SET  (REG) (X)          |  stores the value (X) in the register (REG).
MOV  (SRC_REG) (DST_REG)|  move the value of (SRC_REG) to (DST_REG).
LOAD (REG)              |  push the value of (REG) to top of the stack.
TRN  (REG)              |  set the value of top of the stack to (REG).
HLT                     |  halt command to stop the execution.
=============================================================================================================

 
