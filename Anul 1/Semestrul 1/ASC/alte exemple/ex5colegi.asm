bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ... dandu-se 4 octeti, sa se obt in AX suma numerelor intregi repr de bitii 4-6 ai celor 4 octeti
    a db 00101010b
    b db 11100101b
    c db 00000010b
    d db 10100101b

; our code starts here
segment code use32 class=code
    start:
        xor AX,AX
        or AL,[a]
        and AL,01110000b
        shr AL,4
        
        mov ECX,3
        mov ESI,0
        Repet:
            xor BX,BX
            or BL, byte[b+ESI]
            and BL, 01110000b
            shr BL,4
            add AL,BL
            adc AH,0
            inc ESI
        loop Repet
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
