bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        s db 1,3,-2,-5,3,-8,5,0
        l equ $-s 
        d1 times l db 0
        d2 times l db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un sir de octeti S. Sa se construiasca un sir D1 care sa cont toate numerele pozitive
        ; si un sir D2 care sa contina toate numerele negative din S
        
        mov ECX,l 
        mov ESI,0
        mov EDI,0
        jecxz sfarsit1
        
        repeta1:
            mov AL,[s+ESI]
            cmp AL,0
            js notpozitiv
            mov [d1+EDI],AL
            inc EDI
            notpozitiv:
                inc ESI 
        loop repeta1
        
        sfarsit1:
        mov ECX,l
        mov ESI,0
        mov EDI,0
        jecxz sfarsit2
        
        repeta2:
            mov AL,[s+ESI]
            cmp AL,0
            jns notnegativ
            mov [d2+EDI],AL
            inc EDI
            notnegativ:
                inc ESI
        loop repeta2
        
        sfarsit2:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
