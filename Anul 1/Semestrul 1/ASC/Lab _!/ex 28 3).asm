bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 7
    b dw 30
    c dw 55
    d dw 80

; our code starts here
segment code use32 class=code
    start:;... (d-c) + (b+b-c-a)+d
        mov AX,[d]; AX=d
        sub AX,[c]; AX=d-c
        
        mov BX,[b]; BX=b
        add BX,[b]; BX=b+b
        sub BX,[c]; BX= b+b-c
        sub BX,[a]; BX=b+b-c-a
        
        add AX,BX; AX=AX+BX=d-c+b+b-c-a
        add AX,[d]; AX=AX+d=d-c+b+b-c-a+d 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
