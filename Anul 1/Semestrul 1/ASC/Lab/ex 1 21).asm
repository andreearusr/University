bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 4
    b dw 10
    c dd 15
    d dq 45

; our code starts here
segment code use32 class=code
    start:
        ;(c-a) + (b-d) + d ; interpretare fara semn 
        
        mov AL,[a]; AL=a 
        mov AH,0; AX=a 
        mov BX,AX; BX=AX 
        mov EAX,0
        mov AX,BX; AX=BX 
        push word 0
        push AX
        pop EAX; EAX=a 
        mov EBX,[c]; EBX=c 
        sub EBX,EAX; EBX=c-a
        mov ECX,0; ECX:EBX= c-a
        
        mov EAX,[b]
        mov EDX,0; EDX:EAX=b 
        sub EAX, dword[d]
        sbb EDX, dword[d+4]; EDX:EAX= b-d 
        
        add EAX,EBX
        adc EDX,ECX; EDX:EAX= (c-a)+(b-d)
        
        add EAX, dword[d]
        adc EDX, dword[d+4]; EDX:EAX= (c-a)+(b-d)+d
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
