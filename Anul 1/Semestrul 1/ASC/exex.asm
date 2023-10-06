bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
 ;       mov AH,0
 ;       mov AL,-5
        
 ;       mov BX,10
 ;       imul BX
;        mul BX
 ;       mov CL,-100
;        idiv CL
;        imul CL
;        add AX,10
;        div CL
        
 ;       mov AH,0
 ;       mov AL,-5
        
 ;       mov BX,10
 ;       imul BX
;        mul BX
 ;       mov CX,-100
 ;       idiv CX
;        imul CX
;        add AX,10
 ;       div CX
        
 ;       mov AX,-5
 ;       mov BX,10
;        imul BX
        
        mov AL,251
        mov CL,255
        mov BL,100
        imul BL
 ;       div CL
        idiv CX
 ;       idiv CL
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
