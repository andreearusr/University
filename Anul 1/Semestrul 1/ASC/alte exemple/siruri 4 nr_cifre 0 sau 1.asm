bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        s dw -22,145,-48,127
        ls equ ($-s)/2
        d times ls db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un sir de cuvinte S. Sa se construiasca sirul de octeti d, a.i. d sa contina pentru fiecare pozitie
        ;s:
        ; - nr de biti 0, daca numarul este negativ
        ; - nr de biti 1, daca numarul este pozitiv
    
        mov ESI,s
        mov ECX,ls
        mov EDI,d 
        jecxz sfarsit
        cld 
        
        repeta:
            lodsw  
            cmp AX,0
            push ECX 
            js negativ 
            ; caz-pozitiv
                mov ECX,16
                clc
                cifre_caz1:
                    SHR AX,1
                    jnc skip1
                    inc byte[EDI]
                    skip1:
                loop cifre_caz1
            jmp sfarsit_parcurge
            
            negativ:
                mov ECX,16
                clc
                cifre_caz2:
                    SHR AX,1
                    jc skip2
                    inc byte[EDI]
                    skip2:
                loop cifre_caz2
            sfarsit_parcurge:
            pop ECX
            inc EDI
        loop repeta
        
        sfarsit:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
