bits 32

global start
extern exit
import exit msvcrt.dll

segment data use32 class=data 
    s db 5,25,55,127
    len equ $-s 
    
    s2 times len db 0
    


segment code use32 class=code 
start:
    
    mov ECX,len
    jecxz final
    mov ESI,s
    mov EDI,s2
    cld 
    mov BL,0
    
    repeta:
        lodsb   ;AL<-primul octet
        push ecx 
        
        mov ECX,8
        repeta2:
            shl AL,1
            jc adauga
            jmp aici
            adauga:
                inc BL
            aici:
            
        loop repeta2
        
        mov AL,BL
        stosb
        mov BL,0
        pop ecx 
    loop repeta
    
    final:
    push dword 0
    call [exit]