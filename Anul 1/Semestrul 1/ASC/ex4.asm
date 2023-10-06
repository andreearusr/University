bits 32

global start
extern exit
import exit msvcrt.dll


segment data use32 class=data
    s dd 12345678h,1A2B3C4Dh,0FE98DC76h
    len equ ($-s)/4
    
    d times len db 0
    trei db 3

segment code use32 class=code 
start:
    mov ECX,len
    jecxz final
    mov ESI,s
    mov EDI,d
    cld 
    
    repeta:
        lodsw
        lodsb
        lodsb ;AL octetul bun
        mov DL,AL 
        
        mov AH,0  ;AX<- octetul bun 
        div byte[trei]  ;AL cat   AH rest
        cmp AH,0
        je gasit
        
        jmp aici
        gasit:
            mov AL,DL 
            stosb
        aici:
       
    loop repeta
    
    final:
    
    push dword 0
    call [exit]