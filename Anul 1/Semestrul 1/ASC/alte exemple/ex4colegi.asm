bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; se da un sir de caract s. Construiti sirul d care sa cont toate caracterele cifre din sirul s
    s db '+','4','2','a','8','4','x','5'
    l equ $-s 
    d times l db 0

; our code starts here
segment code use32 class=code
    start:
        mov ECX,l
        mov EBX,0
        mov ESI,0
        
        Repet:
            mov AL,[s+ESI]
            cmp AL,'0';    se compara codul ASCII al lui AL cu codul ASCII al lui 0
            jb skip;       daca Al<0 se sare la skip
            cmp AL,'9'
            ja skip
            mov [d+ESI], AL
            
            inc EBX
            skip:
                inc ESI
        loop Repet
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
