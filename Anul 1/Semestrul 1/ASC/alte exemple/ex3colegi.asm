bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    s1 db '+','4','2','a','8','4','x'
    l1 equ $-s1
    s2 db 'a','4','5',
    l2 equ $-s2
    d times l1+l2 db 0 ; '+','a','x','5','4','a'

; our code starts here
segment code use32 class=code
    start:
        mov ECX, l1
        mov ESI, 0
        mov EDI, d
        jecxz Sfarsit
        Repeta:
            mov AL,[s1+ESI]
            mov [EDI],AL
            inc EDI
            add ESI,3
        cmp ESI,ECX
        jb Repeta
        
        mov ECX, l2
        jecxz Sfarsit
        Repeta_2:
            mov EDX,ECX
            dec EDX
            mov AL,[s2+EDX]
            mov [EDI],AL
            inc EDI
        loop Repeta_2
        
        Sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
