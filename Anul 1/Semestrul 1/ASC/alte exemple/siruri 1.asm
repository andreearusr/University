bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        s1 db 'abcdef'
        l_s1 equ $-s1
        s2 db '12345'
        l_s2 equ $-s2
        d resb (l_s1+l_s2)/2

; our code starts here
segment code use32 class=code
    start:
        ; ...Se dau doua siruri de caractere S1 si S2, Sa se construiasca sirul D prin concatenarea elem de pe 
        ; pozitiile impare din S2 cu elem de pe pozitiile pare din S1
        
        mov EDI,0
        mov ESI,0
        for_s2:
            mov AL,[s2+ESI]
            mov [d+EDI],AL
            inc EDI
            add ESI,2
            cmp ESI, l_s2
        jbe for_s2
        
        mov ESI,1
        for_s1:
            mov AL,[s1+ESI]
            mov [d+EDI],AL
            inc EDI 
            add ESI,2
            cmp ESI,l_s1
        jbe for_s1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
