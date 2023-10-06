bits 32
global start
extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data 
    sir db "256"
    len equ $-sir 
    zece db 10

    format db "%d",0
    suma dd 0
segment code use32 class=code
start:
        
    mov ESI,sir
    cld 
    mov ECX,len 
    
    bucla:
    
        mov EAX,0
        lodsb   ;AL<-2
        sub AL,'0'
        
        mov DL,AL
        
        mov EBX,ECX 
        
        repeta:
            mul byte[zece]
            
            dec ebx
            cmp ebx,0
        jnz repeta        
        
        add dword[suma],EAX 
           
    loop bucla
    
    push dword [suma]
    push dword format
    call [printf]
    add esp,4*2
    

    push dword 0
    call [exit]