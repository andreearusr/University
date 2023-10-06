bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 7
    b db 12
    c db 62
    d db 41
    
    e dw 5
    f dw 110
    g dw 1
    h dw 30

; our code starts here
segment code use32 class=code
    start:;...(e+g-h)/3+ b*c
        mov EAX,[e]; EAX=e 
        add EAX,[g]; EAX=e+g 
        sub EAX,[h]; EAX=e+g-h 
        push EAX
        pop AX
        pop DX
        
        mov BX,3; BX=3
        div BX; AX=DX:AX/BX DX=DX:AX%BX
        mov BX,AX;BX=AX 
        
        mov AH,[c]; AH=c 
        mov AL,[b];AL=b 
        mul AH; AX=AL*AH=b*c
        
        add BX,AX; BX=BX+AX=(e+g-h)/3+b*c
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
