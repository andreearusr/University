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
        b db -15
        c dw 1256
        e dd 34567
        x dq -456
        

; our code starts here
segment code use32 class=code
    start:
        ; (100+a+b*c)/(a-100)+e+x/a  CU SEMN 
        ; b*c => D    b->W
        mov AL,[b]
        cbw
        imul word[c]     ;DX:AX=b*c
        
        ;(100+a+b*c)
        add AX,100       ;AX=100+low[b*c]
        adc DX,0         ;DX=high[b*c]+CF
        mov BX,AX        ;DX:BX=100+b*c
        
        mov AL,[a]
        cbw 
        add BX,AX        ;AX=low[100+b*c]+a
        adc DX,0         ;DX=high[100+b*c]+CF
        
        ;(a-100)
        sub AX,100
        mov CX,AX        ;CX=a-100
        
        ;(100+a+b*c)/(a-100)
        mov AX,BX        ;DX:AX=100+a+b*c
        idiv CX         ;AX=(100+a+b*c)/(a-100)
        mov BX,AX        ;BX=(100+a+b*c)/(a-100)
        
        
        ;x/a
        ;a->doubleword
        mov AL,[a]
        cbw
        cwde
        mov ECX,EAX      ;ECX=a
        
        ;x-> EDX:EAX
        mov EAX,dword[x]
        mov EDX,dword[x+4]
        
        idiv ECX     ;EAX=x/a   EDX=rest
        mov ECX,EAX  ;ECX=x/a
        
        ;(100+a+b*c)/(a-100) ->EAX
        mov AX,BX
        cwde 
        
        ;(100+a+b*c)/(a-100)+e 
        add EAX,[e]
        
        ;(100+a+b*c)/(a-100)+e+x/a
        add EAX,ECX 
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
