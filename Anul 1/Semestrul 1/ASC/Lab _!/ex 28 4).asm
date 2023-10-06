bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 5
    b db 77
    c db 8
    d dw 130

; our code starts here
segment code use32 class=code
    start:;.. d+10*a-b*c
        mov AL,10; AL=10
        mul byte[a]; AX=AL*a=10*a
        mov BX,AX; BX=AX
        
        mov AL,[b]; AL=b
        mul byte[c]; AX=AL*c=b*c
        
        sub BX,AX; BX=BX-AX=10*a-b*c
        add BX,word [d]; BX=BX+d= 10*a-b*c+d 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
