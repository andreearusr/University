bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
extern printf, scanf 
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

import printf msvcrt.dll   
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    message1 db "a=",0
    message2 db "b=",0
    format db "%d",0
    rezultat dq 0

; our code starts here
segment code use32 class=code
    start:
    ; Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze: (a+b) * (a-b).
    ;Rezultatul inmultirii se va salva in memorie in variabila rezultat
    
        push dword message1
        call [printf]
        add esp, 4*1   ; eliberam parametrii de pe stiva
        
        push dword a
        push dword format 
        call [scanf] 
        add esp, 4*2 
        
        push dword message2
        call [printf]
        add esp, 4*1
        
        push dword b 
        push dword format 
        call [scanf]
        add esp, 4*2
        
        mov EAX,dword[a]
        mov EBX,dword[b]
        
        clc
        adc EAX,EBX
        mov ECX,EAX; ECX=a+b 
        
        mov EAX,0
        mov EAX,dword[a]
        
        clc
        sub EAX,EBX; EAX=a-b        
        imul ECX; EDX:EAX = (a+b)*(a-b)
        mov dword [rezultat],EAX
        mov dword [rezultat+4],EDX
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
