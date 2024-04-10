Performance Test 
============

This performance test measures the execution times within popular languages including:

	* C++
	* C#
	* GoLang
	* Python
	* ASM
	* WASM

Notes on x86 Assembly Language
------------

**General**

The 32-bit subset of the x86 instruction set is a fairly clean
assembly language.  It's difficult to tell this from the various Intel
and Microsoft documentation, because the x86 is backwards compatible
with 20-year old processors and operating systems, and _all_ of that
is described. The note describes the x86 instruction set
that we will need and basic information about the Microsoft Assembler
(MASM), which we will use to assemble the generated code.


**MASM Assembly Language Code**

For our purposes, every x86 assembly language file should have this structure.

~~~
  .386
  .model flat, c
  public D_main
  extern get:near, put:near
  .code

  <your generated code goes here>

  end
~~~


The .386 directive at the beginning specifies that the program uses
the 32-bit instruction and register set introduced in the 80386, and
the .model directive specifies that code should use a 32-bit
non-segmented (i.e., Win32, not DOS) memory address space.

The public and extern directives specify routines (labels) defined in
this assembly language file and available to callers in other files 
(public), and labels defined in other files and referenced in this 
assembly language file (extern).  The ":near" option specifies that 
we're using a simple flat memory model, i.e., not calling functions in 
other memory segments.  (The default is "far", which is left over from 
DOS days when programs had to be chopped up into multiple segments, 
each no larger than 64K.  The 32-bit flat memory model includes all of 
the program's code in one large segment, and jumps in that segment 
are considered "near", even if they are a gigabyte away.)


**Statement Format***

An assembly language statement has the following format

~~~
   optLabel:  opcode  operands   ; comment
~~~

*optLabel:* is an optional label.  opcode and operands are assembly
language instructions.  A semicolon indicates the beginning of a
comment, which continues to the end of the source line.

The layout of an Assembly Language program is fairly free-form.  A 
label may appear on a line by itself, as may a comment.  An opcode and 
its operands should appear on one line.

~~~
   aLabel:
        mov  eax,7
                      ; meaningful comment
~~~

