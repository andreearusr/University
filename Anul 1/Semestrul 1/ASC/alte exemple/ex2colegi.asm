bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; se dau 2 siruri de octeti a si b. Construiti sirul r care cont elem lui b in ordine inversa
    ; si elementele lui a in ordine inversa
    ; a: 2,1,-3,0
    ; b: 4,5,7,6,2,1
    ; r: 1,2,6,7,5,4,0,-3,1,2
    a db 2,1,-3,0
    la equ $-a
    b db 4,5,7,6,2,1
    lb equ $-b
    r resb la+lb
    
; our code starts here
segment code use32 class=code
    start:
        mov ESI, b+lb-1
        mov EDI, r
        mov ECX, lb
        
        jecxz Final_muta_b
        
        Muta_b:
            mov AL,[ESI]
            mov [EDI],AL
            dec ESI
            inc EDI
        loop Muta_b
        
        Final_muta_b:
            mov ESI, a+la-1
            mov ECX, la
        
        jecxz Final_muta_a
        Muta_a:
            mov AL,[ESI]
            mov [EDI],AL
            dec ESI
            inc EDI
        loop Muta_a
        
        Final_muta_a:
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
