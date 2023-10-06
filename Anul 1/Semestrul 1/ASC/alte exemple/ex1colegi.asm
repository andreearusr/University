bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1,3,6,2,3,2
    t db 6,3,8,1,2,5
    l equ $-t
    d times l db 0

; our code starts here
segment code use32 class=code
    start:
    ;... (un nou sir ce are ca si elemente suma cifrelor pozitiilor aferente ale celor 2 siruri)
        mov ECX, l
        mov ESI, 0
        
        jecxz Sfarsit
        Repeta:
            mov AL,[s+ESI]
            add AL,[t+ESI]
            mov [d+ESI],AL
            inc ESI
        loop Repeta
        Sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
