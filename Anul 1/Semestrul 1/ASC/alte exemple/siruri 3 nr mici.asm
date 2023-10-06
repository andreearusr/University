bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        s1 db 1,3,6,2,3,7
        s2 db 6,3,8,1,2,5
        l equ $-s1
        d times l db 0; 1,3,6,1,2,5

; our code starts here
segment code use32 class=code
    start:
        mov ECX,l
        mov ESI,0
        jecxz sfarsit
        
        repeta:
            mov AL,[s1+ESI]
            mov AH,[s2+ESI]
            cmp AL,AH
            ja sir2
            mov [d+ESI],AL
            jmp sir1
            
            sir2:
                mov [d+ESI],AH
            sir1:
                inc ESI
        loop repeta
        sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
