bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 8
    b dw 23
    e dd 17
    x dq 63

; our code starts here
segment code use32 class=code
    start:
        ; (a*a/b + b*b)/(2+b)+ e - x ; interpretare fara semn 
        
        mov AL,[a]
        mul byte[a]; AX=a*a 
        mov DX,0; DX:AX=a*a 
        div word[b]; AX=a*a/b, DX=a*a%b 
        mov BX,AX; BX=a*a/b 
        mov CX,0; CX:BX=a*a/b 
        
        mov AX,[b]
        mul word[b]; DX:AX=b*b 
        add AX,BX
        adc DX,CX ; DX:AX= a*a/b+b*b 
        
        mov BX,[b]
        add BX,2; BX=b+2
        div BX; AX=(a*a/b+b*b)/(2+b), DX=(a*a/b+b*b)%(2+b)
        mov CX,AX
        mov EAX,0
        mov AX,CX 
        push word 0
        push AX
        pop EAX; EAX=(a*a/b+b*b)/(2+b)
        
        mov EBX,[e]
        add EAX,EBX; EAX= (a*a/b+b*b)/(2+b)+e
        mov EDX,0; EDX:EAX = (a*a/b+b*b)/(2+b)+e 
        
        sub EAX, dword[e]
        sbb EDX, dword[e+4]; EDX:EAX= (a*a/b+b*b)/(2+b)+e-x
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
