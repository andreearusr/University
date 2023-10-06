bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...se dau 2 siruri de octeti a si b. sa se constr sirul r care sa cont 
    ;  elem lui b in ordine inversa
    
    a db '2133426'
    la equ $-a
    b db '457621'
    lb equ $-b 
    r times 2 db 0

; our code starts here
segment code use32 class=code
    start:
        mov ECX, lb 
        mov ESI,0
        mov EDI, lb-1
        mov AX,0
        jecxz Sfarsit
        
        Repeta:
            mov AL,[b+EDI]
            mov [r+ESI],AL
            inc ESI
            dec EDI
        loop Repeta
        Sfarsit:
        
        mov ECX,la
        mov ESI,0
        mov EDI,0
        mov AX,0
        jecxz Sfarsit1
        Repeta1:
            mov AL,[a+ESI]
            test AL,1;  sau and AL,1
            jpo sari
            mov [r+lb+EDI],AL;  muta in AL elem pare a lui a
            inc EDI
            sari:
                inc ESI
        loop Repeta1
        Sfarsit1:
        mov BX,[r]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
