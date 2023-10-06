bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        a dd 34 
        b db 6
        c db 8
        d db 7
        x dq 103

; our code starts here
segment code use32 class=code
    start:
        ; a=(7+x)/(b*b-c/d+2)  int fara semn
        
        add qword[x],7    ;x=x+7
        
        mov EAX,[x]
        mov EDX,[x+4]
        mov ECX,EAX     ;ECX=x+7=6Eh
        
        mov AL,[b]    
        mul AL     ;AX=b*b=24h
        mov BX,AX  ;BX=b*b=24h
        
        mov AH,0
        mov AL,[c]    ;AX=c
        div byte[d]   ;AL=1h cat  AH=1h rest
        
        mov AH,0
        sub BX,AX   ;BX=b*b-c/d=23h
        add BX,2    ;BX=b*b-c/d+2=25h
         
        mov EAX,ECX  ;EAX=x+7=6Eh
        mov ECX,0
        mov CX,BX
        div ECX 
        sub dword[a],EAX
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