There are no particular formatting requirements.  For readability, 
it's best to start labels in the first column of a source file and 
indent opcodes and operands and line them up in columns if you can 
(but don't obsess over this).

*Opcode names may not be used as labels.*


**x86 Memory Model**

Memory is composed of bytes, each of which has 8 bits.  A 32-bit
integer is stored in 4 consecutive bytes, and it's best if the address
of the integer is a multiple of 4.  This alignment restriction is the
default setup and you shouldn't have to worry about it.  Just be sure
not to alter it by, for example, adding or subtracting a value from
the stack pointer that is not a multiple of 4.  The address of an
integer is the address of the low-order byte, i.e., an integer at
location 1000 consists of bytes 1000-1003; where 1000 contains the
low-order bits and 1003 contains the high-order bits.  Again, you
probably don't have to worry about this.


**x86 Processor Registers and Fetch-Execute Cycle**

There are 8 registers that can be specified in assembly-language
instructions: eax, ebx, ecx, edx, esi, edi, ebp, and esp.  Register
esp points to the top word currently allocated in use on the stack
(which grows down).  It is unwise to use esp for anything else. 
Register ebp is typically used as a pointer into the stack frame of
the currently executing function.

For our project, register eax will be used as the primary arithmetic
register and operations will normally be done there.  Register ecx
will often be used in binary arithmetic operations to hold the second
operand.  In a real compiler, it's important to optimize the use of
the registers by using all of them as effectively as possible, but 
that's beyond the scope of our project.

There are two registers that are implicitly used in x86 programs, but
cannot be referenced explicitly in an assembly language program. 
These are eip, the "instruction pointer" or "program counter"; and
eflags, which contains bits indicating the result of arithmetic and
compare instructions.  (More details about eflags in the description 
of conditional jump instructions, below.)

The basic operation of the processor is to repeatedly fetch and 
execute instructions.

~~~
   while (running) {
      fetch instruction beginning at address in eip;
      eip <- eip + length of instruction;
      execute fetched instruction;
   }
~~~

Execution continues sequentially unless execution of an instruction
causes a jump, which is done by altering eip (which is how conditional
and unconditional jumps, call, and ret work).


**Assembly Language Instructions and Operands**

The format of a typical data manipulation instruction is

~~~
   opcode  dst,src
~~~

One of the operands, dst or src, may be a reference to a memory
location or an integer constant; the other, or both operand(s), should
be a register (in our case, usually eax).

Since all of the variables in D programs are allocated in stack
frames, they are referenced by an address relative to ebp.  So the
following operand formats should be enough (using mov as an example):

~~~
   mov  eax,17        ; store 17 in eax
   mov  eax,ecx       ; copy contents of ecx into eax
   mov  eax,[ebp-12]  ; copy contents of memory location with address 
                      ;   ebp-12 into eax
   mov  [ebp+8],eax   ; copy contents of eax into memory location with
                      ;   address ebp+8
~~~

**Basic Data Manipulation Instructions**

~~~
   mov  dst,src       ; dst <- src
   add  dst,src       ; dst <- dst+src
   sub  dst,src       ; dst <- dst-src
   imul dst,src       ; dst <- dst*src (32-bit product; dst must be
                      ;                 a register)
   push src           ; esp <- esp-4; memory[esp] <- src
                      ;    (i.e., push src onto stack)
   pop  dst           ; dst <- memory[esp]; esp <- esp+4
                      ;    (i.e., pop top of stack into dst
                      ;     and remove it form the stack)
~~~

**Control Flow**

The only control flow available in assembly language is conditional
and unconditional branching, or jumps, and call and ret instructions,
which are used to implement functions.


**Unconditional Jump**

~~~
   jmp  label         ; jump to instruction prefixed with label
~~~

This instruction stores the address of label in the eip register, 
which causes the next instruction to be fetched from that location.  
This mechanism is used by all of the branching instructions and won't 
be mentioned further.

Note: For both unconditional and conditional branches, the MASM
Assembly Language label need not be on the same source line as the
target instruction.  For example, if the code contains

~~~
  label1:
  ; a comment
  label2:  ; more commentary
  label3:  push eax
~~~

a jump to either label1, label2, of label3 will cause execution to 
branch to the push instruction.

**Conditional Jumps**

All arithmetic instructions set flag bits in the eflags register, as 
does the cmp (compare) instruction.

While we probably won't used them for this, the following instructions
can be used after an arithmetic instruction (add, sub, but *not* imul)
to conditionally branch depending on the result value stored in dst.

~~~
  jz   label    ; jump to label if result == 0
  jnz  label    ; jump to label if result != 0
  jg   label    ; jump to label if result > 0
  jng  label    ; jump to label if result <= 0
  jge  label    ; jump to label if result >= 0
  jnge label    ; jump to label if result < 0
  jl   label    ; jump to label if result < 0
  jnl  label    ; jump to label if result >= 0
  jle  label    ; jump to label if result <= 0
  jnle label    ; jump to label if result > 0
~~~

What we will want to use are conditional jumps following a cmp
(compare) instruction.  The idea is to use cmp to set bits in eflags,
then execute an appropriate jump that branches or not depending on the
flags set by the cmp instruction.  Again, we don't reference eflags
directly in the assembly-language code; it is implicit in the
definitions of cmp and the conditional jump instructions.

A compare and jump works like this

~~~
   cmp  op1,op2      ; compare op1 to op2 and set bits in eflags
   jcc  label        ; jmp to label if the condition cc matches
                     ; the current bit values in eflags
~~~

The various jcc instructions are defined as follows

~~~
  je   label    ; jump to label if op1 == op2
  jne  label    ; jump to label if op1 != op2
  jg   label    ; jump to label if op1 > op2
  jng  label    ; jump to label if op1 <= op2
  jge  label    ; jump to label if op1 >= op2
  jnge label    ; jump to label if op1 < op2
  jl   label    ; jump to label if op1 < op2
  jnl  label    ; jump to label if op1 >= op2
  jle  label    ; jump to label if op1 <= op2
  jnle label    ; jump to label if op1 > op2
~~~

**Function Call and Return**

The call and ret instructions provide the basic mechanism for
transferring control for a function call.  A call pushes the
instruction pointer (which contains the address of the instruction
following the call), then jumps to the function.  A ret pops the value
on the top of the stack into eip, which means execution continues at
the popped address.

~~~
  call label    ; push current instruction pointer and jump to label
                ; i.e., esp <- esp-4; memory[esp] <- eip;
                ;       eip <- memory address of label

  ret           ; pop top of stack into eip (jumping to that location)
                ; i.e., eip <- memory[esp]; esp <- esp+4
~~~
   
**Win32 C Calling Conventions**

The call and ret instructions provide the basic mechanism to jump to a
function and get back, but additional conventions are needed to
specify how registers are saved and restored, how arguments are
transmitted, and how a function result is transferred back to the
caller.

**Caller**

To call a function named, for example, f, the function arguments are
pushed on the stack, then a call instruction is executed to branch to
the label on the first instruction of the function.  The instruction
following a call should adjust esp to pop the arguments off the stack
(the called function does not pop the arguments).  The scheme is

~~~
   push arguments
   call f
   add  esp,"size of arguments in bytes"
~~~

For a D program, the quantity added to esp after the function returns
should be 4*(# of arguments), since each argument is a 32-bit int 
occupying 4 bytes.

Note:  The standard Win32 calling sequence requires pushing the 
function arguments from right to left.  In a 1-pass recursive descent 
compiler, it's more natural to push them from left to right as they 
are evaluated.  Feel free to do that to simplify your program.

**Callee**

A function needs to start with code to save some of the registers if
it is going to use them, set up ebp to point to the stack frame, and
allocate space for local variables by decreasing the stack pointer
appropriately.

Here is a template for the code compiled for a function named f

~~~
   f: push ebp         ; save ebp on stack
      mov  ebp,esp     ; set frame pointer to current stack location
      sub  esp,"size of locals in bytes"  ; allocate local variables

      <code generated for the body of function f goes here>

      mov  esp,ebp     ; restore esp to value before local variables
                       ; were allocated (i.e., pop locals)
      pop  ebp         ; restore ebp to value saved at beginning of f
      ret              ; return to caller (instruction following call)
~~~

When the function returns, registers esp, ebp, ebx, esi, and edi should
have their original values.  The above code properly saves and 
restores esp and ebp.  You shouldn't need to use any of the other 
registers mentioned, but if you do, you need to save and restore them 
(with a push at the beginning of the function and a pop at the end).

**Function Result**

For functions that return an int value (which all D functions do), 
the value should be in eax at the time the function returns.

**Example**

Here is an example from lecture.  It is roughly like the code your 
compiler might generate, although don't be alarmed if your code looks 
different.  Source code appears as comments

**Caller:**

~~~
   ; n = sumOf(17,42);
   push 17            ; push arguments
   push 42
   call sumOf         ; jump to label sumOf and push return address
   add  esp,8         ; pop arguments after return
   mov  [ebp+?],eax   ; store function result in n (where ? is the
                      ;   offset of n in the caller's stack frame)

Function sumOf

 ; int sumOf(int x, int y) {
 ;    int a, b;
 sumOf:                 ; function label
     push ebp           ; function prologue (see above)
     mov  ebp,esp
     sub  esp,8
 ; a = y;
     mov  eax,[ebp+8]
     mov  [ebp-4],eax
 ; b = x;
     mov  eax,[ebp+12]
     mov  [ebp-8],eax
 ; return a+b
     mov  eax,[ebp-4]   ; a+b (value in eax)
     push eax
     mov  eax,[ebp-8]
     pop  ecx
     add  eax,ecx
     mov  esp,ebp       ; function return epilogue
     pop  esp
     ret
~~~