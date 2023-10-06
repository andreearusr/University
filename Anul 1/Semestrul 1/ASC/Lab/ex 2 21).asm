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
    b dw -9
    c dd 12
    d dq -30

; our code starts here
segment code use32 class=code
    start:
        ; d-a + (b+a-c) ; interpretare cu semn
        
        mov EBX,dword[d]
        mov ECX,dword[d+4]; ECX:EBX = d
        mov AL,[a]
        cbw; AX=a 
        cwde; EAX=a 
        cdq; EDX:EAX=a 
        
        sub EBX,EAX
        sbb ECX,EDX; ECX:EBX=d-a 
        
        mov AL,[a]
        cbw; AX=a 
        mov BX,[b]
        add AX,BX; AX=b+a 
        cwde; EAX= b+a 
        mov EDX,[c]
        sub EAX,EDX; EAX=b+a-c 
        cdq; EDX:EAX= b+a-c 
        
        add EBX,EAX
        adc ECX,EDX; ECX:EDX= d-a+(b+a-c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
