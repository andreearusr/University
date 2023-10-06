bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    B db 01110101b
    A dw 1010011110000100b
    C db 0

; our code starts here
segment code use32 class=code
    start:
        ; ... sa se inlocuiasca bitii 0-3 ai octetului B
        ;       cu bitii 8-11 ai cuvantului A
       
       mov DL,0; in DL calculam rezultatul
       mov AL,[B]; AL=0111 0101b
       and AL, 11110000b; izolam bitii 4-7 ai lui B
       or DL,AL; DL=0111 0000b
       
       mov AX,[A]; AX=1010011110000100b
       and AX,0000111100000000b; izolam bitii 8-11 ai lui A
       mov CL,8
       ror AX,CL; rotim 8 pozitii spre dreapta, AX=0000000000000111b
       mov BL,AL; BL=0000 0111b
       or DL,BL; DL=0111 0111b
       mov [C],DL; C=01110111b
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
